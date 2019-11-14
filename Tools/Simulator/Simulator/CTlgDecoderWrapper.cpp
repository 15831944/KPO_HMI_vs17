
#include "stdafx.h"
#include "CTlgDecoderWrapper.h"
#include "CStdConverter.h"
#include "CLogWriterWrapper.h"
//----------------------------------
CTlgDecoderWrapper::CTlgDecoderWrapper()
{
  //TlgDecoder = gcnew CTlgDecoder();
}
//----------------------------------
CTlgDecoderWrapper::~CTlgDecoderWrapper()
{
  //delete TlgDecoder;
}

//----------------------------------
void CTlgDecoderWrapper::setTlgProtoTypSet(CTlgInterfaceWrapper^ protoWr)
{
	//this->TlgDecoder->setTlgPrototypSet(protoWr->getTlgProtoTypSet());
}
//----------------------------------
/*void CTlgDecoderWrapper::setTlgFactory(CBaseTlgFactoryWrapper* TlgFactory)
{
  BaseFactory = TlgFactory;
  //TlgDecoder->setFactory(TlgFactory->getFactory());
}*/
//----------------------------------
void CTlgDecoderWrapper::buildTlg(char* buffer,int count)
{
	//TlgDecoder->decodeTlg(buffer,count);
}
//----------------------------------
int CTlgDecoderWrapper::getTlgCount()
{
 	//return TlgDecoder->getTlgCount()
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,
                                                        "This methode is not implement in this clas",
                                                        __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  return 0;
}
//----------------------------------
CTlgWrapper^ CTlgDecoderWrapper::getNextTlg()
{
  CTlgWrapper^ tlgWr=nullptr;
  CTlg* tlg=nullptr;

  //  tlg = TlgDecoder->getNextTlg();
  //if(tlg != 0)
  //{
	  //tlgWr = gcnew CTlgWrapper();
	  //tlgWr->setTlg(tlg);
  //}

  return tlgWr;
}
//----------------------------------