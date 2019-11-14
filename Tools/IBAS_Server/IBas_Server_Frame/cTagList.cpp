#include "cTagList.h"
#define _CLOG9
#include "CBS_Utilities\CBS_Clog.h"

//##ModelId=4289A07200A7
cTagList::cTagList()
{
  // make a list of known data types.
  // first the Telcom built-ins
  knownTypes.insert ("integer");
  knownTypes.insert ("number");
  knownTypes.insert ("string");
  knownTypes.insert ("bool");
  knownTypes.insert ("datetime");

  // CCS specific:
  knownTypes.insert ("FlagA");
  knownTypes.insert ("FlagB");
  knownTypes.insert ("Flag");
  knownTypes.insert ("Counter");
  // add more if needed 
}

//##ModelId=4289A07200A8
void cTagList::addTag(const char *tag, const char * type)
{
  if   (knownTypes.find(type) != knownTypes.end())
  {
    if   ( (*this).find (tag) == (*this).end())
      // Tag not yet stored - do it now
      (*this)[tag] = type;
    else
      // Tag as already been stored. 
    {
      if   (tag[0] == 'f')   // "fb.something" , serious bug
      {
        CLOG1 (<< "Tag " << tag << ": MULTIPLY DEFINED (SERIOUS FOR RECEIVED VALUE)" << std::endl);
      }
      else
      {
        CLOG1 (<< "Tag " << tag << ": MULTIPLY DEFINED (MIGHT BE OK FOR SENDING)" << std::endl);
      }
    }
  }
  else
    CLOG2( << "Found Tag " << tag << " of unknown type " << type << " Might be OK - maybe not. CHECK." << std::endl);

}

