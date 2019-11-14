
#ifndef _CSendItemsServer_H_
#define _CSendItemsServer_H_

#include "CSzenItem.h"
#include "CInterSenderManager.h"
#include "CSzenItem.h"

using namespace System;
//using namespace simulator;

public ref class CSendItemsServer
{
  public: delegate void MessageHandlerTyp(String^ mess,int type);
  
  public:

    enum class Priority 
	  {
		  low,
      normal,
		  high
		};

    value struct WaitItemToSend 
	  {
      CInterSenderManager^ inter;
      CSzenItem^ item;
      Priority itemPriority;
      
      WaitItemToSend(CInterSenderManager^ i,CSzenItem^ it,Priority pri)
      {
        inter = i;
        item = it;
        itemPriority = pri;
      }
		};

    void addItemtoSend(CInterSenderManager^ inter,CSzenItem^ item,Priority priority);
    void sendCyclicItem(CInterConnection^ inter,CItemWrapper^ item);
    void sendSzenItem(CInterConnection^ inter,CItemWrapper^ item,bool cyclicItem);
    static CSendItemsServer^ getSendItemsServer();
    void sendSzenItem(CInterSenderManager^ inter,CSzenItem^ item);
    void setMessageHandler(MessageHandlerTyp^ handler);
    ~CSendItemsServer();
    
  protected:
    CSendItemsServer();
  private:
    Collections::ArrayList^ itemsList;
    static CSendItemsServer^ sendItemsServer=nullptr;
    MessageHandlerTyp^ MessageHandler;

    int Send(unsigned char* buffer, int len,CInterConnection^ interCon);
};

#endif