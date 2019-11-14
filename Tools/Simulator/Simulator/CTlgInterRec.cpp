
#include "stdafx.h"
#include "CTlgInterRec.h"


//--------------------------------------------------------------
CTlgInterRec::CTlgInterRec()
{
//  TlgContainer = new CTlgContainerWrapper();
//  TlgDecoder = new CTlgDecoderWrapper();
   ThreadRec = 0;
   InterIndex=-1;
   InterConnectionListe=0;
   NewTlgEvent=0;
}
//--------------------------------------------------------------
CTlgInterRec::~CTlgInterRec()
{
  if(ThreadRec != 0)
    ThreadRec->Abort();
}
//--------------------------------------------------------------
void CTlgInterRec::receiveTlg()
{
  System::Threading::ThreadStart* ThSt = new System::Threading::ThreadStart(this,CTlgInterRec::receive);

  ThreadRec = new System::Threading::Thread(ThSt);
  ThreadRec->Start();
}
//--------------------------------------------------------------
void CTlgInterRec::setInterConnListe( CInterConnectionListe* liste,int index)
{
  this->InterConnectionListe = liste;
  this->InterIndex = index;
}
//--------------------------------------------------------------
void CTlgInterRec::receive()
{
  char buffer[200];
  int len;
  int count,i;
  CTlgWrapper* tlgWr=0;
  bool flag;
  bool upFlag;
   
  flag = true;
  while(flag)
  {
    //test connection 
    len=InterConnectionListe->receiveByteStream(buffer,200,InterIndex);
	if(len>0)
	{
		//TlgDecoder->buildTlg(buffer,len);
    upFlag=false;
		//while((tlgWr = TlgDecoder->getNextTlg()) != 0)
		//{
			//add to Container
//      TlgContainer->addTlgToContainer(tlgWr);
			upFlag=true;
		//}
    //event to Receiver
    //System::Windows::Forms::Control* con = new System::Windows::Forms::Control();
    //con->Invoke(NewTlgEvent);
    //con->
    //::Invoke( NewTlgEvent);
     if(upFlag)
			 NewTlgEvent->Invoke();
		
	}
  }


}
//--------------------------------------------------------------
//void CTlgInterRec::setBaseTlgFactory( CBaseTlgFactoryWrapper* BaseFactory)
//{
//	this->BaseTlgFactory = BaseFactory;
 // TlgDecoder->setTlgFactory(BaseTlgFactory);
//}
//--------------------------------------------------------------
void CTlgInterRec::setEventNewTlg(DelNewTlg* event)
{
	this->NewTlgEvent=event;
}
//--------------------------------------------------------------
 int CTlgInterRec::getTlgCount()
 {
   return TlgContainer->getTlgCount();
 }
//--------------------------------------------------------------
 CTlgWrapper* CTlgInterRec::getTlg(int index)
 {
    CTlgWrapper* tlgWr = new CTlgWrapper();
    TlgContainer->getTlg(tlgWr,index);

    return tlgWr;
 }
//---------------------------------------------------------------
CTlgBaseContainerWrapper* CTlgInterRec::getTlgContainer()
{
  return TlgContainer;
}
//---------------------------------------------------------------
// void CTlgInterRec::updateTlgView()
 //{
   //int count;
   //CTlgWrapper* tlgWr=new CTlgWrapper();
   //count=TlgContainer->getTlgCount();
   //TlgContainer->getTlg(tlgWr,count);

 //}
//--------------------------------------------------------------

