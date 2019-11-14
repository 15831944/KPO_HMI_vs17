// Copyright (C) 2006 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CCCS_TELEGRAMHANDLER_4582D1DA00B8_INCLUDED
#define _INC_CCCS_TELEGRAMHANDLER_4582D1DA00B8_INCLUDED

#include <string>
#include "CDH_IN_Task.h"
#include "CTelegram_Handler.h"
#include "CDataConversion.h"

#include "iSMC_DataDefinitions_s.hh"
#include "iEventMessages_s.hh"
#include "Telcom_in_s.hh"

#include "CGC_SourceContainer.h"
#include "CGC_Charge_Dest_Container.h"
#include "CGC_Recipe_L1Container.h"
#include "CGC_Plantgroup_Container.h"

#include "CGT_MAT_PURP.h"
#include "CGCL_STIRR_INT.h"
#include "CGT_PARAM.h"
#include "CPD_MAT_AVAIL.h"
#include "CPP_ORDER.h"
#include "CPP_HEAT.h"
#include "CPP_HEAT_PLANT.h"

//##ModelId=4582D1DA00B8
class CCCS_TelegramHandler 
: public CTelegram_Handler
{
public:
	//##ModelId=4582D1FF01C8
	CCCS_TelegramHandler();

	//##ModelId=4582D2030393
	virtual ~CCCS_TelegramHandler();

	virtual bool doOnComplete(const std::string& Key, const std::string& TlgName);

  void handleTelegram(const std::string& Key, const std::string& TlgName);

protected:
  CGC_Plantgroup_Container*  m_pGC_Plantgroup_Container;
  CGC_Charge_Dest_Container* m_pGC_Charge_Dest_Container;
  CGC_SourceContainer*       m_pGC_SourceContainer;
  CGC_Recipe_L1Container*    m_pGC_Recipe_L1Container;

private:

  void SendEventMessage(const std::string& Key, 
                        const std::string& TlgName,
                        const std::string& DataKey,
                        const std::string& PlantId,
                        const std::string& HeatNo,
                        const std::string& TreatId,
                        bool isPlantEvent);



  bool DoProcessCCSHeatStatus(const std::string& Key, const std::string& TlgName);

};

#endif /* _INC_CCCS_TELEGRAMHANDLER_4582D1DA00B8_INCLUDED */
