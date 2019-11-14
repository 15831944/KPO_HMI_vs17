// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CTELCOM_OUTEVENTHANDLER_45ABB3D40099_INCLUDED
#define _INC_CTELCOM_OUTEVENTHANDLER_45ABB3D40099_INCLUDED

//#include "cbs.h" ffra:11/10/2018 as per Hadeed project
#include "cCBS_ORB.h"
#include "corba.h"
#include "CEventHandler.h"
#include "Telcom_Out_factory.h"
#include "iDH_Telcom_s.hh"
#include "telcom.h"
#include "cCBS_StdLog_Task.h"

class CTelcom_QueueManager;
class CTelcom_OutProt;
///////////////////////////////////////////////
//
//In this class we handle received events.
//Construct the required telegram, 
//fetch the necessary data from data provider 
//and put it into the send queue.
//
///////////////////////////////////////////////
//##ModelId=45ABB3D40099
class CTelcom_OutEventHandler : public CEventHandler
{
private:
	//##ModelId=45B4E4B802B5
	CTelcom_OutProt * m_pProtocol;

	//##ModelId=45AFA1A103AF
	Telcom_Out_factory m_TlgFactory;

  CORBA::Any_var m_ActAny;

public:
	//##ModelId=45B4E56F01DF
	void setProtocol(CTelcom_OutProt* value);

	//##ModelId=45AF9E3103DB
	void setQueueManager(CTelcom_QueueManager* value);

	//##ModelId=45ABB42F033E
	CTelcom_OutEventHandler();

	//##ModelId=45ABB4300156
	virtual ~CTelcom_OutEventHandler();

	//##ModelId=45ABB43D0013
	virtual bool handleEvent(const FRIESEvent& Event);

protected:

	//##ModelId=45AF9E00021B
	CTelcom_QueueManager* m_pQueueManager;

	//##ModelId=45AF359D011B
	DH_Telcom::iDH_Telcom_var   m_pDataHandler;

	//Container of telegram names that should be sended.
	//##ModelId=45ABB67001B1
    std::set<std::string> m_TelList;
    
    long m_TelegramOffsetTime;

public:
	//Construct the required telegram, 
	//fetch the necessary data from data provider 
	//and put it into the send queue.
	//##ModelId=45ABB6A502F5
	bool handleEvent(const CEventMessage& Message);

protected:

	//##ModelId=45ABB6A50313
  bool collectTelegramData(const std::string& DataKey, Tlg& theTlg);

	//Reading value for an tlg element from DH
	//##ModelId=45ABB6A5033B
	bool getElementValue(const std::string& TlgName, const std::string& DataKey, TlgElem& te, int TlgElemIndex);


	template<typename SE>
    static bool getElementValue(SE& Sequence, TlgElem& te, int TlgElemIndex, DynamicAny::DynAnyFactory_var DynAnyFact = 0)
  {
    bool RetValue = true;

    if(!DynAnyFact)
    {
      // Get a Factory for DynAny
      /*CORBA::Object_var dynObj = CBS::getORB()->resolve_initial_references("DynAnyFactory");*///ffra: 11/10/2018 :Changed as per hadeed
		CORBA::Object_var dynObj = cCBS_ORB::getORB()->resolve_initial_references("DynAnyFactory");
      DynAnyFact               = DynamicAny::DynAnyFactory::_narrow(dynObj);
    }

    DynamicAny::DynAny_var da = DynAnyFact->create_dyn_any (Sequence);
    CTelcom_OutEventHandler::getDynContent(da, te, TlgElemIndex);

    return RetValue;
  }

  // extracting metadata and write to output stream
  // might be called recursively !
	//##ModelId=44FE999B0047
  static bool getDynContent(DynamicAny::DynAny_ptr da, TlgElem& te, int TlgElemIndex)
  {
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
      cCBS_StdLog_Task::getInstance()->log("the ANY contains a data type that is not (yet) handled", 1);
      break;
    //
    // First the primitives: straight output of the data.
    // --------------------------------------------------
    case CORBA::tk_short:
      {
        long value = da->get_short();
        te.set(value);
      }
      break;
    case CORBA::tk_ushort:
      {
        long value = da->get_ushort();
        te.set(value);
      }
      break;
    case CORBA::tk_long:
      {
        te.set(da->get_long());
      }
      break;
    case CORBA::tk_ulong:
      {
        long value = da->get_ulong();
        te.set(value);
      }
      break;
    case CORBA::tk_boolean:
      {
        te.set(da->get_boolean());
      }
      break;
    //case CORBA::tk_char:  // print in <> brackets to distinguish blank from "nothing".
    //  te.set(CORBA::String_var(da->get_char()));
    //  break;
    case CORBA::tk_double:
      {
        te.set(da->get_double());
      }
      break;
    case CORBA::tk_float:
      {
        te.set(da->get_float());
      }
      break;
    case CORBA::tk_string:
      {
        te.set(CORBA::String_var(da->get_string()));
      }
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

        bool doIteration = true;

        long Index = te.getIndex();

        if ( ds->seek(Index) )
        {
          DynamicAny::DynAny_var cm(ds->current_component());
          CORBA::String_var       memName(ds->current_member_name());

          std::string ActMemberName(memName);

          if ( ActMemberName == te.getName() )
          {
            CTelcom_OutEventHandler::getDynContent(cm, te, Index);     // recurse into sequence 
            doIteration = false;
          }
        }

        if ( doIteration )
        {
          for (unsigned long ii=0; ii<lv_tc->member_count(); ++ii)       // parse the entire struct
          {
            DynamicAny::DynAny_var  cm(ds->current_component());
            CORBA::String_var       memName(ds->current_member_name());

            std::string ActMemberName(memName);

            if ( ActMemberName == te.getName() )
            {
              CTelcom_OutEventHandler::getDynContent(cm,te, ii);       // recurse into struct
              break;
            }

            ds->next();
          }
        }
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
          CTelcom_OutEventHandler::getDynContent(cm,te,ii);            // recurse into array
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
          cCBS_StdLog_Task::getInstance()->log("empty sequence",2);
        }
        else                                                  // not empty
        {
          if ( ds->seek(TlgElemIndex) )
          {
            DynamicAny::DynAny_var cm(ds->current_component());

            CTelcom_OutEventHandler::getDynContent(cm, te, TlgElemIndex);     // recurse into sequence 
          }

          //for (unsigned long ii=0; ii<ds->get_length(); ++ii)
          //{
          //  if ( ii == TlgElemIndex )
          //  {
          //    DynamicAny::DynAny_var cm(ds->current_component());

          //    CTelcom_OutEventHandler::getDynContent(cm, te, ii);     // recurse into sequence 
          //  }

          //  ds->next(); 

          //}

        }                                                     // empty/not empty
      } // almost the end of case
      break;
    }

    return true;
  }


};

#endif /* _INC_CTELCOM_OUTEVENTHANDLER_45ABB3D40099_INCLUDED */
