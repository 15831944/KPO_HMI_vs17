#include <iostream>
#include "stdio.h"
#include "CXML_TlgReader.h"
using namespace std;
#pragma warning(disable: 4290)

int main( int argc, const char *argv[] )
{
  if ((argc >1) && (argc < 4) )
  {
	  // do something
    std::string XMLFileName = "";
    std::string IDLFileName = "";
    std::string ext = "";
    int pos = 0;
    bool useXMLFileName = true;
    
    XMLFileName = argv[1];
    IDLFileName = argv[2];

    if ( ! IDLFileName.empty() )
    {
      useXMLFileName = false;
    }

    //XMLFileName = "adhaepohj.XML";
    pos = XMLFileName.find_last_of(".", XMLFileName.length());
    if(pos == -1)
    {
      std::cout << "File name without extension!";
      return -1;
    }

    ext = XMLFileName.substr(pos + 1, XMLFileName.length() - pos);
    if(strcmp(ext.c_str(),"xml") !=0 && strcmp(ext.c_str(),"XML") !=0)
    {
      std::cout << "File is not XML-File!";
      return -1;
    }
    
    FILE* inFile;
    FILE* outFile;
    std::string erg = "";
    inFile = fopen(XMLFileName.c_str(),"r");

    if(inFile == NULL)
    {
      std::cout << "File " << XMLFileName << " dos't exist!";
      return -1;
    }
    fclose(inFile);
    CXML_TlgReader reader ;
    try
    {
      erg = reader.makeIDL(XMLFileName);
    }
    catch(...)
    {
      std::cout << "XML-File is not consistent.";
      return -1;
    }

    if ( useXMLFileName )
    {
      IDLFileName = XMLFileName.erase(pos + 1,XMLFileName.length()) + "idl";
    }

    outFile = fopen(IDLFileName.c_str(),"w");
    if(outFile == NULL)
    {
      return -1;
    }
    fprintf(outFile,erg.c_str());
    fclose(outFile);

    std::cout << "\n\nFile " << IDLFileName << " generated." << std::endl;
    if ( useXMLFileName )
    {
      std::cout << "***********************************************" << std::endl;
      std::cout << "Don't forget to copy IDL-file from \n" ;
      std::cout << IDLFileName.substr(0,IDLFileName.find_last_of("\\"))  << std::endl;
		  std::cout << "***********************************************" << std::endl;
    }
  }
  else
  {
    std::cout << "    ==================================================\n";
    std::cout << "    Idl genarator.\n";
    std::cout << "    Usage: \n";
    std::cout << "    " << argv[0] << " [IN]" << std::endl;
    std::cout << "    [IN] file.xml - description of telegrams" << std::endl;
    std::cout << "==================================================\n";
  }
  return 0;
}