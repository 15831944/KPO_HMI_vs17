
#ifndef _CSocketConnState_H_
#define _CSocketConnState_H_


#include "CInterConnectionListe.h"

using namespace System;
using namespace System::Collections;
using namespace System::Threading;


__delegate void DelConnStateCheck(int inter,int direction,int status);

__gc class CSocketConnState
{
    public:
            CSocketConnState();
            ~CSocketConnState();

            void setInterConnListe(CInterConnectionListe* liste);
            void startConnStateCheck();
            void setDelConnStateCheck(DelConnStateCheck* del);
            void addNewInter(int count);
//            void setDirection(CInterConnectionListe::DirectionType dir);
    private:
            void checkConnection(System::Object __gc* obj);

            CInterConnectionListe* InterConnListe;
            ArrayList* ConnState;
            System::Threading::Timer* TimerStateCheck;
            DelConnStateCheck* ConnStateDel;
           // CInterConnectionListe::DirectionType Direction;

};


#endif