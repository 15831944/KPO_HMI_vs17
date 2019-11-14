
#ifndef _CTlgInterRec_H_
#define _CTlgInterRec_H_

#include "CTlgBaseContainerWrapper.h"
//#include "CTlgDecoderWrapper.h"
#include "CInterConnectionListe.h"
//#include "CBaseTlgFactoryWrapper.h"

using namespace System;


__delegate void DelNewTlg(void);

__gc class CTlgInterRec
{
    public:
          CTlgInterRec();
          ~CTlgInterRec();
          
          void setInterConnListe( CInterConnectionListe* liste,int index);
		 // void setBaseTlgFactory( CBaseTlgFactoryWrapper* BaseTlgFactory);
          void receiveTlg();
		  void setEventNewTlg(DelNewTlg* event);
       int getTlgCount();
       CTlgWrapper* getTlg(int index);
        CTlgBaseContainerWrapper* getTlgContainer();
     // void updateTlgView();

    private:

           void receive();

           CTlgBaseContainerWrapper* TlgContainer;
//           CTlgDecoderWrapper*   TlgDecoder;
           System::Threading::Thread* ThreadRec;
           CInterConnectionListe* InterConnectionListe;
//		   CBaseTlgFactoryWrapper* BaseTlgFactory;

           int InterIndex;

		   DelNewTlg* NewTlgEvent;

         
};


#endif