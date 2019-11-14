// Copyright (C) 1999 - 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CINTFDATA_40B6F41F0192_INCLUDED
#define _INC_CINTFDATA_40B6F41F0192_INCLUDED

#include <float.h>
#include <string>
#include <map>
#include <sstream>

//#include "cbs.h"  //ffra: from JSW 
#include "X:\SMC\packages\CBS\include\CBS_CorbaLib\cCBS_ORB.h"   //ffra: from Hadeed
#include "corba.h"
#include "CIntfDataRuleSet.h"

#include "CIntfDataType.h"
#include "CData_Provider_Impl.h"


class CData_Provider;


// macro for sorting sequences ascending !
// SORT_SEQ(SourceSeq,SourceStructType,Field)
// SourceSeq        = Sequence of data source
// SourceStructType = Type of data source Struct
// Field            = name of structure element to be compared as key for sort, MUST be numeric !
// usage : SORT_SEQ(AnalysisSeq,sAnalysis,Concentration);
#if defined (SORT_SEQ)
#undef SORT_SEQ
#endif
#define SORT_SEQ(SourceSeq,SourceStructType,Field){\
          /* set initial values for sequence and struct */ \
          long LenSource = CIntfData::getLength(##SourceSeq); \
          long iOuter    = 0;\
          /* start iteration on source sequence for 0 ... n*/ \
          for ( iOuter ; iOuter < LenSource ; ++iOuter ) \
          { \
            double MinValue = DBL_MAX; \
            long   MinIndex = LONG_MAX; \
            long   iInner   = iOuter;\
            /* start iteration on source sequence for 0 ... n*,  1...n, 2...n */ \
            for ( iInner ; iInner < LenSource ; ++iInner ) \
            { \
              /* try to find index for minimum value of "Field" */ \
              SourceStructType SourceStruct;\
              CIntfData::getAt(##SourceStruct,##SourceSeq,iInner);\
              if( ##SourceStruct.##Field < MinValue )\
              { \
                MinValue = ##SourceStruct.##Field;  \
                MinIndex = iInner;  \
              }\
            } /*for ( iInner ; iInner < LenSource ; ++iInner )*/ \
            /* check if index has been found and index is different to actual position */ \
            if ( MinIndex != LONG_MAX && iInner != iOuter ) \
            {\
              /* change positions */ \
              SourceStructType StructOuter;\
              SourceStructType StructInner;\
              CIntfData::getAt(##StructOuter,##SourceSeq,iOuter);\
              CIntfData::getAt(##StructInner,##SourceSeq,MinIndex);\
              CIntfData::setAt(##SourceSeq,##StructOuter,MinIndex);\
              CIntfData::setAt(##SourceSeq,##StructInner,iOuter);\
            }/*if ( MinIndex != LONG_MAX && iInner != iOuter )*/\
          }/*for ( iOuter ; iOuter < LenSource ; ++iOuter )*/\
        }
// #if defined (SORT_SEQ)



// macro for updating sequences
// UPDATE_SEQ(SourceSeq,SourceStruct,AimSeq,AimStruct,Field)
// SourceSeq    = Sequence of data source
// SourceStruct = Struct of data source
// AimSeq       = Sequence type of data aim
// AImStruct    = Struct of data aim
// Field = name of structure element to be compared as key for update
// usage : UPDATE_SEQ(DHSeq,DHStruct,PlantSeq,PlantStruct,Device);
#if defined (UPDATE_SEQ)
#undef UPDATE_SEQ
#endif
#define UPDATE_SEQ(SourceSeq,SourceStruct,AimSeq,AimStruct,Field,FieldType){\
          /* set initial values for sequence and struct */ \
          long LenAim = CIntfData::getLength(*##AimSeq); \
          long LenSource = CIntfData::getLength(*##SourceSeq); \
          /* start iteration an source sequence */ \
          for ( long iDH = 0 ; iDH < LenSource ; ++iDH ) \
          { \
            long Pos = -1; \
            CIntfData::getAt(##SourceStruct,##SourceSeq,iDH);\
            /* start iteration an aim sequence */ \
            for ( long iDM = 0 ; iDM < LenAim ; ++iDM )\
            {\
            CIntfData::getAt(##AimStruct,##AimSeq,iDM);\
              /* compare values at specific field and find position */ \
              if( (##FieldType)##SourceStruct.##Field == (##FieldType)##AimStruct.##Field )\
              {\
                Pos = iDM;\
                break;\
              }\
            }\
            /* if valid position found, update structure, otherwise insert structure */ \
            if ( Pos >= 0 )\
            {\
            CIntfData::setAt(*##AimSeq,##SourceStruct,Pos);\
            }\
            else\
            {\
            CIntfData::insert(*##AimSeq,##SourceStruct);\
            }\
          }\
        }
// #if defined (UPDATE_SEQ)


#if defined (GET_FROM_SEQ)
#undef GET_FROM_SEQ
#endif
#define GET_FROM_SEQ(SourceSeq,SourceStruct,Field,FieldType,Value){\
          /* set initial values for sequence and struct */ \
          long LenSource = CIntfData::getLength(*##SourceSeq); \
          /* start iteration an source sequence */ \
          for ( long iDH = 0 ; iDH < LenSource ; ++iDH ) \
          { \
            long Pos = -1; \
            CIntfData::getAt(##SourceStruct,##SourceSeq,iDH);\
            /* compare values at specific field and find position */ \
            if( (##FieldType)##SourceStruct.##Field == (##FieldType)Value )\
            {\
              break;\
            }\
          }\
        }
// #if defined (GET_FROM_SEQ)


//##ModelId=40B6F41F0192
class CIntfData 
{
public:

  void setRequested(bool value);
  bool isRequested();

	//##ModelId=44FE999A0371
  void setUpdated(bool value);
	//##ModelId=44FE999A03A3
  bool isUpdated();

	//##ModelId=415D878E0231
	static std::string String;

	//##ModelId=415D878E0259
	static std::string Long;

	//##ModelId=415D878E0277
	static std::string Double;

	//##ModelId=415D878E029F
	static std::string Bool;

	//##ModelId=415D878E02C8
	static std::string Any;

	//##ModelId=414957C40121
	CIntfData(CData_Provider* pData_Provider);

  //##ModelId=40D29EAD02D4
  virtual void showContent(long Level);

	//##ModelId=44FE999B001F
  virtual std::string getContent();

	//##ModelId=40BF22590165
	const std::string&  getType() ;

	//##ModelId=40B74F2901AE
	virtual ~CIntfData();

  // reading content of CORBA sequence
  // argument DynAnyFact should be given from outside to prevent multiple calls of 
  // CBS::getORB()->resolve_initial_references("DynAnyFactory");
	template<typename SE>
    static std::string getContent(SE& Sequence, DynamicAny::DynAnyFactory_var DynAnyFact = 0, long Indent = 0)
  {
    std::stringstream Content;

    if(!DynAnyFact)
    {
      // Get a Factory for DynAny
     //CORBA::Object_var dynObj = CBS::getORB()->resolve_initial_references("DynAnyFactory");//ffra :11/10/2017 Since header file is changed as per hadeed CBS to cCBS_ORB.  
	  CORBA::Object_var dynObj = cCBS_ORB::getORB()->resolve_initial_references("DynAnyFactory");
      DynAnyFact               = DynamicAny::DynAnyFactory::_narrow(dynObj);
    }

    DynamicAny::DynAny_var da = DynAnyFact->create_dyn_any (Sequence);
    Content << CIntfData::getDynContent(da,Indent);

    return Content.str();
  }

  // extracting metadata and write to output stream
  // might be called recursively !
	//##ModelId=44FE999B0047
  static std::string getDynContent(DynamicAny::DynAny_ptr da, long& Indent)
  {
    Indent += 1;

    std::stringstream outLine;
    //
    // Aliases
    //
    CORBA::TypeCode_var tc(da->type());
    while (tc->kind() == CORBA::tk_alias)
      tc = tc->content_type();
    //
    // deal with the data types
    //
    switch (tc->kind())
    {
      //
      // expect the unexpected: there are more data types than are handled here...
      // -------------------------------------------------------------------------
    default:
      outLine << "(the ANY contains a data type that is not (yet) handled)";
      break;
    //
    // First the primitives: straight output of the data.
    // --------------------------------------------------
    case CORBA::tk_short:
      outLine << " " << da->get_short();
      break;
    case CORBA::tk_ushort:
      outLine << " " << da->get_ushort();
      break;
    case CORBA::tk_long:
      outLine << " " << da->get_long();
      break;
    case CORBA::tk_ulong:
      outLine << " " << da->get_ulong();
      break;
    case CORBA::tk_boolean:
      outLine << " " << da->get_boolean();
      break;
    case CORBA::tk_char:  // print in <> brackets to distinguish blank from "nothing".
      outLine << " <" << da->get_char() << ">";
      break;
    case CORBA::tk_double:
      outLine << " " << da->get_double();
      break;
    case CORBA::tk_float:
      outLine << " " << da->get_float();
      break;
    case CORBA::tk_string:
      outLine << " <" << CORBA::String_var(da->get_string()) << ">"; // print in <> brackets
      break;

    //
    // Some compounds: structures, arrays, and sequences. These are parsed recursively
    // until primitives are reached. 
    //
    case CORBA::tk_struct:
      {
        // For a structure, display "struct structureName = {element1=value,....}"
        DynamicAny::DynStruct_var ds = DynamicAny::DynStruct::_narrow(da);
        CORBA::TypeCode_var       lv_tc  (ds->type());
        outLine << "struct " << lv_tc->name() << " = {";
        bool isAlias=false;
        while (lv_tc->kind() == CORBA::tk_alias)
        {
          lv_tc = lv_tc->content_type();
          isAlias=true;
        }
        if (isAlias)
        {
          outLine <<"(alias " << lv_tc->name() << ") ";
        }
        for (unsigned long ii=0; ii<lv_tc->member_count(); ++ii)       // parse the entire struct
        {
          DynamicAny::DynAny_var  cm(ds->current_component());
          CORBA::String_var       memName(ds->current_member_name());
          outLine << " " << memName << " = " << CIntfData::getDynContent(cm,Indent);       // recurse into struct
          if (ii <lv_tc->member_count()-1)   outLine << ",";
          ds->next();
        }
        outLine << "}";
      } // almost the end of case
      break;
    case CORBA::tk_array:
      {
        //
        // For an array, print "[index] : value" (remember: value might be compound as well)
        //
        CORBA::TypeCode_var lv_tc(da->type());
        for (unsigned long ii=0; ii<lv_tc->length(); ++ii)           // length is always >0
        {
          DynamicAny::DynAny_var cm(da->current_component());
          outLine<< "["<<ii<<"] :" << CIntfData::getDynContent(cm,Indent);            // recurse into array
          da->next();
        }
      } // almost the end of case
      break;
    case CORBA::tk_sequence:
      {
        //
        // For a Sequence: print type and dimension (if any), and the values
        //
        DynamicAny::DynSequence_var ds = DynamicAny::DynSequence::_narrow(da);
        if   (ds->get_length() <=0)                           // empty sequence ?
        {
          outLine << "(empty sequence)";
        }
        else                                                  // not empty
        {
          CORBA::TypeCode_var lv_tc (ds->type());
          outLine << " " <<  lv_tc->name() << "[" << ds->get_length() << "] = {";
          for (unsigned long ii=0; ii<ds->get_length(); ++ii)
          {
            DynamicAny::DynAny_var cm(ds->current_component());
            outLine << "\n";

            for (long i = 0; i < Indent ; ++i)
            {
              outLine << " ";
            }

            outLine << "[" << ii << "] = " << CIntfData::getDynContent(cm,Indent);     // recurse into sequence 
            ds->next(); 
          }
          outLine << "}";
        }                                                     // empty/not empty
      } // almost the end of case
      break;
    }

    Indent -= 1;

    return outLine.str();
  }

  // inserting structure into CORBA sequence
	template<typename SE, typename V>
	static void preset(SE& Sequence, V Value, CORBA::ULong Length)
  {
    Sequence.length(Length);
    for ( CORBA::ULong Pos = 0 ; Pos < Length ; ++Pos )
    {
      setAt(Sequence, Value, Pos);
    }
  }



  // inserting structure into CORBA sequence
	template<typename SE, typename V>
	inline static void insert(SE& Sequence, V Value)
  {
    CORBA::ULong current = Sequence.length();
    Sequence.length(current+1);
    Sequence[current] = Value;
  }

  // inserting structure into CORBA sequence to defined position
	template<typename SE, typename V>
	static void insert(SE& Sequence, V Value, CORBA::ULong Pos)
  {
    CORBA::ULong current = Sequence.length();
    Sequence.length(current+1);
    current++;
    for (long i = (current-1); i >= Pos; i--)
    {
      if (i < current)
      {
        if (i > Pos)
        {
          Sequence[i] = Sequence[i-1];
        }
        else
        {
          Sequence[i] = Value;
        }
      }
      else
        return;
    }
  }

  // updating structure at CORBA sequence position
	template<typename SE, typename V>
	inline static bool setAt(SE& Sequence, V Value, CORBA::ULong Pos)
  {
    bool RetValue = false;
    if ( Pos < Sequence.length() )
    {
      Sequence[Pos] = Value;
      RetValue = true;
    }

    return RetValue;
  }

  // updating structure at CORBA sequence position
	template<typename SE, typename V>
	static bool setAt(SE* Sequence, V Value, CORBA::ULong Pos)
  {
    bool RetValue = false;
    if ( Pos < (*Sequence).length() )
    {
      (*Sequence)[Pos] = Value;
      RetValue = true;
    }

    return RetValue;
  }

  // return length of en CORBA Sequence
	template<typename SE>
	inline static long getLength(SE& Sequence)
	{
    return Sequence.length();
	}

	template<typename SE>
	static long getLength(SE* Sequence)
	{
    return getLength(*Sequence);
	}


  // return entry at position Pos form CORBA sequence
	template<typename V, typename SE >
	static bool getAt(V& Value, SE* Sequence, CORBA::ULong Pos)
	{
    bool RetValue = false;
    if ( Pos < (*Sequence).length() )
    {
      Value = (*Sequence)[Pos];
      RetValue = true;
    }

    return RetValue;
	}

	template<typename V, typename SE >
	inline static bool getAt(V& Value, SE& Sequence, CORBA::ULong Pos)
	{
    bool RetValue = false;
    if ( Pos < Sequence.length() )
    {
      Value = Sequence[Pos];
      RetValue = true;
    }

    return RetValue;
	}

  // convert CORBA::String_var to std::string data type regarding CORBA memory allocation
  static std::string ToStdString(CORBA::String_var varValue)
  {
    return std::string(varValue);
  }

  // convert CORBA::T* to CORBA::T data type regarding CORBA memory allocation
  template<typename T>
  static T ToCORBAType(T* pValue)
  {
    T::_var_type varValue = pValue;
    return T(varValue);
  }

  // convert sequence to CORBA::Any data type
  template<typename T>
  static CORBA::Any ToAny(T& Sequence)
  {
    CORBA::Any AnySeq;

    T Seq(Sequence);

    AnySeq <<= Seq;
    return AnySeq;
  }

  template<typename T>
  static CORBA::Any ToAny(T* Value)
  {
    CORBA::Any AnySeq;

    T Val(*Value);

    AnySeq <<= Val;
    return AnySeq;
  }

  // convert CORBA::Any to sequence data type
  template<typename T>
    static void FromAny(T& Value,CORBA::Any* AnySequence)
  {
    T* ret = 0;

    if(*AnySequence >>= ret)
    {
      Value = *ret;
    }
    else
    {
      Value.length(0);
    }
  }

  template<typename T>
    static void FromAny(T& Value,CORBA::Any AnySequence)
  {
    T* ret = 0;

    if(AnySequence >>= ret)
    {
      Value = *ret;
    }
    else
    {
      Value.length(0);
    }
  }


  template<typename T>
    static void ValueFromAny(T& Value, CORBA::Any AnySequence)
  {
    T ret;

    if(AnySequence >>= ret)
    {
      Value = ret;
    }
  }


  // read data from SourceIntf and write data to DestIntf
  // for respective DataKeys, Type and Name
	template<typename S>
  static bool readAndWrite(S SourceIntf,  
                           CData_Provider_Impl* DestIntf, 
                           const std::string& SourceKey, 
                           const std::string& DestKey, 
                           const std::string& ActType,
                           const std::string& ActName)
  {
    bool RetValue = false;

    try
    {
      if ( ActType== CIntfData::Any )
      {
        RetValue = true;
        CORBA::Any_var ActAny = SourceIntf->getAny(SourceKey.c_str(),ActName.c_str());

        if ( CIntfData::isValidAny(ActAny) )
        {
          DestIntf->setAny(DestKey.c_str(),ActName.c_str(),ActAny);
        }
        else
        {
          DestIntf->log("CORBA::Any " + ActName + " not found at " + DestIntf->getProviderName() + " with key " + SourceKey, 5);
        }
      }
      else if ( ActType == CIntfData::String )
      {
        RetValue = true;

        CORBA::String_var ActString = SourceIntf->getString(SourceKey.c_str(),ActName.c_str());

        if ( std::string(ActString).length() > 0 )
        {
          DestIntf->setString(DestKey.c_str(),ActName.c_str(), ActString );
        }
        else
        {
          DestIntf->log("CORBA::String " + ActName + " not found at " + DestIntf->getProviderName() + " with key " + SourceKey, 5);
        }
      }
      else if ( ActType == CIntfData::Bool )
      {
        RetValue = true;
        DestIntf->setBoolean(DestKey.c_str(),ActName.c_str(),SourceIntf->getBoolean(SourceKey.c_str(),ActName.c_str()));
      }
      else if ( ActType == CIntfData::Long )
      {
        RetValue = true;

        long ActLong = SourceIntf->getLong(SourceKey.c_str(),ActName.c_str());

        if ( ActLong != DEF::Inv_Long )
        {
          DestIntf->setLong(DestKey.c_str(),ActName.c_str(),ActLong);
        }
        else
        {
          DestIntf->log("CORBA::Long" + ActName + " not found at " + DestIntf->getProviderName() + " with key " + SourceKey, 5);
        }

      }
      else if ( ActType == CIntfData::Double )
      {
        RetValue = true;

        double ActDouble = SourceIntf->getDouble(SourceKey.c_str(),ActName.c_str());

        if ( ActDouble != DEF::Inv_Double)
        {
          DestIntf->setDouble(DestKey.c_str(),ActName.c_str(),ActDouble);
        }
        else
        {
          DestIntf->log("CORBA::Double " + ActName + " not found at " + DestIntf->getProviderName() + " with key " + SourceKey, 5);
        }

      }
    }
    catch(...)
    {
      DestIntf->EventLogExc("copying data","CIntfData::readAndWrite()","");
    }
    return RetValue;

  }




	template<typename S>
  static std::string getIntfDataContent(S SourceIntf,  const std::string& SourceKey)
  {
    bool RetValue = false;
    std::stringstream Content;

    try
    {
      std::vector<std:: string>::iterator itNames;
      seqIntfDataList IntfDataListSeq = ToCORBAType(SourceIntf->getIntfDataList(SourceKey.c_str()));

      for ( long i = 0 ; i < CIntfData::getLength(IntfDataListSeq) ; ++i )
      {
        sIntfDataList IntfDataListStruct;

        CIntfData::getAt(IntfDataListStruct,IntfDataListSeq,i);

        std::string ActName = IntfDataListStruct.Name;
        std::string ActType = IntfDataListStruct.Type;

        if ( ActType== CIntfData::Any )
        {
          RetValue = true;
          Content << CIntfData::getContent(CORBA::Any_var(SourceIntf->getAny(SourceKey.c_str(),ActName.c_str()))) << endl;
        }
        else if ( ActType == CIntfData::String )
        {
          RetValue = true;
          Content << "ActType" << ActType << " Name " << ActName << CORBA::String_var(SourceIntf->getString(SourceKey.c_str(),ActName.c_str() )) << endl;
        }
        else if ( ActType == CIntfData::Bool )
        {
          RetValue = true;
          Content << "ActType" << ActType << " Name " << ActName << SourceIntf->getBoolean(SourceKey.c_str(),ActName.c_str()) << endl;
        }
        else if ( ActType == CIntfData::Long )
        {
          RetValue = true;
          Content << "ActType" << ActType << " Name " << ActName << SourceIntf->getLong(SourceKey.c_str(),ActName.c_str()) << endl;
        }
        else if ( ActType == CIntfData::Double )
        {
          RetValue = true;
          Content << "ActType" << ActType << " Name " << ActName << SourceIntf->getDouble(SourceKey.c_str(),ActName.c_str()) << endl;
        }
      } // for ( long i = 0 ; i < CIntfData::getLength(IntfDataListSeq) ; ++i )
    }
    catch(...)
    {
      SourceIntf->EventLogExc("reading content","CIntfData::getIntfDataContent()","");
    }

    return Content.str();

  }


  // copy data by names of NameList from one data provider interface to another
	template<typename S>
  static bool copyIntfData(S SourceIntf,  
                           CData_Provider_Impl* DestIntf, 
                           const std::string& SourceKey, 
                           const std::string& DestKey, 
                           std::vector<std::string>   NameList)
  {
    bool RetValue = false;

    if ( SourceIntf && DestIntf )
    {
      std::vector<std:: string>::iterator itNames;
      for (itNames = NameList.begin() ; itNames != NameList.end() ; ++ itNames)
      {
        CIntfData::copyIntfData(SourceIntf,
                                DestIntf, 
                                SourceKey, 
                                DestKey, 
                                (*itNames));
      }//for (itNames = NameList.begin() ; itNames != NameList.end() ; ++ itNames)

    }

    return RetValue;
  }

  // copy data by name from one data provider interface to another
	template<typename S> // must be kind of :_var_type
  static bool copyIntfData( S SourceIntf,  
                            CData_Provider_Impl* DestIntf, 
                            const std::string& SourceKey, 
                            const std::string& DestKey, 
                            const std::string& Name = "")
  {
    // empty name is realized as "copy all"
    bool RetValue = false;
    if ( SourceIntf && DestIntf )
    {
      seqIntfDataList IntfDataListSeq = ToCORBAType(SourceIntf->getIntfDataList(SourceKey.c_str()));

      for ( long i = 0 ; i < CIntfData::getLength(IntfDataListSeq) ; ++i )
      {
        sIntfDataList IntfDataListStruct;

        CIntfData::getAt(IntfDataListStruct,IntfDataListSeq,i);

        std::string ActName = IntfDataListStruct.Name;
        std::string ActType = IntfDataListStruct.Type;

        if ( Name.empty() || Name == ActName )
        {
          RetValue = CIntfData::readAndWrite(SourceIntf,  
                                             DestIntf, 
                                             SourceKey, 
                                             DestKey, 
                                             ActType,
                                             ActName);
        }//if ( Name.empty() || Name == ActName )
      }//for ( long i = 0 ; i < CIntfData::getLength(IntfDataListSeq) ; ++i )
    }
	  return RetValue;
  }


  // check validity of CORBA::Any by assuming to be a sequence with length > 0
  static bool isValidAny(CORBA::Any &Any)
  {
    bool RetValue = false;

    if ( &Any ) 
    {
      CORBA::Object_var dynObj     = cCBS_ORB::getORB()->resolve_initial_references("DynAnyFactory");
      DynamicAny::DynAnyFactory_var dynAnyFact  = DynamicAny::DynAnyFactory::_narrow(dynObj);

      DynamicAny::DynAny_var da = dynAnyFact->create_dyn_any(Any);

      CORBA::TypeCode_var tc(da->type());
      while (tc->kind() == CORBA::tk_alias)
      {
        tc = tc->content_type();
      }

      if (tc->kind() == CORBA::tk_sequence)
      {
        //DynamicAny::DynSequence_var ds = DynamicAny::DynSequence::_narrow(da);
        //if (ds->get_length() > 0)         
        //{
          RetValue = true;
        //}
      }
      else if (tc->kind() == CORBA::tk_struct)
      {
        RetValue = true;
      }
    }
    return RetValue;
  }

	//##ModelId=40B6FFBF0279
	void log(const std::string& Message, long Level);

	//##ModelId=40B6F5FD019A
	const std::string& getName();

protected:
	//##ModelId=4149568701B0
	CData_Provider* m_pData_Provider;

	//##ModelId=410F82C70062
	std::string m_SubKey;

  //##ModelId=40D6D22C0037
  std::string m_Key;

  //##ModelId=40BF0FBB03A2
  std::string m_Type;

	//##ModelId=40B6F46601F9
	std::string m_Name;

	//##ModelId=44FE999B00DD
  bool m_isUpdated;

  bool m_isRequested;


};



#endif /* _INC_CINTFDATA_40B6F41F0192_INCLUDED */
