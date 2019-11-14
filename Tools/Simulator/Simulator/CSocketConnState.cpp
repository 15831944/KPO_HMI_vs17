
#include "stdafx.h"
#include "CSocketConnState.h"


//----------------------------------------------------------------------
CSocketConnState::CSocketConnState()
{
  InterConnListe = 0;
  ConnState = new ArrayList();
  TimerStateCheck = 0;
  ConnStateDel=0;
}
//----------------------------------------------------------------------
CSocketConnState::~CSocketConnState()
{
  if(TimerStateCheck != 0)
    TimerStateCheck->Dispose();
}
//----------------------------------------------------------------------
void CSocketConnState::setInterConnListe(CInterConnectionListe* liste)
{
  int count;
  this->InterConnListe = liste;
  ConnState->Clear();
  count = InterConnListe->getInterfaceCount();
  for(int i=0;i<count;i++)
  {
    ConnState->Add(System::Convert::ToString(0));
  }
}
//----------------------------------------------------------------------
void CSocketConnState::startConnStateCheck()
{
  System::Threading::TimerCallback* timerDelegate=0;

  timerDelegate = new System::Threading::TimerCallback(this,CSocketConnState::checkConnection); 
  TimerStateCheck = new System::Threading::Timer(timerDelegate,0,0,1000);

}
//----------------------------------------------------------------------
void CSocketConnState::checkConnection(System::Object __gc* obj)
{
   int count=0;
   bool conFlag;
   int  conFlagInt;
   int dir;
   if(ConnStateDel != 0)
   {
//     if(Direction == CInterConnectionListe::DirectionType::Sender)
  //     dir = 0;
    // if(Direction == CInterConnectionListe::DirectionType::Receiver)
      // dir = 1;
     //InterConnListe->setDirectionMode(Direction);
     count = InterConnListe->getInterfaceCount();
     if(count != ConnState->get_Count())
     {
      addNewInter(count-ConnState->get_Count());
     }
     for(int i=0;i<count;i++)
     {
       conFlagInt=System::Convert::ToInt32(ConnState->get_Item(i)); 
       conFlag=InterConnListe->isConnected(i+1);
       if(!((conFlag) && (conFlagInt == 2)))
       {
          if(conFlag)
          {
            ConnState->set_Item(i,System::Convert::ToString(2));
            ConnStateDel->Invoke(i+1,dir,2);
          }
          else
          {
            conFlag=InterConnListe->isWaiting(i+1);
            if(!((conFlag) && (conFlagInt == 1)))
            {
              if(conFlag)
              {
                ConnState->set_Item(i,System::Convert::ToString(1));
                ConnStateDel->Invoke(i+1,dir,1);
              }
              else
              {
                if(conFlagInt != 0)
                {
                    ConnState->set_Item(i,System::Convert::ToString(0));
                    ConnStateDel->Invoke(i+1,dir,0);
                }
              }
            }
          }
       }
     }

    
   }
}
//----------------------------------------------------------------------
void CSocketConnState::setDelConnStateCheck(DelConnStateCheck* del)
{
  this->ConnStateDel = del;
}
//----------------------------------------------------------------------
void CSocketConnState::addNewInter(int count)
{
  for(int i=0;i<count;i++)
  {
    ConnState->Add(System::Convert::ToString(0));
  }
}
//----------------------------------------------------------------------
/*void CSocketConnState::setDirection(CInterConnectionListe::DirectionType dir)
{
  this->Direction = dir;
}*/
//----------------------------------------------------------------------

