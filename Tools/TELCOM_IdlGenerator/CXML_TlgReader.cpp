#include "CXML_TlgReader.h"

CXML_TlgReader::CXML_TlgReader(void)
{
str = "";
}

CXML_TlgReader::~CXML_TlgReader(void)
{}

std::string CXML_TlgReader::makeIDL(std::string FileName)
{
  TiXmlNode *root;
	TiXmlNode* pChild;
	int type; //   pChild->Type()
  doc = new TiXmlDocument(FileName);
  doc->LoadFile();
  //if(!doc->LoadFile())
  //{
  //  std::cout << "XML-File is corrupt!";
  //  return str;
  //}
  root = doc->FirstChildElement();
  
  for ( pChild = root->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
  {
    type = pChild->Type();

    if( type == TiXmlNode::ELEMENT)
    {
      if(strcmp(pChild->Value(),"telegram") == 0)
      {
        // ********************************************************************************
        //std::cout << "********************************************************************************" << std::endl;
        //std::cout << "Telegram " << pChild->ToElement()->FirstAttribute()->Value() << std::endl;
        // ********************************************************************************

        //str = "";
        str += "\nmodule Telegram_";
        str += pChild->ToElement()->FirstAttribute()->Value();
        str += "\n{\n";
        elemEvaluate(pChild,true);// analysiere modul elemente
        str += "};\n";
      }
      else if(strcmp(pChild->Value(),"type") == 0)
      {
        // ********************************************************************************
        //std::cout << "********************************************************************************" << std::endl;
        //std::cout << "struct " << pChild->ToElement()->FirstAttribute()->Value() << std::endl;
        // ********************************************************************************

        //str = "";
        str += "\nstruct ";
        str += pChild->ToElement()->FirstAttribute()->Value();
        str += "\n{\n";
        elemEvaluate(pChild->FirstChild("element")->FirstChild(),false);// analysiere struct elemente
        str += "};\n";
      }
      else if(strcmp(pChild->Value(),"record") == 0)
      {
        // ********************************************************************************
        //std::cout << "********************************************************************************" << std::endl;
        //std::cout << "record " << pChild->ToElement()->FirstAttribute()->Value() << std::endl;
        // ********************************************************************************

        //str = "";
        str += "\nstruct ";
        str += pChild->ToElement()->FirstAttribute()->Value();
        str += "\n{\n";
        elemEvaluate(pChild->FirstChild("element")->FirstChild(),false);// analysiere struct elemente
        str += "};\n";
      }

	  }//if( type == TiXmlNode::ELEMENT)
	}// for ( pChild = root->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 

  return str;
}

void CXML_TlgReader::elemEvaluate( TiXmlNode* pParent, bool isModule)
{
	TiXmlNode* pChild;
	int t = pParent->Type();

	for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
  {
    if( t == TiXmlNode::ELEMENT)
    {
      if(strcmp(pChild->Value(),"record") == 0) // if pChild->Value() == "record"
      {
        elemEvaluate(pChild,isModule); // gehe rekursive rein
      }
      else if(strcmp(pChild->Value(),"element") == 0)
      {
        // ********************************************************************************
        //std::cout << pChild->ToElement()->FirstAttribute()->Value() << std::endl;
        // ********************************************************************************

        // if userDefined type and not sequence
        if(strcmp(pChild->FirstChild()->NextSiblingElement()->Value(),"userDefined") == 0
          && strcmp(pChild->ToElement()->Attribute("count"),"1") == 0)
        {
          //suche den definierten type
          findUserType(pChild->FirstChild()->NextSiblingElement()->FirstAttribute()->Value(),isModule);
        }
        else if(strcmp(pChild->FirstChild()->NextSiblingElement()->Value(),"record") == 0) // has Child "record"  
        {
          str += "    /* ";
          str += pChild->FirstChild()->NextSiblingElement()->Value(); // XML-Data type
          str += " len=";
          if(pChild->ToElement()->Attribute("len") != NULL)
            str += pChild->ToElement()->Attribute("len");
          str += " count=";
          if(pChild->ToElement()->Attribute("count") != NULL)
            str += pChild->ToElement()->Attribute("count");
          str += " */\n";

          if(isModule)
            str += "  const string ";
          else
            str += "  string ";

          str += pChild->ToElement()->FirstAttribute()->Value(); // Element name

          if(isModule)
          {
            str += " = \"";
            str += pChild->ToElement()->FirstAttribute()->Value(); // Element name
            str += "\"";
          }
          str += ";\n";
          if(pChild->ToElement()->Attribute("count") != NULL)
          {
            str += "\n  struct s";
            str += pChild->ToElement()->FirstAttribute()->Value();
            str += "\n  {\n";

            std::cout << str << std::endl;

            structEvaluate(pChild->FirstChild()->NextSiblingElement(),false);// analysiere struct elemente
            str += "  };\n";

            if(isModule)
            {
              str += "  typedef";
            }
            str += "  sequence <s";
            str += pChild->ToElement()->FirstAttribute()->Value();

            str += "> t_";
            str += pChild->ToElement()->FirstAttribute()->Value();// Element name
            str += ";\n";

          }// if(strcmp(pChild->ToElement()->Attribute("count"),"1") != 0) // if count != 1 -> define sequence
        }
        else
        {
          str += "    /* ";
          str += pChild->FirstChild()->NextSiblingElement()->FirstAttribute()->Value(); // XML-Data type
          str += " len=";
          if(pChild->FirstChild()->NextSiblingElement()->Attribute("len") != NULL)
            str += pChild->FirstChild()->NextSiblingElement()->Attribute("len");
          str += " count=";
          if(pChild->ToElement()->Attribute("count") != NULL)
            str += pChild->ToElement()->Attribute("count");
          str += " */\n";

          if(isModule)
            str += "  const string ";
          else
            str += "  string ";

          str += pChild->ToElement()->FirstAttribute()->Value(); // Element name

          if(isModule)
          {
            str += " = \"";
            str += pChild->ToElement()->FirstAttribute()->Value(); // Element name
            str += "\"";
          }
          str += ";\n";
          if(pChild->ToElement()->Attribute("count") != NULL)
          {
            if(strcmp(pChild->ToElement()->Attribute("count"),"1") != 0) // if count != 1 -> define sequence
            { 
              if(isModule)
              {
                str += "  typedef";
              }
              str += "  sequence <";
              if(strcmp(pChild->FirstChild()->NextSiblingElement()->FirstAttribute()->Value(),"integer") == 0)
                str += "long";
              else if(strcmp(pChild->FirstChild()->NextSiblingElement()->FirstAttribute()->Value(),"number") == 0)
                str += "double";
              else if(strcmp(pChild->FirstChild()->NextSiblingElement()->FirstAttribute()->Value(),"DateTime") == 0)
                str += "string";
              else
                str += pChild->FirstChild()->NextSiblingElement()->FirstAttribute()->Value();// Element type

              str += "> t_";
              str += pChild->ToElement()->FirstAttribute()->Value();// Element name
              str += ";\n";
            }// if(strcmp(pChild->ToElement()->Attribute("count"),"1") != 0) // if count != 1 -> define sequence
          } // if(pChild->ToElement()->Attribute("count") != NULL)
        } // if not userDefined type
      }//  else if(strcmp(pChild->Value(),"element") == 0)
	  }//  if( t == TiXmlNode::ELEMENT)
  }// for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 


  // ********************************************************************************
  // std::cout << str << std::endl;
  // ********************************************************************************

}// void CXML_TlgReader::elemEvaluate( TiXmlNode* pParent)

void CXML_TlgReader::structEvaluate( TiXmlNode* pParent, bool isModule )
{
	TiXmlNode* pChild;
	int t = pParent->Type();

	for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 
  {
    if( t == TiXmlNode::ELEMENT)
    {
      if(strcmp(pChild->Value(),"record") == 0) // if pChild->Value() == "record"
      {
        elemEvaluate(pChild,isModule); // gehe rekursive rein
      }
      else if(strcmp(pChild->Value(),"element") == 0)
      {
        // ********************************************************************************
        //std::cout << pChild->ToElement()->FirstAttribute()->Value() << std::endl;
        // ********************************************************************************

        // if userDefined type and not sequence
        if(strcmp(pChild->FirstChild()->NextSiblingElement()->Value(),"userDefined") == 0
          && strcmp(pChild->ToElement()->Attribute("count"),"1") == 0)
        {
          //suche den definierten type
          findUserType(pChild->FirstChild()->NextSiblingElement()->FirstAttribute()->Value(),isModule);
        }
        else if(strcmp(pChild->FirstChild()->NextSiblingElement()->Value(),"record") == 0) // has Child "record"  
        {
          str += "    /* ";
          str += pChild->FirstChild()->NextSiblingElement()->Value(); // XML-Data type
          str += " len=";
          if(pChild->ToElement()->Attribute("len") != NULL)
            str += pChild->ToElement()->Attribute("len");
          str += " count=";
          if(pChild->ToElement()->Attribute("count") != NULL)
            str += pChild->ToElement()->Attribute("count");
          str += " */\n";

          if(isModule)
            str += "  const string ";
          else
            str += "  string ";

          str += pChild->ToElement()->FirstAttribute()->Value(); // Element name

          if(isModule)
          {
            str += " = \"";
            str += pChild->ToElement()->FirstAttribute()->Value(); // Element name
            str += "\"";
          }
          str += ";\n";
          if(pChild->ToElement()->Attribute("count") != NULL)
          {
            str += "\n  struct s";
            str += pChild->ToElement()->FirstAttribute()->Value();
            str += "\n  {\n";

            std::cout << str << std::endl;

            structEvaluate(pChild->FirstChild()->NextSiblingElement(),false);// analysiere struct elemente
            str += "  };\n";

            if(isModule)
            {
              str += "  typedef";
            }
            str += "  sequence <s";
            str += pChild->ToElement()->FirstAttribute()->Value();

            str += "> t_";
            str += pChild->ToElement()->FirstAttribute()->Value();// Element name
            str += ";\n";

          }// if(strcmp(pChild->ToElement()->Attribute("count"),"1") != 0) // if count != 1 -> define sequence
        }
        else
        {
          str += "    ";

          if(strcmp(pChild->FirstChild()->NextSiblingElement()->FirstAttribute()->Value(),"integer") == 0)
            str += "long";
          else if(strcmp(pChild->FirstChild()->NextSiblingElement()->FirstAttribute()->Value(),"number") == 0)
            str += "double";
          else if(strcmp(pChild->FirstChild()->NextSiblingElement()->FirstAttribute()->Value(),"DateTime") == 0)
            str += "string";
          else
            str += pChild->FirstChild()->NextSiblingElement()->FirstAttribute()->Value();// Element type

          str += " ";

          str += pChild->ToElement()->FirstAttribute()->Value();// Element name

          str += ";\n";
        } // if not userDefined type
      }//  else if(strcmp(pChild->Value(),"element") == 0)
	  }//  if( t == TiXmlNode::ELEMENT)
  }// for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) 


  // ********************************************************************************
  // std::cout << str << std::endl;
  // ********************************************************************************

}// void CXML_TlgReader::elemEvaluate( TiXmlNode* pParent)


void CXML_TlgReader::findUserType(std::string DefName,bool isModule)
{
  TiXmlNode* pChild;
  for(pChild = doc->FirstChild()->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
  {
    if(strcmp(pChild->Value(),"type") == 0) // if type definition
    {
      if(strcmp(pChild->ToElement()->FirstAttribute()->Value(),DefName.c_str()) == 0) // if definitionname found
      {
        str += "  /* struct s";
        str += pChild->ToElement()->FirstAttribute()->Value();
        str += "{   */\n";
        elemEvaluate(pChild->FirstChild("element")->FirstChild(),isModule);
        str += "  /*} ";
        str += pChild->ToElement()->FirstAttribute()->Value(); 
        str += "  */\n";
      }// if definitionname found
    }
    else if(strcmp(pChild->Value(),"record") == 0) // if type definition
    {
      if(strcmp(pChild->ToElement()->FirstAttribute()->Value(),DefName.c_str()) == 0) // if definitionname found
      {
        str += "  /* struct s";
        str += pChild->ToElement()->FirstAttribute()->Value();
        str += "{   */\n";
        elemEvaluate(pChild->FirstChild("element")->FirstChild(),isModule);
        str += "  /*} ";
        str += pChild->ToElement()->FirstAttribute()->Value(); 
        str += "  */\n";
      }// if definitionname found
    }

  }
}

