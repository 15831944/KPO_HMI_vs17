#ifndef CTAGLIST_H
#define CTAGLIST_H

#include <string>
#include <map>
#include <set>

//##ModelId=4289A072009B
class cTagList : public std::map <std::string,std::string> 
{
public:
	//##ModelId=4289A07200A7
  cTagList();
	//##ModelId=4289A07200A8
  void addTag (const char *tag, const char * type );

protected:
	//##ModelId=4289A07200B0
  std::set <std::string> knownTypes; 
};


#endif // CTAGLIST_H
