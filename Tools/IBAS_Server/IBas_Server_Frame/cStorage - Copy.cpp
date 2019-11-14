#include "cstorage.h"
#pragma warning (disable: 4311 4312 4267)
#include "BASIntrf_s.h"
#pragma warning (default: 4311 4312 4267)

#define _CLOG9
#include "CBS_Utilities\CBS_Clog.h"

#include <sstream>

#include "Telcom_In_TagList.h"
#include <algorithm>
#include <functional>

cStorage::cStorage(void)
{
  Telcom_In_TagList tagList;
  for   ( Telcom_In_TagList::const_iterator it = tagList.begin();
          it != tagList.end();
          ++it)
  {
    if  (it->second == std::string ("number"))
    {
      store (it->first, (float) 0.0, false);
    }
    else if (it->second == std::string ("string"))
    {
      store (it->first, "", false);
    }
    else
    {
      store (it->first, 0l, false);
    }
  }
}

cStorage::~cStorage(void)
{
}

// static data member
cStorage *cStorage::thisOne;

// get instance
cStorage *cStorage::instance()
{
  if   ( ! thisOne )
  {
    thisOne = new cStorage;
  }
  return thisOne;
}


void cStorage::store  (const std::string &tag, long  lVal, bool mayThrow, bool isForced)
{
  std::string key = tag;

  vMap::iterator it = find(key);

  std::string sTag = "";
  for( it = begin() ; it != end() ; it++)
  {
    std::stringstream stsrTag;

    stsrTag << it->first;

    sTag = stsrTag.str();

    if ( sTag == key)
      break;
  }

  it = find(key);

  if   (it != end() )
  {
    if   ( ! (it->second.isLocked) || isForced )    // do it only if its not locked or if power user is at work...
    {
      if (it->second.discr == tLong )
      {
        it->second.val.l = lVal;
        if   (it->second.isLocked) 
        {
          // Locked Value must have been overwritten by power user via isForced=true
          //
          CLOG2 (<< "Value of  <" << tag << ">: Overwritten by priviledged user, value now " << it->second.val.l << std::endl);
        }
      }
      else  if (mayThrow)
      {
        // invalid to store invalid Type! (user wants to store long but definition (by Discr!) suggest some other type)
        // If some program experiences this exception, the error is THERE! Type mismatch!
        CLOG2 (<< "Tag <" << tag << ">: Invalid attempt to store long value." << std::endl);
        throw IBAS::EXC_IncorrectTagType();     
      }
    }
  }
  else if (!mayThrow)
  {
    Value v;
    v.isLocked = false;       // Start Not Locked
    v.discr = tLong;
    v.val.l = lVal;
    (*this)[key] = v;
    CLOG5(<< "Added new Tag: " << tag << " as long" << std::endl);
  }
  else
  {
    // Normally, throw an exception if Tag has not been found.
    CLOG2 (<< "Tag <" << tag << "> not known." << std::endl);
    throw IBAS::EXC_TagNotFound();
  }
}
void cStorage::store  (const std::string &tag, float fVal, bool mayThrow, bool isForced)
{
  std::string key = tag;

  vMap::iterator it = find(key);
  if   (it != end() )
  {
    if   ( ! (it->second.isLocked) || isForced )    // do it only if its not locked or if power user is at work...
    {
      if   (it->second.discr == tFloat)
      {
        it->second.val.f = fVal;
        if   (it->second.isLocked) 
        {
          // Locked Value must have been overwritten by power user via isForced=true
          //
          CLOG2 (<< "Value of  <" << tag << ">: Overwritten by priviledged user, value now " << it->second.val.f << std::endl);
        }
      }
      else if (mayThrow)
      {
        // invalid to store invalid Type (try to store float but storage is not float).
        CLOG2 (<< "Tag <" << tag << ">: Invalid attempt to store float value." << std::endl);
        throw IBAS::EXC_IncorrectTagType();
      }
    }
  }
  else if (!mayThrow)
  {
    Value v;
    v.isLocked = false;       // Start Not Locked
    v.discr = tFloat;
    v.val.f = fVal;
    (*this)[key] = v;
    CLOG5(<< "Added new Tag: " << tag << " as float" << std::endl);
  }
  else
  {
    // Normally, throw an exception if Tag has not been found.
    CLOG2 (<< "Tag <" << tag << "> not known." << std::endl);
    throw IBAS::EXC_TagNotFound();
  }
}

void cStorage::store  (const std::string &tag, const std::string &sVal, bool mayThrow, bool isForced)
{
  std::string key = tag;

  vMap::iterator it = find(key);
  if   (it != end() )
  {
    if   ( ! (it->second.isLocked) || isForced )    // do it only if its not locked or if power user is at work...
    {
      if   (it->second.discr == tString)
      {
        it->second.s =sVal;
        if   (it->second.isLocked) 
        {
          // Locked Value must have been overwritten by power user via isForced=true
          //
          CLOG2 (<< "Value of  <" << tag << ">: Overwritten by priviledged user, value now " << it->second.s << std::endl);
        }
      }
      else if (mayThrow)
      {
        // invalid to store numeric value in a string!
        CLOG2 (<< "Tag <" << tag << ">: Invalid attempt to store string value." << std::endl);
        throw IBAS::EXC_IncorrectTagType();
      }
    }
  }
  else if   (!mayThrow)
  {
    Value v;
    v.isLocked = false;       // Start Not Locked
    v.discr = tString;
    v.s = sVal;
    (*this)[key] = v;
    CLOG5(<< "Added new Tag: " << tag << " as string" << std::endl);
  }
  else
  {
    // Normally, throw an exception if Tag has not been found.
    CLOG2 (<< "Tag <" << tag << "> not known." << std::endl);
    throw IBAS::EXC_TagNotFound();
  }
}

bool cStorage::setLock (const std::string &tag, bool newValue)
{
  return false;
 //not supported
}


void cStorage::setAllLocks (bool newValue)
{
  //not supported
}

void cStorage::logAllLocks()
{
 //not supported
} // end of this function

bool cStorage::isLocked (const std::string &tag)
{
  bool retval = false;

  // no assumption if its a set value (sp.) or a get value (fb.) 
  //
  vMap::iterator it = end();

  if   (*(tag.c_str()+2) == '.')                                  // qualified name. Very good.
  {
    it = find(tag);
    retval = it->second.isLocked;
  }
  else
  {
    std::string keySP=std::string("sp.") + tag;
    std::string keyFB=std::string("fb.") + tag;

    vMap::iterator itSP = find(keySP);
    vMap::iterator itFB = find(keyFB);

    // now exactly one of the 2 iterators must be set, and not both set and not both null.


    if        (itFB!= end() && itSP == end())   it = itFB;        // Unique: it is the Value From L1
    else if   (itSP!= end() && itFB == end())   it = itSP;        // Unique: it is the Set Point
    else if   (itSP!= end() && itFB != end())
    {
                                                                  // not unique: Tag serves for setpoint and get - Value 
      CLOG2 (<< "Tag <" << tag << "> not unique - could be fb." 
             << tag << " or sp." << tag << ", no lock state retrieved." 
             << std::endl);
      throw IBAS::EXC_IncorrectTagType();  
    }
    else if   (itSP== end() && itFB == end())
    {
      // Tag not known at all - exception thrown below, nothing to do here
    }
  }

  if   (it!= end())
  {
    retval = it->second.isLocked;
  }
  else 
  {
    // Tag not known at all 
    CLOG2 (<< "Tag <" << tag << "> not known, so no lock state retrieved." << std::endl);
    throw IBAS::EXC_TagNotFound();
  }

  // Note that here, retval has really been set to the old lock state of the variable.
  // In all error cases we do not get here but bail out via an exception 
  return retval;
}

bool cStorage::getListOfLockedValues(std::vector<std::string> &retList )
{
  //not supported
  return false;
}


// retrieve the various kinds of data...
bool cStorage::retrieve (const std::string &tag, long & retLong, bool dontThrowException)
{

  bool retval = true;   // assume success

  std::string key = tag;

  vMap::iterator it = find(key);
  if   (it != end() )
  {
    switch (it->second.discr )
    {
    case tLong:
      retLong = it->second.val.l;
      break;
    case tFloat:    // we allow floats to be retrieved as ints.
      if   (dontThrowException)
      {
        retLong = static_cast<long>(it->second.val.f);
        break;
      }
      else
      {
        // do nothing but fall down to "default"
      }
      // no "break" here.
    default:
      // invalid: string returned as Long.
      retval = false;
      if   (!dontThrowException)
      {
        CLOG2 (<< "Tag <" << tag << ">: Invalid attempt to retrieve long value." << std::endl);
        throw IBAS::EXC_IncorrectTagType();
      }
      break;
    }
  }
  else
  {
    // data not stored with tagged name
    if   (!dontThrowException)
    {
      CLOG2 (<< "Tag <" << tag << "> not known." << std::endl);
      throw IBAS::EXC_TagNotFound( );
    }
    retval=false;
  }
  return retval;
}

bool cStorage::retrieve (const std::string &tag, float & retFloat, bool dontThrowException)
{

  bool retval = true;   // assume success

  std::string key = tag;

  vMap::iterator it = find(key);
  if   (it != end() )
  {
    switch (it->second.discr )
    {
    case tFloat:    // we allow floats to be retrieved as ints.
      retFloat = it->second.val.f;
      break;
    case tLong:
      if   (dontThrowException)
      {
        retFloat = static_cast<float> (it->second.val.l);
        break;
      }
      else
      {
        // do nothing but fall down to "default"
      }
      // no "break" here.
    default:
      // invalid: string returned as Long.
      retval = false;
      if   (!dontThrowException)
      {
        CLOG2 (<< "Tag <" << tag << ">: Invalid attempt to retrieve float value." << std::endl);
        throw IBAS::EXC_IncorrectTagType();
      }
      break;
    }
  }
  else
  {
    // data not stored with tagged name
    if   (!dontThrowException)
    {
      CLOG2 (<< "Tag <" << tag << "> not known." << std::endl);
      throw IBAS::EXC_TagNotFound( );
    }
    retval=false;
  }
  return retval;
}
bool cStorage::retrieve (const std::string &tag, std::string &retString, bool dontThrowException)
{
  bool retval = true;   // assume success

  std::string key = tag;

  vMap::iterator it = find(key);
  if   (it != end() )
  {
    switch (it->second.discr )
    {
    case tString:    // we allow floats to be retrieved as ints.
      retString = it->second.s;
      break;
    default:
      // invalid type request
      retval = false;
      if   (!dontThrowException)
      {
        CLOG2 (<< "Tag <" << tag << ">: Invalid attempt to retrieve string value." << std::endl);
        throw IBAS::EXC_IncorrectTagType();
      }
      break;
    }
  }
  else
  {
    // data not stored with tagged name
    if   (!dontThrowException)
    {
      CLOG2 (<< "Tag <" << tag << "> not known." << std::endl);
      throw IBAS::EXC_TagNotFound( );
    }
    retval=false;
  }
  return retval;

}

