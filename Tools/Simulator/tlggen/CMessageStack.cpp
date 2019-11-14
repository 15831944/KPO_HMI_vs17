// Copyright 2006 SMS - Demag AG

//-----------------------------------------------
#include "CMessageStack.h"
//-----------------------------------------------
CMessageStack::CMessageStack()
{

}
//-----------------------------------------------
CMessageStack::~CMessageStack()
{

}
//-----------------------------------------------
CMessageStack* CMessageStack::getMessageStack()
{
  if(MessageStack == 0)
  {
    MessageStack = new CMessageStack();
    MessageStack->clearMessage();
  }
  return MessageStack;
}
//-----------------------------------------------
void CMessageStack::clearMessage()
{
  MessStack.clear();
  MessType.clear();
  ActMess = 0;
}
//-----------------------------------------------
void CMessageStack::addMessage(const std::string& mess,int type)
{
  MessStack.push_back(mess);
  MessType.push_back(type);
}
//-----------------------------------------------
bool CMessageStack::getActMessage_(std::string& mess,int* type)
{
  bool ret = false;
  if(ActMess < int(MessStack.size()))
  {
    mess = MessStack[ActMess];
    (*type) = MessType[ActMess];
    ActMess++;
   ret = true;
  }
  return ret;
}

//-----------------------------------------------

bool CMessageStack::getActMessage(std::string& mess,int* type)
{
  bool ret = false;
  ret =  getActMessage_ (mess,type);
  return ret;
}
//-----------------------------------------------
CMessageStack* CMessageStack::MessageStack = 0; 
//-----------------------------------------------
