#include "IBASConnection.h"
#include "cCBS_CorbaProxy.h"
#include "cCBS_CorbaProxy.cpp"
#include <string>
#include <sstream>

using namespace System::Runtime::InteropServices;

Meltshop::IBASConnection::IBASConnection(void)
{
  m_PlantName = NULL;
  m_BASIntrf = NULL;
}

void Meltshop::IBASConnection::initialize(String ^context, String ^intrfName, String ^plantName)
{
  IntPtr ptContext = Marshal::StringToHGlobalAnsi(context);
  IntPtr ptIntrfName = Marshal::StringToHGlobalAnsi(intrfName);
  IntPtr ptPlant = Marshal::StringToHGlobalAnsi(plantName);
  m_PlantName = new std::string((char*) ptPlant.ToPointer());
  Marshal::FreeHGlobal(ptPlant);
  std::string sContext((char*) ptContext.ToPointer());
  std::string sInterface((char*) ptIntrfName.ToPointer());
  //initialize the ORB if necessary
  if (CBS::hasORB() == false)
  {
    if (CBS::setORB() == false)
      throw gcnew ApplicationException("Unable to initialize ORB! CBS::setORB() failed");
  }
  CORBA::Object_var obj = CBS::getObjectReference(sContext.c_str(), sInterface.c_str());
  if (CORBA::is_nil(obj))
    throw gcnew System::ApplicationException("Could not find CORBA object");
  Marshal::FreeHGlobal(ptContext);
  Marshal::FreeHGlobal(ptIntrfName);
  m_BASIntrf = IBAS::BASIntrf::_nil();
  m_BASIntrf = IBAS::BASIntrf::_narrow(obj);
}

Object^ Meltshop::IBASConnection::readValue(System::String ^itemName, LibTelcom::TelcomDataType type)
{
  IntPtr ptItemName = Marshal::StringToHGlobalAnsi(itemName);
  std::stringstream tagName;
  tagName << m_PlantName->c_str() << "." << ((char*)ptItemName.ToPointer());
  Marshal::FreeHGlobal(ptItemName);
  try
  {
    if (type == LibTelcom::TelcomDataType::Integer)
    {
      long lValue;
      m_BASIntrf->getLong(tagName.str().c_str(), lValue);
      return gcnew Int32(lValue);
    }
    else if (type == LibTelcom::TelcomDataType::Number)
    {
      float fValue;
      m_BASIntrf->getFloat(tagName.str().c_str(), fValue);
      return gcnew Double(fValue);
    }
    else if (type == LibTelcom::TelcomDataType::String)
    {
      CORBA::String_var retVal;
      m_BASIntrf->getString(tagName.str().c_str(), retVal);
      return gcnew String(retVal);
    }
  }
  catch (CORBA::UserException& e)
  {
    String^ errString = String::Concat("Caught CORBA::UserException:", gcnew String(e._name()));
    throw gcnew System::ApplicationException(errString);
  }
  catch (CORBA::SystemException& e)
  {
    String^ errString = String::Concat("Caught CORBA::SystemException:", gcnew String(e._name()));
    throw gcnew System::ApplicationException(errString);
  }
  return itemName;
}
