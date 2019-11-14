// Copyright (C) 1991 - 1999 Rational Software Corporation

#include "misc.h"
#include "cSMON_Interface.h"
#include "cSysMon_Comp.h"
#include "IntrfImpl.h"




void cSMON_Interface::getOwnStateDetails(CORBA::String_out details)
{
	// ToDo: Add your specialized code here or after the call to base class


	cCBS_Task::getOwnStateDetails(details);
	
	
	
}

cSMON_Interface::~cSMON_Interface()
{
	// ToDo: Add your specialized code here and/or call the base class
}


cSMON_Interface::cSMON_Interface()
{
	// TODO: Add your specialized code here.
	
}



void cSMON_Interface::ownRunDown()
{
	// get a reference to the root POA
        PortableServer::POA_var rootPOA = CBS::getRootPOA();
        
        //PortableServer::ObjectId_var oid = rootPOA->servant_to_id(m_pMoldServant);

        // Deactivate the servant
        rootPOA->deactivate_object(*rootPOA->servant_to_id(m_pServant));

        cCBS_Task::ownRunDown();
        this->setWorking(false);
}

//##ModelId=41208788032D
void cSMON_Interface::ownStartUp()
{
		m_pServant = cSysMon_Comp::getSysMon_Comp()->m_IntrfImpl;

		// get a reference to the root POA
        PortableServer::POA_var rootPOA = CBS::getRootPOA();

        // Activate the servant
		rootPOA->activate_object(m_pServant);

        //Obtain a refence to object
		CORBA::Object_var obj = m_pServant->_this();

        //Register object with naming service
        if (CBS::bindObjectToName(obj,CBS::getProjectName(),"SMONIntrf"))
        {
                LOG_(1, "Servant of SMONIntrf is activated");
        }

        cCBS_Task::ownStartUp();
        this->setWorking(true);

}

