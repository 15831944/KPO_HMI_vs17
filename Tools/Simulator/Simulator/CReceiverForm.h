#pragma once

#include "CTlgPrototypTreeViewForm.h"
#include "CTlgContainerTreeViewForm.h"
#include "CMessageForm.h"
//#include "CTlgDecoder.h"
//#include "CTlgInterRec.h"
#include "CInterConnectionListe.h"
//#include "CSocketConnState.h"
#include "CTlgInterfaceWrapper.h"
#include "CInterReceiverManager.h"
#include "CAnalyzeLogFileForm.h"
#include "CItemPrototypContainerForm.h"
#include "CItemView.h"

//-----------------------------------------
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

//public delegate  void DelUpdateConnRecInfo(String^ inter);

namespace simulator
{
  /// <summary> 
  /// Summary for CReceiverForm
  ///
  /// WARNING: If you change the name of this class, you will need to change the 
  ///          'Resource File Name' property for the managed resource compiler tool 
  ///          associated with all .resx files this class depends on.  Otherwise,
  ///          the designers will not be able to interact properly with localized
  ///          resources associated with this form.
  /// </summary>
  public ref class CReceiverForm : public System::Windows::Forms::Form
  {
  public: 
    //CReceiverForm(void)
    //{
    //  InitializeComponent();
    //  InterReceiverManListe = gcnew ArrayList();
    //  ReceiveTlgContainer = gcnew CTlgContainerWrapper();
    //}
      
    CReceiverForm(Panel^ parent);
    void setInterfaceList(ArrayList^ arr);
    void setActiveInterface(String^ inter);
    void setMessageForm(CMessageForm^ messForm);
    void setInterConnListe(CInterConnectionListe^ liste);
    void setConnListe(CInterConnectionListe^ recListe);
    void addInterface(CTlgInterfaceWrapper^ inter,CInterConnection^ interConn);
    // !!!
    void addInterface(CTlgInterfaceWrapper^ inter);
    void updateConnectionStatus(String^ inter);
    void removeInter(String^ inter);
    void showInterConnInfo();
    // !!!
    void showAnazyzeForm(int index,String^ path);
    void closeAnazyzeForm(); 
    
  protected: 
    //void Dispose(Boolean disposing)
    //{
    //  if (disposing && components)
    //  {
    //    components->Dispose();
    //  }
    //  __super::Dispose(disposing);
    //}
    private: System::Windows::Forms::Panel ^  panLeft;
    private: System::Windows::Forms::Splitter ^  splittVer1;
    private: System::Windows::Forms::Panel ^  panBottom;
    private: System::Windows::Forms::Splitter ^  splittHor1;
    private: System::Windows::Forms::Panel ^  panTlgView;

    private: System::Windows::Forms::Panel ^  panTreeView;
    private: System::Windows::Forms::Panel ^  panTreeViewHeader;
    private: System::Windows::Forms::Panel ^  panTreeViewCon;
    private: System::Windows::Forms::Label ^  labDescr;
    private: System::Windows::Forms::Panel ^  panCount;
    private: System::Windows::Forms::Label ^  label1;
    private: System::Windows::Forms::TextBox ^  txtBxCount;
    private: System::Windows::Forms::GroupBox ^  grpBxCon;
    private: System::Windows::Forms::Label ^  label2;
    private: System::Windows::Forms::Label ^  label3;
    private: System::Windows::Forms::Label ^  label4;
    private: System::Windows::Forms::Label ^  labInter;
    private: System::Windows::Forms::Label ^  labHostName;
    private: System::Windows::Forms::Label ^  labIpAddr;
    private: System::Windows::Forms::Label ^  labPort;
    private: System::Windows::Forms::Label ^  label9;
    private: System::Windows::Forms::GroupBox ^  groupBox1;

    private: System::Windows::Forms::Label ^  label5;
    private: System::Windows::Forms::Label ^  label6;


    private: System::Windows::Forms::Label ^  labConTyp;
    private: System::Windows::Forms::Label ^  labConStatus;
    private: System::Windows::Forms::CheckBox ^  checkBxAllTlg;
    private: System::Windows::Forms::Button ^  button1;
    private: System::Windows::Forms::Button ^  buttRec;

    private: System::ComponentModel::IContainer ^  components;


    private:
    /// <summary>
    /// Required designer variable.
    /// </summary>


    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void)
    {
      this->panLeft = gcnew System::Windows::Forms::Panel();
      this->panTreeView = gcnew System::Windows::Forms::Panel();
      this->panTreeViewCon = gcnew System::Windows::Forms::Panel();
      this->panTreeViewHeader = gcnew System::Windows::Forms::Panel();
      this->buttRec = gcnew System::Windows::Forms::Button();
      this->groupBox1 = gcnew System::Windows::Forms::GroupBox();
      this->checkBxAllTlg = gcnew System::Windows::Forms::CheckBox();
      this->grpBxCon = gcnew System::Windows::Forms::GroupBox();
      this->labConStatus = gcnew System::Windows::Forms::Label();
      this->labConTyp = gcnew System::Windows::Forms::Label();
      this->label6 = gcnew System::Windows::Forms::Label();
      this->label5 = gcnew System::Windows::Forms::Label();
      this->label9 = gcnew System::Windows::Forms::Label();
      this->labPort = gcnew System::Windows::Forms::Label();
      this->labIpAddr = gcnew System::Windows::Forms::Label();
      this->labHostName = gcnew System::Windows::Forms::Label();
      this->labInter = gcnew System::Windows::Forms::Label();
      this->label4 = gcnew System::Windows::Forms::Label();
      this->label3 = gcnew System::Windows::Forms::Label();
      this->label2 = gcnew System::Windows::Forms::Label();
      this->panCount = gcnew System::Windows::Forms::Panel();
      this->button1 = gcnew System::Windows::Forms::Button();
      this->txtBxCount = gcnew System::Windows::Forms::TextBox();
      this->label1 = gcnew System::Windows::Forms::Label();
      this->labDescr = gcnew System::Windows::Forms::Label();
      this->splittVer1 = gcnew System::Windows::Forms::Splitter();
      this->panBottom = gcnew System::Windows::Forms::Panel();
      this->splittHor1 = gcnew System::Windows::Forms::Splitter();
      this->panTlgView = gcnew System::Windows::Forms::Panel();
      this->panLeft->SuspendLayout();
      this->panTreeView->SuspendLayout();
      this->panTreeViewHeader->SuspendLayout();
      this->groupBox1->SuspendLayout();
      this->grpBxCon->SuspendLayout();
      this->panCount->SuspendLayout();
      this->SuspendLayout();
      // 
      // panLeft
      // 
      this->panLeft->Controls->Add(this->panTreeView);
      this->panLeft->Dock = System::Windows::Forms::DockStyle::Left;
      this->panLeft->Location = System::Drawing::Point(0, 0);
      this->panLeft->Name = "panLeft";
      this->panLeft->Size = System::Drawing::Size(216, 325);
      this->panLeft->TabIndex = 0;
      // 
      // panTreeView
      // 
      this->panTreeView->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panTreeView->Controls->Add(this->panTreeViewCon);
      this->panTreeView->Controls->Add(this->panTreeViewHeader);
      this->panTreeView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panTreeView->Location = System::Drawing::Point(0, 0);
      this->panTreeView->Name = "panTreeView";
      this->panTreeView->Size = System::Drawing::Size(216, 325);
      this->panTreeView->TabIndex = 1;
      // 
      // panTreeViewCon
      // 
      this->panTreeViewCon->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panTreeViewCon->Location = System::Drawing::Point(0, 224);
      this->panTreeViewCon->Name = "panTreeViewCon";
      this->panTreeViewCon->Size = System::Drawing::Size(212, 97);
      this->panTreeViewCon->TabIndex = 1;
      // 
      // panTreeViewHeader
      // 
      this->panTreeViewHeader->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->panTreeViewHeader->Controls->Add(this->buttRec);
      this->panTreeViewHeader->Controls->Add(this->groupBox1);
      this->panTreeViewHeader->Controls->Add(this->grpBxCon);
      this->panTreeViewHeader->Controls->Add(this->panCount);
      this->panTreeViewHeader->Controls->Add(this->labDescr);
      this->panTreeViewHeader->Dock = System::Windows::Forms::DockStyle::Top;
      this->panTreeViewHeader->Location = System::Drawing::Point(0, 0);
      this->panTreeViewHeader->Name = "panTreeViewHeader";
      this->panTreeViewHeader->Size = System::Drawing::Size(212, 224);
      this->panTreeViewHeader->TabIndex = 0;
      // 
      // buttRec
      // 
      this->buttRec->Location = System::Drawing::Point(128, 160);
      this->buttRec->Name = "buttRec";
      this->buttRec->Size = System::Drawing::Size(75, 32);
      this->buttRec->TabIndex = 4;
      this->buttRec->Text = "Receive";
      this->buttRec->Click += gcnew System::EventHandler(this, &CReceiverForm::OnButtRecClick);
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->checkBxAllTlg);
      this->groupBox1->Location = System::Drawing::Point(8, 153);
      this->groupBox1->Name = "groupBox1";
      this->groupBox1->Size = System::Drawing::Size(112, 40);
      this->groupBox1->TabIndex = 3;
      this->groupBox1->TabStop = false;
      // 
      // checkBxAllTlg
      // 
      this->checkBxAllTlg->Location = System::Drawing::Point(8, 10);
      this->checkBxAllTlg->Name = "checkBxAllTlg";
      this->checkBxAllTlg->Size = System::Drawing::Size(88, 20);
      this->checkBxAllTlg->TabIndex = 0;
      this->checkBxAllTlg->Text = "Show All";
			this->checkBxAllTlg->CheckedChanged += gcnew System::EventHandler(this, &CReceiverForm::OnCheckBxAllTlgCheckedChanged);
      // 
      // grpBxCon
      // 
      this->grpBxCon->Controls->Add(this->labConStatus);
      this->grpBxCon->Controls->Add(this->labConTyp);
      this->grpBxCon->Controls->Add(this->label6);
      this->grpBxCon->Controls->Add(this->label5);
      this->grpBxCon->Controls->Add(this->label9);
      this->grpBxCon->Controls->Add(this->labPort);
      this->grpBxCon->Controls->Add(this->labIpAddr);
      this->grpBxCon->Controls->Add(this->labHostName);
      this->grpBxCon->Controls->Add(this->labInter);
      this->grpBxCon->Controls->Add(this->label4);
      this->grpBxCon->Controls->Add(this->label3);
      this->grpBxCon->Controls->Add(this->label2);
      this->grpBxCon->Location = System::Drawing::Point(8, 20);
      this->grpBxCon->Name = "grpBxCon";
      this->grpBxCon->Size = System::Drawing::Size(200, 132);
      this->grpBxCon->TabIndex = 2;
      this->grpBxCon->TabStop = false;
      this->grpBxCon->Text = "Connection";
      // 
      // labConStatus
      // 
      this->labConStatus->Location = System::Drawing::Point(70, 114);
      this->labConStatus->Name = "labConStatu";
      this->labConStatus->Size = System::Drawing::Size(100, 10);
      this->labConStatus->TabIndex = 11;
      this->labConStatus->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // labConTyp
      // 
      this->labConTyp->Location = System::Drawing::Point(70, 88);
      this->labConTyp->Name = "labConTyp";
      this->labConTyp->Size = System::Drawing::Size(100, 18);
      this->labConTyp->TabIndex = 10;
      this->labConTyp->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // label6
      // 
      this->label6->Location = System::Drawing::Point(8, 108);
      this->label6->Name = "label6";
      this->label6->Size = System::Drawing::Size(40, 20);
      this->label6->TabIndex = 9;
      this->label6->Text = "Status:";
      this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // label5
      // 
      this->label5->Location = System::Drawing::Point(8, 90);
      this->label5->Name = "label5";
      this->label5->Size = System::Drawing::Size(40, 16);
      this->label5->TabIndex = 8;
      this->label5->Text = "Typ:";
      this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // label9
      // 
      this->label9->Location = System::Drawing::Point(8, 72);
      this->label9->Name = "label9";
      this->label9->Size = System::Drawing::Size(40, 16);
      this->label9->TabIndex = 7;
      this->label9->Text = "Port:";
      this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // labPort
      // 
      this->labPort->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right);
      this->labPort->Location = System::Drawing::Point(70, 71);
      this->labPort->Name = "labPort";
      this->labPort->Size = System::Drawing::Size(100, 15);
      this->labPort->TabIndex = 6;
      this->labPort->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // labIpAddr
      // 
      this->labIpAddr->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right);
      this->labIpAddr->Location = System::Drawing::Point(70, 56);
      this->labIpAddr->Name = "labIpAddr";
      this->labIpAddr->Size = System::Drawing::Size(100, 13);
      this->labIpAddr->TabIndex = 5;
      this->labIpAddr->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // labHostName
      // 
      this->labHostName->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right);
      this->labHostName->Location = System::Drawing::Point(70, 37);
      this->labHostName->Name = "labHostName";
      this->labHostName->Size = System::Drawing::Size(100, 14);
      this->labHostName->TabIndex = 4;
      this->labHostName->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // labInter
      // 
      this->labInter->Anchor = (System::Windows::Forms::AnchorStyles)((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right);
      this->labInter->Location = System::Drawing::Point(70, 19);
      this->labInter->Name = "labInter";
      this->labInter->Size = System::Drawing::Size(106, 13);
      this->labInter->TabIndex = 3;
      this->labInter->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // label4
      // 
      this->label4->Location = System::Drawing::Point(8, 54);
      this->label4->Name = "label4";
      this->label4->Size = System::Drawing::Size(48, 16);
      this->label4->TabIndex = 2;
      this->label4->Text = "Ip Addr:";
      this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // label3
      // 
      this->label3->Location = System::Drawing::Point(8, 36);
      this->label3->Name = "label3";
      this->label3->Size = System::Drawing::Size(40, 16);
      this->label3->TabIndex = 1;
      this->label3->Text = "Host:";
      this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // label2
      // 
      this->label2->Location = System::Drawing::Point(8, 18);
      this->label2->Name = "label2";
      this->label2->Size = System::Drawing::Size(56, 16);
      this->label2->TabIndex = 0;
      this->label2->Text = "Interface:";
      this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // panCount
      // 
      this->panCount->Controls->Add(this->button1);
      this->panCount->Controls->Add(this->txtBxCount);
      this->panCount->Controls->Add(this->label1);
      this->panCount->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->panCount->Location = System::Drawing::Point(0, 198);
      this->panCount->Name = "panCount";
      this->panCount->Size = System::Drawing::Size(210, 24);
      this->panCount->TabIndex = 1;
      // 
      // button1
      // 
      this->button1->Location = System::Drawing::Point(136, 2);
      this->button1->Name = "button1";
      this->button1->Size = System::Drawing::Size(75, 20);
      this->button1->TabIndex = 2;
      this->button1->Text = "Clear View";
      this->button1->Click += gcnew System::EventHandler(this, &CReceiverForm::OnButClearViewClick);
      // 
      // txtBxCount
      // 
      this->txtBxCount->BorderStyle = System::Windows::Forms::BorderStyle::None;
      this->txtBxCount->Enabled = false;
      this->txtBxCount->Location = System::Drawing::Point(48, 6);
      this->txtBxCount->Name = "txtBxCount";
      this->txtBxCount->Size = System::Drawing::Size(48, 13);
      this->txtBxCount->TabIndex = 1;
      this->txtBxCount->Text = "";
      // 
      // label1
      // 
      this->label1->Dock = System::Windows::Forms::DockStyle::Left;
      this->label1->Location = System::Drawing::Point(0, 0);
      this->label1->Name = "label1";
      this->label1->Size = System::Drawing::Size(48, 24);
      this->label1->TabIndex = 0;
      this->label1->Text = "Count:";
      this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // labDescr
      // 
      this->labDescr->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->labDescr->Dock = System::Windows::Forms::DockStyle::Top;
      this->labDescr->Location = System::Drawing::Point(0, 0);
      this->labDescr->Name = "labDescr";
      this->labDescr->Size = System::Drawing::Size(210, 20);
      this->labDescr->TabIndex = 0;
      this->labDescr->Text = "Receive";
      this->labDescr->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      // 
      // splittVer1
      // 
      this->splittVer1->Location = System::Drawing::Point(216, 0);
      this->splittVer1->Name = "splittVer1";
      this->splittVer1->Size = System::Drawing::Size(3, 325);
      this->splittVer1->TabIndex = 1;
      this->splittVer1->TabStop = false;
      // 
      // panBottom
      // 
      this->panBottom->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->panBottom->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->panBottom->Location = System::Drawing::Point(219, 225);
      this->panBottom->Name = "panBottom";
      this->panBottom->Size = System::Drawing::Size(341, 100);
      this->panBottom->TabIndex = 2;
      // 
      // splittHor1
      // 
      this->splittHor1->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->splittHor1->Location = System::Drawing::Point(219, 224);
      this->splittHor1->Name = "splittHor1";
      this->splittHor1->Size = System::Drawing::Size(341, 1);
      this->splittHor1->TabIndex = 3;
      this->splittHor1->TabStop = false;
      // 
      // panTlgView
      // 
      this->panTlgView->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->panTlgView->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panTlgView->Location = System::Drawing::Point(219, 0);
      this->panTlgView->Name = "panTlgView";
      this->panTlgView->Size = System::Drawing::Size(341, 224);
      this->panTlgView->TabIndex = 4;
      // 
      // CReceiverForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(560, 325);
      this->Controls->Add(this->panTlgView);
      this->Controls->Add(this->splittHor1);
      this->Controls->Add(this->panBottom);
      this->Controls->Add(this->splittVer1);
      this->Controls->Add(this->panLeft);
      this->Name = "CReceiverForm";
      this->Text = "CReceiverForm";
			this->Resize += gcnew System::EventHandler(this, &CReceiverForm::OnResizeForm);
      this->panLeft->ResumeLayout(false);
      this->panTreeView->ResumeLayout(false);
      this->panTreeViewHeader->ResumeLayout(false);
      this->groupBox1->ResumeLayout(false);
      this->grpBxCon->ResumeLayout(false);
      this->panCount->ResumeLayout(false);
      this->ResumeLayout(false);

    }    


    System::Void OnCheckBxAllTlgCheckedChanged(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnButClearViewClick(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnButtRecClick(System::Object ^  sender, System::EventArgs ^  e);
    
    void updateInterfaceInfo();
    void updateTlgView();
    System::Void OnResizeForm(System::Object ^  sender, System::EventArgs ^  e);
    void initViewComponent();
    void updateConnection(int inter,int dir,int status);
    void udateRecListe();
    void updateConnInfo();
    // !!!
    CAnalyzeLogFileForm^ AnalyzeLogFileForm;
    CItemPrototypContainerForm^ TlgTreeViewForm;
    /*CTlgContainerTreeViewForm^  TlgTreeViewForm;*/
    CItemView^ TlgViewForm; 
    /*CTlgViewForm^ TlgViewForm;*/
    String^ ActiveInterface;
    //====================================
    // !!!
    ArrayList^ InterfaceListe;
    ArrayList^ BaseFactoryArray;
    ArrayList^ InterRecArray;
    CInterConnectionListe^ InterConnectionListe;
    CTlgContainerWrapper^ ReceiveTlgContainer;
    CTlgContainerWrapper^ DynamicTlgContainer;
    //====================================
    CMessageForm^ MessageForm;
    // CSocketConnState^ ConnState;
    //    DelConnStateCheck^ ConnStateCheckDel;
    //----------------------------------------------
    CInterConnectionListe^  RecConnListe;
    //----------------------------------------------
    ArrayList^ InterReceiverManListe;
    CInterReceiverManager^ getInterface(String^ inter);
    int getInterfaceIndex(String^ inter);
    void showContainerTlg();
    void showNewTlg(CItemWrapper^ tlg);
    void showTlgDetailView(CItemWrapper^ tlg,CItemView::CreateTypForm typ);
    void showMessage(String^ mess,int modi);
    bool m_dynAdaptation;
    //----------------------------------------------
    // Fürs Laden einer Konfiguration für die dynamische Adaption der Simulation
    void loadConfigForDynSimulation(String^ act_int);
  };
}