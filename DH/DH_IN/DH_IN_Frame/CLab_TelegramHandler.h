// Copyright (C) 2006 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CLAB_TELEGRAMHANDLER_4582CC7F00DA_INCLUDED
#define _INC_CLAB_TELEGRAMHANDLER_4582CC7F00DA_INCLUDED

#include "CTelegram_Handler.h"

//class CPP_HEAT;
//class CPP_HEAT_PLANT;
//class CPD_LADLE_ANL;
//class CPD_LADLE_DATA;
//class CChem_Elem_Container;
//class CGC_Plant_Container;

//##ModelId=4582CC7F00DA
class CLab_TelegramHandler 
: public CTelegram_Handler
{
public:
	//##ModelId=4582CFC1028E
	CLab_TelegramHandler();

	//##ModelId=4582CFC5032B
	virtual ~CLab_TelegramHandler();

	//##ModelId=458692160327
	virtual bool doOnComplete(const std::string& Key, const std::string& TlgName);

  void fillAnalysisSequence(seqAnalysis &SeqAnalysis, const std::string& Element, double Concentration);

  void SendEventMessage(const std::string& Key, const std::string& TlgName, const std::string& DataKey, const std::string& PlantId, const std::string& HeatId, const std::string& TreatId, bool isPlantEvent);

  bool DoProcessLABSMC01IsAlive(const std::string& Key, const std::string& TlgName);
  bool DoProcessLABSMC02SteelAnalysis(const std::string& Key, const std::string& TlgName);
  bool DoProcessLABSMC03SlagAnalysis(const std::string& Key, const std::string& TlgName);

private:

protected:
  
};

#endif /* _INC_CLAB_TELEGRAMHANDLER_4582CC7F00DA_INCLUDED */