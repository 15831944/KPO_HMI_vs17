
// use config file e.g.: -config $(XPACT_SMC)\CFG\Tools\DBDataImporter.ini


#if defined(WIN32) || defined(_WIN32) 
  #pragma warning(disable:4786)
  #pragma warning(disable:4503)
#endif

#include <vector>

#include "iEventMessages_s.hh"
#include "CEventMessage.h"
#include "cCBS_StdEvent_Task.h"
#include "cCBS_StdCORBA_Task.h"
#include "cCBS_StdDB_Task.h"

#include "cCorbaProxyAdapter.h"
#include "cCorbaTraits.h"
#include "cCorbaPOAAdapter.h"
#include "cCBSClientTask.h"
#include "cTheAppORB.h"
#include "cTheAppPOA.h"
#include "cTheAppTraits.h"
#include "cCBS_CPPException.h"
#include "CDataConversion.h"

#include "CIntfData.h"
#include "cCBS_StdInitBase.h"
#include "iSMC_DataDefinitions_s.hh"
#include "iSMC_DataProvider_s.hh"
#include "CProductID.h"
#include "cCBS_StdFrame.h"

#include "CDateTime.h"

#include "CMDB_AIM_SLAG_COMPONENTS.h"
#include "CMDB_GRADE_ELEMENTS.h"
#include "CMDB_GRADE_FORMULAS.h"
#include "CMDB_STEEL_FORMULAS.h"
#include "CMDB_STEEL_GRADES.h"
#include "CAUX_VALUES.h"

#include "CMDB_MATERIALS.h"
#include "CMDB_MAT_ANALYSIS_ELEMENTS.h"
#include "CMDB_MAT_SLAG_COMPONENTS.h"

#include "CGT_MAT.h"
#include "CGT_MAT_CHEM.h"
#include "CGT_MAT_EFF.h"
#include "CGT_MAT_PURP.h"
#include "CPD_BIN.h"

#include "CGC_MEASUREMENT_NAME.h"
#include "DEF_GC_MEASUREMENT_NAME_SCOPE.h"
#include "DEF_GC_MEASUREMENT_NAME.h"
#include "DEF_GT_PURP.h"


#include "CGT_GRADE.h"
#include "CGT_GRADE_ANL.h"
#include "CGT_GRADE_EQUIV.h"
#include "CGT_GRADE_PRODPRAC.h"
#include "CGT_GRADE_SINGLE_AIMS.h"

#include "CGT_EQUIV.h"
#include "CGT_EQUIV_ENTRY.h"

#include "CHD_RESTRI_ENTRY.h"
#include "CGT_RESTRI_ENTRY.h"
#include "CPD_RECIPE_ENTRY.h"

#include "CGC_Plantgroup_Container.h"


int main( int argc, const char *argv[], char *envp[] )
{

  try
  {
    // activate SMM Application Environment
    cCBS_StdFrame *pCBS_StdFrame = new cCBS_StdFrame(argc, argv);

    // run the application / CORBA
    pCBS_StdFrame->runAsClient();

    cCBS_Connection* pConnection;

    cCBS_StdDB_Task* pDB_Task = cCBS_StdDB_Task::getInstance();
    cCBS_StdInitBase *pStdInitBase = cCBS_StdInitBase::getInstance();

    std::string DBName;
    std::string DBUser;
    std::string DBPassword;

    if (pDB_Task)
    {
      try
      {  
        bool result = false;
        if ( !( pStdInitBase->getEntry("DATABASE", "SMC_DBName", DBName) &&
                pStdInitBase->getEntry("DATABASE", "SMC_DBUser", DBUser)  &&
                pStdInitBase->getEntry("DATABASE", "SMC_DBPassword", DBPassword) ))
        {
          std::cerr << "Can not read SMC database settings from ini-file" << std::endl;
          exit(EXIT_FAILURE);
        }

        pConnection = pDB_Task->getConnection(DBName,DBUser, DBPassword);

        if (pConnection)
        {
          pConnection->setAutoCommit(false);
        }
      }
      catch(...) 
      {
        std::cout << "exception caught at getConnection() in CModelTask::setDBConnections()" << std::endl;
      }
    }


    long input = 1;

    CDateTime Now;

    do 
    {
      cout << endl << endl << endl;
      cout << "DB Data Importer Tool" << endl;
      cout << "*********************" << endl;
      cout << "**    C O R U S   ***" << endl;
      cout << "*********************" << endl;

      cout << "Input : " << endl;
      cout << "0 for exit" << endl;
      cout << "1 read and display new data for MATERIALS" << endl;
      cout << "2 delete existing material data " << endl;
      cout << "3 import new data " << endl;
      cout << "4 commit input " << endl;
      cin >> input;

      try
      {
        switch (input)
        {
          case 1:
          {
            CMDB_MATERIALS MDB_MATERIALS(pConnection);

            if ( MDB_MATERIALS.select(CSMC_DBData::unspecString) )
            {
              for ( long i = 1 ; i <= MDB_MATERIALS.getLastRow() ; ++i )
              {
                std::cout << MDB_MATERIALS.getMATERIAL_ID(i)        <<  " "
                          << MDB_MATERIALS.getMATERIAL_NAME(i)      <<  " "
                          << MDB_MATERIALS.getMATERIAL_CLASS(i)     <<  " "
                          << MDB_MATERIALS.getDESCRIPTION(i)        <<  " "
                          << MDB_MATERIALS.getWIRE_SPECIFIC_WGT(i)  <<  " "
                          << MDB_MATERIALS.getSPECIFIC_WGT(i)       <<  " "
                          << MDB_MATERIALS.getMATERIAL_ID(i)        <<  " "
                          << MDB_MATERIALS.getAVAILABILITY(i)       <<  " "
                          << MDB_MATERIALS.getPRIORITY(i)           <<  " "
                          << MDB_MATERIALS.getHUMIDITY(i)           <<  " "
                          << MDB_MATERIALS.getYIELD(i)              <<  " "
                          << MDB_MATERIALS.getCHILL_FACTOR(i)       <<  " "
                          << MDB_MATERIALS.getMATERIAL_ID(i)        <<  " "
                          << MDB_MATERIALS.getMELTING_ENERGY(i)     <<  " "
                          << MDB_MATERIALS.getCAO_RATIO(i)          <<  " "
                          << MDB_MATERIALS.getEAF_YIELD(i)          <<  " "
                          << MDB_MATERIALS.getMETALLIC_FLG(i)       <<  " "
                          << MDB_MATERIALS.getMATERIAL_ID(i)        <<  " "
                          << MDB_MATERIALS.getGANGUE_PCT(i)         <<  " "
                          << MDB_MATERIALS.getDRI_C_RATIO(i)        <<  " "
                          << MDB_MATERIALS.getDRI_DUST_PCT(i)       <<  " "
                          << MDB_MATERIALS.getDRI_LIME_RATIO(i)     <<  " "
                          << MDB_MATERIALS.getDRI_MAX_RATE(i)       <<  " "
                          << MDB_MATERIALS.getDRI_METAL_PCT(i)      <<  " "
                          << MDB_MATERIALS.getDRI_O_RATIO(i)        <<  " "
                          << MDB_MATERIALS.getDRI_TOT_FE_PCT(i)     <<  " "
                          << MDB_MATERIALS.getSLAGBUILDER(i)        <<  " "
                          << MDB_MATERIALS.getSLAGBUILDER2(i)       <<  std::endl ;

              }
            }

            break;
          }

          case 2 : 
          {
            std::string YesNo;
            cout << "do you really want to delete data at : " << DBName << " Y/N" << endl;
            cin >> YesNo;

            if ( YesNo == "Y" || YesNo == "y" )
            {
              cout << "deleting data from " << DBName << endl ;

              CGT_MAT             GT_MAT(pConnection);
              CGT_MAT_CHEM        GT_MAT_CHEM(pConnection);
              CGT_MAT_EFF         GT_MAT_EFF(pConnection);
              CGT_MAT_PURP        GT_MAT_PURP(pConnection);
              CPD_BIN             PD_BIN(pConnection);
              CHD_RESTRI_ENTRY    HD_RESTRI_ENTRY(pConnection);
              CGT_RESTRI_ENTRY    GT_RESTRI_ENTRY(pConnection);
              CPD_RECIPE_ENTRY    PD_RECIPE_ENTRY(pConnection);

              std::vector<std::string> MatCodes;
              std::vector<std::string>::iterator MatCodesIt;

              if ( GT_MAT.select(CSMC_DBData::unspecString) )
              {
                for ( long i = 1 ; i <= GT_MAT.getLastRow() ; ++i )
                {
                  std::string MAT_CODE = GT_MAT.getMAT_CODE(i);

                  MatCodes.push_back(MAT_CODE);

                  if ( HD_RESTRI_ENTRY.select(CSMC_DBData::unspecString,CSMC_DBData::unspecString,"LF",
                                              CSMC_DBData::unspecLong,CSMC_DBData::unspecLong,CSMC_DBData::unspecLong,
                                              CSMC_DBData::unspecString,CSMC_DBData::unspecLong,CSMC_DBData::unspecString,CSMC_DBData::unspecLong) )
                  {
                    cout << "deleting HD_RESTRI_ENTRY for material " << MAT_CODE << endl ;
                    HD_RESTRI_ENTRY.deleteRows();
                  }

                  if ( GT_RESTRI_ENTRY.select("LF",CSMC_DBData::unspecLong,CSMC_DBData::unspecLong,CSMC_DBData::unspecLong,
                                              CSMC_DBData::unspecLong,CSMC_DBData::unspecString,CSMC_DBData::unspecLong,
                                              CSMC_DBData::unspecString,CSMC_DBData::unspecLong) )
                  {
                    cout << "deleting GT_RESTRI_ENTRY for material " << MAT_CODE << endl ;
                    GT_RESTRI_ENTRY.deleteRows();
                  }


                  if ( GT_MAT_CHEM.select(MAT_CODE,CSMC_DBData::unspecString) )
                  {
                    cout << "deleting GT_MAT_CHEM for material " << MAT_CODE << endl ;
                    GT_MAT_CHEM.deleteRows();
                  }

                  if ( GT_MAT_EFF.select(MAT_CODE,CSMC_DBData::unspecString) )
                  {
                    cout << "deleting GT_MAT_EFF for material " << MAT_CODE << endl ;
                    GT_MAT_EFF.deleteRows();
                  }

                  if ( GT_MAT_PURP.selectByPlant("LF", CSMC_DBData::unspecLong, MAT_CODE,CSMC_DBData::unspecString) )
                  {
                    cout << "deleting GT_MAT_PURP for material " << MAT_CODE << endl ;
                    GT_MAT_PURP.deleteRows();
                  }

                  if ( PD_BIN.select("LF", CSMC_DBData::unspecLong,CSMC_DBData::unspecString, MAT_CODE) )
                  {
                    cout << "deleting PD_BIN for material " << MAT_CODE << endl ;
                    PD_BIN.deleteRows();
                  }

                  if ( PD_RECIPE_ENTRY.select(CSMC_DBData::unspecString,CSMC_DBData::unspecString,CSMC_DBData::unspecString,
                                              CSMC_DBData::unspecString,CSMC_DBData::unspecLong,
                                              CSMC_DBData::unspecString,CSMC_DBData::unspecLong,MAT_CODE) )
                  {
                    cout << "deleting PD_RECIPE_ENTRY for material " << MAT_CODE << endl ;
                    PD_RECIPE_ENTRY.CSMC_DBData::deleteRows();
                  }

                }
              }

              for ( MatCodesIt = MatCodes.begin() ; MatCodesIt != MatCodes.end() ; ++MatCodesIt)
              {
                std::string MAT_CODE = *MatCodesIt;
                
                cout << "deleting material " << MAT_CODE << endl ;

                if ( GT_MAT.select(MAT_CODE) )
                {
                  GT_MAT.deleteRows();
                }
              }
              
              cout << endl;
            }
            
            break;
          }

          case 3: 
          {
              CAUX_VALUES             AUX_VALUES(pConnection);

              CMDB_MATERIALS              MDB_MATERIALS(pConnection);
              CMDB_MAT_ANALYSIS_ELEMENTS  MDB_MAT_ANALYSIS_ELEMENTS(pConnection);
              CMDB_MAT_SLAG_COMPONENTS    MDB_MAT_SLAG_COMPONENTS(pConnection);

              CMDB_STEEL_GRADES         MDB_STEEL_GRADES(pConnection);
              CMDB_STEEL_FORMULAS       MDB_STEEL_FORMULAS(pConnection);
              CMDB_GRADE_ELEMENTS       MDB_GRADE_ELEMENTS(pConnection);
              CMDB_GRADE_FORMULAS       MDB_GRADE_FORMULAS(pConnection);

              CGT_MAT                   GT_MAT(pConnection);
              CGT_MAT_CHEM              GT_MAT_CHEM(pConnection);
              CGT_MAT_EFF               GT_MAT_EFF(pConnection);
              CGT_MAT_PURP              GT_MAT_PURP(pConnection);

              CGT_GRADE                 GT_GRADE(pConnection);
              CGT_GRADE_ANL             GT_GRADE_ANL(pConnection);
              CGT_GRADE_EQUIV           GT_GRADE_EQUIV(pConnection);
              CGT_GRADE_PRODPRAC        GT_GRADE_PRODPRAC(pConnection);
              CGT_GRADE_SINGLE_AIMS     GT_GRADE_SINGLE_AIMS(pConnection);

              CGC_MEASUREMENT_NAME      GC_MEASUREMENT_NAME(pConnection);
              CGT_EQUIV                 GT_EQUIV(pConnection);
              CGT_EQUIV_ENTRY           GT_EQUIV_ENTRY(pConnection);
              CGC_Plantgroup_Container  GC_Plantgroup_Container(pConnection);

              cout << " ************************** " << endl;
              cout << " ************************** " << endl;
              cout << "       MATERIAL DATA        " << endl;
              cout << " ************************** " << endl;
              cout << " ************************** " << endl;

              std::string PLANT = "LF";
              long UnitGroupNo = GC_Plantgroup_Container.getUnitGroupNo(PLANT);

              if ( MDB_MATERIALS.select(CSMC_DBData::unspecString) )
              {
                for ( long i = 1 ; i <= MDB_MATERIALS.getLastRow() ; ++i )
                {
                  std::string MATERIAL_ID = MDB_MATERIALS.getMATERIAL_ID(i);

                  cout << " importing data for " << MATERIAL_ID  <<  endl;

                  if ( GT_MAT.select(MATERIAL_ID) )
                  {
                    GT_MAT.deleteRows();
                  }


                  GT_MAT.setMAT_CODE            (MATERIAL_ID);
                  GT_MAT.setDESCRIPTION         (MDB_MATERIALS.getMATERIAL_NAME(i));
                  GT_MAT.setDESCR_C             (MDB_MATERIALS.getDESCRIPTION(i));
                  GT_MAT.setCHARGE_PRIORITY     ((long)MDB_MATERIALS.getPRIORITY(i));    
                  GT_MAT.setPRICE               (1);
                  GT_MAT.setDENSITY             ((long)MDB_MATERIALS.getSPECIFIC_WGT(i));
                  //GT_MAT.setBULK_DENSITY        ((long)MDB_MATERIALS.getSPECIFIC_WGT(i));
                  GT_MAT.setENTHALPY            (0.4);
                  GT_MAT.setSPEC_HEAT           (0.00021);
                  GT_MAT.setHOMOG               (10000000);
                  GT_MAT.setDISTRIB_STEEL_SLAG  (1);
                  //GT_MAT.setFEED_SPEED          ();
                  //GT_MAT.setFEED_TEMP_FACT                    ();
                  //GT_MAT.setMG_EQUIVALENT                    ();
                  //GT_MAT.setMULTIPLE_ADDITION                    ();
                  GT_MAT.setAVAIL               (1);
                  GT_MAT.setWIRE_DENSITY        (MDB_MATERIALS.getWIRE_SPECIFIC_WGT(i));
                  GT_MAT.setAVAIL               (1);
                  GT_MAT.setMINWEIGHT           (0);


                  GT_MAT.insert();
                  
                  cout << " ************************** " << endl;
                  cout << " ************************** " << endl;
                  cout << "     A N A L A Y S I S      " << endl;
                  cout << " ************************** " << endl;
                  cout << " ************************** " << endl;
                  double ANA_CONC   = 0.;
                  double COMP_CONC  = 0.;
                  if ( MDB_MAT_ANALYSIS_ELEMENTS.select(MATERIAL_ID, CSMC_DBData::unspecLong) )
                  {
                    for ( long i = 1 ; i <= MDB_MAT_ANALYSIS_ELEMENTS.getLastRow() ; ++i )
                    {
                      long ELEMENT_CODE = MDB_MAT_ANALYSIS_ELEMENTS.getELEMENT_CODE(i);

                      std::string ENAME = AUX_VALUES.getElementName(ELEMENT_CODE);

                      cout << " importing data for " << ENAME <<  endl;

                      if ( !GC_MEASUREMENT_NAME.select(ENAME) )
                      {
                        GC_MEASUREMENT_NAME.setMEASNAME(ENAME);
                        GC_MEASUREMENT_NAME.setSCOPENO(DEF_GC_MEASUREMENT_NAME_SCOPE::Steel);
                        
                        GC_MEASUREMENT_NAME.insert();
                      }


                      double VALUE      = MDB_MAT_ANALYSIS_ELEMENTS.getVALUE(i);

                      if ( VALUE > 0 && ENAME != CSMC_DBData::unspecString )
                      {
                        if ( GT_MAT_CHEM.select(MATERIAL_ID,ENAME) )
                        {
                          GT_MAT_CHEM.deleteRows();
                        }

                        GT_MAT_CHEM.setMAT_CODE(MATERIAL_ID);
                        GT_MAT_CHEM.setENAME(ENAME);
                        GT_MAT_CHEM.setVALUE(VALUE);

                        GT_MAT_CHEM.insert();

                        ANA_CONC = ANA_CONC + VALUE;
                      }
                    }
                  }

                  if ( MDB_MAT_SLAG_COMPONENTS.select(MATERIAL_ID, CSMC_DBData::unspecLong) )
                  {
                    for ( long i = 1 ; i <= MDB_MAT_SLAG_COMPONENTS.getLastRow() ; ++i )
                    {
                      long COMPONENT_CODE = MDB_MAT_SLAG_COMPONENTS.getCOMPONENT_CODE(i);

                      std::string ENAME = AUX_VALUES.getComponentName(COMPONENT_CODE);

                      cout << " importing data for " << ENAME <<  endl;

                      if ( !GC_MEASUREMENT_NAME.select(ENAME) )
                      {
                        GC_MEASUREMENT_NAME.setMEASNAME(ENAME);
                        GC_MEASUREMENT_NAME.setSCOPENO(DEF_GC_MEASUREMENT_NAME_SCOPE::Slag);
                        
                        GC_MEASUREMENT_NAME.insert();
                      }


                      double VALUE      = MDB_MAT_SLAG_COMPONENTS.getVALUE(i);

                      if ( VALUE > 0 && ENAME != CSMC_DBData::unspecString)
                      {
                        if ( GT_MAT_CHEM.select(MATERIAL_ID,ENAME) )
                        {
                          GT_MAT_CHEM.deleteRows();
                        }
                        
                        GT_MAT_CHEM.setMAT_CODE(MATERIAL_ID);
                        GT_MAT_CHEM.setENAME(ENAME);
                        GT_MAT_CHEM.setVALUE(VALUE);

                        GT_MAT_CHEM.insert();

                        COMP_CONC = COMP_CONC + VALUE;
                      }
                    }
                  }

                  double CORRECTION = 100. - ANA_CONC - COMP_CONC;

                  if ( ANA_CONC > COMP_CONC && CORRECTION > 0. )
                  {
                    GT_MAT_CHEM.setMAT_CODE(MATERIAL_ID);
                    GT_MAT_CHEM.setENAME(DEF_GC_MEASUREMENT_NAME::Fe_X);
                    GT_MAT_CHEM.setVALUE(CORRECTION);

                    GT_MAT_CHEM.insert();
                  }
                  else if ( ANA_CONC <= COMP_CONC && CORRECTION > 0. )
                  {
                    GT_MAT_CHEM.setMAT_CODE(MATERIAL_ID);
                    GT_MAT_CHEM.setENAME(DEF_GC_MEASUREMENT_NAME::Slag_X);
                    GT_MAT_CHEM.setVALUE(CORRECTION);

                    GT_MAT_CHEM.insert();
                  }



                  cout << " ************************** " << endl;
                  cout << " ************************** " << endl;
                  cout << "    E F F I C I E N C Y     " << endl;
                  cout << " ************************** " << endl;
                  cout << " ************************** " << endl;
                  std::string EFF_NAME = "Furnace";
                  if ( GT_MAT_EFF.select(MATERIAL_ID,EFF_NAME ) )
                  {
                    GT_MAT_EFF.deleteRows();
                  }

                  GT_MAT_EFF.setMAT_CODE  ( MATERIAL_ID );
                  GT_MAT_EFF.setEFF_NAME  ( EFF_NAME );
                  GT_MAT_EFF.setVALUE     ( MDB_MATERIALS.getYIELD(i) );

                  GT_MAT_EFF.insert();

                  EFF_NAME = "Ladle";
                  if ( GT_MAT_EFF.select(MATERIAL_ID,EFF_NAME ) )
                  {
                    GT_MAT_EFF.deleteRows();
                  }

                  GT_MAT_EFF.setMAT_CODE  ( MATERIAL_ID );
                  GT_MAT_EFF.setEFF_NAME  ( EFF_NAME );
                  GT_MAT_EFF.setVALUE     ( MDB_MATERIALS.getYIELD(i) );

                  GT_MAT_EFF.insert();

                  cout << " ************************** " << endl;
                  cout << " ************************** " << endl;
                  cout << "       P U R P O S E        " << endl;
                  cout << " ************************** " << endl;
                  cout << " ************************** " << endl;
                  long MATERIAL_CLASS   = MDB_MATERIALS.getMATERIAL_CLASS(i);

                  std::vector<std::string> PurpCodes;
                  std::vector<std::string>::iterator PurpCodesIt;
                  
                  if ( MATERIAL_CLASS == 1 ) // draad
                  {
                    PurpCodes.push_back(DEF_GT_PURP::Wire_Default);
                    PurpCodes.push_back(DEF_GT_PURP::Wire_Feeder);
                    PurpCodes.push_back(DEF_GT_PURP::Wire_Avail);
                    PurpCodes.push_back(DEF_GT_PURP::FinalTrimming);
                  }
                  if ( MATERIAL_CLASS == 2 ) //poeder
                  {
                    PurpCodes.push_back(DEF_GT_PURP::LimeInjection);
                  }
                  if ( MATERIAL_CLASS == 3 ) //DRI
                  {
                    PurpCodes.push_back(DEF_GT_PURP::Bin_Default);
                    PurpCodes.push_back(DEF_GT_PURP::Bin_Avail);
                    PurpCodes.push_back(DEF_GT_PURP::Alloy);
                    PurpCodes.push_back(DEF_GT_PURP::AlloyFinal);
                    PurpCodes.push_back(DEF_GT_PURP::AlloyInitial);
                  }
                  if ( MATERIAL_CLASS == 4 ) // bulk
                  {
                    PurpCodes.push_back(DEF_GT_PURP::Bin_Default);
                    PurpCodes.push_back(DEF_GT_PURP::Bin_Avail);
                    PurpCodes.push_back(DEF_GT_PURP::Alloy);
                    PurpCodes.push_back(DEF_GT_PURP::AlloyFinal);
                    PurpCodes.push_back(DEF_GT_PURP::AlloyInitial);
                  }
                  if ( MATERIAL_CLASS == 5 ) // schrot
                  {
                    PurpCodes.push_back(DEF_GT_PURP::Bin_Default);
                    PurpCodes.push_back(DEF_GT_PURP::Bin_Avail);
                    PurpCodes.push_back(DEF_GT_PURP::Cooling);
                    PurpCodes.push_back(DEF_GT_PURP::Alloy);
                    PurpCodes.push_back(DEF_GT_PURP::AlloyFinal);
                    PurpCodes.push_back(DEF_GT_PURP::AlloyInitial);
                  }

                  for ( PurpCodesIt = PurpCodes.begin() ; PurpCodesIt != PurpCodes.end() ; ++PurpCodesIt )
                  {
                    std::string PURP_CODE = *PurpCodesIt;

                    if ( GT_MAT_PURP.select(UnitGroupNo,MATERIAL_ID,PURP_CODE ) )
                    {
                      GT_MAT_PURP.deleteRows();
                    }
                    GT_MAT_PURP.setUNITGROUPNO  ( UnitGroupNo );
                    GT_MAT_PURP.setMAT_CODE     ( MATERIAL_ID );
                    GT_MAT_PURP.setPURP_CODE    ( PURP_CODE );

                    GT_MAT_PURP.insert();
                  }
                }
              }

              cout << " ************************** " << endl;
              cout << " ************************** " << endl;
              cout << "     STEEL GRADE DATA       " << endl;
              cout << " ************************** " << endl;
              cout << " ************************** " << endl;

              if ( MDB_STEEL_GRADES.select(CSMC_DBData::unspecString) )
              {
                for ( long i = 1 ; i <= MDB_STEEL_GRADES.getLastRow() ; ++i )
                {
                  std::string STEEL_GRADE_ID = MDB_STEEL_GRADES.getSTEEL_GRADE_ID(i);

                  cout << " importing data for " << STEEL_GRADE_ID <<  endl;

                  if ( GT_GRADE.select(STEEL_GRADE_ID) )
                  {
                    GT_GRADE.deleteRows();
                  }

                  GT_GRADE.setSTEELGRADECODE        (STEEL_GRADE_ID);
                  GT_GRADE.setSTEELGRADECODEDESCR   (MDB_STEEL_GRADES.getDESCRIPTION(i));
                  //GT_GRADE.setSTEELGRADECODEDESCR_C ("");
                  GT_GRADE.setLIQTEMP               (MDB_STEEL_GRADES.getLIQUIDUS_TEMP(i));
                  GT_GRADE.setUSERCODE              ("import");
                  GT_GRADE.setREVTIME               (Now);

                  GT_GRADE.insert();

                  cout << " ************************** " << endl;
                  cout << " ************************** " << endl;
                  cout << "       A N A L Y S I S      " << endl;
                  cout << " ************************** " << endl;
                  cout << " ************************** " << endl;
                  if ( MDB_GRADE_ELEMENTS.select(STEEL_GRADE_ID,CSMC_DBData::unspecLong) )
                  {
                    for ( long i = 1 ; i <= MDB_GRADE_ELEMENTS.getLastRow() ; ++i )
                    {
                      long ELEMENT_CODE = MDB_GRADE_ELEMENTS.getELEMENT_CODE(i);

                      std::string ENAME = AUX_VALUES.getElementName(ELEMENT_CODE);

                      cout << " importing data for " << ENAME <<  endl;

                      if ( !GC_MEASUREMENT_NAME.select(ENAME) )
                      {
                        GC_MEASUREMENT_NAME.setMEASNAME(ENAME);
                        GC_MEASUREMENT_NAME.setSCOPENO(DEF_GC_MEASUREMENT_NAME_SCOPE::Steel);
                        
                        GC_MEASUREMENT_NAME.insert();
                      }

                      if ( ENAME != CSMC_DBData::unspecString )
                      {
                        // ***************** M I N **********************************************************
                        std::string AIMTYPE = "Min";
                        double      VALUE   = MDB_GRADE_ELEMENTS.getMIN_VALUE(i);

                        if ( GT_GRADE_ANL.select(PLANT,STEEL_GRADE_ID,AIMTYPE,ENAME) )
                        {
                          GT_GRADE_ANL.deleteRows();
                        }

                        GT_GRADE_ANL.setPLANT           (PLANT);
                        GT_GRADE_ANL.setSTEELGRADECODE  (STEEL_GRADE_ID);
                        GT_GRADE_ANL.setAIMTYPE         (AIMTYPE);
                        GT_GRADE_ANL.setANL             (VALUE);
                        GT_GRADE_ANL.setENAME           (ENAME);

                        GT_GRADE_ANL.insert();

                        // ***************** A I M  **********************************************************
                        AIMTYPE = "Aim";
                        VALUE   = MDB_GRADE_ELEMENTS.getAIM_VALUE(i);

                        if ( GT_GRADE_ANL.select(PLANT,STEEL_GRADE_ID,AIMTYPE,ENAME) )
                        {
                          GT_GRADE_ANL.deleteRows();
                        }

                        if ( VALUE > 0 )
                        {
                          GT_GRADE_ANL.setPLANT           (PLANT);
                          GT_GRADE_ANL.setSTEELGRADECODE  (STEEL_GRADE_ID);
                          GT_GRADE_ANL.setAIMTYPE         (AIMTYPE);
                          GT_GRADE_ANL.setANL             (VALUE);
                          GT_GRADE_ANL.setENAME           (ENAME);

                          GT_GRADE_ANL.insert();
                        }

                        // ***************** M A X  **********************************************************
                        AIMTYPE = "Max";
                        VALUE   = MDB_GRADE_ELEMENTS.getMAX_VALUE(i);

                        if ( GT_GRADE_ANL.select(PLANT,STEEL_GRADE_ID,AIMTYPE,ENAME) )
                        {
                          GT_GRADE_ANL.deleteRows();
                        }

                        GT_GRADE_ANL.setPLANT           (PLANT);
                        GT_GRADE_ANL.setSTEELGRADECODE  (STEEL_GRADE_ID);
                        GT_GRADE_ANL.setAIMTYPE         (AIMTYPE);
                        GT_GRADE_ANL.setANL             (VALUE);
                        GT_GRADE_ANL.setENAME           (ENAME);

                        if ( VALUE > 0 )
                        {
                          GT_GRADE_ANL.insert();
                        }
                      } // if ( ENAME != CSMC_DBData::unspecString )
                    }
                  } // if ( MDB_GRADE_ELEMENTS.select(STEEL_GRADE_ID,CSMC_DBData::unspecLong) )

                  cout << " ************************** " << endl;
                  cout << " ************************** " << endl;
                  cout << "   E Q U I V A L E N C E S  " << endl;
                  cout << " ************************** " << endl;
                  cout << " ************************** " << endl;
                  
                  if ( MDB_STEEL_FORMULAS.select(CSMC_DBData::unspecString) )
                  {
                    for ( long i = 1 ; i <= MDB_STEEL_FORMULAS.getLastRow() ; ++i )
                    {
                      std::string FORMULA_ID = MDB_STEEL_FORMULAS.getFORMULA_ID(i);

                      cout << " importing data for " << FORMULA_ID <<  endl;

                      if ( GT_EQUIV.select(FORMULA_ID) )
                      {
                        GT_EQUIV.deleteRows();
                      }

                      GT_EQUIV.setEQ_NAME           (FORMULA_ID);
                      GT_EQUIV.setDESCRIPTION       (MDB_STEEL_FORMULAS.getDESCRIPTION(i));
                      GT_EQUIV.setOFFSET            (MDB_STEEL_FORMULAS.getOFFSET(i));

                      std::string NUMERATOR   = MDB_STEEL_FORMULAS.getNUMERATOR(i);
                      std::string DENOMINATOR = MDB_STEEL_FORMULAS.getDENOMINATOR(i);

                      GT_EQUIV.insert();

                      if ( !GC_MEASUREMENT_NAME.select(FORMULA_ID) )
                      {
                        GC_MEASUREMENT_NAME.setMEASNAME(FORMULA_ID);
                        GC_MEASUREMENT_NAME.setSCOPENO(DEF_GC_MEASUREMENT_NAME_SCOPE::Equiv);
                        
                        GC_MEASUREMENT_NAME.insert();
                      }


                      std::map<std::string,double> Entries;
                      std::map<std::string,double>::iterator EntriesIt;

                      std::string NUMERATOR_REST    = NUMERATOR;
                      std::string DENOMINATOR_REST  = DENOMINATOR;

                      if ( !NUMERATOR_REST.empty() )
                      {
                        bool FindNext = true;
                        long Position = 1;
                        long Type     = 1; // NUMERATOR

                        while ( FindNext )
                        {
                          long Position = (long)NUMERATOR_REST.find_first_of("+");

                          if ( Position == std::string::npos )
                          {
                            Position = (long)NUMERATOR_REST.find_first_of("-");
                          }

                          if ( Position == std::string::npos )
                          {
                            Position = NUMERATOR_REST.length();
                            FindNext = false;
                          }

                          std::string Entry = NUMERATOR_REST.substr(0,Position);
                          Entry             = CDataConversion::Trim(Entry);

                          if ( Position < (long)NUMERATOR_REST.length() )
                          {
                            NUMERATOR_REST    = NUMERATOR_REST.substr(Position+1,NUMERATOR_REST.length());
                          }

                          long PosMulti       = Entry.find_first_of("*");
                          double Factor       = CDataConversion::StringToDouble( Entry.substr(0,PosMulti) );
                          std::string Element = Entry.substr(PosMulti+1,Entry.length());

                          Entries.insert( std::pair<std::string,double>(Element,Factor) );

                        } // while ( FindNext )

                        for ( EntriesIt = Entries.begin() ; EntriesIt != Entries.end() ; ++EntriesIt)
                        {
                          if ( GT_EQUIV_ENTRY.select(FORMULA_ID,Type,EntriesIt->first) )
                          {
                            GT_EQUIV_ENTRY.deleteRows();
                          }

                          GT_EQUIV_ENTRY.setEQ_NAME     (FORMULA_ID);
                          GT_EQUIV_ENTRY.setENAME       (EntriesIt->first);
                          GT_EQUIV_ENTRY.setFACTOR      (EntriesIt->second);
                          GT_EQUIV_ENTRY.setTYPE        (Type);

                          GT_EQUIV_ENTRY.insert();
                        }
                      } // if ( !NUMERATOR_REST.empty() )

                      Entries.erase(Entries.begin(),Entries.end());

                      if ( !DENOMINATOR_REST.empty() )
                      {
                        bool FindNext = true;
                        long Position = 1;
                        long Type     = 2; // DENOMINATOR

                        while ( FindNext )
                        {
                          long Position = (long)DENOMINATOR_REST.find_first_of("+");

                          if ( Position == std::string::npos )
                          {
                            Position = (long)DENOMINATOR_REST.find_first_of("-");
                          }

                          if ( Position == std::string::npos )
                          {
                            Position = DENOMINATOR_REST.length();
                            FindNext = false;
                          }

                          std::string Entry = DENOMINATOR_REST.substr(0,Position);
                          Entry             = CDataConversion::Trim(Entry);

                          if ( Position < (long)DENOMINATOR_REST.length() )
                          {
                            DENOMINATOR_REST    = DENOMINATOR_REST.substr(Position+1,DENOMINATOR_REST.length());
                          }

                          long PosMulti       = Entry.find_first_of("*");

                          if ( PosMulti != std::string::npos )
                          {
                            long Factor         = CDataConversion::StringToLong( Entry.substr(0,PosMulti) );
                            std::string Element = Entry.substr(PosMulti+1,Entry.length());
  
                            Entries.insert( std::pair<std::string,double>(Element,Factor) );
                          }

                        } // while ( FindNext )

                        for ( EntriesIt = Entries.begin() ; EntriesIt != Entries.end() ; ++EntriesIt)
                        {
                          if ( GT_EQUIV_ENTRY.select(FORMULA_ID,Type,EntriesIt->first) )
                          {
                            GT_EQUIV_ENTRY.deleteRows();
                          }

                          GT_EQUIV_ENTRY.setEQ_NAME     (FORMULA_ID);
                          GT_EQUIV_ENTRY.setENAME       (EntriesIt->first);
                          GT_EQUIV_ENTRY.setFACTOR      (EntriesIt->second);
                          GT_EQUIV_ENTRY.setTYPE        (Type);

                          GT_EQUIV_ENTRY.insert();
                        }
                      } // if ( !DENOMINATOR_REST.empty() )
                    }
                  }

                  if ( MDB_GRADE_FORMULAS.select(CSMC_DBData::unspecString,STEEL_GRADE_ID ) )
                  {
                    long GT_GRADE_EQUIV_counter = 1;

                    for ( long i = 1 ; i <= MDB_GRADE_FORMULAS.getLastRow() ; ++i )
                    {
                      std::string FORMULA_ID = MDB_GRADE_FORMULAS.getFORMULA_ID(i);

                      // ***************** M I N **********************************************************
                      std::string AIMTYPE = "Min";
                      double      VALUE   = MDB_GRADE_FORMULAS.getMIN_VALUE(i);

                      if ( VALUE > 0 )
                      {
                        if ( GT_GRADE_ANL.select(PLANT,STEEL_GRADE_ID,AIMTYPE,FORMULA_ID) )
                        {
                          GT_GRADE_ANL.deleteRows();
                        }

                        GT_GRADE_ANL.setPLANT           (PLANT);
                        GT_GRADE_ANL.setSTEELGRADECODE  (STEEL_GRADE_ID);
                        GT_GRADE_ANL.setAIMTYPE         (AIMTYPE);
                        GT_GRADE_ANL.setANL             (VALUE);
                        GT_GRADE_ANL.setENAME           (FORMULA_ID);

                        GT_GRADE_ANL.insert();
                      }

                      AIMTYPE = "Max";
                      VALUE   = MDB_GRADE_FORMULAS.getMAX_VALUE(i);

                      if ( VALUE > 0 )
                      {
                        if ( GT_GRADE_ANL.select(PLANT,STEEL_GRADE_ID,AIMTYPE,FORMULA_ID) )
                        {
                          GT_GRADE_ANL.deleteRows();
                        }

                        GT_GRADE_ANL.setPLANT           (PLANT);
                        GT_GRADE_ANL.setSTEELGRADECODE  (STEEL_GRADE_ID);
                        GT_GRADE_ANL.setAIMTYPE         (AIMTYPE);
                        GT_GRADE_ANL.setANL             (VALUE);
                        GT_GRADE_ANL.setENAME           (FORMULA_ID);

                        GT_GRADE_ANL.insert();
                      }

                      if ( GT_GRADE_EQUIV.select(STEEL_GRADE_ID,FORMULA_ID) )
                      {
                        GT_GRADE_EQUIV.deleteRows();
                      }
                      GT_GRADE_EQUIV.setDEF_ORDER(GT_GRADE_EQUIV_counter);
                      GT_GRADE_EQUIV.setSTEELGRADECODE(STEEL_GRADE_ID);
                      GT_GRADE_EQUIV.setEQ_NAME(FORMULA_ID);

                      ++GT_GRADE_EQUIV_counter;
                      GT_GRADE_EQUIV.insert();

                    } // for ( long i = 1 ; i <= MDB_GRADE_FORMULAS.getLastRow() ; ++i )
                  } // if ( MDB_GRADE_FORMULAS.select(CSMC_DBData::unspecString,STEEL_GRADE_ID ) )
                } // for ( long i = 1 ; i <= MDB_STEEL_GRADES.getLastRow() ; ++i )
              } // if ( MDB_STEEL_GRADES.select(CSMC_DBData::unspecString) )

            break;
          }
          case 4 : 
          {
            CGT_GRADE               GT_GRADE(pConnection); // no matter which table !
            GT_GRADE.commit();

            break;
          }
          default:
            {
              input = 0;
              break;
            }

        }

      }

      catch(CORBA::SystemException& sExc) 
      {
      }

      catch(CORBA::Exception& cExc) 
      {
      }

      catch(...)
      {
        cout << "exception caught "  << endl;
      }

    } while (input != 0);

  }
  catch(cCBS_Exception Exc)
  {
    cout << Exc << endl;
  }

  catch(...)
  {
    cout << "exception caught "  << endl;
  }

  return 0;
}

