#pragma once
#pragma warning(disable:4677)


#include "CItemWrapper.h"
#include "CItemView.h"
#include "CSzenarium.h"
#include "CInterBaseManager.h"
#include "CMessageForm.h"
#include "CInterSenderManager.h"
#include "CXmlInterConfigReader.h"
//------------------------------------------------------
#include "CXmlSzenReader.h" // for Xml_Szen
#include "CProgressBarViewForm.h"
//------------------------------------------------------
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#undef MessageBox
#undef GetObject

namespace simulator
{
	/// <summary> 
	/// Summary for CSzenariumForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CSzenariumForm : public System::Windows::Forms::Form
	{
	  public: delegate void RemoveSzenarioItemFromViewTyp();
    public: delegate void SelectSzenItemTyp(CItemWrapper^ tlg,CItemView::CreateTypForm typ);
    public: delegate void MessageHandlerTyp(String^ mess,int type);
    public: delegate void SzenariumModusEventTyp(int modi);
    public: delegate void UpdateSzenEventTyp(bool flag);

  public: 
		//CSzenariumForm(void)
		//{
		//	InitializeComponent();
		//	InterConnListe = nullptr;
		//	SendSzenThread = nullptr;
    //  SendCyclicSzenThread = nullptr;
		//	MessageHandler = nullptr;
		//	SzenariumModusEvent=nullptr;
		//	UpdateSzenEvent=nullptr;
		//	SelItemColor=Color::FromKnownColor(KnownColor::MediumSlateBlue);
		//	SendItemColor=Color::FromKnownColor(KnownColor::Green);
		//	DefaultColor=Color::FromKnownColor(KnownColor::Control);
		//	//ChangeValueColor=Color::Yellow;
		//	ChangeValueColor=Color::GreenYellow;
		//	UpDataFlag=false;
    //  progressBar=nullptr;
		//}
		value struct sendItemByteInfo
	  {
		  unsigned char* buffer;
      int len;
		  sendItemByteInfo(unsigned char* b,int l)
      {
        buffer = b;
        len = l;
      }
	  };
		value struct SzenItemInfo
		{
			Panel^ pan;
			Button^ but;
			Label^ lab;
			TextBox^ txtBx;
      Label^ LabDebug;

      void Clean()
      {
        pan->~Panel();
        but->~Button();
        lab->~Label();
        txtBx->~TextBox();
        LabDebug->~Label();
      }
		};
    CSzenariumForm(Panel^ parent); 
    void addToSzenarium(CItemWrapper^ tlg,double time);
    void addToSzenarium(CItemWrapper^ tlg);
    void showSzenarium();
    void saveSzenarium(String^ path);
    void saveSimpleTimeSzenarium(String^ path);
    void loadSzenarium(String^ path,ArrayList^ protoSet);
    void setMessageBox(CMessageForm^ messBox);
    void calcDelay(double rel);
    void setSelectSzenItemTyp(SelectSzenItemTyp^ eventTyp);
    void setRemoveSzenarioItemFromViewTyp(RemoveSzenarioItemFromViewTyp^ eventTyp);
    void updateItem(CItemWrapper^ tlgWr);
    void setInterConnListe(ArrayList^ liste);
    void sendSzenarium(bool sendComplet);
    void stopSendSzenarium(bool abort);
    void setMessageHandler(MessageHandlerTyp^ handler);
    void setSzenariumModusEvent(SzenariumModusEventTyp^ szenModus);
    CItemBaseContainerWrapper^ getSzenariumContainer();
    void selectTelegram(int index);
    void setUpdateSzenEvent(UpdateSzenEventTyp^ CloseSzen);
    void updateSzenFile();
    void ShowFromDateilView();
    int getSelSzenItem();
    void removeInterfaceFromSzenarium(String^ inter);
    void removeAllCyclicTlgInSzenario();
    void showCyclicTelegramsInSzenario();
    void messageHandler(String^ mess,int type);
    int getCountOfItems();
    bool IsSendMode();
    bool IsSzenarionSending();
    bool TlgsFromInterInSzenario(String^ inter);
    void setSzenChangeModus();
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
  private: System::Windows::Forms::Panel ^  panBackGround;
  private: System::Windows::Forms::Panel ^  panTitel;
  private: System::Windows::Forms::Label ^  labSzen;
  private: System::Windows::Forms::Panel ^  panBody;
  private: System::Windows::Forms::ImageList ^  imageList;
  private: System::Windows::Forms::TabPage ^  tabPage1;
  private: System::Windows::Forms::Label ^  label1;
  private: System::Windows::Forms::TextBox ^  txtBxTime;
  private: System::Windows::Forms::Label ^  label2;
  private: System::Windows::Forms::Label ^  label3;
  private: System::Windows::Forms::Label ^  label4;
  private: System::Windows::Forms::Label ^  label5;
  private: System::Windows::Forms::TrackBar ^  trackBarTime;
  private: System::Windows::Forms::TextBox ^  txtBxSimTime;
  private: System::Windows::Forms::TextBox ^  txtBxRealTime;
  private: System::Windows::Forms::TextBox ^  txtBxDauer;
  private: System::Windows::Forms::Label ^  label6;
  private: System::Windows::Forms::Label ^  label7;
  private: System::Windows::Forms::Panel ^  panel1;

  private: System::Windows::Forms::Panel ^  panDebug;
  private: System::Windows::Forms::TabControl ^  tabCntrlTime;
  private: System::Windows::Forms::TabPage ^  tabPageRealTime;
	private: System::Windows::Forms::Panel ^  panel2;
	private: System::Windows::Forms::Button ^  buttRem;
	private: System::Windows::Forms::NumericUpDown ^  numericUpCopyDown;
	private: System::Windows::Forms::Panel ^  panScrollBar;
	private: System::Windows::Forms::VScrollBar ^  vScrollBar1;
  private: System::Windows::Forms::Panel^  panItemCon;
  private: System::Windows::Forms::Button ^  buttDupl;
  private: System::Windows::Forms::Panel ^  panDebugModus;
	private: System::Windows::Forms::Label ^  label9;
	private: System::Windows::Forms::Button ^  buttStep;
	private: System::Windows::Forms::Button ^  butRun;
  private: System::Windows::Forms::ContextMenu ^  PopUpMenu;
  private: System::Windows::Forms::MenuItem ^  menuItemSend;
  private: System::Windows::Forms::MenuItem ^  menuSendFromThis;
  private: System::Windows::Forms::MenuItem ^  menuSetCyclicTlg;     
  private: System::Windows::Forms::Button ^  buttDelayOk;

  private: System::Windows::Forms::Button ^  buttTlgUp;
  private: System::Windows::Forms::Button ^  buttTlgDown;
  private: System::Windows::Forms::NumericUpDown ^  numUpDownTlg;
  private: System::Windows::Forms::Button ^  buttSort;
  private: System::Windows::Forms::Button^  butModi;
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
      this->components = (gcnew System::ComponentModel::Container());
      System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(CSzenariumForm::typeid));
      this->panBackGround = (gcnew System::Windows::Forms::Panel());
      this->panBody = (gcnew System::Windows::Forms::Panel());
      this->panItemCon = (gcnew System::Windows::Forms::Panel());
      this->panScrollBar = (gcnew System::Windows::Forms::Panel());
      this->vScrollBar1 = (gcnew System::Windows::Forms::VScrollBar());
      this->panDebug = (gcnew System::Windows::Forms::Panel());
      this->panTitel = (gcnew System::Windows::Forms::Panel());
      this->panel2 = (gcnew System::Windows::Forms::Panel());
      this->buttSort = (gcnew System::Windows::Forms::Button());
      this->buttTlgUp = (gcnew System::Windows::Forms::Button());
      this->buttTlgDown = (gcnew System::Windows::Forms::Button());
      this->numUpDownTlg = (gcnew System::Windows::Forms::NumericUpDown());
      this->panDebugModus = (gcnew System::Windows::Forms::Panel());
      this->butRun = (gcnew System::Windows::Forms::Button());
      this->buttStep = (gcnew System::Windows::Forms::Button());
      this->label9 = (gcnew System::Windows::Forms::Label());
      this->numericUpCopyDown = (gcnew System::Windows::Forms::NumericUpDown());
      this->buttRem = (gcnew System::Windows::Forms::Button());
      this->buttDupl = (gcnew System::Windows::Forms::Button());
      this->panel1 = (gcnew System::Windows::Forms::Panel());
      this->butModi = (gcnew System::Windows::Forms::Button());
      this->tabCntrlTime = (gcnew System::Windows::Forms::TabControl());
      this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
      this->buttDelayOk = (gcnew System::Windows::Forms::Button());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->txtBxTime = (gcnew System::Windows::Forms::TextBox());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->tabPageRealTime = (gcnew System::Windows::Forms::TabPage());
      this->label7 = (gcnew System::Windows::Forms::Label());
      this->label6 = (gcnew System::Windows::Forms::Label());
      this->txtBxDauer = (gcnew System::Windows::Forms::TextBox());
      this->trackBarTime = (gcnew System::Windows::Forms::TrackBar());
      this->label5 = (gcnew System::Windows::Forms::Label());
      this->txtBxSimTime = (gcnew System::Windows::Forms::TextBox());
      this->label4 = (gcnew System::Windows::Forms::Label());
      this->txtBxRealTime = (gcnew System::Windows::Forms::TextBox());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->labSzen = (gcnew System::Windows::Forms::Label());
      this->imageList = (gcnew System::Windows::Forms::ImageList(this->components));
      this->PopUpMenu = (gcnew System::Windows::Forms::ContextMenu());
      this->menuItemSend = (gcnew System::Windows::Forms::MenuItem());
      this->menuSendFromThis = (gcnew System::Windows::Forms::MenuItem());
      this->menuSetCyclicTlg = (gcnew System::Windows::Forms::MenuItem());
      this->panBackGround->SuspendLayout();
      this->panBody->SuspendLayout();
      this->panScrollBar->SuspendLayout();
      this->panTitel->SuspendLayout();
      this->panel2->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numUpDownTlg))->BeginInit();
      this->panDebugModus->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpCopyDown))->BeginInit();
      this->panel1->SuspendLayout();
      this->tabCntrlTime->SuspendLayout();
      this->tabPage1->SuspendLayout();
      this->tabPageRealTime->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarTime))->BeginInit();
      this->SuspendLayout();
      // 
      // panBackGround
      // 
      this->panBackGround->Controls->Add(this->panBody);
      this->panBackGround->Controls->Add(this->panTitel);
      this->panBackGround->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panBackGround->Location = System::Drawing::Point(0, 0);
      this->panBackGround->Name = L"panBackGround";
      this->panBackGround->Size = System::Drawing::Size(441, 469);
      this->panBackGround->TabIndex = 0;
      // 
      // panBody
      // 
      this->panBody->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panBody->Controls->Add(this->panItemCon);
      this->panBody->Controls->Add(this->panScrollBar);
      this->panBody->Controls->Add(this->panDebug);
      this->panBody->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panBody->Location = System::Drawing::Point(0, 192);
      this->panBody->Name = L"panBody";
      this->panBody->Size = System::Drawing::Size(441, 277);
      this->panBody->TabIndex = 1;
      // 
      // panItemCon
      // 
      this->panItemCon->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panItemCon->Location = System::Drawing::Point(16, 0);
      this->panItemCon->Name = L"panItemCon";
      this->panItemCon->Size = System::Drawing::Size(409, 273);
      this->panItemCon->TabIndex = 3;
      this->panItemCon->Resize += gcnew System::EventHandler(this, &CSzenariumForm::OnResizeItemCountPanel);
      // 
      // panScrollBar
      // 
      this->panScrollBar->Controls->Add(this->vScrollBar1);
      this->panScrollBar->Dock = System::Windows::Forms::DockStyle::Right;
      this->panScrollBar->Location = System::Drawing::Point(425, 0);
      this->panScrollBar->Name = L"panScrollBar";
      this->panScrollBar->Size = System::Drawing::Size(12, 273);
      this->panScrollBar->TabIndex = 2;
      // 
      // vScrollBar1
      // 
      this->vScrollBar1->Dock = System::Windows::Forms::DockStyle::Fill;
      this->vScrollBar1->LargeChange = 1;
      this->vScrollBar1->Location = System::Drawing::Point(0, 0);
      this->vScrollBar1->Minimum = 1;
      this->vScrollBar1->Name = L"vScrollBar1";
      this->vScrollBar1->Size = System::Drawing::Size(12, 273);
      this->vScrollBar1->TabIndex = 0;
      this->vScrollBar1->Value = 1;
      this->vScrollBar1->ValueChanged += gcnew System::EventHandler(this, &CSzenariumForm::OnScrollValueChange);
      // 
      // panDebug
      // 
      this->panDebug->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panDebug->Dock = System::Windows::Forms::DockStyle::Left;
      this->panDebug->Location = System::Drawing::Point(0, 0);
      this->panDebug->Name = L"panDebug";
      this->panDebug->Size = System::Drawing::Size(16, 273);
      this->panDebug->TabIndex = 0;
      // 
      // panTitel
      // 
      this->panTitel->Controls->Add(this->panel2);
      this->panTitel->Controls->Add(this->panel1);
      this->panTitel->Controls->Add(this->tabCntrlTime);
      this->panTitel->Controls->Add(this->labSzen);
      this->panTitel->Dock = System::Windows::Forms::DockStyle::Top;
      this->panTitel->Location = System::Drawing::Point(0, 0);
      this->panTitel->Name = L"panTitel";
      this->panTitel->Size = System::Drawing::Size(441, 192);
      this->panTitel->TabIndex = 0;
      // 
      // panel2
      // 
      this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
      this->panel2->Controls->Add(this->buttSort);
      this->panel2->Controls->Add(this->buttTlgUp);
      this->panel2->Controls->Add(this->buttTlgDown);
      this->panel2->Controls->Add(this->numUpDownTlg);
      this->panel2->Controls->Add(this->panDebugModus);
      this->panel2->Controls->Add(this->numericUpCopyDown);
      this->panel2->Controls->Add(this->buttRem);
      this->panel2->Controls->Add(this->buttDupl);
      this->panel2->Location = System::Drawing::Point(0, 144);
      this->panel2->Name = L"panel2";
      this->panel2->Size = System::Drawing::Size(464, 56);
      this->panel2->TabIndex = 6;
      // 
      // buttSort
      // 
      this->buttSort->Enabled = false;
      this->buttSort->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"buttSort.Image")));
      this->buttSort->ImageAlign = System::Drawing::ContentAlignment::BottomLeft;
      this->buttSort->Location = System::Drawing::Point(128, 24);
      this->buttSort->Name = L"buttSort";
      this->buttSort->Size = System::Drawing::Size(72, 24);
      this->buttSort->TabIndex = 8;
      this->buttSort->Text = L"      Sort";
      this->buttSort->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      this->buttSort->Visible = false;
      this->buttSort->Click += gcnew System::EventHandler(this, &CSzenariumForm::OnClickButtSort);
      // 
      // buttTlgUp
      // 
      this->buttTlgUp->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"buttTlgUp.Image")));
      this->buttTlgUp->Location = System::Drawing::Point(88, 24);
      this->buttTlgUp->Name = L"buttTlgUp";
      this->buttTlgUp->Size = System::Drawing::Size(34, 24);
      this->buttTlgUp->TabIndex = 7;
      this->buttTlgUp->Click += gcnew System::EventHandler(this, &CSzenariumForm::OnButtTlgUpClick);
      // 
      // buttTlgDown
      // 
      this->buttTlgDown->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"buttTlgDown.Image")));
      this->buttTlgDown->Location = System::Drawing::Point(48, 24);
      this->buttTlgDown->Name = L"buttTlgDown";
      this->buttTlgDown->Size = System::Drawing::Size(34, 24);
      this->buttTlgDown->TabIndex = 6;
      this->buttTlgDown->Click += gcnew System::EventHandler(this, &CSzenariumForm::OnButtTlgDownClick);
      // 
      // numUpDownTlg
      // 
      this->numUpDownTlg->Location = System::Drawing::Point(0, 24);
      this->numUpDownTlg->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numUpDownTlg->Name = L"numUpDownTlg";
      this->numUpDownTlg->Size = System::Drawing::Size(48, 20);
      this->numUpDownTlg->TabIndex = 5;
      this->numUpDownTlg->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      // 
      // panDebugModus
      // 
      this->panDebugModus->Controls->Add(this->butRun);
      this->panDebugModus->Controls->Add(this->buttStep);
      this->panDebugModus->Controls->Add(this->label9);
      this->panDebugModus->Location = System::Drawing::Point(288, 1);
      this->panDebugModus->Name = L"panDebugModus";
      this->panDebugModus->Size = System::Drawing::Size(168, 20);
      this->panDebugModus->TabIndex = 4;
      // 
      // butRun
      // 
      this->butRun->Dock = System::Windows::Forms::DockStyle::Left;
      this->butRun->Enabled = false;
      this->butRun->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"butRun.Image")));
      this->butRun->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
      this->butRun->Location = System::Drawing::Point(92, 0);
      this->butRun->Name = L"butRun";
      this->butRun->Size = System::Drawing::Size(60, 20);
      this->butRun->TabIndex = 4;
      this->butRun->Text = L"Run";
      this->butRun->Click += gcnew System::EventHandler(this, &CSzenariumForm::OnButRunClick);
      // 
      // buttStep
      // 
      this->buttStep->Dock = System::Windows::Forms::DockStyle::Left;
      this->buttStep->Enabled = false;
      this->buttStep->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"buttStep.Image")));
      this->buttStep->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
      this->buttStep->Location = System::Drawing::Point(32, 0);
      this->buttStep->Name = L"buttStep";
      this->buttStep->Size = System::Drawing::Size(60, 20);
      this->buttStep->TabIndex = 3;
      this->buttStep->Text = L"Step";
      this->buttStep->Click += gcnew System::EventHandler(this, &CSzenariumForm::OnButtStepClick);
      // 
      // label9
      // 
      this->label9->Dock = System::Windows::Forms::DockStyle::Left;
      this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->label9->Location = System::Drawing::Point(0, 0);
      this->label9->Name = L"label9";
      this->label9->Size = System::Drawing::Size(32, 20);
      this->label9->TabIndex = 2;
      this->label9->Text = L"Break  Point";
      // 
      // numericUpCopyDown
      // 
      this->numericUpCopyDown->Location = System::Drawing::Point(0, 0);
      this->numericUpCopyDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      this->numericUpCopyDown->Name = L"numericUpCopyDown";
      this->numericUpCopyDown->Size = System::Drawing::Size(48, 20);
      this->numericUpCopyDown->TabIndex = 2;
      this->numericUpCopyDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
      // 
      // buttRem
      // 
      this->buttRem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"buttRem.Image")));
      this->buttRem->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
      this->buttRem->Location = System::Drawing::Point(128, 0);
      this->buttRem->Name = L"buttRem";
      this->buttRem->Size = System::Drawing::Size(72, 24);
      this->buttRem->TabIndex = 1;
      this->buttRem->Text = L"Remove";
      this->buttRem->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
      this->buttRem->Click += gcnew System::EventHandler(this, &CSzenariumForm::OnButtRemoveClick);
      // 
      // buttDupl
      // 
      this->buttDupl->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"buttDupl.Image")));
      this->buttDupl->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
      this->buttDupl->Location = System::Drawing::Point(48, 0);
      this->buttDupl->Name = L"buttDupl";
      this->buttDupl->Size = System::Drawing::Size(74, 24);
      this->buttDupl->TabIndex = 0;
      this->buttDupl->Text = L"   Duplicate";
      this->buttDupl->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
      this->buttDupl->Click += gcnew System::EventHandler(this, &CSzenariumForm::OnButtCopyClick);
      // 
      // panel1
      // 
      this->panel1->Controls->Add(this->butModi);
      this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
      this->panel1->Location = System::Drawing::Point(0, 24);
      this->panel1->Name = L"panel1";
      this->panel1->Size = System::Drawing::Size(441, 24);
      this->panel1->TabIndex = 5;
      // 
      // butModi
      // 
      this->butModi->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
      this->butModi->BackColor = System::Drawing::Color::LightGreen;
      this->butModi->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->butModi->Location = System::Drawing::Point(32, 0);
      this->butModi->Name = L"butModi";
      this->butModi->Size = System::Drawing::Size(381, 24);
      this->butModi->TabIndex = 4;
      this->butModi->Text = L"Switch to send mode";
      this->butModi->UseVisualStyleBackColor = false;
      this->butModi->TextChanged += gcnew System::EventHandler(this, &CSzenariumForm::butModi_TextChanged);
      this->butModi->Click += gcnew System::EventHandler(this, &CSzenariumForm::butModi_Click);
      // 
      // tabCntrlTime
      // 
      this->tabCntrlTime->Controls->Add(this->tabPage1);
      this->tabCntrlTime->Controls->Add(this->tabPageRealTime);
      this->tabCntrlTime->Location = System::Drawing::Point(0, 48);
      this->tabCntrlTime->Name = L"tabCntrlTime";
      this->tabCntrlTime->SelectedIndex = 0;
      this->tabCntrlTime->Size = System::Drawing::Size(464, 96);
      this->tabCntrlTime->TabIndex = 1;
      this->tabCntrlTime->SelectedIndexChanged += gcnew System::EventHandler(this, &CSzenariumForm::OnSelectedIndexChanged);
      // 
      // tabPage1
      // 
      this->tabPage1->Controls->Add(this->buttDelayOk);
      this->tabPage1->Controls->Add(this->label2);
      this->tabPage1->Controls->Add(this->txtBxTime);
      this->tabPage1->Controls->Add(this->label1);
      this->tabPage1->Location = System::Drawing::Point(4, 22);
      this->tabPage1->Name = L"tabPage1";
      this->tabPage1->Size = System::Drawing::Size(456, 70);
      this->tabPage1->TabIndex = 0;
      this->tabPage1->Text = L"Simple Time";
      // 
      // buttDelayOk
      // 
      this->buttDelayOk->Location = System::Drawing::Point(144, 10);
      this->buttDelayOk->Name = L"buttDelayOk";
      this->buttDelayOk->Size = System::Drawing::Size(40, 20);
      this->buttDelayOk->TabIndex = 5;
      this->buttDelayOk->Text = L"Ok";
      this->buttDelayOk->Click += gcnew System::EventHandler(this, &CSzenariumForm::OnButtDelayOkClick);
      // 
      // label2
      // 
      this->label2->Location = System::Drawing::Point(112, 10);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(26, 20);
      this->label2->TabIndex = 4;
      this->label2->Text = L"sec";
      this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // txtBxTime
      // 
      this->txtBxTime->Location = System::Drawing::Point(76, 10);
      this->txtBxTime->Name = L"txtBxTime";
      this->txtBxTime->Size = System::Drawing::Size(32, 20);
      this->txtBxTime->TabIndex = 3;
      this->txtBxTime->Text = L"1";
      // 
      // label1
      // 
      this->label1->Location = System::Drawing::Point(8, 10);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(64, 20);
      this->label1->TabIndex = 2;
      this->label1->Text = L"Time Offset";
      this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // tabPageRealTime
      // 
      this->tabPageRealTime->AutoScroll = true;
      this->tabPageRealTime->Controls->Add(this->label7);
      this->tabPageRealTime->Controls->Add(this->label6);
      this->tabPageRealTime->Controls->Add(this->txtBxDauer);
      this->tabPageRealTime->Controls->Add(this->trackBarTime);
      this->tabPageRealTime->Controls->Add(this->label5);
      this->tabPageRealTime->Controls->Add(this->txtBxSimTime);
      this->tabPageRealTime->Controls->Add(this->label4);
      this->tabPageRealTime->Controls->Add(this->txtBxRealTime);
      this->tabPageRealTime->Controls->Add(this->label3);
      this->tabPageRealTime->Location = System::Drawing::Point(4, 22);
      this->tabPageRealTime->Name = L"tabPageRealTime";
      this->tabPageRealTime->Size = System::Drawing::Size(456, 70);
      this->tabPageRealTime->TabIndex = 1;
      this->tabPageRealTime->Text = L"Real Time";
      // 
      // label7
      // 
      this->label7->Location = System::Drawing::Point(140, 45);
      this->label7->Name = L"label7";
      this->label7->Size = System::Drawing::Size(16, 16);
      this->label7->TabIndex = 10;
      this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // label6
      // 
      this->label6->Location = System::Drawing::Point(0, 45);
      this->label6->Name = L"label6";
      this->label6->Size = System::Drawing::Size(56, 16);
      this->label6->TabIndex = 9;
      this->label6->Text = L"Duration:";
      this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // txtBxDauer
      // 
      this->txtBxDauer->BackColor = System::Drawing::SystemColors::Window;
      this->txtBxDauer->Location = System::Drawing::Point(57, 44);
      this->txtBxDauer->Name = L"txtBxDauer";
      this->txtBxDauer->ReadOnly = true;
      this->txtBxDauer->Size = System::Drawing::Size(62, 20);
      this->txtBxDauer->TabIndex = 8;
      // 
      // trackBarTime
      // 
      this->trackBarTime->BackColor = System::Drawing::SystemColors::Control;
      this->trackBarTime->Location = System::Drawing::Point(45, 16);
      this->trackBarTime->Minimum = 10;
      this->trackBarTime->Name = L"trackBarTime";
      this->trackBarTime->Size = System::Drawing::Size(87, 45);
      this->trackBarTime->TabIndex = 5;
      this->trackBarTime->Value = 10;
      this->trackBarTime->Scroll += gcnew System::EventHandler(this, &CSzenariumForm::OnScrollTrackBar);
      // 
      // label5
      // 
      this->label5->Location = System::Drawing::Point(170, 20);
      this->label5->Name = L"label5";
      this->label5->Size = System::Drawing::Size(16, 23);
      this->label5->TabIndex = 4;
      this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // txtBxSimTime
      // 
      this->txtBxSimTime->Enabled = false;
      this->txtBxSimTime->Location = System::Drawing::Point(136, 20);
      this->txtBxSimTime->Name = L"txtBxSimTime";
      this->txtBxSimTime->Size = System::Drawing::Size(32, 20);
      this->txtBxSimTime->TabIndex = 3;
      this->txtBxSimTime->Text = L"1";
      // 
      // label4
      // 
      this->label4->Location = System::Drawing::Point(35, 20);
      this->label4->Name = L"label4";
      this->label4->Size = System::Drawing::Size(16, 23);
      this->label4->TabIndex = 2;
      this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // txtBxRealTime
      // 
      this->txtBxRealTime->Enabled = false;
      this->txtBxRealTime->Location = System::Drawing::Point(0, 20);
      this->txtBxRealTime->Name = L"txtBxRealTime";
      this->txtBxRealTime->Size = System::Drawing::Size(32, 20);
      this->txtBxRealTime->TabIndex = 1;
      this->txtBxRealTime->Text = L"1";
      // 
      // label3
      // 
      this->label3->Location = System::Drawing::Point(0, 5);
      this->label3->Name = L"label3";
      this->label3->Size = System::Drawing::Size(215, 16);
      this->label3->TabIndex = 0;
      this->label3->Text = L"Real Time        To       Simulation Time";
      // 
      // labSzen
      // 
      this->labSzen->Dock = System::Windows::Forms::DockStyle::Top;
      this->labSzen->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->labSzen->Location = System::Drawing::Point(0, 0);
      this->labSzen->Name = L"labSzen";
      this->labSzen->Size = System::Drawing::Size(441, 24);
      this->labSzen->TabIndex = 0;
      this->labSzen->Text = L"Scenario";
      this->labSzen->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      // 
      // imageList
      // 
      this->imageList->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imageList.ImageStream")));
      this->imageList->TransparentColor = System::Drawing::Color::Transparent;
      this->imageList->Images->SetKeyName(0, L"");
      this->imageList->Images->SetKeyName(1, L"");
      // 
      // PopUpMenu
      // 
      this->PopUpMenu->MenuItems->AddRange(gcnew cli::array< System::Windows::Forms::MenuItem^  >(3) {this->menuItemSend, this->menuSendFromThis, 
        this->menuSetCyclicTlg});
      this->PopUpMenu->Popup += gcnew System::EventHandler(this, &CSzenariumForm::OnPopupMenuClick);
      // 
      // menuItemSend
      // 
      this->menuItemSend->Index = 0;
      this->menuItemSend->Text = L"Send Telegram";
      this->menuItemSend->Click += gcnew System::EventHandler(this, &CSzenariumForm::OnClickMenuItemSend);
      // 
      // menuSendFromThis
      // 
      this->menuSendFromThis->Index = 1;
      this->menuSendFromThis->Text = L"Send From This";
      this->menuSendFromThis->Click += gcnew System::EventHandler(this, &CSzenariumForm::OnClickMenuSendFromThis);
      // 
      // menuSetCyclicTlg
      // 
      this->menuSetCyclicTlg->Index = 2;
      this->menuSetCyclicTlg->Text = L"Add To Cyclic Container";
      this->menuSetCyclicTlg->Click += gcnew System::EventHandler(this, &CSzenariumForm::OnClickMenuSetCyclicTlg);
      // 
      // CSzenariumForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(441, 469);
      this->Controls->Add(this->panBackGround);
      this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        static_cast<System::Byte>(0)));
      this->KeyPreview = true;
      this->Name = L"CSzenariumForm";
      this->Text = L"CSzenariumForm";
      this->Load += gcnew System::EventHandler(this, &CSzenariumForm::OnLoadForm);
      this->Activated += gcnew System::EventHandler(this, &CSzenariumForm::OnActivated);
      this->Leave += gcnew System::EventHandler(this, &CSzenariumForm::OnLeaveFocus);
      this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &CSzenariumForm::CSzenariumForm_KeyUp);
      this->panBackGround->ResumeLayout(false);
      this->panBody->ResumeLayout(false);
      this->panScrollBar->ResumeLayout(false);
      this->panTitel->ResumeLayout(false);
      this->panel2->ResumeLayout(false);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numUpDownTlg))->EndInit();
      this->panDebugModus->ResumeLayout(false);
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpCopyDown))->EndInit();
      this->panel1->ResumeLayout(false);
      this->tabCntrlTime->ResumeLayout(false);
      this->tabPage1->ResumeLayout(false);
      this->tabPage1->PerformLayout();
      this->tabPageRealTime->ResumeLayout(false);
      this->tabPageRealTime->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBarTime))->EndInit();
      this->ResumeLayout(false);

    }		


    //---------------------------------------------------------
    System::Void butModi_Click(System::Object^  sender, System::EventArgs^  e); 
    System::Void OnLoadForm(System::Object ^  sender, System::EventArgs ^  e);
	  System::Void OnActivated(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnScrollTrackBar(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnSelectedIndexChanged(System::Object ^  sender, System::EventArgs ^  e);
	  System::Void OnButtRemoveClick(System::Object ^  sender, System::EventArgs ^  e);
	  System::Void OnButtCopyClick(System::Object ^  sender, System::EventArgs ^  e);
    // !!!
	  //System::Void OnButSzenCloseClick(System::Object ^  sender, System::EventArgs ^  e);
	  //System::Void OnScrollBarScroll(System::Object ^  sender, System::Windows::Forms::ScrollEventArgs ^  e);
    System::Void OnLeaveFocus(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnSzenLabelClick(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnSzenButtonClick(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnSzenValidatedTextBox(System::Object ^  sender, System::EventArgs ^  e);
	  System::Void OnButtDelayOkClick(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnButtStepClick(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnButRunClick(System::Object ^  sender, System::EventArgs ^  e);
	  System::Void OnDebugLabelClick(System::Object ^  sender, System::EventArgs ^  e);
	  System::Void OnResizeItemCountPanel(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnClickMenuItemSend(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnClickMenuSendFromThis(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnClickMenuSetCyclicTlg(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnButtTlgDownClick(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnButtTlgUpClick(System::Object ^  sender, System::EventArgs ^  e);
	  System::Void OnPopupMenuClick(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnClickButtSort(System::Object ^  sender, System::EventArgs ^  e);
	  System::Void OnScrollValueChange(System::Object ^  sender, System::EventArgs ^  e);
    System::Void CSzenariumForm_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e); 
    System::Void MouseWheelHandler(System::Object ^  sender, System::Windows::Forms::MouseEventArgs^ e);
    System::Void butModi_TextChanged(System::Object^  sender, System::EventArgs^  e);
    //---------------------------------------------------------

	static String^ mEditMode = "Switch to send mode";
  static String^ mSendMode = "Switch to edit mode";
  bool IgnoreDelayTimeOfUnselctedTlgs;
  CMessageForm^ MessageBox;
	CSzenarium^ Szenarium;
	ArrayList^ SzenItemInfoArray;
	ArrayList^ InterConnListe;
  int FocucedItem;
	SelectSzenItemTyp^ SelectItemEvent;
	MessageHandlerTyp^ MessageHandler;
	//Thread, sendet das Szenarium
  System::Threading::Thread^ SendSzenThread;
  //Thread, sendet zyklische Telegramme im Szenarium
  System::Threading::Thread^ SendCyclicSzenThread;
  //Beendet das Senden des Szenariums
  bool StopSendSzenario;
	//int IndexOfSendItem;
	//int IndexOfSendSzenItem;
	int DebugModus;
  int SendTelIndex;
	Color SelItemColor;
  Color SendItemColor;
  Color DefaultColor;
  Color ChangeValueColor;
	bool UpDataFlag;
	SzenariumModusEventTyp^ SzenariumModusEvent;
  UpdateSzenEventTyp^ UpdateSzenEvent;
  RemoveSzenarioItemFromViewTyp^ RemoveSzenarioItemFromViewEvent;

	CInterBaseManager^ getProtoInterface(String^ interName,ArrayList^ liste);
  CProgressBarViewForm^ progressBar;
  System::Threading::Timer^ timerWatch;

	//=====================================
	void showItemContainer(int underPos);
	void initSzenItem(int count);
  void clearSzenView();
  int getFocusedSzenItem(int index);
  void setLabDefaultColor();
	void sendTelegrams(Object^ sendComplet);
	CInterSenderManager^ getInterface(String^ inter);
	//! Diese Methode aendert Ansicht zwischen Send und Edit Mode.
  void changeMode();
	void updateRelationDelay();
	void setItemTxtBoxModus(bool mode);
	void updateViewTelFromScroll();
  void sendOneTelegram();
  void setDisableFocus();    
  void updateSzenView();
	void updateScrollPosition();
	void showSzenFromScrollPos();
	void setScrollFromSelectedItem(int offset,int dir);
  void setScrollFromSendedItem();
  void EditModeUpdateToItemView();
  void sendCyclicTelegrams();
  void CompareConfigIdWithFileId (CItemWrapper^ item,CXmlInterConfigReader^ confFileReader);
  void getMassageFromSzenario(String^ mess);
  void UpdateProgressBar(int value);
  void SzenStatusWatcher(Object^ stateInfo);
};
}