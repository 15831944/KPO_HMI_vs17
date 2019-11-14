
#ifndef _CTlgDecoderWrapper_H_
#define _CTlgDecoderWrapper_H_

//---------------------------------------------------
#include "CTlgWrapper.h"
//#include "CTlgDecoder.h"
#include "CTlgInterfaceWrapper.h"
//---------------------------------------------------
using namespace System;
//---------------------------------------------------

public ref class CTlgDecoderWrapper
{
    public:
          CTlgDecoderWrapper();
          ~CTlgDecoderWrapper();
          void buildTlg(char* buffer,int count);
          //void setTlgFactory(CBaseTlgFactoryWrapper* TlgFactory);
		  int getTlgCount();
		  CTlgWrapper^ getNextTlg();
		  void setTlgProtoTypSet(CTlgInterfaceWrapper^ protoWr);
    private:
          //CBaseTlgFactoryWrapper* BaseFactory;
          //CTlgDecoder* TlgDecoder;

          
         
};


#endif