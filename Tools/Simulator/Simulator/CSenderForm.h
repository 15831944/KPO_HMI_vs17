#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


//-------------------------------------------------------------
#include "CTlgTreeViewForm.h"
#include "CTlgViewForm.h"
#include "CMessageForm.h"
#include "CSzenariumForm.h"
#include "CItemBaseContainerWrapper.h"
#include "CInterBaseManager.h"
#include "CInterSenderManager.h"
#include "CTlgInterfaceWrapper.h"
#include "CInterUseCase.h"
#include "CInterConnectionListe.h"
#include "CItemView.h"
//-------------------------------------------------------------

namespace simulator
{
	/// <summary> 
	/// Zusammenfassung für CFileReaderViewForm
	///
	/// Achtung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie die Eigenschaft
	///          'Ressourcendateiname' für das Compilertool für verwaltete Ressourcen ändern, 
	///          das allen .resx-Dateien zugewiesen ist, von denen diese Klasse abhängt. 
	///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public ref class CSenderForm : public System::Windows::Forms::Form
	{
     public: delegate void OpenSenderConnectionDialogTyp();
	public: 
		CSenderForm(void)
		{
			InitializeComponent();
			initViewComponent();
		}
		CSenderForm(Panel^ parent);
		CItemBaseContainerWrapper^ getLogFileContainer();
    CItemBaseContainerWrapper^ getSzenariumContainer();
		//CSzenarium^ getSzenarium();
		//void setColor(System::Drawing::Color col,int id);
		//void showSzenarium(CSzenarium^ szen);
		void setMessageForm(CMessageForm^ messForm);
		//void setActiveInterface(int index);
		void showInterfaceTlg();
		void showContainerTlg();
		void setTlgProtoTypContainer(CItemBaseContainerWrapper^ con);
		void setTlgContainer(CItemBaseContainerWrapper^ con);
		void sendSzenarium();
		void updateSzenFile();
		void addInterface(CTlgInterfaceWrapper^ inter,CInterConnection^ interConn);
    String^ findInterface(String^ path);
    void setActiveInterface(String^ inter);
    String^ getInterfaceDescr(String^ inter);
    String^ getInterfaceVersion(String^ inter);
		int loadLogFile(String^ path,String^ interName,bool const& abort);
		int getLogTlgCount(String^ interName);
		int getLogTlgTotalCount(String^ interName);
		void showLogTlg(String^ interName);
    void saveSzenarium(String^ path);
    void saveSimpleTimeSzenarium(String^ path);
    void loadSzenarium(String^ path);
		void updateUseCaseView();
    void stopSendSzenarium(bool abort);
		void setUpdateSzenariumModus(CSzenariumForm::SzenariumModusEventTyp^ event);
    void removeInter(String^ inter);
		void clearLogFile(String^ inter);
		void setFilterLogFile(array <String^>^ reg);
		void selectLogFileTelegram(int index);
		void selectSzenariumTelegram(int index);
    void enableSzenChangeMode(int mode);
    void setSzenUpdateEvent(CSzenariumForm::UpdateSzenEventTyp^ szenUpdateEvent);
    int getSelSzenItem();
    void closeLogFile();
    void selectAllTlgFromLogFile();
    void removeSelectionTlgFromLogFile();
    //! prueft, ob Telegramm - Log - File geladen ist
    bool isLogFileLoad(String^ inter);
    void setLogFileViewEventTyp(CTlgTreeViewForm::LogFileViewEventTyp^ event);
    void setLabConnStatus (int status);
    void clearUseCaseView();
    void ClosePrototypItemView();
    void removeSzenarioItemFromView();
    int getCountOfSzenarioItems();
    bool isSendMode(); 
    bool isSzenarioSending();
    void removeAllCyclicTlgInSzenario();
    bool isSzenarioCreated();
    bool TlgsFromInterInSzenario(String^ inter);
    int getLogFileTlgCount(String^ interName);
    List<CItemBaseContainerWrapper^>^ getAllLoadedLogFiles();
    void OpenAutoCreateSzenarioForm (List<CTlgInterfaceWrapper^>^ InterfaceProtoArray);
    void setOpenSenderConnectionDialogTyp(OpenSenderConnectionDialogTyp^ del);
    void setIgnoreDelayTimeOfUnselctedTlgs(bool value);
	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
	private: System::Windows::Forms::Panel ^  panTlgFileReader;
	private: System::Windows::Forms::Splitter ^  splitVer1;
	private: System::Windows::Forms::Panel ^  panMessage;
	private: System::Windows::Forms::Splitter ^  splitHor;
	private: System::Windows::Forms::Splitter ^  splitVer2;
	private: System::Windows::Forms::Panel ^  panTlgView;
	private: System::Windows::Forms::Panel ^  panUseCaseView;
  private: System::Windows::Forms::Panel ^  panConnStatus;
  private: System::Windows::Forms::Label ^  labConnStatus;
  private: System::Windows::Forms::ImageList ^  imageConnStatusList;
  private: System::Windows::Forms::Panel ^  panSzenAndConnStatus;
  private: System::Windows::Forms::Panel ^  panSzen;
  private: System::Windows::Forms::Label ^  labConnStatusDesc;
  private: System::Windows::Forms::Panel^  panTlgFileReaderNew;
  private: System::Windows::Forms::Button^  butShowAllConStatus;
  private: System::ComponentModel::IContainer ^  components;
  private: System::Void splitVer1_DoubleClick(System::Object^  sender, System::EventArgs^  e);
  private: System::Void splitHor_DoubleClick(System::Object^  sender, System::EventArgs^  e);
  private: System::Void splitVer2_DoubleClick(System::Object^  sender, System::EventArgs^  e);
  private: System::Void labConnStatus_DoubleClick(System::Object^  sender, System::EventArgs^  e);
  private: System::Void butShowAllConStatus_Click(System::Object^  sender, System::EventArgs^  e); 


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
      System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(CSenderForm::typeid));
      this->panTlgFileReader = (gcnew System::Windows::Forms::Panel());
      this->panTlgFileReaderNew = (gcnew System::Windows::Forms::Panel());
      this->panConnStatus = (gcnew System::Windows::Forms::Panel());
      this->butShowAllConStatus = (gcnew System::Windows::Forms::Button());
      this->labConnStatusDesc = (gcnew System::Windows::Forms::Label());
      this->labConnStatus = (gcnew System::Windows::Forms::Label());
      this->imageConnStatusList = (gcnew System::Windows::Forms::ImageList(this->components));
      this->splitVer1 = (gcnew System::Windows::Forms::Splitter());
      this->panMessage = (gcnew System::Windows::Forms::Panel());
      this->splitHor = (gcnew System::Windows::Forms::Splitter());
      this->panSzenAndConnStatus = (gcnew System::Windows::Forms::Panel());
      this->panSzen = (gcnew System::Windows::Forms::Panel());
      this->splitVer2 = (gcnew System::Windows::Forms::Splitter());
      this->panUseCaseView = (gcnew System::Windows::Forms::Panel());
      this->panTlgView = (gcnew System::Windows::Forms::Panel());
      this->panTlgFileReader->SuspendLayout();
      this->panConnStatus->SuspendLayout();
      this->panSzenAndConnStatus->SuspendLayout();
      this->SuspendLayout();
      // 
      // panTlgFileReader
      // 
      this->panTlgFileReader->Controls->Add(this->panTlgFileReaderNew);
      this->panTlgFileReader->Controls->Add(this->panConnStatus);
      this->panTlgFileReader->Dock = System::Windows::Forms::DockStyle::Left;
      this->panTlgFileReader->Location = System::Drawing::Point(0, 0);
      this->panTlgFileReader->MinimumSize = System::Drawing::Size(215, 0);
      this->panTlgFileReader->Name = L"panTlgFileReader";
      this->panTlgFileReader->Size = System::Drawing::Size(216, 519);
      this->panTlgFileReader->TabIndex = 0;
      // 
      // panTlgFileReaderNew
      // 
      this->panTlgFileReaderNew->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panTlgFileReaderNew->Location = System::Drawing::Point(0, 26);
      this->panTlgFileReaderNew->Name = L"panTlgFileReaderNew";
      this->panTlgFileReaderNew->Size = System::Drawing::Size(216, 493);
      this->panTlgFileReaderNew->TabIndex = 1;
      // 
      // panConnStatus
      // 
      this->panConnStatus->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->panConnStatus->Controls->Add(this->butShowAllConStatus);
      this->panConnStatus->Controls->Add(this->labConnStatusDesc);
      this->panConnStatus->Controls->Add(this->labConnStatus);
      this->panConnStatus->Dock = System::Windows::Forms::DockStyle::Top;
      this->panConnStatus->Location = System::Drawing::Point(0, 0);
      this->panConnStatus->Name = L"panConnStatus";
      this->panConnStatus->Size = System::Drawing::Size(216, 26);
      this->panConnStatus->TabIndex = 0;
      // 
      // butShowAllConStatus
      // 
      this->butShowAllConStatus->Location = System::Drawing::Point(144, 1);
      this->butShowAllConStatus->Name = L"butShowAllConStatus";
      this->butShowAllConStatus->Size = System::Drawing::Size(58, 21);
      this->butShowAllConStatus->TabIndex = 2;
      this->butShowAllConStatus->Text = L"Show all";
      this->butShowAllConStatus->UseVisualStyleBackColor = true;
      this->butShowAllConStatus->Click += gcnew System::EventHandler(this, &CSenderForm::butShowAllConStatus_Click);
      // 
      // labConnStatusDesc
      // 
      this->labConnStatusDesc->Location = System::Drawing::Point(6, -1);
      this->labConnStatusDesc->Name = L"labConnStatusDesc";
      this->labConnStatusDesc->Size = System::Drawing::Size(103, 23);
      this->labConnStatusDesc->TabIndex = 1;
      this->labConnStatusDesc->Text = L"Connection status:";
      this->labConnStatusDesc->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      // 
      // labConnStatus
      // 
      this->labConnStatus->ImageIndex = 0;
      this->labConnStatus->ImageList = this->imageConnStatusList;
      this->labConnStatus->Location = System::Drawing::Point(115, 1);
      this->labConnStatus->Name = L"labConnStatus";
      this->labConnStatus->Size = System::Drawing::Size(23, 23);
      this->labConnStatus->TabIndex = 0;
      this->labConnStatus->DoubleClick += gcnew System::EventHandler(this, &CSenderForm::labConnStatus_DoubleClick);
      // 
      // imageConnStatusList
      // 
      this->imageConnStatusList->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imageConnStatusList.ImageStream")));
      this->imageConnStatusList->TransparentColor = System::Drawing::Color::Transparent;
      this->imageConnStatusList->Images->SetKeyName(0, L"");
      this->imageConnStatusList->Images->SetKeyName(1, L"");
      this->imageConnStatusList->Images->SetKeyName(2, L"");
      // 
      // splitVer1
      // 
      this->splitVer1->Location = System::Drawing::Point(216, 0);
      this->splitVer1->MaximumSize = System::Drawing::Size(3, 0);
      this->splitVer1->Name = L"splitVer1";
      this->splitVer1->Size = System::Drawing::Size(3, 519);
      this->splitVer1->TabIndex = 1;
      this->splitVer1->TabStop = false;
      this->splitVer1->DoubleClick += gcnew System::EventHandler(this, &CSenderForm::splitVer1_DoubleClick);
      // 
      // panMessage
      // 
      this->panMessage->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panMessage->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->panMessage->Location = System::Drawing::Point(219, 439);
      this->panMessage->Name = L"panMessage";
      this->panMessage->Size = System::Drawing::Size(659, 80);
      this->panMessage->TabIndex = 2;
      // 
      // splitHor
      // 
      this->splitHor->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->splitHor->Location = System::Drawing::Point(219, 436);
      this->splitHor->Name = L"splitHor";
      this->splitHor->Size = System::Drawing::Size(659, 3);
      this->splitHor->TabIndex = 3;
      this->splitHor->TabStop = false;
      this->splitHor->DoubleClick += gcnew System::EventHandler(this, &CSenderForm::splitHor_DoubleClick);
      // 
      // panSzenAndConnStatus
      // 
      this->panSzenAndConnStatus->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->panSzenAndConnStatus->Controls->Add(this->panSzen);
      this->panSzenAndConnStatus->Dock = System::Windows::Forms::DockStyle::Left;
      this->panSzenAndConnStatus->Location = System::Drawing::Point(219, 0);
      this->panSzenAndConnStatus->Name = L"panSzenAndConnStatus";
      this->panSzenAndConnStatus->Size = System::Drawing::Size(77, 436);
      this->panSzenAndConnStatus->TabIndex = 4;
      // 
      // panSzen
      // 
      this->panSzen->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panSzen->Location = System::Drawing::Point(0, 0);
      this->panSzen->MinimumSize = System::Drawing::Size(180, 0);
      this->panSzen->Name = L"panSzen";
      this->panSzen->Size = System::Drawing::Size(180, 434);
      this->panSzen->TabIndex = 1;
      // 
      // splitVer2
      // 
      this->splitVer2->Location = System::Drawing::Point(296, 0);
      this->splitVer2->MaximumSize = System::Drawing::Size(3, 0);
      this->splitVer2->Name = L"splitVer2";
      this->splitVer2->Size = System::Drawing::Size(3, 436);
      this->splitVer2->TabIndex = 5;
      this->splitVer2->TabStop = false;
      this->splitVer2->DoubleClick += gcnew System::EventHandler(this, &CSenderForm::splitVer2_DoubleClick);
      // 
      // panUseCaseView
      // 
      this->panUseCaseView->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->panUseCaseView->Dock = System::Windows::Forms::DockStyle::Top;
      this->panUseCaseView->Location = System::Drawing::Point(299, 0);
      this->panUseCaseView->Name = L"panUseCaseView";
      this->panUseCaseView->Size = System::Drawing::Size(579, 24);
      this->panUseCaseView->TabIndex = 9;
      // 
      // panTlgView
      // 
      this->panTlgView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panTlgView->Location = System::Drawing::Point(299, 24);
      this->panTlgView->MinimumSize = System::Drawing::Size(200, 0);
      this->panTlgView->Name = L"panTlgView";
      this->panTlgView->Size = System::Drawing::Size(579, 412);
      this->panTlgView->TabIndex = 12;
      // 
      // CSenderForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(878, 519);
      this->Controls->Add(this->panTlgView);
      this->Controls->Add(this->panUseCaseView);
      this->Controls->Add(this->splitVer2);
      this->Controls->Add(this->panSzenAndConnStatus);
      this->Controls->Add(this->splitHor);
      this->Controls->Add(this->panMessage);
      this->Controls->Add(this->splitVer1);
      this->Controls->Add(this->panTlgFileReader);
      this->Name = L"CSenderForm";
      this->Text = L"CSenderForm";
      this->Load += gcnew System::EventHandler(this, &CSenderForm::OnLoadForm);
      this->SizeChanged += gcnew System::EventHandler(this, &CSenderForm::OnSizeChangedForm);
      this->panTlgFileReader->ResumeLayout(false);
      this->panConnStatus->ResumeLayout(false);
      this->panSzenAndConnStatus->ResumeLayout(false);
      this->ResumeLayout(false);

    }		
		System::Void OnSizeChangedForm(System::Object ^  sender, System::EventArgs ^  e);
		System::Void OnLoadForm(System::Object ^  sender, System::EventArgs ^  e);
		//System::Void OnActivatedForm(System::Object ^  sender, System::EventArgs ^  e);
		System::Void OnButtUseCaseClick(System::Object ^  sender, System::EventArgs ^  e);
		
		CTlgTreeViewForm^ TlgTreeViewForm;
		/*CTlgViewForm^ TlgViewForm;*/
		CItemView^ TlgViewForm;
    CSzenariumForm^ SzenariumForm;
		CMessageForm^ MessageForm;
    System::Windows::Forms::ToolTip ^ConnStatusToolTip;
    ArrayList^ InterSenderManListe;
		String^ ActiveInterface;
    System::Threading::Thread^ SendSzenThread;
    OpenSenderConnectionDialogTyp^ OpenSenderConnectionDialogDel;

    void initViewComponent();
    void updateTlgPrototypView(CItemWrapper^ wrp,CItemView::CreateTypForm typ);
    void addToSzenarium(CItemWrapper^ tlg,double time,bool modi);
		void addToSzenarium(CItemWrapper^ tlg,bool modi);
    void updateTlgInSzenarium(CItemWrapper^ tlg);
		void messageHandler(String^ mess,int type);
		void messageErrorHandler(String^ error);
    void messageOkHandler(String^ info);
		//void sendTelegrams();
    CInterSenderManager^ getInterface(String^ inter);
    int getInterfaceIndex(String^ inter);
		void updateUseCaseView(CInterUseCase^ interUseCase);
    void updateContainerViewFromDeteilView();
    void updateSzenarioChange();
};
}
