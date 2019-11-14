#include "stdafx.h"
#include "CCyclicItemContainer.h"
#include "CCyclicElemTable.h"
#include "CItemWrapper.h"
#include "CTlgElemWrapper.h"
#include "CTlgWrapper.h"
#include "CInterConnectionListe.h"
#include "CFormatConverterWrapper.h"
#include "CSendItemsServer.h"
#include "CLogWriterWrapper.h"

using namespace System;

//-------------------------------------------
CCyclicItemContainer::CCyclicItemContainer()
{
  //this->ItemTable = gcnew Collections::Hashtable();
  InterfaceTable = gcnew Collections::Hashtable();
  iterator = InterfaceTable->Keys->GetEnumerator();  
  iterator->Reset();

  lastInterName = nullptr;
  iteratorOfItem = nullptr;
  lastAddedItem = nullptr;
  Szenarium = nullptr;
  writeMessage = nullptr;
}
//-------------------------------------------
bool CCyclicItemContainer::TlgsFromInterInCyclicCon(String^ interName)
{
  if (InterfaceTable->Contains(interName))
    return true;
  else
    return false;
}
//-------------------------------------------
void CCyclicItemContainer::setWriteMessageDelTyp(WriteMessageDelTyp^ typ)
{
  writeMessage=typ;
}
//-------------------------------------------
void CCyclicItemContainer::addSzenariumPointer(CSzenarium^ szen)
{
  Szenarium=szen;
}
//-------------------------------------------
void CCyclicItemContainer::removeSzenariumPointer()
{
  Szenarium=nullptr;
}
//-------------------------------------------
CCyclicItemContainer::~CCyclicItemContainer()
{
}
//-------------------------------------------
CCyclicItemContainer^ CCyclicItemContainer::getCyclicItemContainer()
{
  if(cyclicItemContainer == nullptr)
  {
    cyclicItemContainer = gcnew CCyclicItemContainer();
  }
  return cyclicItemContainer; 
}
//-------------------------------------------
void CCyclicItemContainer::addItemToContainer (String^ interName, CItemWrapper^ item, bool isProtoItem)
{
  String^ line = nullptr;
  String^ Error = nullptr;
  CItemWrapper^ itemNew = gcnew CTlgWrapper();
  itemNew=item->clone();
	String^ mess = nullptr;
  
  if (isProtoItem && !(setIdFromConfiguration(itemNew)))
  {
    mess = String::Concat("Id for ",item->getName()," is not defined.");
		CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		if (writeMessage)
    {
      writeMessage->Invoke(mess,2); 
    }
    return;
  }

  if (!LoadFormInterConf(itemNew))
    return;
  
  line=itemNew->getSerialiseTlgAsString("|");
  Error=itemNew->fillTlg(line);
  if(Error)
  {
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,Error,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		writeMessage->Invoke(Error,2);
    return;
  }

  Collections::Hashtable^ temp = nullptr;
  //Wenn Interface schon in der HashMap exis.
  if (InterfaceTable->ContainsKey(interName))
  {
    temp = safe_cast <Collections::Hashtable^> (InterfaceTable[interName]);
  }
  else
  {
    temp = gcnew Collections::Hashtable();
    InterfaceTable->Add(interName,temp);
  }
  
  //Wenn keine Tlg mit dieser Name exis. 
  if (!temp->ContainsKey(itemNew->getName()))
  {
    try
    {
      temp->Add(itemNew->getName(),gcnew CCyclicElemTable(itemNew));
      //Szenaruim Itemsa aktualisieren
      if (Szenarium)
        Szenarium->setAllSameItemToCyclic(itemNew,true);
      lastInterName=nullptr;
    }
    catch(System::ArgumentException^ e)
    {
      String^ mess = System::String::Concat("The name of the elements is not unique. This telegram <",item->getName(),"> is not supported.");
      if (writeMessage)
        writeMessage->Invoke(mess,2); 

      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
																															  __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,e->Message,
																															  __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      removeItem(item);
      return;
    }
  }
  else
  {
    String^ mess = String::Concat("Cyclic telegram <",itemNew->getName(),"> is already existing.");
		CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
                                                           __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		if (writeMessage)
    {
      writeMessage->Invoke(mess,1); 
    }
    return;
  }
  
  lastAddedItem=itemNew;
	mess = String::Concat(itemNew->getName()," added to cyclic container.");
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
																												__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  if (writeMessage)
	{
		writeMessage->Invoke(mess,0); 
	}
}
//-------------------------------------------
bool CCyclicItemContainer::setIdFromConfiguration(CItemWrapper^ item)
{
  CInterConfigWrapper^ interConfig = gcnew CInterConfigWrapper();
  String^ valueFromConfig = interConfig->getTlgId(item->getInterfece(),item->getName());
  
  if (valueFromConfig && (valueFromConfig->Equals("") || valueFromConfig->Equals(" ")))
    return false;
  
  String^ elemIdName = interConfig->getElemId(item->getInterfece());
  int indexSubElem;
  CTlgElemWrapper^ elem = gcnew CTlgElemWrapper();
  if (item->getSubElemCount(1)>0)
  {
    indexSubElem = item->getSubElemIndex(item->getElemName(1),elemIdName); 
    elem->setTlgElem(item->getElem(1)->getSubElem(indexSubElem));
  }
  else
  {
    indexSubElem = 1;
    elem->setTlgElem(item->getElem(1));
  }
  elem->setValue(valueFromConfig,item->getInterfece());
  return true;
}
//-------------------------------------------
void CCyclicItemContainer::addItemToContainer (String^ interName, CItemWrapper^ item,CCyclicElemTable^ elemTable, bool isProtoItem)
{
  String^ line = nullptr;
  String^ Error = nullptr;
	String^ mess = nullptr;
  CItemWrapper^ itemNew = gcnew CTlgWrapper();
  itemNew=item->clone();
  
  if (isProtoItem && !(setIdFromConfiguration(item)))
  {
    mess = String::Concat("Id for ",itemNew->getName()," is not defined.");
		CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
																												__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		if (writeMessage)
    {
      writeMessage->Invoke(mess,2); 
    }
    return;
  }

  if (!LoadFormInterConf(itemNew))
    return;
  
  line=itemNew->getSerialiseTlgAsString("|");
  Error=itemNew->fillTlg(line);
  if(Error)
  {
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,Error,
																												__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		writeMessage->Invoke(Error,2);
    return;
  }

  Collections::Hashtable^ temp = nullptr;
  if (InterfaceTable->ContainsKey(interName))
  {
    temp = safe_cast <Collections::Hashtable^> (InterfaceTable[interName]);
  }
  else
  {
    temp = gcnew Collections::Hashtable();
    InterfaceTable->Add(interName,temp);
  }

  if (!temp->Contains(itemNew->getName()))
  {
    temp->Add(itemNew->getName(),elemTable);
    //Szenaruim Itemsa aktualisieren
    if (Szenarium)
      Szenarium->setAllSameItemToCyclic(item,true);
    lastInterName=nullptr;
  }
  else
  {
    mess = String::Concat("Cyclic telegram <",itemNew->getName(),"> is already existing.");
		CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
																												__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
		if (writeMessage)
    {
      writeMessage->Invoke(mess,1); 
    }
    return;
  }
  lastAddedItem=itemNew;
  mess = String::Concat(itemNew->getName()," added to cyclic container.");
  CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
																												__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
	if (writeMessage)
    writeMessage->Invoke(mess,0);
}
//---------------------------------------------
CCyclicElemTable^ CCyclicItemContainer::getElemTable(String^ interName,CItemWrapper^ item)
{
  if (InterfaceTable->Contains(interName))
  {
    Collections::Hashtable^ temp = nullptr;
    temp = safe_cast <Collections::Hashtable^> (InterfaceTable[interName]);
    if (temp->Contains(item->getName()))
    {
      return (safe_cast <CCyclicElemTable^> (temp[item->getName()]));
    }
    else
    {
      return nullptr;
    }
  }
  else
  {
    return nullptr;
  }
}
//---------------------------------------------
CCyclicElemTable^ CCyclicItemContainer::getElemTable(String^ interName,String^ itemName)
{
  if (InterfaceTable->Contains(interName))
  {
    Collections::Hashtable^ temp = nullptr;
    temp = safe_cast <Collections::Hashtable^> (InterfaceTable[interName]);
    if (temp->Contains(itemName))
    {
      return (safe_cast <CCyclicElemTable^> (temp[itemName]));
    }
    else
    {
      return nullptr;
    }
  }
  else
  {
    return nullptr;
  }
}
//---------------------------------------------
void CCyclicItemContainer::iterReset()
{
  iterator = InterfaceTable->Keys->GetEnumerator();
  iterator->Reset();
}
//---------------------------------------------
String^ CCyclicItemContainer::getNextInterface()
{
  if (iterator->MoveNext())
  {
    return safe_cast <String^> (iterator->Current);
  }
  else
  {
    iterator->Reset();
    return nullptr;
  }
}
//---------------------------------------------
CCyclicElemTable^ CCyclicItemContainer::getNextItem(String^ interName)
{
  iterator->Reset();
  /*lastInterName = 0;*/
  /*iteratorOfItem = 0;*/
  String^ StringKey=nullptr;

  Collections::Hashtable^ temp = nullptr;
  temp = safe_cast <Collections::Hashtable^> (InterfaceTable[interName]);

  if (!lastInterName || !(lastInterName->Equals(interName)))
  {
    lastInterName = interName;
    if (temp)
    {
      iteratorOfItem = temp->Keys->GetEnumerator(); 
      iteratorOfItem->Reset();
    }
    else
      return nullptr;
  }

  if (iteratorOfItem->MoveNext())
  {
    StringKey = safe_cast <String^> (iteratorOfItem->Current);
    return safe_cast <CCyclicElemTable^> (temp[StringKey]);
  }
  else
  {
    iteratorOfItem->Reset();
    return nullptr;
  }
}
//---------------------------------------------
int CCyclicItemContainer::getInterfaceCount()
{
  return InterfaceTable->Count;
}
//---------------------------------------------
CItemWrapper^ CCyclicItemContainer::getLastAddedItem()
{
  return lastAddedItem;
}
//---------------------------------------------
bool CCyclicItemContainer::isItemInContainer(CItemWrapper^ item)
{
  //Wenn Interface im Container vorkommt
  if (InterfaceTable->Contains(item->getInterfece()))
  {
    Collections::Hashtable^ temp = nullptr;
    temp = safe_cast <Collections::Hashtable^> (InterfaceTable[item->getInterfece()]);
    //Wenn Tlg im Container vorkommt
    if (temp->Contains(item->getName()))
      return true;
  }
  //Sonst  
  return false;
}
//---------------------------------------------
bool CCyclicItemContainer::removeItem(CItemWrapper^ item)
{
  //Wenn Interface im Container vorkommt
  if (InterfaceTable->Contains(item->getInterfece()))
  {
    Collections::Hashtable^ temp = nullptr;
    temp = safe_cast <Collections::Hashtable^> (InterfaceTable[item->getInterfece()]);
    //Wenn Tlg im Container vorkommt
    if (temp->Contains(item->getName()))
    {
      temp->Remove(item->getName());
      //Falls keine weitere Items exis. , Interface entfernen
      if (temp->Count==0)
        InterfaceTable->Remove(item->getInterfece());
      //Szenaruim Items aktualisieren
      if (Szenarium)
        Szenarium->setAllSameItemToCyclic(item,false);
      //Iterator neu definieren
      iteratorOfItem = temp->Keys->GetEnumerator(); 
      iteratorOfItem->Reset();
      iterReset();
    }
    else if (temp->Count == 0)
      InterfaceTable->Remove(item->getInterfece());

    //Ausgabe
    String^ mess = "Cyclic telegramm <" + item->getName() + "> from container removed.";
    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
																							            __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    if (writeMessage)
      writeMessage->Invoke(mess,0);  

    return true;
  }
  return false;
}
//--------------------------------------------------
bool CCyclicItemContainer::IsSending()
{
  if (ThreadTable)
  {
    if (ThreadTable->Count==0)
      return false;
    else
      return true;
  }
  else
    return false;
}
//--------------------------------------------------
void CCyclicItemContainer::StopAll()
{
  //HashMap mit Threads komplett durchlaufen und alle Threads beenden
  if (ThreadTable)
  {
    Collections::IEnumerator^ iter = ThreadTable->Keys->GetEnumerator();  
    iter->Reset();
    Object^ tmpObj=nullptr;
    Threading::Thread^ tmpThr=nullptr;
    String^ tmpStr=nullptr;
		String^ mess = nullptr;
    bool ok=true;

    while(iter->MoveNext())
    {
      tmpObj=nullptr;
      tmpObj=iter->Current;
      if (tmpObj)
      {
        tmpStr = safe_cast <String^>(tmpObj);
        tmpThr = safe_cast <Threading::Thread^>(ThreadTable[tmpStr]);
        tmpThr->Abort();

				mess = String::Concat("Send of ",tmpStr," stopping");
        CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
																											__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
        if (writeMessage)
          writeMessage->Invoke(mess,1);  
      }
    }//End While
    //HashMap leeren
    ThreadTable->Clear();
  }
}
//--------------------------------------------------
void CCyclicItemContainer::Send(CInterConnectionListe^ SendInterConnectionListe)
{
  String^ mess = nullptr;
  CLogWriterWrapper^ logWriter = CLogWriterWrapper::getLogWriterWrapper();
	
  if (getCountOfInterface() > 0) 
  {
    if (!IsSending())
    {
      ThreadTable = gcnew Collections::Hashtable();
      String^ interName = nullptr;
      CCyclicElemTable^ elemTable = nullptr;
      ArrayList^ tmpList = nullptr;
      Threading::Thread^ tmpThread = nullptr;
      ArrayList^ tmpInterList = gcnew ArrayList();
      //Interface Namen 
      iterReset();

      bool ok2=true;
      while(ok2)
      {
        interName = getNextInterface();
        if (interName)
          tmpInterList->Add(interName);
        else
          ok2=false;
      }
      
      for (int i=0;i<tmpInterList->Count;i++)
      {
        interName=safe_cast <String^> (tmpInterList[i]);
        ok2=true;
        while (ok2)
        {
          elemTable = getNextItem(interName);
          if (elemTable)
          {
            interName=elemTable->getInterfaceName();
            //Interval : > 0 ms.
            if (elemTable->getTimeInterval()>0)
            {
              if (SendInterConnectionListe->getInterfaceAt(SendInterConnectionListe->getInterNummber(interName))->isConnected())
              {
                //
                tmpList = gcnew ArrayList();
                //Kopie von Item
                CItemWrapper^ cpItem = nullptr;
                cpItem = gcnew CTlgWrapper();
                cpItem->setTlg(elemTable->getItem()->getClonedTlg());
                //
                tmpList->Add(cpItem);
                tmpList->Add(elemTable);
                tmpList->Add(findAllNumericElem(cpItem));
                tmpList->Add(SendInterConnectionListe->getInterfaceAt(SendInterConnectionListe->getInterNummber(interName)));
                //Cyclic Thread
                tmpThread = nullptr;
                tmpThread = gcnew Threading::Thread(gcnew Threading::ParameterizedThreadStart(this,&CCyclicItemContainer::SendCyclicItem));
                if (tmpThread)
                {
                  ThreadTable->Add(String::Concat(interName,"\\",elemTable->getItemName()),tmpThread);
                  tmpThread->Start(tmpList);
                }
              }
              else
              {
                mess = String::Concat("No connection <",elemTable->getInterfaceName(),">");
						    logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
																																		    __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
						    writeMessage->Invoke(mess,2);
              }
            }
            else
            {
              mess = String::Concat("Time interval for cyclic telegrams ",elemTable->getItemName()," is not defined");
					    logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
																																	    __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
					    if (writeMessage)
                writeMessage->Invoke(mess,2);
            }
          }
          else
          {
            ok2 = false;
          }
          elemTable=nullptr;
          
        }//end while schleife
        interName=nullptr;
      }// end for schleife
    }
    else
    {
      String^ mess = "Process of send cyclic telegrams already run";
      if (writeMessage)
        writeMessage->Invoke(mess,1);
      logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
    }
  }
  else //Wenn keine zyklische Tlg im Con drin sind
  {
    String^ mess = "No cyclic telegrams found";
    if (writeMessage)
      writeMessage->Invoke(mess,2);
    logWriter->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,__FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
  }
}
//------------------------------------------------------
void CCyclicItemContainer::SendCyclicItem(System::Object^ obj)
{
  if (obj)
  {
    ArrayList^ liste = safe_cast <ArrayList^> (obj);
    CInterConnection^ interCon = nullptr;
    CCyclicElemTable^ elemTable = nullptr;
    CItemWrapper^ cpItem = nullptr;
    ArrayList^ numListElem = nullptr;
    //Beide Objekte aus der Array Liste rausholen
    cpItem = safe_cast <CItemWrapper^> (liste[0]);
    elemTable = safe_cast <CCyclicElemTable^> (liste[1]);
    numListElem = safe_cast <ArrayList^> (liste[2]);
    interCon = safe_cast <CInterConnection^> (liste[3]);
    
    try
    {
      String^ mess = nullptr;
      CTlgElemWrapper^ tmpElem = nullptr;
      double tmpValueDouble = 0;
      String^ tmpValueString = nullptr;
      CCyclicElemStatus^ tmpElemStatus = nullptr;
      bool ok;
      DateTime before;
      int sleepTime;
      CSendItemsServer^ sendServer = CSendItemsServer::getSendItemsServer();

      if (liste->Count == 4)
      {
        int count=0;
        if (cpItem && numListElem && interCon && elemTable)
        {       
          while (interCon && interCon->isConnected())
          {
            //Zeit merken
            before = DateTime::Now;
          
            //Rundeanzahl erhöhen
            count++;

            for (int i=0;i<numListElem->Count;i++)
            {
              //Aktuelle Element Wert
              tmpElem = safe_cast <CTlgElemWrapper^>(numListElem[i]);
              tmpElem->getElemValue(tmpValueString);
              tmpValueDouble=CFormatConverterWrapper::StringToDouble(tmpValueString);
              //
              tmpElemStatus=elemTable->getElemStatus(tmpElem);
              if (tmpElemStatus->getVariabelTyp() != CCyclicElemStatus::changeTyp::none)
              {
                if (tmpElemStatus->getVariabelTyp() == CCyclicElemStatus::changeTyp::plus)
                  tmpValueDouble += tmpElemStatus->getVariabelValue();
                else if (tmpElemStatus->getVariabelTyp() == CCyclicElemStatus::changeTyp::minus)
                  tmpValueDouble -= tmpElemStatus->getVariabelValue();
                else if (tmpElemStatus->getVariabelTyp() == CCyclicElemStatus::changeTyp::multiple)
                  tmpValueDouble *= tmpElemStatus->getVariabelValue();
                else if (tmpElemStatus->getVariabelTyp() == CCyclicElemStatus::changeTyp::divide)
                  tmpValueDouble /= tmpElemStatus->getVariabelValue();
            
                //Wenn der EndValue nicht ueberschritten ist
                ok = false;
                if (tmpValueDouble>=tmpElemStatus->getMinValue() && tmpValueDouble<=tmpElemStatus->getMaxValue())
                    ok = true;
                //if (tmpElemStatus->getVariabelTyp() == CCyclicElemStatus::changeTyp::plus 
                //   || tmpElemStatus->getVariabelTyp() == CCyclicElemStatus::changeTyp::multiple)
                //{
                //  if (tmpValueDouble<=tmpElemStatus->getEndValue())
                //    ok = true;
                //}
                //else //if - or /
                //{
                //  if (tmpValueDouble>=tmpElemStatus->getEndValue())
                //    ok = true;
                //}
           
                if (ok)
                {
                  if (tmpElem->getElemType()->Equals("Double") || tmpElem->getElemType()->Equals("Float"))
                    tmpElem->setValue(CFormatConverterWrapper::DoubleToString(tmpValueDouble),cpItem->getInterfece());
                  else if (tmpElem->getElemType()->Equals("Integer") || tmpElem->getElemType()->Equals("ShortInteger"))
                    tmpElem->setValue(CFormatConverterWrapper::IntToString((int)tmpValueDouble),cpItem->getInterfece());
                }
              }//End If None
            }//End For Scheife

            //Zeit vergleichen und eventuell Thread Sleep
            sleepTime = elemTable->getTimeInterval() - System::DateTime::Now.Subtract(before).TotalMilliseconds;
            if (sleepTime > 0)
              Threading::Thread::CurrentThread->Sleep(sleepTime);
            else
            {
              //Warnung Verzögerung
              mess = String::Concat("Delay time of cyclic telegram",elemTable->getItemName(),"is wrong");
					    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Warning,mess,
																																	    __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
					    if (writeMessage)
                writeMessage->Invoke(mess,1);
            }
				    //Senden
            if (interCon)
              sendServer->sendCyclicItem(interCon,cpItem);
            else
            {
              //Fehlermeldung
            }
          }//End While
          if (interCon && !interCon->isConnected())
			    {
            mess = String::Concat("No connection <",elemTable->getInterfaceName(),">");
				    CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Error,mess,
																											    __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
				    if (writeMessage)
              writeMessage->Invoke(mess,2);
			    }
        }
        else
          return;
      }
      else
        return;
    }
    catch (Threading::ThreadAbortException^ e)
    {
      String^ mess = String::Concat("Thread for cyclic telegramm <",cpItem->getName(),"> aborted");
      CLogWriterWrapper::getLogWriterWrapper()->WriteMessage(CLogWriterWrapper::MessTyp::Info,mess,
																											    __FILE__,__FUNCTION__,__LINE__,gcnew Diagnostics::StackTrace(true),3);
      System::Threading::Thread::CurrentThread->ResetAbort();
      return;
    }
  }
}
//-----------------------------------------
ArrayList^ CCyclicItemContainer::findAllNumericElem (CItemWrapper^ item)
{
  ArrayList^ liste = gcnew ArrayList();
  int count = item->getTlgElemCount();
  CTlgElemWrapper^ elem = nullptr;
  //Elemente 
  for (int j=1;j<=count;j++)
  {
    elem = gcnew CTlgElemWrapper();
    elem->setTlgElem(item->getElem(j)); 

    if (elem->getSubElemCount() > 0)
      findAllNmericSubElem(elem,liste);
	  else if (elem->getElemType()->Equals("Double") || elem->getElemType()->Equals("Float")
			|| elem->getElemType()->Equals("Integer") || elem->getElemType()->Equals("ShortInteger"))
      liste->Add(elem);
  }
  return liste;
}
//-----------------------------------------
void CCyclicItemContainer::findAllNmericSubElem (CTlgElemWrapper^ elem, ArrayList^ liste)
{
  for (int j=1;j<=elem->getSubElemCount();j++)
  {
    CTlgElemWrapper^ elemSub = gcnew CTlgElemWrapper();
    elemSub->setTlgElem(elem->getSubElem(j));
    
    if (elemSub->getSubElemCount()>0)
      findAllNmericSubElem(elemSub,liste);
    else if (elemSub->getElemType()->Equals("Double") || elemSub->getElemType()->Equals("Float")
			|| elemSub->getElemType()->Equals("Integer") || elemSub->getElemType()->Equals("ShortInteger"))
      liste->Add(elemSub);
  }
}
//-----------------------------------------
int CCyclicItemContainer::getCountOfInterface()
{
  return InterfaceTable->Count;
}
//------------------------------------------------------------------------------
bool CCyclicItemContainer::LoadFormInterConf (CItemWrapper^ item)
{  
  //Interface Konfiguration
  CInterConfigWrapper^ interConf = gcnew CInterConfigWrapper();
  //Einige Einstellungen aus Interface - Konfigutiuion
  String^ ItemLenId = interConf->getElemLenId(item->getInterfece());
  int LenIdModus = interConf->getLenIdTreatModus(item->getInterfece());
  int indexSubElem;
  CTlgElemWrapper^ elem = gcnew CTlgElemWrapper();
  if (item->getSubElemCount(1)>0)
  {
    indexSubElem = item->getSubElemIndex(item->getElemName(1),ItemLenId); 
    elem->setTlgElem(item->getElem(1)->getSubElem(indexSubElem));
  }
  else
  {
    indexSubElem = item->getElemIndex(ItemLenId);
    elem->setTlgElem(item->getElem(indexSubElem));
  }

  if(LenIdModus == 1)
    elem->setValue(System::Convert::ToString(item->getTlgTransBytesCount()),item->getInterfece());
  else if(LenIdModus == 2)
    elem->setValue(System::Convert::ToString(item->getTlgBodyTransBytesCount()),item->getInterfece());

  
  return true;
  /* if (isItemEmpty && LenIdModus !=3)
  {
    itemElem->setValue(safe_cast <System::String^> (obj[1]),this->Item->getName());
  }*/
}