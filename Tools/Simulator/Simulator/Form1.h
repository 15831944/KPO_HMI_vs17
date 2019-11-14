#pragma once

#include "CSenderForm.h"
#include "CReceiverForm.h"
#include "CSenderForm.h"
#include "CItemBaseContainerWrapper.h"
#include "CMessageForm.h"
#include "CInterConnectionListe.h"
#include "CSocketConnectionForm.h"
#include "CStatusConnectionForm.h"
#include "CSzenarium.h"
#include "CXmlSzenWriter.h"
#include "CXmlSzenReader.h"
#include "CXmlInterConfigWriter.h"
#include "CInterConfigWrapper.h"
#include "CTlgInterfaceWrapper.h"
#include "CTlgLogFileReaderWrapper.h"
#include "CMessageWriter.h"
#include "CInterConnection.h"
#include "CAppSetting.h"
#include "CInfoForm.h"
#include "CInterConfigForm.h"
#include "CTlgContainerSortForm.h"
#include "CTlgContainerFindForm.h"
#include "CTlgContainerFilterForm.h"
#include "CBofMainForm.h"
#include "CProgressBarViewForm.h"
#include "CSplashForm.h"

#undef MessageBox

namespace simulator
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
  using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary> 
	/// Zusammenfassung für Form1
	///
	/// Achtung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie die Eigenschaft
	///          'Ressourcendateiname' für das Compilertool für verwaltete Ressourcen ändern, 
	///          das allen .resx-Dateien zugewiesen ist, von denen diese Klasse abhängt. 
	///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{	  
  public:
		Form1(CSplashForm^ splash)
		{
			this->Splash = splash;
      InitializeComponent();
			initComponent();
      splash->Close();
		}

    value struct ifNewIncfFileTyp
    {
      bool newFile;
      String^ path;
      String^ inter;
    };
    value struct ifNewIncfFileTyp^ ifNewIncfFile; 
  
	protected:
	//void Dispose(Boolean disposing)
	//{
	//	if (disposing && components)
	//	{
	//		components->Dispose();
	//	}
	//	__super::Dispose(disposing);
	//}
	private: System::Windows::Forms::MainMenu ^  mainMenu;
  private: System::Windows::Forms::Panel ^  panHead;
	private: System::Windows::Forms::Panel ^  panViewBackGround;
	private: System::Windows::Forms::MenuItem ^  menuFileOpenNew;
	private: System::Windows::Forms::MenuItem ^  menuFileOpenAdd;
	private: System::Windows::Forms::MenuItem ^  MenuModel;
	private: System::Windows::Forms::MenuItem ^  menuFileOpen;
  private: System::Windows::Forms::MenuItem ^  menuSzenarium;
  private: System::Windows::Forms::MenuItem ^  menuSzenSend;
  private: System::Windows::Forms::Label ^  labInterfaceName;
  private: System::Windows::Forms::MenuItem ^  menuItem1;
  private: System::Windows::Forms::MenuItem ^  menuViewSender;
  private: System::Windows::Forms::MenuItem ^  menuViewReceiver;
	private: System::Windows::Forms::MenuItem ^  menuItem2;
	private: System::Windows::Forms::MenuItem ^  MenuInerConnection;
	private: System::Windows::Forms::MenuItem ^  menuInterConnStatus;
  private: System::Windows::Forms::Label ^  labInter;
  private: System::Windows::Forms::Label ^  labVersion;
  private: System::Windows::Forms::Label ^  labVersionInfo;
  private: System::Windows::Forms::MenuItem ^  menuInterConfig;
  private: System::Windows::Forms::MenuItem ^  MenuLogFile;
  private: System::Windows::Forms::MenuItem ^  MenuInterfaceLoad;
  private: System::Windows::Forms::MenuItem ^  MenuInterfaceRemove;
  private: System::Windows::Forms::MenuItem ^  MenuLogFileSort;
  private: System::Windows::Forms::MenuItem ^  MenuLogFileFilter;
  private: System::Windows::Forms::MenuItem ^  MenuLogFileFind;
  private: System::Windows::Forms::MenuItem ^  MenuLogFileClose;
  private: System::Windows::Forms::MenuItem ^  MenuSzenariumOpen;
  private: System::Windows::Forms::MenuItem ^  menuItem3;
  private: System::Windows::Forms::MenuItem ^  MenuSzenariumFind;
  private: System::Windows::Forms::MenuItem ^  menuItem4;
  private: System::Windows::Forms::MenuItem ^  menuItem5;
  private: System::Windows::Forms::MenuItem ^  menuItem6;
  private: System::Windows::Forms::MenuItem ^  menuModelSpez;
  private: System::Windows::Forms::MenuItem ^  menuModelSpezBof;
  private: System::Windows::Forms::MenuItem ^  menuLogFileTrace;
	private: System::Windows::Forms::MenuItem ^  menuItem7;
  private: System::Windows::Forms::MenuItem^  MenuHelp;
  private: System::Windows::Forms::HelpProvider^  helpProvider1;
  private: System::Windows::Forms::MenuItem^  menuItemHelpIndex;
  private: System::Windows::Forms::MenuItem^  menuItemContents;
  private: System::Windows::Forms::MenuItem^  menuItemHelpAbout;
  private: System::Windows::Forms::MenuItem^  MenuCyclicTelegrams;
  private: System::Windows::Forms::MenuItem^  MenuCyclicShow;
  private: System::Windows::Forms::MenuItem^  MenuCyclicSend;
  private: System::Windows::Forms::MenuItem^  MenuCyclicStop;
  private: System::Windows::Forms::MenuItem^  MenuRemoveAllCyclicTelegrams;
  private: System::Windows::Forms::MenuItem^  MenuSaveRealTimeSzen;
  private: System::Windows::Forms::MenuItem^  MenuSaveSimpleTimeSzen;
  private: System::Windows::Forms::MenuItem^  MenuSettings;
  private: System::Windows::Forms::MenuItem^  MenuAppConf;
  private: System::Windows::Forms::MenuItem^  CreateSzenarioWithConditions;
  private: System::Windows::Forms::MenuItem^  menuItem8;
  private: System::Windows::Forms::MenuItem^  menuItemIgnoreTimeOfUnselectedTlgs;
  private: System::Windows::Forms::MenuItem^  menuItem9;
  private: System::Windows::Forms::MenuItem^  menuItemCorbaViewer;
  private: System::ComponentModel::IContainer^  components;

private:
	/// <summary>
	/// Erforderliche Designervariable.
	/// </summary>


	/// <summary>
	/// Erforderliche Methode für die Designerunterstützung. 
	/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
	/// </summary>
	void InitializeComponent(void)
	{
    this->components = (gcnew System::ComponentModel::Container());
    this->mainMenu = (gcnew System::Windows::Forms::MainMenu(this->components));
    this->MenuModel = (gcnew System::Windows::Forms::MenuItem());
    this->MenuInterfaceLoad = (gcnew System::Windows::Forms::MenuItem());
    this->menuItem2 = (gcnew System::Windows::Forms::MenuItem());
    this->MenuInterfaceRemove = (gcnew System::Windows::Forms::MenuItem());
    this->MenuInerConnection = (gcnew System::Windows::Forms::MenuItem());
    this->menuInterConnStatus = (gcnew System::Windows::Forms::MenuItem());
    this->menuInterConfig = (gcnew System::Windows::Forms::MenuItem());
    this->MenuLogFile = (gcnew System::Windows::Forms::MenuItem());
    this->menuFileOpen = (gcnew System::Windows::Forms::MenuItem());
    this->menuFileOpenNew = (gcnew System::Windows::Forms::MenuItem());
    this->menuFileOpenAdd = (gcnew System::Windows::Forms::MenuItem());
    this->MenuLogFileSort = (gcnew System::Windows::Forms::MenuItem());
    this->MenuLogFileFilter = (gcnew System::Windows::Forms::MenuItem());
    this->MenuLogFileFind = (gcnew System::Windows::Forms::MenuItem());
    this->MenuLogFileClose = (gcnew System::Windows::Forms::MenuItem());
    this->menuItem5 = (gcnew System::Windows::Forms::MenuItem());
    this->menuItem6 = (gcnew System::Windows::Forms::MenuItem());
    this->menuLogFileTrace = (gcnew System::Windows::Forms::MenuItem());
    this->menuSzenarium = (gcnew System::Windows::Forms::MenuItem());
    this->MenuSzenariumOpen = (gcnew System::Windows::Forms::MenuItem());
    this->menuItem3 = (gcnew System::Windows::Forms::MenuItem());
    this->MenuSaveRealTimeSzen = (gcnew System::Windows::Forms::MenuItem());
    this->MenuSaveSimpleTimeSzen = (gcnew System::Windows::Forms::MenuItem());
    this->MenuRemoveAllCyclicTelegrams = (gcnew System::Windows::Forms::MenuItem());
    this->MenuSzenariumFind = (gcnew System::Windows::Forms::MenuItem());
    this->menuSzenSend = (gcnew System::Windows::Forms::MenuItem());
    this->menuItem4 = (gcnew System::Windows::Forms::MenuItem());
    this->menuItem7 = (gcnew System::Windows::Forms::MenuItem());
    this->CreateSzenarioWithConditions = (gcnew System::Windows::Forms::MenuItem());
    this->menuItem8 = (gcnew System::Windows::Forms::MenuItem());
    this->menuItemIgnoreTimeOfUnselectedTlgs = (gcnew System::Windows::Forms::MenuItem());
    this->menuItem1 = (gcnew System::Windows::Forms::MenuItem());
    this->menuViewSender = (gcnew System::Windows::Forms::MenuItem());
    this->menuViewReceiver = (gcnew System::Windows::Forms::MenuItem());
    this->menuModelSpez = (gcnew System::Windows::Forms::MenuItem());
    this->menuModelSpezBof = (gcnew System::Windows::Forms::MenuItem());
    this->MenuCyclicTelegrams = (gcnew System::Windows::Forms::MenuItem());
    this->MenuCyclicShow = (gcnew System::Windows::Forms::MenuItem());
    this->MenuCyclicSend = (gcnew System::Windows::Forms::MenuItem());
    this->MenuCyclicStop = (gcnew System::Windows::Forms::MenuItem());
    this->MenuSettings = (gcnew System::Windows::Forms::MenuItem());
    this->MenuAppConf = (gcnew System::Windows::Forms::MenuItem());
    this->menuItem9 = (gcnew System::Windows::Forms::MenuItem());
    this->menuItemCorbaViewer = (gcnew System::Windows::Forms::MenuItem());
    this->MenuHelp = (gcnew System::Windows::Forms::MenuItem());
    this->menuItemContents = (gcnew System::Windows::Forms::MenuItem());
    this->menuItemHelpIndex = (gcnew System::Windows::Forms::MenuItem());
    this->menuItemHelpAbout = (gcnew System::Windows::Forms::MenuItem());
    this->panHead = (gcnew System::Windows::Forms::Panel());
    this->labVersionInfo = (gcnew System::Windows::Forms::Label());
    this->labVersion = (gcnew System::Windows::Forms::Label());
    this->labInter = (gcnew System::Windows::Forms::Label());
    this->labInterfaceName = (gcnew System::Windows::Forms::Label());
    this->panViewBackGround = (gcnew System::Windows::Forms::Panel());
    this->helpProvider1 = (gcnew System::Windows::Forms::HelpProvider());
    this->panHead->SuspendLayout();
    this->SuspendLayout();
    // 
    // mainMenu
    // 
    this->mainMenu->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(9) {this->MenuModel, this->MenuLogFile, 
      this->menuSzenarium, this->menuItem1, this->menuModelSpez, this->MenuCyclicTelegrams, this->MenuSettings, this->menuItem9, this->MenuHelp});
    this->mainMenu->RightToLeft = System::Windows::Forms::RightToLeft::No;
    // 
    // MenuModel
    // 
    this->MenuModel->Index = 0;
    this->MenuModel->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(6) {this->MenuInterfaceLoad, 
      this->menuItem2, this->MenuInterfaceRemove, this->MenuInerConnection, this->menuInterConnStatus, this->menuInterConfig});
    this->MenuModel->Text = L"&Interface";
    this->MenuModel->Select += gcnew System::EventHandler(this, &Form1::MenuModel_Click);
    this->MenuModel->Click += gcnew System::EventHandler(this, &Form1::MenuModel_Click);
    // 
    // MenuInterfaceLoad
    // 
    this->MenuInterfaceLoad->Index = 0;
    this->MenuInterfaceLoad->Text = L"Load Interface";
    this->MenuInterfaceLoad->Click += gcnew System::EventHandler(this, &Form1::OnMenuFileLoadModelClick);
    // 
    // menuItem2
    // 
    this->menuItem2->Index = 1;
    this->menuItem2->Text = L"View";
    // 
    // MenuInterfaceRemove
    // 
    this->MenuInterfaceRemove->Index = 2;
    this->MenuInterfaceRemove->Text = L"Remove Interface";
    this->MenuInterfaceRemove->Click += gcnew System::EventHandler(this, &Form1::OnInterfaceRemoveClick);
    // 
    // MenuInerConnection
    // 
    this->MenuInerConnection->Index = 3;
    this->MenuInerConnection->Text = L"Connection";
    this->MenuInerConnection->Click += gcnew System::EventHandler(this, &Form1::OnMenuConnectionClick);
    // 
    // menuInterConnStatus
    // 
    this->menuInterConnStatus->Index = 4;
    this->menuInterConnStatus->Text = L"Connection Status";
    this->menuInterConnStatus->Click += gcnew System::EventHandler(this, &Form1::OnMenuInterConnStatus);
    // 
    // menuInterConfig
    // 
    this->menuInterConfig->Index = 5;
    this->menuInterConfig->Text = L"Configuration";
    this->menuInterConfig->Click += gcnew System::EventHandler(this, &Form1::OnClickMenuInterConfig);
    // 
    // MenuLogFile
    // 
    this->MenuLogFile->Index = 1;
    this->MenuLogFile->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(8) {this->menuFileOpen, this->MenuLogFileSort, 
      this->MenuLogFileFilter, this->MenuLogFileFind, this->MenuLogFileClose, this->menuItem5, this->menuItem6, this->menuLogFileTrace});
    this->MenuLogFile->Text = L"&Log-File";
    this->MenuLogFile->Select += gcnew System::EventHandler(this, &Form1::MenuLogFile_Select);
    // 
    // menuFileOpen
    // 
    this->menuFileOpen->Index = 0;
    this->menuFileOpen->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(2) {this->menuFileOpenNew, 
      this->menuFileOpenAdd});
    this->menuFileOpen->Text = L"Open Log File";
    // 
    // menuFileOpenNew
    // 
    this->menuFileOpenNew->Index = 0;
    this->menuFileOpenNew->Shortcut = System::Windows::Forms::Shortcut::CtrlO;
    this->menuFileOpenNew->Text = L"As New File";
    this->menuFileOpenNew->Click += gcnew System::EventHandler(this, &Form1::OnMenOpenFileClick);
    // 
    // menuFileOpenAdd
    // 
    this->menuFileOpenAdd->Index = 1;
    this->menuFileOpenAdd->Shortcut = System::Windows::Forms::Shortcut::CtrlShiftO;
    this->menuFileOpenAdd->Text = L"Add To File";
    this->menuFileOpenAdd->Click += gcnew System::EventHandler(this, &Form1::OnMenOpenFileClick);
    // 
    // MenuLogFileSort
    // 
    this->MenuLogFileSort->Index = 1;
    this->MenuLogFileSort->Text = L"Sort";
    this->MenuLogFileSort->Click += gcnew System::EventHandler(this, &Form1::OnMenuLogFileSortClick);
    // 
    // MenuLogFileFilter
    // 
    this->MenuLogFileFilter->Index = 2;
    this->MenuLogFileFilter->Text = L"Filter";
    this->MenuLogFileFilter->Click += gcnew System::EventHandler(this, &Form1::OnMenuLogFileFilterClick);
    // 
    // MenuLogFileFind
    // 
    this->MenuLogFileFind->Index = 3;
    this->MenuLogFileFind->Text = L"Find Telegram";
    this->MenuLogFileFind->Click += gcnew System::EventHandler(this, &Form1::OnMenuLogFileFindTelClick);
    // 
    // MenuLogFileClose
    // 
    this->MenuLogFileClose->Index = 4;
    this->MenuLogFileClose->Text = L"Close Log File";
    this->MenuLogFileClose->Click += gcnew System::EventHandler(this, &Form1::OnMenuLogFileCloseClick);
    // 
    // menuItem5
    // 
    this->menuItem5->Index = 5;
    this->menuItem5->Shortcut = System::Windows::Forms::Shortcut::CtrlS;
    this->menuItem5->Text = L"Select All";
    this->menuItem5->Click += gcnew System::EventHandler(this, &Form1::OnMenuLogFileSelectAll);
    // 
    // menuItem6
    // 
    this->menuItem6->Index = 6;
    this->menuItem6->Shortcut = System::Windows::Forms::Shortcut::CtrlN;
    this->menuItem6->Text = L"Remove Selection";
    this->menuItem6->Click += gcnew System::EventHandler(this, &Form1::OnMenuLogFileRemoveSel);
    // 
    // menuLogFileTrace
    // 
    this->menuLogFileTrace->Index = 7;
    this->menuLogFileTrace->Text = L"Analyze Log File";
    this->menuLogFileTrace->Click += gcnew System::EventHandler(this, &Form1::OnMenuLogFileTraceClick);
    // 
    // menuSzenarium
    // 
    this->menuSzenarium->Index = 2;
    this->menuSzenarium->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(9) {this->MenuSzenariumOpen, 
      this->menuItem3, this->MenuRemoveAllCyclicTelegrams, this->MenuSzenariumFind, this->menuSzenSend, this->menuItem4, this->menuItem7, 
      this->CreateSzenarioWithConditions, this->menuItem8});
    this->menuSzenarium->Text = L"&Scenario";
    this->menuSzenarium->Select += gcnew System::EventHandler(this, &Form1::menuSzenarium_Select);
    this->menuSzenarium->Click += gcnew System::EventHandler(this, &Form1::menuSzenarium_Click);
    // 
    // MenuSzenariumOpen
    // 
    this->MenuSzenariumOpen->Index = 0;
    this->MenuSzenariumOpen->Text = L"Open Scenario";
    this->MenuSzenariumOpen->Click += gcnew System::EventHandler(this, &Form1::OnMenuFileSzenOpenClick);
    // 
    // menuItem3
    // 
    this->menuItem3->Index = 1;
    this->menuItem3->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(2) {this->MenuSaveRealTimeSzen, 
      this->MenuSaveSimpleTimeSzen});
    this->menuItem3->Text = L"Save Scenario";
    // 
    // MenuSaveRealTimeSzen
    // 
    this->MenuSaveRealTimeSzen->Index = 0;
    this->MenuSaveRealTimeSzen->Text = L"Real Time";
    this->MenuSaveRealTimeSzen->Click += gcnew System::EventHandler(this, &Form1::OnMenuFileSaveSzen);
    // 
    // MenuSaveSimpleTimeSzen
    // 
    this->MenuSaveSimpleTimeSzen->Index = 1;
    this->MenuSaveSimpleTimeSzen->Text = L"Simple Time";
    this->MenuSaveSimpleTimeSzen->Click += gcnew System::EventHandler(this, &Form1::MenuSaveSimpleTimeSzen_Click);
    // 
    // MenuRemoveAllCyclicTelegrams
    // 
    this->MenuRemoveAllCyclicTelegrams->Index = 2;
    this->MenuRemoveAllCyclicTelegrams->Text = L"Remove All Cyclic Telegrams";
    this->MenuRemoveAllCyclicTelegrams->Click += gcnew System::EventHandler(this, &Form1::MenuRemoveAllCyclicTelegrams_Click);
    // 
    // MenuSzenariumFind
    // 
    this->MenuSzenariumFind->Index = 3;
    this->MenuSzenariumFind->Text = L"Find Telegram";
    this->MenuSzenariumFind->Click += gcnew System::EventHandler(this, &Form1::OnMenuLogFileFindTelClick);
    // 
    // menuSzenSend
    // 
    this->menuSzenSend->Index = 4;
    this->menuSzenSend->Text = L"Send";
    this->menuSzenSend->Click += gcnew System::EventHandler(this, &Form1::OnMenuSzenSendClick);
    // 
    // menuItem4
    // 
    this->menuItem4->Index = 5;
    this->menuItem4->Text = L"Stop";
    this->menuItem4->Click += gcnew System::EventHandler(this, &Form1::OnSzenStopClick);
    // 
    // menuItem7
    // 
    this->menuItem7->Index = 6;
    this->menuItem7->Text = L"Close Scenario";
    this->menuItem7->Click += gcnew System::EventHandler(this, &Form1::OnSzenCloseClick);
    // 
    // CreateSzenarioWithConditions
    // 
    this->CreateSzenarioWithConditions->Index = 7;
    this->CreateSzenarioWithConditions->Text = L"Create Szenario";
    this->CreateSzenarioWithConditions->Click += gcnew System::EventHandler(this, &Form1::CreateSzenarioWithConditions_Click);
    // 
    // menuItem8
    // 
    this->menuItem8->Index = 8;
    this->menuItem8->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(1) {this->menuItemIgnoreTimeOfUnselectedTlgs});
    this->menuItem8->Text = L"Options";
    // 
    // menuItemIgnoreTimeOfUnselectedTlgs
    // 
    this->menuItemIgnoreTimeOfUnselectedTlgs->Index = 0;
    this->menuItemIgnoreTimeOfUnselectedTlgs->Text = L"Ignore Time of unselected Tlgs";
    this->menuItemIgnoreTimeOfUnselectedTlgs->Click += gcnew System::EventHandler(this, &Form1::menuItemIgnoreTimeOfUnselectedTlgs_Click);
    // 
    // menuItem1
    // 
    this->menuItem1->Index = 3;
    this->menuItem1->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(2) {this->menuViewSender, this->menuViewReceiver});
    this->menuItem1->Text = L"View";
    // 
    // menuViewSender
    // 
    this->menuViewSender->Index = 0;
    this->menuViewSender->Text = L"Sender";
    this->menuViewSender->Click += gcnew System::EventHandler(this, &Form1::OnMenuViewSenderClick);
    // 
    // menuViewReceiver
    // 
    this->menuViewReceiver->Index = 1;
    this->menuViewReceiver->Text = L"Receiver";
    this->menuViewReceiver->Click += gcnew System::EventHandler(this, &Form1::OnMenuViewSenderClick);
    // 
    // menuModelSpez
    // 
    this->menuModelSpez->Index = 4;
    this->menuModelSpez->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(1) {this->menuModelSpezBof});
    this->menuModelSpez->Text = L"Model";
    // 
    // menuModelSpezBof
    // 
    this->menuModelSpezBof->Index = 0;
    this->menuModelSpezBof->Text = L"BOF";
    this->menuModelSpezBof->Click += gcnew System::EventHandler(this, &Form1::OnMenuModelSpezBof);
    // 
    // MenuCyclicTelegrams
    // 
    this->MenuCyclicTelegrams->Index = 5;
    this->MenuCyclicTelegrams->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(3) {this->MenuCyclicShow, 
      this->MenuCyclicSend, this->MenuCyclicStop});
    this->MenuCyclicTelegrams->Text = L"Cyclic Telegrams";
    this->MenuCyclicTelegrams->Select += gcnew System::EventHandler(this, &Form1::MenuCyclicTelegrams_Select);
    // 
    // MenuCyclicShow
    // 
    this->MenuCyclicShow->Index = 0;
    this->MenuCyclicShow->Text = L"Configuration";
    this->MenuCyclicShow->Click += gcnew System::EventHandler(this, &Form1::MenuCyclicShow_Click);
    // 
    // MenuCyclicSend
    // 
    this->MenuCyclicSend->Index = 1;
    this->MenuCyclicSend->Text = L"Send";
    this->MenuCyclicSend->Click += gcnew System::EventHandler(this, &Form1::MenuCyclicSend_Click);
    // 
    // MenuCyclicStop
    // 
    this->MenuCyclicStop->Index = 2;
    this->MenuCyclicStop->Text = L"Stop";
    this->MenuCyclicStop->Click += gcnew System::EventHandler(this, &Form1::MenuCyclicStop_Click);
    // 
    // MenuSettings
    // 
    this->MenuSettings->Index = 6;
    this->MenuSettings->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(1) {this->MenuAppConf});
    this->MenuSettings->Text = L"Settings";
    // 
    // MenuAppConf
    // 
    this->MenuAppConf->Index = 0;
    this->MenuAppConf->Text = L"Configuration";
    this->MenuAppConf->Click += gcnew System::EventHandler(this, &Form1::MenuAppConf_Click);
    // 
    // menuItem9
    // 
    this->menuItem9->Index = 7;
    this->menuItem9->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(1) {this->menuItemCorbaViewer});
    this->menuItem9->Text = L"Corba";
    // 
    // menuItemCorbaViewer
    // 
    this->menuItemCorbaViewer->Index = 0;
    this->menuItemCorbaViewer->Text = L"Corba Viewer";
    this->menuItemCorbaViewer->Click += gcnew System::EventHandler(this, &Form1::menuItemCorbaViewer_Click);
    // 
    // MenuHelp
    // 
    this->MenuHelp->Index = 8;
    this->MenuHelp->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(3) {this->menuItemContents, this->menuItemHelpIndex, 
      this->menuItemHelpAbout});
    this->MenuHelp->Text = L"Help";
    // 
    // menuItemContents
    // 
    this->menuItemContents->Index = 0;
    this->menuItemContents->Text = L"Content";
    this->menuItemContents->Click += gcnew System::EventHandler(this, &Form1::menuItemContents_Click);
    // 
    // menuItemHelpIndex
    // 
    this->menuItemHelpIndex->Index = 1;
    this->menuItemHelpIndex->Text = L"Index";
    this->menuItemHelpIndex->Click += gcnew System::EventHandler(this, &Form1::menuItemHelpIndex_Click);
    // 
    // menuItemHelpAbout
    // 
    this->menuItemHelpAbout->Index = 2;
    this->menuItemHelpAbout->Text = L"About Simulator";
    this->menuItemHelpAbout->Click += gcnew System::EventHandler(this, &Form1::menuItemHelpAbout_Click);
    // 
    // panHead
    // 
    this->panHead->BackColor = System::Drawing::SystemColors::Control;
    this->panHead->Controls->Add(this->labVersionInfo);
    this->panHead->Controls->Add(this->labVersion);
    this->panHead->Controls->Add(this->labInter);
    this->panHead->Controls->Add(this->labInterfaceName);
    this->panHead->Dock = System::Windows::Forms::DockStyle::Top;
    this->panHead->Enabled = false;
    this->panHead->Location = System::Drawing::Point(0, 0);
    this->panHead->Name = L"panHead";
    this->panHead->Size = System::Drawing::Size(776, 7);
    this->panHead->TabIndex = 0;
    // 
    // labVersionInfo
    // 
    this->labVersionInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
      static_cast<System::Byte>(0)));
    this->labVersionInfo->Location = System::Drawing::Point(232, 16);
    this->labVersionInfo->Name = L"labVersionInfo";
    this->labVersionInfo->Size = System::Drawing::Size(100, 23);
    this->labVersionInfo->TabIndex = 3;
    this->labVersionInfo->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
    this->labVersionInfo->Visible = false;
    // 
    // labVersion
    // 
    this->labVersion->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
      static_cast<System::Byte>(0)));
    this->labVersion->Location = System::Drawing::Point(120, 16);
    this->labVersion->Name = L"labVersion";
    this->labVersion->Size = System::Drawing::Size(64, 23);
    this->labVersion->TabIndex = 2;
    this->labVersion->Text = L"Version:";
    this->labVersion->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
    this->labVersion->Visible = false;
    // 
    // labInter
    // 
    this->labInter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
      static_cast<System::Byte>(0)));
    this->labInter->Location = System::Drawing::Point(120, 0);
    this->labInter->Name = L"labInter";
    this->labInter->Size = System::Drawing::Size(72, 16);
    this->labInter->TabIndex = 1;
    this->labInter->Text = L"Interface:";
    this->labInter->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
    this->labInter->Visible = false;
    // 
    // labInterfaceName
    // 
    this->labInterfaceName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, 
      System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
    this->labInterfaceName->Location = System::Drawing::Point(240, 0);
    this->labInterfaceName->Name = L"labInterfaceName";
    this->labInterfaceName->Size = System::Drawing::Size(160, 16);
    this->labInterfaceName->TabIndex = 0;
    this->labInterfaceName->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
    this->labInterfaceName->Visible = false;
    // 
    // panViewBackGround
    // 
    this->panViewBackGround->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
    this->panViewBackGround->Dock = System::Windows::Forms::DockStyle::Fill;
    this->panViewBackGround->Location = System::Drawing::Point(0, 7);
    this->panViewBackGround->Name = L"panViewBackGround";
    this->helpProvider1->SetShowHelp(this->panViewBackGround, true);
    this->panViewBackGround->Size = System::Drawing::Size(776, 666);
    this->panViewBackGround->TabIndex = 1;
    // 
    // helpProvider1
    // 
    this->helpProvider1->HelpNamespace = L"Simulator.chm";
    // 
    // Form1
    // 
    this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
    this->ClientSize = System::Drawing::Size(776, 673);
    this->Controls->Add(this->panViewBackGround);
    this->Controls->Add(this->panHead);
    this->HelpButton = true;
    this->helpProvider1->SetHelpNavigator(this, System::Windows::Forms::HelpNavigator::Index);
    this->Menu = this->mainMenu;
    this->Name = L"Form1";
    this->helpProvider1->SetShowHelp(this, true);
    this->Text = L"Simulator-Level 2 (Sender)";
    this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
    this->Load += gcnew System::EventHandler(this, &Form1::OnLoadSimForm);
    this->SizeChanged += gcnew System::EventHandler(this, &Form1::OnSizeChange);
    this->Closed += gcnew System::EventHandler(this, &Form1::OnCloseForm);
    this->panHead->ResumeLayout(false);
    this->ResumeLayout(false);

  }	
	System::Void OnLoadSimForm(System::Object ^  sender, System::EventArgs ^  e);
	System::Void OnMenOpenFileClick(System::Object ^  sender, System::EventArgs ^  e);
	System::Void OnMenuModelClick(System::Object ^  sender, System::EventArgs ^  e);
  // System::Void OnMenuSzenConnectionClick(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnMenuSzenSendClick(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnMenuFileLoadModelClick(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnMenuFileSaveSzen(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnMenuFileSzenOpenClick(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnMenuViewSenderClick(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnMenuConnectionClick(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnCloseForm(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnMenuInterConnStatus(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnSizeChange(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnClickMenuInterConfig(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnInterfaceRemoveClick(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnMenuLogFileSortClick(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnMenuLogFileFilterClick(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnMenuLogFileFindTelClick(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnMenuLogFileCloseClick(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnMenuSzenariumFindClick(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnSzenStopClick(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnMenuLogFileSelectAll(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnMenuLogFileRemoveSel(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnMenuModelSpezBof(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnMenuLogFileTraceClick(System::Object ^  sender, System::EventArgs ^  e);
  System::Void OnSzenCloseClick(System::Object ^  sender, System::EventArgs ^  e);
  System::Void menuItemHelpIndex_Click(System::Object^  sender, System::EventArgs^  e);
  System::Void menuItemContents_Click(System::Object^  sender, System::EventArgs^  e);
  System::Void menuItemHelpAbout_Click(System::Object^  sender, System::EventArgs^  e);
  System::Void MenuCyclicShow_Click(System::Object^  sender, System::EventArgs^  e);
  System::Void MenuCyclicSend_Click(System::Object^  sender, System::EventArgs^  e);
  System::Void MenuCyclicStop_Click(System::Object^  sender, System::EventArgs^  e);
  System::Void MenuRemoveAllCyclicTelegrams_Click(System::Object^  sender, System::EventArgs^  e);
  System::Void MenuSaveSimpleTimeSzen_Click(System::Object^  sender, System::EventArgs^  e);
  System::Void MenuAppConf_Click(System::Object^  sender, System::EventArgs^  e);
  System::Void MenuModel_Click(System::Object^  sender, System::EventArgs^  e);
  System::Void CreateSzenarioWithConditions_Click(System::Object^  sender, System::EventArgs^  e);
  System::Void MenuLogFile_Select(System::Object^  sender, System::EventArgs^  e);
  System::Void MenuCyclicTelegrams_Select(System::Object^  sender, System::EventArgs^  e);
  System::Void menuSzenarium_Select(System::Object^  sender, System::EventArgs^  e);
  System::Void menuItemCorbaViewer_Click(System::Object^  sender, System::EventArgs^  e);
  
  enum class DirectionType{Send,Rec};
	void initViewComponent();
  //		void setModel(CTlgBaseWrapper::ModelTyp mod);
  void loadInterfaces();
  void sendTlg();
  void initComponent();
  int loadInterface(String^ path);
  void treatRecConnection(int index);
  void disSocketConnection();
  void updateConnStatusLabel(String^ inter);
  void setKompPos();
  void changeActiveInterface(String^ inter);
	//int findInterface(String^ path);
  void updateConnectionSenderInfo(String^ inter);
  void updateConnectionReceiverInfo(String^ inter);
  bool IsInterLoaded(String^ name);
	void updateSzenariumMidus(int modi);
	void activateSenderMenu();
	void activateReceiverMenu();
	void setFilterLogFile(array <String^>^ reg);
	CTlgInterfaceWrapper^ getActiveInterfaceWrapper();
	void findInLogFile(int pos);
	void findInSzenarium(int pos);
	void sortedLogFileView();
  void setSzenUpdateModus(bool flag);
  void updateMenuLogFileView(bool flag);
  void logFileReadThread();
  String^ getInterfaceNameFromXmlFile(String^ path);
  bool setIncfFile(String^ path);
  void AbortLogFileReadThread();
  void CloseForm();
  void WriteMessage(String^ mes, int typ);
  void OpenSenderConnectionStatusDialog();

  CSenderForm^ SenderForm;
	CReceiverForm^ ReceiverForm;
  //		CTlgBaseWrapper^ TlgBaseWrapper;
	//CItemBaseContainerWrapper^ TlgContainerWrapper;
  //		CTlgBaseWrapper::ModelTyp Model;
  CSzenarium^ Szen;
  List<CTlgInterfaceWrapper^>^ InterfaceProtoArray;
  CStatusConnectionForm^ StatusConnectionForm;
  CMessageForm^ MessageForm;
  //CBofForm^ BofForm;
  CBofMainForm^ BofMainForm;
  //--------------------------------------------
  CTlgContainerSortForm^ TlgContainerSortForm;
  CTlgContainerFindForm^ TlgContainerFindForm;
  CTlgContainerFilterForm^ TlgContainerFilterForm;
  //--------------------------------------------
  CInterConnectionListe^ SendInterConnectionListe;
  CInterConnectionListe^ RecInterConnectionListe;
  int ActInterface;
	String^ Interface;
  DirectionType Direction;    

  //For LogFileRead - Thread
  //--------------------------------------------
	int RetLogFileReader;
  String^ interName;
  String^ fileName;
  System::Threading::Thread^ LogFileReadThread;
  CProgressBarViewForm^ barView;
  CSplashForm^ Splash;

  //gibt an, ob SimulatorForm beim Start geladen wird. Wird nur beim Interface Laden verwendet.
  bool isSimFormLoaded;
private: System::Void menuItemIgnoreTimeOfUnselectedTlgs_Click(System::Object^  sender, System::EventArgs^  e) {

           if (this->menuItemIgnoreTimeOfUnselectedTlgs->Checked)
           {
              this->menuItemIgnoreTimeOfUnselectedTlgs->Checked = false;
              this->SenderForm->setIgnoreDelayTimeOfUnselctedTlgs(false);
           }
           else
           {
              this->menuItemIgnoreTimeOfUnselectedTlgs->Checked = true;
              this->SenderForm->setIgnoreDelayTimeOfUnselctedTlgs(true);
           }
         }
private: System::Void menuSzenarium_Click(System::Object^  sender, System::EventArgs^  e) {
           


         }
};
}

