#ifndef CSTORAGE_H
#define CSTORAGE_H

#include <string>
#include <map>
#include <vector>
#include <string>

// define allowed data types
typedef enum eTypes {tLong,tFloat,tString}  eType;

// define storage area for Floats,Longs, Strings
typedef struct
{ 
  bool isLocked;    // Regular users will not overwrite value if it "isLocked"

  int discr;        // discriminator for following union
  union             // save 4 bytes...
  {
    long l;
    float f;
  } val;
  std::string s;
}    Value;

typedef std::map <std::string, Value>   vMap;

class cStorage : public vMap
{
public:

  static cStorage * instance();

  // Store the various kinds of data
  // the mayThrow flag is for internal use only (not for General User)
  void store (const std::string &tag, long  lVal, bool mayThrow=true, bool isForced=false);
  void store (const std::string &tag, float fVal, bool mayThrow=true, bool isForced=false);
  void store (const std::string &tag, const std::string &sVal, bool mayThrow=true, bool isForced=false);

  // retrieve the various kinds of data...

  bool retrieve (const std::string &tag, long  &retLong,  bool DontThrowException=false);
  bool retrieve (const std::string &tag, float &retFloat, bool DontThrowException=false);
  bool retrieve (const std::string &tag, std::string &retString, bool DontThrowException=false);
 
  // Set/Clear Lock status:
  //
  // set new status and returns previous status. Throws the usual exception if Tag is not known
  bool setLock  (const std::string &tag, bool value);
  void setAllLocks (bool value);

  bool isLocked (const std::string &tag);

  bool getListOfLockedValues(std::vector<std::string> &retList );

  void logAllLocks(void);

  eTypes allowedTypes;

private:
  cStorage(void);
  virtual ~cStorage(void);
  static cStorage *thisOne;
};



#endif // CSTORAGE_H