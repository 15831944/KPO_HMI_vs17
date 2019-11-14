// Copyright (C) 2007 SMS Demag AG
#pragma warning(disable:4482)

#include <sstream>
#include "cCBS_StdLog_Task.h"
#include "cDateTime.h"
#include "CTelcom_FileTransport.h"



//##ModelId=4374B4F202FB
CTelcom_FileTransport::CTelcom_FileTransport()
: openFile(0),headTlgName("Head")
{
  // translation for Steel/Hot Metal
  elemTransSteelHM["C"]    = "AnlValSteel_C";
  elemTransSteelHM["MN"]   = "AnlValSteel_Mn";
  elemTransSteelHM["S"]    = "AnlValSteel_S";
  elemTransSteelHM["P"]    = "AnlValSteel_P";
  elemTransSteelHM["SI"]   = "AnlValSteel_Si";
  elemTransSteelHM["CU"]   = "AnlValSteel_Cu";
  elemTransSteelHM["NI"]   = "AnlValSteel_Ni";
  elemTransSteelHM["CR"]   = "AnlValSteel_Cr";
  elemTransSteelHM["MO"]   = "AnlValSteel_Mo";
  elemTransSteelHM["V"]    = "AnlValSteel_V";
  elemTransSteelHM["SN"]   = "AnlValSteel_Sn";
  elemTransSteelHM["AL"]   = "AnlValSteel_Al";
  elemTransSteelHM["ALSOL"]= "AnlValSteel_Al_S";
  elemTransSteelHM["ALOXY"]= "AnlValSteel_Al_Oxy";   // not found in "General Standards"
  elemTransSteelHM["N"]    = "AnlValSteel_N";
  elemTransSteelHM["CA"]   = "AnlValSteel_Ca";
  elemTransSteelHM["ZN"]   = "AnlValSteel_ZN";       // not found in "General Standards"
  elemTransSteelHM["AS"]   = "AnlValSteel_As";
  elemTransSteelHM["NB"]   = "AnlValSteel_Nb";
  elemTransSteelHM["TI"]   = "AnlValSteel_Ti";
  elemTransSteelHM["CO"]   = "AnlValSteel_Co";
  elemTransSteelHM["W"]    = "AnlValSteel_W";
  elemTransSteelHM["PB"]   = "AnlValSteel_Pb";
  elemTransSteelHM["B"]    = "AnlValSteel_B";
  elemTransSteelHM["ZR"]   = "AnlValSteel_Zr";
  elemTransSteelHM["SB"]   = "AnlValSteel_Sb";
  elemTransSteelHM["O"]    = "AnlValSteel_O";
  elemTransSteelHM["CE"]   = "AnlValSteel_Ce";
  elemTransSteelHM["FE%"]  = "AnlValSteel_FE";       // not found in "General Standards"
  elemTransSteelHM["MNSI"] = "AnlValSteel_MN_SI";    // not found in "General Standards"
  elemTransSteelHM["BSOL"] = "AnlValSteel_B_S";      // not found in "General Standards"
  elemTransSteelHM["BOXY"] = "AnlValSteel_B_Oxy";    // not found in "General Standards"

  // translation for Slag
  elemTransSlag["SiO2"]   = "AnlValSlag_Si_O2";
  elemTransSlag["CaO"]    = "AnlValSlag_CaO";
  elemTransSlag["Al2O3"]  = "AnlValSlag_Al2_O3";
  elemTransSlag["MgO"]    = "AnlValSlag_MgO";
  elemTransSlag["FeO"]    = "AnlValSlag_FeO";
  elemTransSlag["S"]      = "AnlValSlag_S";
  elemTransSlag["MnO"]    = "AnlValSlag_MnO";
  elemTransSlag["K2O"]    = "AnlValSlag_K2O";   // not found in "General Standards"
  elemTransSlag["TiO2"]   = "AnlValSlag_Ti_O2";
  elemTransSlag["K.B"]    = "AnlValSlag_KB";    // not found in "General Standards"
  elemTransSlag["B.B"]    = "AnlValSlag_BB";    // not found in "General Standards"
  elemTransSlag["Fe"]     = "AnlValSlag_Fe";
  elemTransSlag["P"]      = "AnlValSlag_P";     // not found in "General Standards"
  elemTransSlag["Fe2O3"]  = "AnlValSlag_Fe2_O3";
  elemTransSlag["Na2O"]   = "AnlValSlag_Na2O";  // not found in "General Standards"
  elemTransSlag["Baz"]    = "AnlValSlag_Baz";   // not found in "General Standards"
  elemTransSlag["TOPLAM"] = "AnlValSlag_TOPLAM";// not found in "General Standards"

  m_LocalMsgFormat  = "CSV";
  m_RemoteMsgFormat = "FEL";
}

//##ModelId=4370C62002A3
CTelcom_FileTransport::~CTelcom_FileTransport()
{
}

//##ModelId=4373077803B5
void CTelcom_FileTransport::configure(const std::string & section, bas::Configuration & c)
{
  AbstractTransport::configure(section, c);
  // go to needed section
  c.setSection("SMS_FileReaderTransport");

  anlFilePath = c.gets("AnalysisFilePath");
  int i = anlFilePath.length();
  if (anlFilePath[i-1] != '\\')   anlFilePath += "\\";

  deleteProcessedFiles = c.getbool("deleteProcessedFiles", false);
  renameProcessedFiles = c.getbool("renameProcessedFiles", true);
  retryInterval = c.geti("RetryInterval",2); 

  std::stringstream Message;
  Message << "Use analysis directory: " << anlFilePath;
  Message << ", directory polling interval: " << retryInterval << "sec.";
  cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1);

  // set analysis file names
  HotMetalBF       = c.gets("HotMetalBF",       "Hot_Metal_BF.txt");
  HotMetalBeforeDS = c.gets("HotMetalBeforeDS", "Hot_Metal_DS_before.txt");
  HotMetalAfterDS  = c.gets("HotMetalAfterDS",  "Hot_Metal_DS_after.txt");
  SteelAnlBOF      = c.gets("SteelAnlBOF",      "Steel_Analysis_BOF.txt");
  SteelAnlLF       = c.gets("SteelAnlLF",       "Steel_Analysis_LF.txt");
  SlagAnlBOF       = c.gets("SlagAnlBOF",       "Slag_Analysis_BOF.txt");
  SlagAnlLF        = c.gets("SlagAnlLF",        "Slag_Analysis_LF.txt");

  return;
}

//##ModelId=437307790012
int  CTelcom_FileTransport::receive(TCMessage & msg)
{
  int retVal = -1;
  tofillMsg = &msg;
  setFinished(false);

  if ((anlKind == eAnlKind::HMBF) 
   || (anlKind == eAnlKind::HMDSBefore) 
   || (anlKind == eAnlKind::HMDSAfter))
  {
    retVal = receiveHotMetalAnl();
  }
  else if ((anlKind == eAnlKind::SteelBOF)
        || (anlKind == eAnlKind::SteelLF))
  {
    retVal = receiveSteelAnl();
  }
  else if ((anlKind == eAnlKind::SlagBOF)
        || (anlKind == eAnlKind::SlagLF))
  {
    retVal = receiveSlagAnl();
  }

  tofillMsg = 0;
  return retVal;
}

//##ModelId=437307790044
void CTelcom_FileTransport::send(const TCMessage & msg)
{
}

//##ModelId=437307790076
int CTelcom_FileTransport::doConnect()
{
  Sleep(retryInterval*1000);

  int retval = -1;                        // -1 indicates timeout, 0 means "Connected.
  setFinished(true);
  finishedFileProcessing = false;

  // scan specified folder for specified files.
  // If one found, open the it and
  // return zero - connected. Then we come into Receive where
  // we really read.
  // depends on file name set anlKind for using in receive

  currentFile = anlFilePath + HotMetalBF;
  openFile = new std::ifstream(currentFile.c_str());
  if (openFile->is_open())
  {
    anlKind = eAnlKind::HMBF;
    return 0;
  }
  else
    delete openFile;

  currentFile = anlFilePath + HotMetalBeforeDS;
  openFile = new std::ifstream(currentFile.c_str());
  if (openFile->is_open())
  {
    anlKind = eAnlKind::HMDSBefore;
    return 0;
  }
  else
    delete openFile;

  currentFile = anlFilePath + HotMetalAfterDS;
  openFile = new std::ifstream(currentFile.c_str());
  if (openFile->is_open())
  {
    anlKind = eAnlKind::HMDSAfter;
    return 0;
  }
  else
    delete openFile;

  currentFile = anlFilePath + SteelAnlBOF;
  openFile = new std::ifstream(currentFile.c_str());
  if (openFile->is_open())
  {
    anlKind = eAnlKind::SteelBOF;
    return 0;
  }
  else
    delete openFile;

  currentFile = anlFilePath + SteelAnlLF;
  openFile = new std::ifstream(currentFile.c_str());
  if (openFile->is_open())
  {
    anlKind = eAnlKind::SteelLF;
    return 0;
  }
  else
    delete openFile;

  currentFile = anlFilePath + SlagAnlBOF;
  openFile = new std::ifstream(currentFile.c_str());
  if (openFile->is_open())
  {
    anlKind = eAnlKind::SlagBOF;
    return 0;
  }
  else
    delete openFile;

  currentFile = anlFilePath + SlagAnlLF;
  openFile = new std::ifstream(currentFile.c_str());
  if (openFile->is_open())
  {
    anlKind = eAnlKind::SlagLF;
    return 0;
  }
  else
    delete openFile;

  return retval;
}

//##ModelId=43730779008A
int CTelcom_FileTransport::doDisconnect()
{
  int retval = 0;
  if (openFile)
  {
    openFile->close();
    delete openFile;
    openFile = 0;
    if (finished())
    {
      if (deleteProcessedFiles)
      {
        // unlink is another word for delete
        _unlink(currentFile.c_str());
      }
      else if (renameProcessedFiles)
      {
        CDateTime now;
        std::string DateFormat ("%Y%m%d%H%M%S***");

        rename(currentFile.c_str(), (currentFile+"-PROCESSED-"+ now.asString(DateFormat) ).c_str());
      }
    }
  }
  return retval;
}



//##ModelId=4373077900A8
int CTelcom_FileTransport::doListen()
{
  // there is no real Client or Server behaviour in File reading. Just read ...
  return doConnect();
}


//================================================================================================


//##ModelId=4381894F0056
int CTelcom_FileTransport::receiveSteelAnl()
{
  int retval = 0;
  std::string TlgName("LBL211");

  if (openFile && tofillMsg)   
  {
      bool done = false;
      char line[1000];
      do 
      {
        openFile->getline (line, sizeof(line));
      }
      while (line[0] != 'N' && ! (done = openFile->eof())) ;

      if (done ) 
      {
        // read the file to the end or the 1st line that is not good.

        finishedFileProcessing = true;  // signal we can delete/rename it...
        setFinished(true);
        retval = -1;
        //throw ETransport("File successfully read to the end (this is not an error)");
      }
      else
      {
        // parse line and have 1 telegram
        /////////////////////////////////

        Tlg *tlgLab = m_pFactory->makeTlg(TlgName);
        long blen = tlgLab->getLen();//-(m_pFactory->getTlg(headTlgName)->getLen());
        tlgLab->clear();

        CDateTime now;
        std::string tlgDate = now.asString ("%Y%m%d");       // "20011231"   - YYYYMMDD 
        std::string tlgTime = now.asString ("%H%M%S***");   // "134559999" - HHMMSSmmm
        
        (*tlgLab)["Header"]["MessageId"].set(1811L);
        (*tlgLab)["Header"]["MessageLength"].set(blen);
        (*tlgLab)["Header"]["MessageCount"].set(1L);
        (*tlgLab)["Header"]["UnitNo"].set(1L);

        cTokenizer parser(line);
        std::string   dummy = parser.nextToken();

        // read date/time
        std::string hh   = parser.nextToken();
        std::string min  = parser.nextToken();
        std::string day  = parser.nextToken();
        std::string mon  = parser.nextToken();
        std::string year = parser.nextToken();

        //Telcom Module has date/Time format YYYYMMDDHHMMSS
        std::string AnlTime = year + mon + day + hh + min + "00";

        // skip 4 tokens
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();


        // next token looks like "ELK1-1".
        // ELK1 is the Sample location (not numeric, i.e. not exactly as specified),
        // and the number behind the minus sign is the sample number
        std::string sampleLocationAndNumber = parser.nextToken();
        std::string SampleLocation = sampleLocationAndNumber.substr(0,sampleLocationAndNumber.find('-'));
        std::string SampleCounter  = sampleLocationAndNumber.substr(sampleLocationAndNumber.find('-')+1,
                                      sampleLocationAndNumber.size()-sampleLocationAndNumber.find('-'));

        if (SampleLocation.substr(0,2)=="KV")
        {
          (*tlgLab)["Plant"] = 1L;  // BOF
          (*tlgLab)["PlantNo"] = SampleLocation.substr(2,3);
        }
        else if (SampleLocation.substr(0,3)=="ELK")
        {
          (*tlgLab)["Plant"] = 2L;  // LF
          (*tlgLab)["PlantNo"] = SampleLocation.substr(3,4);
        }
        else
        {
          std::stringstream Message;
          Message << "CTelcom_FileTransport: read undefined plant.";
          cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1);
        }

        // OrderID is specified in the Telegram but not contained in the file.
        (*tlgLab)["OrderID"] = "";

        // LadleNo is specified in the Telegram but not contained in the file.
        (*tlgLab)["LadleNo"] = 0L;

        // set SampleCounter
        (*tlgLab)["SmplCounter"] = SampleCounter;

        // heat no:
        std::string HeatNo = parser.nextToken();
        (*tlgLab)["HeatID"] = HeatNo;

        // TreatId is specified in the Telegram but not contained in the file.
        (*tlgLab)["TreatID"] = "";

        // set sample code ( isdemir does not use sample code
        (*tlgLab)["SmplCode"] = "";

        // set anl time
        (*tlgLab)["SmplTime"].set(AnlTime);

        // set process stage
        (*tlgLab)["ProcessStage"].set(0L);

        // sample is usable
        (*tlgLab)["SmplUsable"].set(1L);

        // skip 2 tokens
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();

        // skip 5 tokens
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();

        // No of ANalysis elements
        std::string noEle = parser.nextToken();

        // next are analysis pairs of ( ElementName,  Conc %)
        std::string Elem;
        std::string Conc;
        std::map<std::string, double>    eleMap;

        while ((Elem = parser.nextToken()) != ","
            && (Conc = parser.nextToken()) != ",")
        {
          // here we have a valid Element/Conc pair.
          strstrmaptype::const_iterator it;
          if ((it = elemTransSteelHM.find(Elem)) != elemTransSteelHM.end())
          {
            if ((*it).second != "")
            {
              double d;
              std::stringstream s;
              // Conc may contain special characters like '>'. Get rid of it.

              for (long ll=0; ll < (long)Conc.length(); ll++)
              {
                if (!isdigit(Conc[ll]))
                  Conc[ll]=' ';
                else break; // only until we see 1st digit
              }

              s.str(Conc);
              s >> d;
              (*tlgLab)[(*it).second]=d;

              std::stringstream Message;
              Message << Elem << " : " << d;
              cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 2);
            }
            else
            {
              std::stringstream Message;
              Message << "CTelcom_FileTransport: read undefined Element named <" << Elem << ">.";
              cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1);
            }
          }
          else
          {
            // dont know what to do with element Elem
            std::stringstream Message;
            Message << "CTelcom_FileTransport: read undefined Element named <" << Elem << ">." << " ";
            cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1);
          }
        }
        (*tlgLab)["AnlValSteel_SP1"] = 1L;
        (*tlgLab)["AnlValSteel_SP2"] = 2L;
        (*tlgLab)["AnlValSteel_SP3"] = 3L;
        (*tlgLab)["AnlValSteel_SP4"] = 4L;
        (*tlgLab)["AnlValSteel_SP5"] = 5L;


        tlgLab->setSerializer(FormatMgr::instance()->getSerializer(m_LocalMsgFormat));

        tofillMsg->clear();
        tofillMsg->setType(TlgName);
        tofillMsg->setBufFormat(m_LocalMsgFormat);
        tlgLab->serialize(tofillMsg->bufOstr() );        // Copy the local message to user's TCMessage

        delete tlgLab;
        retval = tofillMsg->bufLen();
        return retval;
      }
  }
  return retval;
}


//===============================================================================================


//##ModelId=43818A0A0192
int CTelcom_FileTransport::receiveSlagAnl()
{
  int retval = -1;
  std::string TlgName("LBL212");

  if (openFile && tofillMsg)   
  {
      bool done = false;
      char line[1000];
      do
      {
        openFile->getline (line, sizeof(line));
      }
      while (line[0] != 'N' && ! (done = openFile->eof())) ;

      if (done ) 
      {
        // read the file to the end or the 1st line that is not good.
        finishedFileProcessing = true;  // signal we can delete/rename it...
        setFinished(true);
        retval = -1;
        //throw ETransport("File successfully read to the end (this is not an error)");
      }
      else
      {
        // parse line and have 1 telegram
        /////////////////////////////////

        Tlg *tlgLab = m_pFactory->makeTlg(TlgName);
        long blen = tlgLab->getLen()-(m_pFactory->getTlg(headTlgName)->getLen());
        tlgLab->clear();

        CDateTime now;
        std::string tlgDate = now.asString ("%Y%m%d");       // "20011231"  - YYYYMMDD 
        std::string tlgTime = now.asString ("%H%M%S***");    // "134559999" - HHMMSSmmm
        
        (*tlgLab)["Header"]["MsgID"].set(TlgName);
        (*tlgLab)["Header"]["CreaDate"].set(tlgDate.c_str());
        (*tlgLab)["Header"]["CreaTime"].set(tlgTime.c_str());

        (*tlgLab)["Header"]["Org"].set(20L);
        (*tlgLab)["Header"]["Blen"].set(blen);
        (*tlgLab)["Header"]["Reserve"].set(" ");

        cTokenizer parser(line);
        std::string   dummy = parser.nextToken();

        // read date/time
        std::string hh   = parser.nextToken();
        std::string min  = parser.nextToken();
        std::string day  = parser.nextToken();
        std::string mon  = parser.nextToken();
        std::string year = parser.nextToken();

        //Telcom Module has date/Time format YYYYMMDDHHMMSS
        std::string AnlTime = year + mon + day + hh + min + "00";

        // The Tlg requires an Action flag but we dont have it -
        // set to always 1.
        // The value is never evaluated nor used.

        // skip 4 tokens
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();


        // next token looks like "ELK1-1" or "KV1-1".
        // KG2 is the Sample location (not numeric, i.e. not exactly as specified),
        // and the number behind the minus sign is the sample number ( not yet at HM )
        std::string sampleLocationAndNumber = parser.nextToken();
        std::string SampleLocation = sampleLocationAndNumber.substr(0,sampleLocationAndNumber.find('-'));
        std::string SampleCounter;
        if (sampleLocationAndNumber.find('-') != std::string::npos)
        {
          SampleCounter = sampleLocationAndNumber.substr(sampleLocationAndNumber.find('-')+1,
                           sampleLocationAndNumber.size()-sampleLocationAndNumber.find('-'));
        }

        // set plant and plant number
        if (SampleLocation.substr(0,2)=="KV")
        {
          (*tlgLab)["Plant"] = 1L;  // BOF
          (*tlgLab)["PlantNo"] = SampleLocation.substr(2,3);
        }
        else if (SampleLocation.substr(0,3)=="ELK")
        {
          (*tlgLab)["Plant"] = 2L;  // LF
          (*tlgLab)["PlantNo"] = SampleLocation.substr(3,4);
        }
        else
        {
          std::stringstream Message;
          Message << "CTelcom_FileTransport: receiveSlagAnl: read undefined plant.";
          cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1);
        }

        // Set HeadID.
        std::string HeatID = parser.nextToken();
        (*tlgLab)["HeatID"] = HeatID;

        // No order id.
        (*tlgLab)["OrderID"] = "";

        // LadleNo not used at Isdemir
        (*tlgLab)["LadleNo"].set("");

        // set SampleCounter
        if (SampleCounter.empty())
        {
          std::string mes("WARNING: receiveSlagAnl: No sample counter received.");
          mes += " Counter is default set to 1";
          cCBS_StdLog_Task::getInstance()->log(mes.c_str(), 1);
          (*tlgLab)["SmplCounter"] = "1";
        }
        else
          (*tlgLab)["SmplCounter"] = SampleCounter;

        // set sample code ( isdemir does not use sample code
        (*tlgLab)["SmplCode"] = "";

        // set anl time
        (*tlgLab)["SmplTime"].set(AnlTime);
        
        // set process stage
        (*tlgLab)["ProcessStage"].set(0L);

        // sample is useble
        (*tlgLab)["SmplUsable"].set(1L);


        // skip 8 tokens
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();

        // No of ANalysis elements
        std::string noEle = parser.nextToken();

        // next are analysis pairs of ( ElementName,  Conc %)
        std::string Elem;
        std::string Conc;
        std::map<std::string, double>    eleMap;

        while ((Elem = parser.nextToken()) != ","
            && (Conc = parser.nextToken()) != ",")
        {
          // here we have a valid Element/Conc pair.
          strstrmaptype::const_iterator it;
          if ((it = elemTransSlag.find(Elem)) != elemTransSlag.end())
          {
            if ((*it).second != "")
            {
              double d;
              std::stringstream s;
              // Conc may contain special characters like '>'. Get rid of it.

              for (long ll=0; ll < (long)Conc.length(); ll++)
              {
                if (!isdigit(Conc[ll]))
                  Conc[ll]=' ';
                else break; // only until we see 1st digit
              }

              s.str(Conc);
              s >> d;
              (*tlgLab)[(*it).second]=d;

              //std::stringstream Message;
              //Message << Elem << " : " << d;
              //cCBS_StdLog_Task::getInstance()->log(Message.str().c_str());
            }
            else
            {
              std::stringstream Message;
              Message << "CTelcom_FileTransport: read undefined Element named <" << Elem << ">.";
              cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1);
            }
          }
          else
          {
            // dont know what to do with element Elem
            std::stringstream Message;
            Message << "CTelcom_FileTransport: read undefined Element named <" << Elem << ">." << " ";
            cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1);
          }
        }
        (*tlgLab)["AnlValSlag_SP1"] = 1L;
        (*tlgLab)["AnlValSlag_SP2"] = 2L;
        (*tlgLab)["AnlValSlag_SP3"] = 3L;
        (*tlgLab)["AnlValSlag_SP4"] = 4L;
        (*tlgLab)["AnlValSlag_SP5"] = 5L;


        tlgLab->setSerializer(FormatMgr::instance()->getSerializer(m_LocalMsgFormat));

        tofillMsg->clear();
        tofillMsg->setType(TlgName);
        tofillMsg->setBufFormat(m_LocalMsgFormat);
        tlgLab->serialize(tofillMsg->bufOstr() );        // Copy the local message to user's TCMessage

        delete tlgLab;
        retval = tofillMsg->bufLen();
        return retval;
      }
  }
  return retval;
}


//=======================================================================================


//##ModelId=438199B5006A
int CTelcom_FileTransport::receiveHotMetalAnl()
{
  int retval = 0;
  std::string TlgName("LBL213");

  if (openFile && tofillMsg)   
  {
      bool done = false;
      char line[1000];
      do 
      {
        openFile->getline (line, sizeof(line));
      }
      while (line[0] != 'N' && ! (done = openFile->eof())) ;

      if (done ) 
      {
        // read the file to the end or the 1st line that is not good.

        finishedFileProcessing = true;  // signal we can delete/rename it...
        setFinished(true);
        retval = -1;
        //throw ETransport("File successfully read to the end (this is not an error)");
      }
      else
      {
        // parse line and have 1 telegram
        /////////////////////////////////

        Tlg *tlgLab = (m_pFactory)->makeTlg(TlgName);
        long blen = tlgLab->getLen()-(m_pFactory->getTlg(headTlgName)->getLen());
        tlgLab->clear();

        CDateTime now;
        std::string tlgDate = now.asString ("%Y%m%d");       // "20011231"  - YYYYMMDD 
        std::string tlgTime = now.asString ("%H%M%S***");    // "134559999" - HHMMSSmmm
        
        (*tlgLab)["Header"]["MsgID"].set(TlgName);
        (*tlgLab)["Header"]["CreaDate"].set(tlgDate.c_str());
        (*tlgLab)["Header"]["CreaTime"].set(tlgTime.c_str());

        (*tlgLab)["Header"]["Org"].set(20L);
        (*tlgLab)["Header"]["Blen"].set(blen);
        (*tlgLab)["Header"]["Reserve"].set(" ");

        cTokenizer parser(line);
        std::string   dummy = parser.nextToken();

        // read date/time
        std::string hh   = parser.nextToken();
        std::string min  = parser.nextToken();
        std::string day  = parser.nextToken();
        std::string mon  = parser.nextToken();
        std::string year = parser.nextToken();

        //Telcom Module has date/Time format YYYYMMDDHHMMSS
        std::string AnlTime = year + mon + day + hh + min + "00";

        // The Tlg requires an Action flag but we dont have it -
        // set to always 1.
        // The value is never evaluated nor used.

        // skip 4 tokens
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();


        // next token looks like "KG2" or "YF3".
        // KG2 is the Sample location (not numeric, i.e. not exactly as specified),
        // and the number behind the minus sign is the sample number ( not yet at HM )
        std::string sampleLocationAndNumber = parser.nextToken();
        std::string SampleLocation = sampleLocationAndNumber.substr(0,sampleLocationAndNumber.find('-'));
        std::string SampleCounter;
        if (sampleLocationAndNumber.find('-') != std::string::npos)
        {
          SampleCounter = sampleLocationAndNumber.substr(sampleLocationAndNumber.find('-')+1,
                           sampleLocationAndNumber.size()-sampleLocationAndNumber.find('-'));
        }

        // set plant and plant number
        if (SampleLocation.substr(0,2)=="KG")
        {
          (*tlgLab)["Plant"] = 1L;  // DS
          (*tlgLab)["PlantNo"] = SampleLocation.substr(2,3);
        }
        else if (SampleLocation.substr(0,2)=="YF")
        {
          (*tlgLab)["Plant"] = 2L;  // BF(blast furnace)
          (*tlgLab)["PlantNo"] = SampleLocation.substr(2,3);
        }
        else
        {
          std::stringstream Message;
          Message << "CTelcom_FileTransport: read undefined plant.";
          cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1);
        }

        // Hot metal analysis is not assigned to a heat.
        std::string HeatID = parser.nextToken();
        (*tlgLab)["HeatID"].set(HeatID);

        // set order id:
        (*tlgLab)["OrderID"].set("");

        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();

        // HMLadleNo
        std::string HMLadleNo = parser.nextToken();
        (*tlgLab)["HMLadleNo"].set(HMLadleNo);

        // set SampleCounter
        if (SampleCounter.empty())
          (*tlgLab)["SmplCounter"] = "1";
        else
          (*tlgLab)["SmplCounter"].set(SampleCounter);


        // set sample code ( isdemir does not use sample code
        (*tlgLab)["SmplCode"] = "";

        // set anl time
        (*tlgLab)["SmplTime"].set(AnlTime);
        
        // set process stage
        if (anlKind == eAnlKind::HMDSBefore)
          (*tlgLab)["ProcessStage"].set(1L);
        else if (anlKind == eAnlKind::HMDSAfter)
          (*tlgLab)["ProcessStage"].set(2L);
        else
          (*tlgLab)["ProcessStage"].set(0L);

        // sample is useble
        (*tlgLab)["SmplUsable"].set(1L);


        // skip 4 tokens
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();
        dummy=parser.nextToken();

        // No of ANalysis elements
        std::string noEle = parser.nextToken();

        // next are analysis pairs of ( ElementName,  Conc %)
        std::string Elem;
        std::string Conc;
        std::map<std::string, double>    eleMap;

        while ((Elem = parser.nextToken()) != ","
            && (Conc = parser.nextToken()) != ",")
        {
          // here we have a valid Element/Conc pair.
          strstrmaptype::const_iterator it;
          if ((it = elemTransSteelHM.find(Elem)) != elemTransSteelHM.end())
          {
            if ((*it).second != "")
            {
              double d;
              std::stringstream s;
              // Conc may contain special characters like '>'. Get rid of it.

              for (long ll=0; ll < (long)Conc.length(); ll++)
              {
                if (!isdigit(Conc[ll]))
                  Conc[ll]=' ';
                else break; // only until we see 1st digit
              }

              s.str(Conc);
              s >> d;
              (*tlgLab)[(*it).second]=d;

              std::stringstream Message;
              Message << Elem << " : " << d;
              cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 2);
            }
            else
            {
              std::stringstream Message;
              Message << "CTelcom_FileTransport: read undefined Element named <" << Elem << ">.";
              cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1);
            }
          }
          else
          {
            // dont know what to do with element Elem
            std::stringstream Message;
            Message << "CTelcom_FileTransport: read undefined Element named <" << Elem << ">." << " ";
            cCBS_StdLog_Task::getInstance()->log(Message.str().c_str(), 1);
          }
        }
        (*tlgLab)["AnlValSteel_SP1"] = 1L;
        (*tlgLab)["AnlValSteel_SP2"] = 2L;
        (*tlgLab)["AnlValSteel_SP3"] = 3L;
        (*tlgLab)["AnlValSteel_SP4"] = 4L;
        (*tlgLab)["AnlValSteel_SP5"] = 5L;


        tlgLab->setSerializer(FormatMgr::instance()->getSerializer(m_LocalMsgFormat));

        tofillMsg->clear();
        tofillMsg->setType(TlgName);
        tofillMsg->setBufFormat(m_LocalMsgFormat);
        tlgLab->serialize(tofillMsg->bufOstr() );        // Copy the local message to user's TCMessage

        delete tlgLab;
        retval = tofillMsg->bufLen();
        return retval;
      }
  }
  return retval;
}

void CTelcom_FileTransport::setFactory(TlgFactory* Factory)
{
	m_pFactory = Factory;
}

void CTelcom_FileTransport::setHeaderTlgType(std::string headName)
{
  headName = headName;
}