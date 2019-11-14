#pragma once

//----------------------------------------------------
#include "CInterConnectionListe.h"
#include "CSocketConnection.h"
#include "CMessageForm.h"
//----------------------------------------------------
//#include "CInterConnMan.h"
//----------------------------------------------------
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


//delegate void DelTreatmentRecConn(int index);


namespace simulator
{
  /// <summary> 
  /// Zusammenfassung für CSocketConnectionForm
  ///
  /// Achtung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie die Eigenschaft
  ///          'Ressourcendateiname' für das Compilertool für verwaltete Ressourcen ändern, 
  ///          das allen .resx-Dateien zugewiesen ist, von denen diese Klasse abhängt. 
  ///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
  ///          arbeiten, die diesem Formular zugewiesen sind.
  /// </summary>
  public ref class CSocketConnectionForm : public System::Windows::Forms::Form
  {
  public: 
    CSocketConnectionForm(CInterConnectionListe^ liste)
    {
      InitializeComponent();
      this->InterConnectionListe = liste;
      Interface = nullptr;
      TreatmentRecConn = nullptr;
      MessageForm = gcnew CMessageForm(panMess);
      InterConnectionListe->setDelConnection(gcnew DelIsConnected(this,&CSocketConnectionForm::updateConnectionInfo));
    }
    CSocketConnectionForm(CInterConnectionListe^ liste,String^ ActInter,bool connFlag)
    {
      InitializeComponent();
      this->InterConnectionListe = liste;
      Interface = ActInter;
      TreatmentRecConn = nullptr;
      MessageForm = gcnew CMessageForm(panMess);
      InterConnectionListe->setDelConnection(gcnew DelIsConnected(this,&CSocketConnectionForm::updateConnectionInfo));
      ConnectionFlag = connFlag;

      if (!connFlag)
        button1->Text="Prepare for connect";
    }
    void setDelTreatmentRecConn(DelTreatmentRecConn^ trConn);
  protected:
    //void Dispose(Boolean disposing)
    //{
    //  if (disposing && components)
    //  {
    //    components->Dispose();
    //  }
    //  __super::Dispose(disposing);
    //}

  private: System::Windows::Forms::GroupBox ^  grpBxConnChose;
  private: System::Windows::Forms::GroupBox ^  groupBxConnChose;
  private: System::Windows::Forms::Label ^  label1;
  private: System::Windows::Forms::Label ^  label2;

  private: System::Windows::Forms::Button ^  button2;
  private: System::Windows::Forms::Button ^  buttHelp;
  private: System::Windows::Forms::Button ^  buttLoad;
  private: System::Windows::Forms::Button ^  buttSave;
  private: System::Windows::Forms::Label ^  label4;
  private: System::Windows::Forms::CheckBox ^  chkBxLocHost;
  private: System::Windows::Forms::ComboBox ^  comBxIpAddr;
  private: System::Windows::Forms::TextBox ^  txtBxIpCount;
  private: System::Windows::Forms::Label ^  label5;
  private: System::Windows::Forms::Label ^  labHost;
  private: System::Windows::Forms::TextBox ^  txtBxPort;
  private: System::Windows::Forms::RadioButton ^  radioButtClient;
  private: System::Windows::Forms::RadioButton ^  radioButtServer;
  private: System::Windows::Forms::GroupBox ^  groupBox1;
  private: System::Windows::Forms::Label ^  labType;
  private: System::Windows::Forms::Label ^  label6;
  private: System::Windows::Forms::ListBox ^  listBoxInter;
  private: System::Windows::Forms::Panel ^  panMess;
  private: System::Windows::Forms::Label ^  labStatusInfo;
  private: System::Windows::Forms::Label ^  labTypeInfo;
  private: System::Windows::Forms::Button ^  buttClose;
  private: System::Windows::Forms::Button ^  button1;
  private: System::ComponentModel::IContainer ^  components;
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
      this->grpBxConnChose = (gcnew System::Windows::Forms::GroupBox());
      this->radioButtClient = (gcnew System::Windows::Forms::RadioButton());
      this->radioButtServer = (gcnew System::Windows::Forms::RadioButton());
      this->groupBxConnChose = (gcnew System::Windows::Forms::GroupBox());
      this->labHost = (gcnew System::Windows::Forms::Label());
      this->label5 = (gcnew System::Windows::Forms::Label());
      this->txtBxPort = (gcnew System::Windows::Forms::TextBox());
      this->chkBxLocHost = (gcnew System::Windows::Forms::CheckBox());
      this->txtBxIpCount = (gcnew System::Windows::Forms::TextBox());
      this->comBxIpAddr = (gcnew System::Windows::Forms::ComboBox());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->buttLoad = (gcnew System::Windows::Forms::Button());
      this->buttSave = (gcnew System::Windows::Forms::Button());
      this->button2 = (gcnew System::Windows::Forms::Button());
      this->buttHelp = (gcnew System::Windows::Forms::Button());
      this->buttClose = (gcnew System::Windows::Forms::Button());
      this->label4 = (gcnew System::Windows::Forms::Label());
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->labStatusInfo = (gcnew System::Windows::Forms::Label());
      this->label6 = (gcnew System::Windows::Forms::Label());
      this->labTypeInfo = (gcnew System::Windows::Forms::Label());
      this->labType = (gcnew System::Windows::Forms::Label());
      this->listBoxInter = (gcnew System::Windows::Forms::ListBox());
      this->panMess = (gcnew System::Windows::Forms::Panel());
      this->button1 = (gcnew System::Windows::Forms::Button());
      this->grpBxConnChose->SuspendLayout();
      this->groupBxConnChose->SuspendLayout();
      this->groupBox1->SuspendLayout();
      this->SuspendLayout();
      // 
      // grpBxConnChose
      // 
      this->grpBxConnChose->Controls->Add(this->radioButtClient);
      this->grpBxConnChose->Controls->Add(this->radioButtServer);
      this->grpBxConnChose->Location = System::Drawing::Point(168, 8);
      this->grpBxConnChose->Name = "grpBxConnChose";
      this->grpBxConnChose->Size = System::Drawing::Size(336, 35);
      this->grpBxConnChose->TabIndex = 1;
      this->grpBxConnChose->TabStop = false;
      this->grpBxConnChose->Text = "Connection Mode";
      // 
      // radioButtClient
      // 
      this->radioButtClient->Location = System::Drawing::Point(128, 16);
      this->radioButtClient->Name = "radioButtClient";
      this->radioButtClient->Size = System::Drawing::Size(104, 16);
      this->radioButtClient->TabIndex = 1;
      this->radioButtClient->Text = "Client";
      this->radioButtClient->Click += gcnew System::EventHandler(this, &CSocketConnectionForm::OnCheckedChangedRadButtClient);
      // 
      // radioButtServer
      // 
      this->radioButtServer->Location = System::Drawing::Point(16, 16);
      this->radioButtServer->Name = "radioButtServer";
      this->radioButtServer->Size = System::Drawing::Size(104, 16);
      this->radioButtServer->TabIndex = 0;
      this->radioButtServer->Text = "Server";
      this->radioButtServer->Click += gcnew System::EventHandler(this, &CSocketConnectionForm::OnCheckedChangedRadButtServer);
      // 
      // groupBxConnChose
      // 
      this->groupBxConnChose->Controls->Add(this->labHost);
      this->groupBxConnChose->Controls->Add(this->label5);
      this->groupBxConnChose->Controls->Add(this->txtBxPort);
      this->groupBxConnChose->Controls->Add(this->chkBxLocHost);
      this->groupBxConnChose->Controls->Add(this->txtBxIpCount);
      this->groupBxConnChose->Controls->Add(this->comBxIpAddr);
      this->groupBxConnChose->Controls->Add(this->label2);
      this->groupBxConnChose->Controls->Add(this->label1);
      this->groupBxConnChose->Controls->Add(this->buttLoad);
      this->groupBxConnChose->Controls->Add(this->buttSave);
      this->groupBxConnChose->Location = System::Drawing::Point(168, 48);
      this->groupBxConnChose->Name = "groupBxConnChose";
      this->groupBxConnChose->Size = System::Drawing::Size(338, 128);
      this->groupBxConnChose->TabIndex = 2;
      this->groupBxConnChose->TabStop = false;
      // 
      // labHost
      // 
      this->labHost->Location = System::Drawing::Point(80, 10);
      this->labHost->Name = "labHost";
      this->labHost->Size = System::Drawing::Size(100, 16);
      this->labHost->TabIndex = 9;
      // 
      // label5
      // 
      this->label5->Location = System::Drawing::Point(8, 10);
      this->label5->Name = "label5";
      this->label5->Size = System::Drawing::Size(56, 16);
      this->label5->TabIndex = 8;
      this->label5->Text = "Host";
      this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // txtBxPort
      // 
      this->txtBxPort->Location = System::Drawing::Point(72, 64);
      this->txtBxPort->Name = "txtBxPort";
      this->txtBxPort->Size = System::Drawing::Size(128, 20);
      this->txtBxPort->TabIndex = 5;
      // 
      // chkBxLocHost
      // 
      this->chkBxLocHost->Location = System::Drawing::Point(248, 35);
      this->chkBxLocHost->Name = "chkBxLocHost";
      this->chkBxLocHost->Size = System::Drawing::Size(80, 22);
      this->chkBxLocHost->TabIndex = 4;
      this->chkBxLocHost->Text = "Local Host";
      this->chkBxLocHost->CheckedChanged += gcnew System::EventHandler(this, &CSocketConnectionForm::OnCheckedLocHost);
      // 
      // txtBxIpCount
      // 
      this->txtBxIpCount->Location = System::Drawing::Point(208, 35);
      this->txtBxIpCount->Name = "txtBxIpCount";
      this->txtBxIpCount->ReadOnly = true;
      this->txtBxIpCount->Size = System::Drawing::Size(32, 20);
      this->txtBxIpCount->TabIndex = 3;
      // 
      // comBxIpAddr
      // 
      this->comBxIpAddr->Location = System::Drawing::Point(72, 35);
      this->comBxIpAddr->Name = "comBxIpAddr";
      this->comBxIpAddr->Size = System::Drawing::Size(128, 21);
      this->comBxIpAddr->TabIndex = 2;
      // 
      // label2
      // 
      this->label2->Location = System::Drawing::Point(8, 64);
      this->label2->Name = "label2";
      this->label2->Size = System::Drawing::Size(48, 24);
      this->label2->TabIndex = 1;
      this->label2->Text = "Port No";
      // 
      // label1
      // 
      this->label1->Location = System::Drawing::Point(8, 35);
      this->label1->Name = "label1";
      this->label1->Size = System::Drawing::Size(56, 16);
      this->label1->TabIndex = 0;
      this->label1->Text = "IP Addr.";
      // 
      // buttLoad
      // 
      this->buttLoad->Location = System::Drawing::Point(40, 96);
      this->buttLoad->Name = "buttLoad";
      this->buttLoad->Size = System::Drawing::Size(110, 23);
      this->buttLoad->TabIndex = 4;
      this->buttLoad->Text = "Load Configuration";
      this->buttLoad->Click += gcnew System::EventHandler(this, &CSocketConnectionForm::OnClickButtLoad);
      // 
      // buttSave
      // 
      this->buttSave->Location = System::Drawing::Point(192, 96);
      this->buttSave->Name = "buttSave";
      this->buttSave->Size = System::Drawing::Size(110, 23);
      this->buttSave->TabIndex = 5;
      this->buttSave->Text = "Save Configuration";
      this->buttSave->Click += gcnew System::EventHandler(this, &CSocketConnectionForm::OnClickButtSave);
      // 
      // button2
      // 
      this->button2->Location = System::Drawing::Point(258, 288);
      this->button2->Name = "button2";
      this->button2->Size = System::Drawing::Size(118, 23);
      this->button2->TabIndex = 7;
      this->button2->Text = "Disconnect";
      this->button2->Click += gcnew System::EventHandler(this, &CSocketConnectionForm::OnClickButtDisconnect);
      // 
      // buttHelp
      // 
      this->buttHelp->Enabled = false;
      this->buttHelp->Location = System::Drawing::Point(11, 288);
      this->buttHelp->Name = "buttHelp";
      this->buttHelp->Size = System::Drawing::Size(96, 23);
      this->buttHelp->TabIndex = 3;
      this->buttHelp->Text = "Help";
      // 
      // buttClose
      // 
      this->buttClose->Location = System::Drawing::Point(408, 288);
      this->buttClose->Name = "buttClose";
      this->buttClose->Size = System::Drawing::Size(96, 23);
      this->buttClose->TabIndex = 7;
      this->buttClose->Text = "Close";
      this->buttClose->Click += gcnew System::EventHandler(this, &CSocketConnectionForm::OnClickButtOk);
      // 
      // label4
      // 
      this->label4->Location = System::Drawing::Point(8, 0);
      this->label4->Name = "label4";
      this->label4->Size = System::Drawing::Size(104, 16);
      this->label4->TabIndex = 9;
      this->label4->Text = "Aviable Interfacie";
      this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->labStatusInfo);
      this->groupBox1->Controls->Add(this->label6);
      this->groupBox1->Controls->Add(this->labTypeInfo);
      this->groupBox1->Controls->Add(this->labType);
      this->groupBox1->Location = System::Drawing::Point(8, 144);
      this->groupBox1->Name = "groupBox1";
      this->groupBox1->Size = System::Drawing::Size(144, 128);
      this->groupBox1->TabIndex = 10;
      this->groupBox1->TabStop = false;
      this->groupBox1->Text = "Connection Statu";
      // 
      // labStatusInfo
      // 
      this->labStatusInfo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->labStatusInfo->Location = System::Drawing::Point(11, 80);
      this->labStatusInfo->Name = "labStatusInfo";
      this->labStatusInfo->Size = System::Drawing::Size(122, 16);
      this->labStatusInfo->TabIndex = 3;
      // 
      // label6
      // 
      this->label6->Location = System::Drawing::Point(8, 64);
      this->label6->Name = "label6";
      this->label6->Size = System::Drawing::Size(40, 16);
      this->label6->TabIndex = 2;
      this->label6->Text = "Status:";
      this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // labTypeInfo
      // 
      this->labTypeInfo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->labTypeInfo->Location = System::Drawing::Point(50, 24);
      this->labTypeInfo->Name = "labTypeInfo";
      this->labTypeInfo->Size = System::Drawing::Size(82, 16);
      this->labTypeInfo->TabIndex = 1;
      // 
      // labType
      // 
      this->labType->Location = System::Drawing::Point(8, 24);
      this->labType->Name = "labType";
      this->labType->Size = System::Drawing::Size(40, 16);
      this->labType->TabIndex = 0;
      this->labType->Text = "Type:";
      this->labType->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // listBoxInter
      // 
      this->listBoxInter->Location = System::Drawing::Point(8, 16);
      this->listBoxInter->Name = "listBoxInter";
      this->listBoxInter->Size = System::Drawing::Size(144, 121);
      this->listBoxInter->TabIndex = 11;
      this->listBoxInter->Enter += gcnew System::EventHandler(this, &CSocketConnectionForm::OnListBoxInterEnter);
      this->listBoxInter->SelectedIndexChanged += gcnew System::EventHandler(this, &CSocketConnectionForm::OnListBoxSelIndexChanged);
      // 
      // panMess
      // 
      this->panMess->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->panMess->Location = System::Drawing::Point(168, 184);
      this->panMess->Name = "panMes";
      this->panMess->Size = System::Drawing::Size(336, 88);
      this->panMess->TabIndex = 12;
      // 
      // button1
      // 
      this->button1->Location = System::Drawing::Point(135, 288);
      this->button1->Name = "button1";
      this->button1->Size = System::Drawing::Size(117, 23);
      this->button1->TabIndex = 13;
      this->button1->Text = "Connect";
      this->button1->Click += gcnew System::EventHandler(this, &CSocketConnectionForm::OnClickButtConnection);
      // 
      // CSocketConnectionForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(514, 322);
      this->Controls->Add(this->button1);
      this->Controls->Add(this->panMess);
      this->Controls->Add(this->listBoxInter);
      this->Controls->Add(this->groupBox1);
      this->Controls->Add(this->label4);
      this->Controls->Add(this->buttClose);
      this->Controls->Add(this->buttHelp);
      this->Controls->Add(this->groupBxConnChose);
      this->Controls->Add(this->grpBxConnChose);
      this->Controls->Add(this->button2);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->Name = "CSocketConnectionForm";
      this->ShowInTaskbar = false;
      this->Text = "CSocketConnectionForm";
      this->Load += gcnew System::EventHandler(this, &CSocketConnectionForm::OnLoad);
      this->grpBxConnChose->ResumeLayout(false);
      this->groupBxConnChose->ResumeLayout(false);
      this->groupBxConnChose->PerformLayout();
      this->groupBox1->ResumeLayout(false);
      this->ResumeLayout(false);

    }    



    System::Void OnLoad(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnCheckedLocHost(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnClickButtConnection(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnListBoxSelIndexChanged(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnListBoxInterEnter(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnClickButtDisconnect(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnClickButtOk(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnClickButtCancel(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnClickButtSave(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnClickButtLoad(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnCheckedChangedRadButtServer(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnCheckedChangedRadButtClient(System::Object ^  sender, System::EventArgs ^  e);
    
    void initInterfaceListe();
    void initCompConfiguration();
    void updateConnectionInfo(bool status);
    void updateFromConnToView();
    void updateFromViewToConn();
    void turnOnOffConnDisconnButtons(String^ status);

    CInterConnectionListe^ InterConnectionListe; 
    DelTreatmentRecConn^  TreatmentRecConn;

    CMessageForm^ MessageForm;
    String^ Interface;
    bool ConnectionFlag;        

         

};
}
