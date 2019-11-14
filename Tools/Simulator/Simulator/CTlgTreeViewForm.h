#pragma once

//--------------------------------------------------------------
#include "CItemBaseContainerWrapper.h"
#include "CItemWrapper.h"
#include "CTlgWrapper.h"
#include "CTlgContainerTreeViewForm.h"
#include "CInterUseCase.h" 
#include "CItemPrototypContainerForm.h"
//-------------------------------------------------------------
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

//----------------------------------------------------------------------
namespace simulator
{
  /// <summary> 
  /// Zusammenfassung für CTlgTreeViewForm
  ///
  /// Achtung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie die Eigenschaft
  ///          'Ressourcendateiname' für das Compilertool für verwaltete Ressourcen ändern, 
  ///          das allen .resx-Dateien zugewiesen ist, von denen diese Klasse abhängt. 
  ///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
  ///          arbeiten, die diesem Formular zugewiesen sind.
  /// </summary>
  public ref class CTlgTreeViewForm : public System::Windows::Forms::Form
  {
    public: delegate void addToSzenDelTyp(CItemWrapper^ wrp,double time,bool modi);
    public: delegate void LogFileViewEventTyp(bool flag);  
    public: 
      CTlgTreeViewForm(void)
      {
        InitializeComponent();
        UpdateModus = true;
        Flag=true;
        myWr = gcnew CTlgWrapper();
        Count = 0;
        AddToSzenDel=nullptr;
        ChekedLabArray=nullptr;
        buttAdd->Enabled=false;
        SzenUpFlag=true;
        LogFileViewEvent=nullptr;
      }
      CTlgTreeViewForm(Panel^ parent);
      void setFileName(String^ fileName);
      void setTlgCount(int count);
      void setTlgPrototypContainer(CItemBaseContainerWrapper^ con);
      void showTlgPrototypContainer(String^ InterDesc,String^ InterVersion);
      void setTlgContainer(CItemBaseContainerWrapper^ con);
      void showTlgContainer();
      void setAfterSelectPrototypEvent(CItemPrototypContainerForm::AfterSelectPrototypEvent^ event);
      void setAfterSelectTlgContainerEvent(CTlgContainerTreeViewForm::AfterSelectEvent^ event);
      void setAddToSzenDel(addToSzenDelTyp^ del);
      void clearView();
      void updateUseCaseView(String^ interName,String^ useCaseName);
      void setFilterLogFile(String^ inter,array <String^>^ reg);
      void selectLogFileTelegramm(int index);
      void enableSzenMode(bool mode);
      void clearLogFileView();
      void setMessageHandler(CTlgContainerTreeViewForm::DelMessageHandlerTyp^ messNandl,CItemPrototypContainerForm::DelMessageHandlerPrototyp^ messHandl1);
      void selectAllTlgFromLogFile();
      void removeSelectionTlgFrommLogFile();
      void setLogFileViewEvent(LogFileViewEventTyp^ event);
    protected: 
      //void Dispose(Boolean disposing)
      //{
      //  if (disposing && components)
      //  {
      //    components->Dispose();
      //  }
      //  __super::Dispose(disposing);
      //}
      private: System::Windows::Forms::Panel ^  panHead;
      private: System::Windows::Forms::Label ^  labFileName;
      private: System::Windows::Forms::Panel ^  panHead2;
      private: System::Windows::Forms::Splitter ^  splitHor;
      private: System::Windows::Forms::Panel ^  panBody;
      private: System::Windows::Forms::Panel ^  panFilter;
      private: System::Windows::Forms::Panel ^  panTlgCount;
      private: System::Windows::Forms::ImageList ^  imageList;
      private: System::Windows::Forms::Label ^  label2;
      private: System::Windows::Forms::TextBox ^  textBox2;
      private: System::Windows::Forms::TabControl ^  tabControl;
      private: System::Windows::Forms::TabPage ^  tabPage1;
      private: System::Windows::Forms::TabPage ^  tabPage2;
      private: System::Windows::Forms::Panel ^  panTreeViewBack;
      private: System::Windows::Forms::Panel ^  panLabArray;
      private: System::Windows::Forms::Button ^  buttAdd;
      private: System::Windows::Forms::Panel ^  panHinterTreeView;
      private: System::Windows::Forms::Panel^  panTop;
      private: System::Windows::Forms::Label^  labInterVer;
      private: System::Windows::Forms::Label^  labInterDesc;
      private: System::Windows::Forms::Panel^  panFilterTopView;
  private: System::Windows::Forms::Label^  labFilterText;

      private: System::Windows::Forms::Label^  labFilter;
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
      this->components = (gcnew System::ComponentModel::Container());
      System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(CTlgTreeViewForm::typeid));
      this->panHead = (gcnew System::Windows::Forms::Panel());
      this->panHead2 = (gcnew System::Windows::Forms::Panel());
      this->panTlgCount = (gcnew System::Windows::Forms::Panel());
      this->buttAdd = (gcnew System::Windows::Forms::Button());
      this->textBox2 = (gcnew System::Windows::Forms::TextBox());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->panFilter = (gcnew System::Windows::Forms::Panel());
      this->labFileName = (gcnew System::Windows::Forms::Label());
      this->splitHor = (gcnew System::Windows::Forms::Splitter());
      this->panBody = (gcnew System::Windows::Forms::Panel());
      this->tabControl = (gcnew System::Windows::Forms::TabControl());
      this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
      this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
      this->panTreeViewBack = (gcnew System::Windows::Forms::Panel());
      this->panHinterTreeView = (gcnew System::Windows::Forms::Panel());
      this->panLabArray = (gcnew System::Windows::Forms::Panel());
      this->panFilterTopView = (gcnew System::Windows::Forms::Panel());
      this->labFilterText = (gcnew System::Windows::Forms::Label());
      this->labFilter = (gcnew System::Windows::Forms::Label());
      this->imageList = (gcnew System::Windows::Forms::ImageList(this->components));
      this->panTop = (gcnew System::Windows::Forms::Panel());
      this->labInterVer = (gcnew System::Windows::Forms::Label());
      this->labInterDesc = (gcnew System::Windows::Forms::Label());
      this->panHead->SuspendLayout();
      this->panHead2->SuspendLayout();
      this->panTlgCount->SuspendLayout();
      this->panBody->SuspendLayout();
      this->tabControl->SuspendLayout();
      this->tabPage2->SuspendLayout();
      this->panTreeViewBack->SuspendLayout();
      this->panFilterTopView->SuspendLayout();
      this->panTop->SuspendLayout();
      this->SuspendLayout();
      // 
      // panHead
      // 
      this->panHead->BackColor = System::Drawing::SystemColors::Control;
      this->panHead->Controls->Add(this->panHead2);
      this->panHead->Dock = System::Windows::Forms::DockStyle::Top;
      this->panHead->Location = System::Drawing::Point(0, 80);
      this->panHead->Name = L"panHead";
      this->panHead->Size = System::Drawing::Size(708, 30);
      this->panHead->TabIndex = 0;
      // 
      // panHead2
      // 
      this->panHead2->BackColor = System::Drawing::SystemColors::Control;
      this->panHead2->Controls->Add(this->panTlgCount);
      this->panHead2->Controls->Add(this->panFilter);
      this->panHead2->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panHead2->Location = System::Drawing::Point(0, 0);
      this->panHead2->Name = L"panHead2";
      this->panHead2->Size = System::Drawing::Size(708, 30);
      this->panHead2->TabIndex = 1;
      // 
      // panTlgCount
      // 
      this->panTlgCount->BackColor = System::Drawing::SystemColors::Control;
      this->panTlgCount->Controls->Add(this->buttAdd);
      this->panTlgCount->Controls->Add(this->textBox2);
      this->panTlgCount->Controls->Add(this->label2);
      this->panTlgCount->Dock = System::Windows::Forms::DockStyle::Top;
      this->panTlgCount->Location = System::Drawing::Point(0, 0);
      this->panTlgCount->Name = L"panTlgCount";
      this->panTlgCount->Size = System::Drawing::Size(708, 24);
      this->panTlgCount->TabIndex = 1;
      // 
      // buttAdd
      // 
      this->buttAdd->Anchor = System::Windows::Forms::AnchorStyles::Right;
      this->buttAdd->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
      this->buttAdd->Location = System::Drawing::Point(611, 2);
      this->buttAdd->Name = L"buttAdd";
      this->buttAdd->Size = System::Drawing::Size(93, 23);
      this->buttAdd->TabIndex = 2;
      this->buttAdd->Tag = L" ";
      this->buttAdd->Text = L"Add to Scenario";
      this->buttAdd->Click += gcnew System::EventHandler(this, &CTlgTreeViewForm::OnClickButtonAdd);
      // 
      // textBox2
      // 
      this->textBox2->Anchor = System::Windows::Forms::AnchorStyles::Left;
      this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
      this->textBox2->Enabled = false;
      this->textBox2->Location = System::Drawing::Point(48, 6);
      this->textBox2->Name = L"textBox2";
      this->textBox2->Size = System::Drawing::Size(40, 13);
      this->textBox2->TabIndex = 1;
      // 
      // label2
      // 
      this->label2->Dock = System::Windows::Forms::DockStyle::Left;
      this->label2->Location = System::Drawing::Point(0, 0);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(48, 24);
      this->label2->TabIndex = 0;
      this->label2->Text = L"Count:";
      this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // panFilter
      // 
      this->panFilter->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->panFilter->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->panFilter->Location = System::Drawing::Point(0, 6);
      this->panFilter->Name = L"panFilter";
      this->panFilter->Size = System::Drawing::Size(708, 24);
      this->panFilter->TabIndex = 0;
      // 
      // labFileName
      // 
      this->labFileName->BackColor = System::Drawing::SystemColors::Control;
      this->labFileName->Dock = System::Windows::Forms::DockStyle::Top;
      this->labFileName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->labFileName->Location = System::Drawing::Point(0, 0);
      this->labFileName->Name = L"labFileName";
      this->labFileName->Size = System::Drawing::Size(708, 26);
      this->labFileName->TabIndex = 0;
      this->labFileName->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      this->labFileName->MouseHover += gcnew System::EventHandler(this, &CTlgTreeViewForm::labFileName_MouseHover);
      // 
      // splitHor
      // 
      this->splitHor->BackColor = System::Drawing::SystemColors::Control;
      this->splitHor->Dock = System::Windows::Forms::DockStyle::Top;
      this->splitHor->Location = System::Drawing::Point(0, 110);
      this->splitHor->Name = L"splitHor";
      this->splitHor->Size = System::Drawing::Size(708, 3);
      this->splitHor->TabIndex = 1;
      this->splitHor->TabStop = false;
      // 
      // panBody
      // 
      this->panBody->AutoScroll = true;
      this->panBody->BackColor = System::Drawing::SystemColors::Control;
      this->panBody->Controls->Add(this->tabControl);
      this->panBody->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panBody->Location = System::Drawing::Point(0, 113);
      this->panBody->Name = L"panBody";
      this->panBody->Size = System::Drawing::Size(708, 496);
      this->panBody->TabIndex = 2;
      this->panBody->SizeChanged += gcnew System::EventHandler(this, &CTlgTreeViewForm::OnSizeFormChanged);
      // 
      // tabControl
      // 
      this->tabControl->Controls->Add(this->tabPage1);
      this->tabControl->Controls->Add(this->tabPage2);
      this->tabControl->Dock = System::Windows::Forms::DockStyle::Fill;
      this->tabControl->Location = System::Drawing::Point(0, 0);
      this->tabControl->Name = L"tabControl";
      this->tabControl->SelectedIndex = 0;
      this->tabControl->Size = System::Drawing::Size(708, 496);
      this->tabControl->TabIndex = 0;
      this->tabControl->SelectedIndexChanged += gcnew System::EventHandler(this, &CTlgTreeViewForm::OnSelectedIndexChanged);
      // 
      // tabPage1
      // 
      this->tabPage1->AutoScroll = true;
      this->tabPage1->Location = System::Drawing::Point(4, 22);
      this->tabPage1->Name = L"tabPage1";
      this->tabPage1->Size = System::Drawing::Size(700, 470);
      this->tabPage1->TabIndex = 0;
      this->tabPage1->Text = L"Available Tlg";
      this->tabPage1->Resize += gcnew System::EventHandler(this, &CTlgTreeViewForm::tabPage1_Resize);
      // 
      // tabPage2
      // 
      this->tabPage2->Controls->Add(this->panTreeViewBack);
      this->tabPage2->Location = System::Drawing::Point(4, 22);
      this->tabPage2->Name = L"tabPage2";
      this->tabPage2->Size = System::Drawing::Size(700, 470);
      this->tabPage2->TabIndex = 1;
      this->tabPage2->Text = L"File";
      // 
      // panTreeViewBack
      // 
      this->panTreeViewBack->Controls->Add(this->panHinterTreeView);
      this->panTreeViewBack->Controls->Add(this->panFilterTopView);
      this->panTreeViewBack->Controls->Add(this->panLabArray);
      this->panTreeViewBack->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panTreeViewBack->Location = System::Drawing::Point(0, 0);
      this->panTreeViewBack->Name = L"panTreeViewBack";
      this->panTreeViewBack->Size = System::Drawing::Size(700, 470);
      this->panTreeViewBack->TabIndex = 0;
      this->panTreeViewBack->Resize += gcnew System::EventHandler(this, &CTlgTreeViewForm::OnResizePanel);
      // 
      // panHinterTreeView
      // 
      this->panHinterTreeView->Dock = System::Windows::Forms::DockStyle::Right;
      this->panHinterTreeView->Location = System::Drawing::Point(500, 0);
      this->panHinterTreeView->Name = L"panHinterTreeView";
      this->panHinterTreeView->Size = System::Drawing::Size(200, 455);
      this->panHinterTreeView->TabIndex = 1;
      this->panHinterTreeView->Resize += gcnew System::EventHandler(this, &CTlgTreeViewForm::panHinterTreeView_Resize);
      // 
      // panLabArray
      // 
      this->panLabArray->Location = System::Drawing::Point(0, 0);
      this->panLabArray->Name = L"panLabArray";
      this->panLabArray->Size = System::Drawing::Size(12, 120);
      this->panLabArray->TabIndex = 0;
      // 
      // panFilterTopView
      // 
      this->panFilterTopView->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panFilterTopView->Controls->Add(this->labFilterText);
      this->panFilterTopView->Controls->Add(this->labFilter);
      this->panFilterTopView->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->panFilterTopView->Location = System::Drawing::Point(0, 455);
      this->panFilterTopView->Name = L"panFilterTopView";
      this->panFilterTopView->Size = System::Drawing::Size(700, 15);
      this->panFilterTopView->TabIndex = 1;
      // 
      // labFilterText
      // 
      this->labFilterText->Dock = System::Windows::Forms::DockStyle::Fill;
      this->labFilterText->Location = System::Drawing::Point(53, 0);
      this->labFilterText->Name = L"labFilterText";
      this->labFilterText->Size = System::Drawing::Size(643, 11);
      this->labFilterText->TabIndex = 1;
      this->labFilterText->Text = L"none";
      this->labFilterText->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // labFilter
      // 
      this->labFilter->Dock = System::Windows::Forms::DockStyle::Left;
      this->labFilter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->labFilter->Location = System::Drawing::Point(0, 0);
      this->labFilter->Name = L"labFilter";
      this->labFilter->Size = System::Drawing::Size(53, 11);
      this->labFilter->TabIndex = 0;
      this->labFilter->Text = L"Filter :";
      this->labFilter->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      // 
      // imageList
      // 
      this->imageList->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imageList.ImageStream")));
      this->imageList->TransparentColor = System::Drawing::Color::Transparent;
      this->imageList->Images->SetKeyName(0, L"");
      this->imageList->Images->SetKeyName(1, L"");
      // 
      // panTop
      // 
      this->panTop->BackColor = System::Drawing::SystemColors::Control;
      this->panTop->Controls->Add(this->labInterVer);
      this->panTop->Controls->Add(this->labInterDesc);
      this->panTop->Controls->Add(this->labFileName);
      this->panTop->Dock = System::Windows::Forms::DockStyle::Top;
      this->panTop->Location = System::Drawing::Point(0, 0);
      this->panTop->Name = L"panTop";
      this->panTop->Size = System::Drawing::Size(708, 80);
      this->panTop->TabIndex = 3;
      // 
      // labInterVer
      // 
      this->labInterVer->BackColor = System::Drawing::SystemColors::Control;
      this->labInterVer->Dock = System::Windows::Forms::DockStyle::Fill;
      this->labInterVer->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold));
      this->labInterVer->Location = System::Drawing::Point(0, 52);
      this->labInterVer->Name = L"labInterVer";
      this->labInterVer->Size = System::Drawing::Size(708, 28);
      this->labInterVer->TabIndex = 2;
      this->labInterVer->Text = L"Version : ";
      this->labInterVer->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      // 
      // labInterDesc
      // 
      this->labInterDesc->BackColor = System::Drawing::SystemColors::Control;
      this->labInterDesc->Dock = System::Windows::Forms::DockStyle::Top;
      this->labInterDesc->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold));
      this->labInterDesc->Location = System::Drawing::Point(0, 26);
      this->labInterDesc->Name = L"labInterDesc";
      this->labInterDesc->Size = System::Drawing::Size(708, 26);
      this->labInterDesc->TabIndex = 1;
      this->labInterDesc->Text = L"Description : ";
      this->labInterDesc->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      // 
      // CTlgTreeViewForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->BackColor = System::Drawing::SystemColors::InactiveCaption;
      this->ClientSize = System::Drawing::Size(708, 609);
      this->Controls->Add(this->panBody);
      this->Controls->Add(this->splitHor);
      this->Controls->Add(this->panHead);
      this->Controls->Add(this->panTop);
      this->KeyPreview = true;
      this->Name = L"CTlgTreeViewForm";
      this->Text = L"CTlgTreeViewForm";
      this->SizeChanged += gcnew System::EventHandler(this, &CTlgTreeViewForm::OnSizeFormChanged);
      this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &CTlgTreeViewForm::OnKeyDownEvent);
      this->panHead->ResumeLayout(false);
      this->panHead2->ResumeLayout(false);
      this->panTlgCount->ResumeLayout(false);
      this->panTlgCount->PerformLayout();
      this->panBody->ResumeLayout(false);
      this->tabControl->ResumeLayout(false);
      this->tabPage2->ResumeLayout(false);
      this->panTreeViewBack->ResumeLayout(false);
      this->panFilterTopView->ResumeLayout(false);
      this->panTop->ResumeLayout(false);
      this->ResumeLayout(false);

    }    

    System::Void OnClickLabel(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnSizeFormChanged(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnClickButtonFilter(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnClickButtonAdd(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnKeyDownEvent(System::Object ^  sender, System::Windows::Forms::KeyEventArgs ^  e);
    System::Void OnResizePanel(System::Object ^  sender, System::EventArgs ^  e);
    System::Void tabPage1_Resize(System::Object ^  sender, System::EventArgs ^  e);
    System::Void panHinterTreeView_Resize(System::Object ^  sender, System::EventArgs ^  e);
    System::Void AfterCollapseTreeView(System::Object ^  sender, System::Windows::Forms::TreeViewEventArgs ^  e);
    System::Void AfterExpandTreeView(System::Object ^  sender, System::Windows::Forms::TreeViewEventArgs ^  e);
    System::Void OnSelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e);
    
    CItemBaseContainerWrapper^ TlgContainer;
    System::Collections::ArrayList^ LabArray;
    array <bool>^ ChekedLabArray;
    bool UpdateModus;
    bool Flag;
    bool SzenUpFlag;
    int Count;
    CItemWrapper^ myWr;
    //setting of tool tips
    System::Windows::Forms::ToolTip^ ToolTipFileName;
    CItemPrototypContainerForm^   PrototypForm;
    CTlgContainerTreeViewForm^   FileReaderForm;
    addToSzenDelTyp^ AddToSzenDel;
    LogFileViewEventTyp^ LogFileViewEvent;
    ToolTip^ FilterLogFileToolTip;

    void initViewComponente();
    void getTreeNode(TreeNode^ node,CItemWrapper^ tlg);
    void initLabelArray(int count);
    int calcNewHeight(TreeNode^ node);
    void setTreeViewHeight();
    int getCheckedTlgCount();
    void updateContainerView();
    void updateCheckedState(int pos,int count);
    void scrollTreeViewValChange();
    void setLabArrayPanPosition();
    void UpdateLogFileFilter(String^ filter);

  private: 
    System::Void labFileName_MouseHover(System::Object ^  sender, System::EventArgs ^  e)
    {
	    if(tabControl->SelectedIndex == 0)
	    {
        ToolTipFileName->RemoveAll();
		    if(PrototypForm)
		    {
          ToolTipFileName->SetToolTip(labFileName,PrototypForm->getPathFile());
        }
	    }
	    if(tabControl->SelectedIndex == 1)
	    {
        ToolTipFileName->RemoveAll();
		    if(FileReaderForm)
		    {
          ToolTipFileName->SetToolTip(labFileName,FileReaderForm->getPathFile());
        }
      }
    }
};
}
