// Copyright (C) 2004 SMS Demag AG

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif
#ifndef _INC_CSAMPLECODE_437495FD00E3_INCLUDED
#define _INC_CSAMPLECODE_437495FD00E3_INCLUDED

#include <string>
#include <map>
#include <set>
#include <vector>

#include "CFormattedID.h"

class CCFormattedIDElement;

//##ModelId=437495FD00E3
class CSampleCode : public CFormattedID
{
public:

  std::string getLocation(const std::string& SampleCode);

	//##ModelId=43F2F3730343
	std::string getSampleID(long SampleType  , const std::string PlantID, const std::string ProcessStage);

	//##ModelId=43F2F2D70027
	std::string generateSampleID(long SampleType  , const std::string PlantID, const std::string ProcessStage);

	//##ModelId=44FE9C2D01F2
	std::string getSampleCode(long SampleType, const std::string PlantID, long PlantNo, const std::string ProcessStage, long Counter);

	//##ModelId=43F2130E0398
	std::string getSampleCode(long SampleType  , const std::string PlantID, const std::string ProcessStage, long Counter);

  //##
  std::string getSampleCode(long SampleType, long Counter, const std::string Location);

	std::string getSampleCode(long SampleType, const std::string PlantID, const std::string ProcessStage, long Counter, const std::string Location);


	//##ModelId=439EA5F10129
	long getCounterLength();

	//##ModelId=437B44B90312
	std::string getSampleIDFromCode(const std::string& SampleCode);

	//##ModelId=437A11FA0139
	long getCounter(const std::string& SampleCode);

	//##ModelId=437A11A80203
	long getSampleType(const std::string& SampleCode);

	//##ModelId=437A11BD0256
	std::string getPlantId(const std::string& SampleCode);

	//##ModelId=44FE9C2D026A
  long getPlantNo(const std::string& SampleCode);

  //##ModelId=437A11CD00AC
	std::string getProcessStage(const std::string& SampleCode);

	//##ModelId=4379C47C00A8
	long getMaxCounter();

	//##ModelId=437497C501B0
	std::string getSampleID(const std::string SampleType, const std::string PlantID, const std::string ProcessStage);

	//##ModelId=4374983203C4
	std::string getSampleCode(const std::string SampleType, const std::string PlantID, const std::string ProcessStage, long Counter , const std::string Location);

	//##ModelId=43749889021B
	virtual ~CSampleCode();

	//##ModelId=4374988A0070
	CSampleCode();

	//##ModelId=44FE9C2D0292
	void reset();

protected:
	//##ModelId=439EDC1D0358
	virtual void init();

	//##ModelId=4379A768000E
	static std::string m_QualifierSeparator;

	//##ModelId=43749B5D00A4
	static std::string m_QualifierSampleType;

	//##ModelId=43749B7B026D
	static std::string m_QualifierPlantID;

	//##ModelId=44FE9C2D02BB
	static std::string m_QualifierPlantNo;

  //##ModelId=43749B8700BE
	static std::string m_QualifierProcessStage;

	//##ModelId=43749B93009E
	static std::string m_QualifierCounter;

  static std::string m_QualifierLocation;


private:
	//##ModelId=43F213B7039B
	std::string generateSampleCode(long SampleType, const std::string PlantID, const std::string ProcessStage, long Counter , const std::string Location);

	//##ModelId=44FE9C2D02E2
	std::string generateSampleCode(long SampleType, const std::string PlantID, long PlantNo, const std::string ProcessStage, long Counter , const std::string Location);

  //##ModelId=43785AA1022A
	std::string generateSampleID(const std::string SampleType, const std::string PlantID, const std::string ProcessStage);

	//##ModelId=43785AAC0317
	std::string generateSampleCode(const std::string SampleType, const std::string PlantID, const std::string ProcessStage, long Counter , const std::string Location);

  std::string generateSampleCode(long SampleType, long Counter, const std::string Location);

	//##ModelId=43749CA60140
	std::string m_SampleCode;

	//##ModelId=43749CAD0259
	std::string m_SampleID;

};

#endif /* _INC_CSAMPLECODE_437495FD00E3_INCLUDED */
