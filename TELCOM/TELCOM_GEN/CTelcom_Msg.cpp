// Copyright (C) 2007 SMS Demag AG

#include "CTelcom_Msg.h"
#include <sstream>




//##ModelId=45B0DE2F03B0
long CTelcom_Msg::GlobalCounter = 0;

//##ModelId=45AB998A02BE
CTelcom_Msg::CTelcom_Msg() : m_IamNo(0)
{
  if (GlobalCounter > 65534)
    GlobalCounter = 0;

  ++GlobalCounter;
  m_IamNo = GlobalCounter;

}

//##ModelId=45AB998B0180
CTelcom_Msg::~CTelcom_Msg()
{
  if (m_pTlg)
    delete m_pTlg;
}

//##ModelId=45B0D9D700C1
std::string CTelcom_Msg::getType()
{
  return m_MsgType;
}

//##ModelId=45B0D9D700F3
void CTelcom_Msg::setType(std::string& value)
{
  m_MsgType = value;
}

//##ModelId=45B0D9D7012F
Tlg* CTelcom_Msg::getTlg()
{
  return m_pTlg;
}

//##ModelId=45B0DC93026D
void CTelcom_Msg::setTlg(Tlg* value)
{
	m_pTlg = value;
  m_MsgType = m_pTlg->getId();
}

//##ModelId=45B0DFD70037
std::string CTelcom_Msg::getPlantID()
{
	return m_PlantID;
}

//##ModelId=45B0DFEC0107
void CTelcom_Msg::setPlantID(const std::string& value)
{
	m_PlantID = value;
}

//##ModelId=45B0E044009C
long CTelcom_Msg::getCounter()
{
	return m_IamNo;
}

//##ModelId=45B0E4E50072
void CTelcom_Msg::setSender(const std::string& value)
{
	m_Sender = value;
}

//##ModelId=45B0E4F501D3
std::string CTelcom_Msg::getSender()
{
	return m_Sender;
}

//##ModelId=45B0E51300B9
std::string CTelcom_Msg::getOrderID()
{
	return m_OrderID;
}

//##ModelId=45B0E5210366
void CTelcom_Msg::setOrderID(const std::string& value)
{
	m_OrderID = value;
}

