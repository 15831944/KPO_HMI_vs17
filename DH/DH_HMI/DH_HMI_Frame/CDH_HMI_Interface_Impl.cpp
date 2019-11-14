// Copyright (C) 2006 SMS Demag AG

#include "CDH_HMI_Interface_Impl.h"

// forces a CIntfDataElement to be instantiated with Key !
// function CData_Provider::getIntfReqList will return a list containg elements !
void CDH_HMI_Interface_Impl::beforeDataAccess(const std::string & Key,const std::string & Name)
{  
  indicate(Key.c_str());

  if (!Key.empty() && Key != DEF::Inv_String)
  { 
    log("Data with Name <" + Name + "> will be accessed for key <" + Key + ">", 4);
  }
}

