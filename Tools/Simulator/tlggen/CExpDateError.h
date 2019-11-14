// Copyright 2006 SMS - Demag AG
#ifndef _CExpDateError_H_
#define _CExpDateError_H_

#include "CExpBaseTimeError.h" 
#include <string>

//------------------------------------------------------
// Name:  CExpDateError.h
// Descr: Mit dieser Klasse werden Fehler in Datumformat behandeln     
// Date:
// Autor: Emeljanov Anatolij 
//------------------------------------------------------

//##ModelId=4404D3B40187
class CExpDateError : public CExpBaseTimeError
{
  public:
	  //##ModelId=4404D3B40196
    CExpDateError(const std::string& format,const std::string& date);
	  //##ModelId=4404D3B40199
    ~CExpDateError();
	  //##ModelId=4404D3B4019A
    const std::string& getDate();
  private:
		//! fehlerhafte Datum
	  //##ModelId=441B3AF00222
    std::string Date;
};
#endif
