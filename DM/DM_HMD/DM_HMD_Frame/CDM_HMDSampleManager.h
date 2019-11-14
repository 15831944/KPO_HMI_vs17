// Copyright (C) 2007 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CDM_HMDSAMPLEMANAGER_4164FDA9006D_INCLUDED
#define _INC_CDM_HMDSAMPLEMANAGER_4164FDA9006D_INCLUDED

#include "CDM_SampleManager.h"
#include "CSampleCode.h"

typedef struct _struSampleInformationData
{
  long SampleType;
  long SampleNo;
  std::string Plant;
  std::string ProcessStage;
} sSampleInformationData;


class CDM_HMDProductManagementInterface_Impl;
class CEventMessage;

//##ModelId=45139A710383
class CDM_HMDSampleManager : public CDM_SampleManager
{
public:

	//##ModelId=45139A71038B
	virtual ~CDM_HMDSampleManager();

	//##ModelId=45139A71038D
	CDM_HMDSampleManager();

	std::string m_DefaultProcessStage;
	void setDefaultProcessStage(const std::string& value);
	std::map<std::string,std::string> m_ProcessStageEventList;
	void insertProcessStage(const std::string& EventMessage, const std::string& Stage);
	void insertType(const std::string& EventMessage,  long Type);
	std::map<std::string,long> m_SampleTypeEventList;
	std::string getActSampleCode(const std::string& ProductID, long SampleType   );
	CSampleCode m_FormattedSampleCode;
	std::string getPlantId(const std::string& SampleCode);
	std::string getProductProcessStage(const std::string& ProductID);
	long getProductSampleNo(const std::string& ProductID, long Type);
	std::multimap<std::string,sSampleInformationData> m_ProductSampleInformationList;
	std::string getProcessStage(const std::string& SampleCode);

	std::string getSampleCode( long SampleType, const std::string PlantID, long PlantNo, const std::string ProcessStage, long SampleNo);


	std::string getSampleCode( long SampleType, const std::string PlantID, const std::string ProcessStage, long SampleNo);
	std::string getSampleCode( long SampleType, const std::string Location, long SampleNo);
	std::string getPlant(const std::string& ProductID, long Type);
	void init();
	long m_MaxSampleNo;
	void log(const std::string& Message, long Level);
	  void showContent(const std::string& ProductID);
		void initProductSampleInformation(const std::string& ProductID, const std::string& Plant);

		void removeProcessStages(const std::string& ProductID);
		void deleteProductSampleInformation(const std::string& ProductID);
		std::vector<long> m_SampleTypeList;

protected:

	//##ModelId=45139A71038E
  std::string createSampleCodeFromScratch(std::string& ProductID, long ActProbeType, const std::string ActPlantID, const std::string ActProcessStage, long ActSampleCounter);

		//##ModelId=45139A710394
  

};

#endif /* _INC_CDM_HMDSAMPLEMANAGER_4164FDA9006D_INCLUDED */
