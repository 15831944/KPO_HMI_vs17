#pragma once
#include "./CTlgInterfaceWrapper.h"
#include "./CInterConnection.h"
#include "./CStdConverter.h"
#include "./CTlgContainerWrapper.h"
#include "./CInterReceiverManager.h"
#include "./CInterBaseManager.h"
#include "./CInterConfigWrapper.h"
#include "./CSenderForm.h"
#include "./CBofMainForm.h"
#include <io.h>
#include <stdio.h>
#include "CLogWriterWrapper.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Threading;

namespace simulator
{
	/// <summary> 
	/// Summary for CBofMainForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CBofMainForm : public System::Windows::Forms::Form
	{
	public: 
		CBofMainForm(void)
		{
			InitializeComponent();
      initComponent();
		}
     
    //CBofMainForm(Panel* parent);

    //...set and get Interface des Telegramms
		void setTlgInterface(CTlgInterfaceWrapper ^W);
        CTlgInterfaceWrapper^ getTlgInterface();
		//...set and get InterConnection als Receiver
		void setInterConnectionReceive(CInterConnection ^R);
        CInterConnection^ getInterConnectionReceive();
		//...set and get InterConnection als Sender
		void setInterConnectionSenden(CInterConnection ^I);
        CInterConnection^ getInterConnectionSenden();
    
    void initComponent();
    void Tlgreceiven(CItemWrapper^ tlg);
    void Tlgsenden();

	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	/*if (C_trd->IsAlive)
	 //        C_trd->Abort();*/
  //    if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
  /// </Init Component>
  private: System::Windows::Forms::Panel ^  panel1;
  private: System::Windows::Forms::Panel ^  panel2;
  private: System::Windows::Forms::GroupBox ^  groupBox3;
  private: System::Windows::Forms::Panel ^  panel3;
  private: System::Windows::Forms::GroupBox ^  GasModelgroupBox;
  private: System::Windows::Forms::TextBox ^  textBox8;
  private: System::Windows::Forms::TextBox ^  textBox7;
  private: System::Windows::Forms::TextBox ^  textBox6;
  private: System::Windows::Forms::TextBox ^  textBox5;
  private: System::Windows::Forms::Label ^  label25;
  private: System::Windows::Forms::Label ^  label26;
  private: System::Windows::Forms::Label ^  label27;
  private: System::Windows::Forms::Label ^  label28;
  private: System::Windows::Forms::TextBox ^  textBox4;
  private: System::Windows::Forms::TextBox ^  textBox3;
  private: System::Windows::Forms::Label ^  label29;
  private: System::Windows::Forms::Label ^  label30;
  private: System::Windows::Forms::TextBox ^  textBox2;
  private: System::Windows::Forms::Label ^  label31;
  private: System::Windows::Forms::TextBox ^  textBox1;
  private: System::Windows::Forms::Label ^  label32;
  private: System::Windows::Forms::GroupBox ^  WaterGasgroupBox;
  private: System::Windows::Forms::TextBox ^  textBox13;
  private: System::Windows::Forms::TextBox ^  textBox12;
  private: System::Windows::Forms::TextBox ^  textBox11;
  private: System::Windows::Forms::TextBox ^  textBox10;
  private: System::Windows::Forms::TextBox ^  textBox9;
  private: System::Windows::Forms::Label ^  label33;
  private: System::Windows::Forms::Label ^  label34;
  private: System::Windows::Forms::Label ^  label35;
  private: System::Windows::Forms::Label ^  label36;
  private: System::Windows::Forms::Label ^  label37;
  private: System::Windows::Forms::Panel ^  panel4;

  private: System::Windows::Forms::Button ^  weiterbutton;
  private: System::Windows::Forms::Button ^  startbutton;
  private: System::Windows::Forms::TextBox ^  textBox14;
  private: System::Windows::Forms::Button ^  stopbutton;
  private: System::Windows::Forms::Splitter ^  splitter1;
  private: System::Windows::Forms::Panel ^  panel5;

  private: System::Windows::Forms::PictureBox ^  pictureBox1;
private: System::Windows::Forms::Label ^  label41;
private: System::Windows::Forms::Label ^  label42;
private: System::Windows::Forms::Label ^  label43;
private: System::Windows::Forms::Label ^  label44;
private: System::Windows::Forms::Label ^  label45;
private: System::Windows::Forms::Label ^  label46;
private: System::Windows::Forms::Label ^  label47;
private: System::Windows::Forms::Label ^  label48;
private: System::Windows::Forms::Label ^  label19;
private: System::Windows::Forms::Label ^  label20;


private: System::Windows::Forms::GroupBox ^  ConposgroupBox;
private: System::Windows::Forms::Label ^  label49;
private: System::Windows::Forms::Label ^  label50;
private: System::Windows::Forms::TextBox ^  textBox26;
private: System::Windows::Forms::TextBox ^  textBox27;
private: System::Windows::Forms::TextBox ^  textBoxlancehigh;
private: System::Windows::Forms::Label ^  labellancehigh;
private: System::Windows::Forms::Label ^  label24;
private: System::Windows::Forms::Label ^  label23;
private: System::Windows::Forms::Label ^  label22;
private: L1SimulatorControls::Led ^  led24;
private: L1SimulatorControls::Led ^  led23;
private: L1SimulatorControls::Led ^  led22;
private: System::Windows::Forms::Button ^  Sendbutton;
private: System::Windows::Forms::Button ^  Receivenbutton;
private: System::Windows::Forms::GroupBox ^  HMCgroupBox;

private: System::Windows::Forms::Label ^  label53;
private: System::Windows::Forms::Label ^  label54;
private: System::Windows::Forms::Label ^  label55;
private: System::Windows::Forms::Label ^  label56;
private: System::Windows::Forms::GroupBox ^  lanceblowstatusgroupBox;
private: System::Windows::Forms::TextBox ^  textBox33;
private: System::Windows::Forms::TextBox ^  textBox34;
private: System::Windows::Forms::TextBox ^  textBox35;
private: System::Windows::Forms::TextBox ^  textBox36;
private: System::Windows::Forms::Label ^  label57;
private: System::Windows::Forms::Label ^  label58;
private: System::Windows::Forms::Label ^  label59;
private: System::Windows::Forms::GroupBox ^  GasStatusgroupBox;
private: System::Windows::Forms::Label ^  label21;
private: System::Windows::Forms::Label ^  label38;
private: System::Windows::Forms::NumericUpDown ^  numericUpDown3;
private: System::Windows::Forms::NumericUpDown ^  numericUpDown2;
private: System::Windows::Forms::Label ^  label39;
private: System::Windows::Forms::NumericUpDown ^  numericUpDown1;

private: System::Windows::Forms::TextBox ^  textBox37;
private: System::Windows::Forms::Label ^  label61;
private: System::Windows::Forms::Label ^  label62;
private: System::Windows::Forms::TextBox ^  textBox38;
private: System::Windows::Forms::Label ^  label63;
private: System::Windows::Forms::TextBox ^  textBox39;
private: System::Windows::Forms::GroupBox ^  DeslagginggroupBox;
private: System::Windows::Forms::TextBox ^  textBox40;
private: System::Windows::Forms::Label ^  label64;
private: System::Windows::Forms::GroupBox ^  TappinggroupBox;
private: System::Windows::Forms::TextBox ^  textBox41;
private: System::Windows::Forms::TextBox ^  textBox42;
private: System::Windows::Forms::TextBox ^  textBox43;
private: System::Windows::Forms::Label ^  label65;
private: System::Windows::Forms::Label ^  label66;
private: System::Windows::Forms::Label ^  label67;
private: System::Windows::Forms::GroupBox ^  BlowStartgroupBox;
private: System::Windows::Forms::GroupBox ^  ReadyforBlowgroupBox;
private: System::Windows::Forms::GroupBox ^  SampleTakengroupBox;
private: System::Windows::Forms::TextBox ^  textBox44;
private: System::Windows::Forms::TextBox ^  textBox45;
private: System::Windows::Forms::TextBox ^  textBox46;
private: System::Windows::Forms::Label ^  label68;
private: System::Windows::Forms::Label ^  label69;
private: System::Windows::Forms::Label ^  label70;
private: System::Windows::Forms::TextBox ^  textBox47;
private: System::Windows::Forms::TextBox ^  textBox48;
private: System::Windows::Forms::Label ^  label71;
private: System::Windows::Forms::Label ^  label72;
private: System::Windows::Forms::TextBox ^  textBox49;
private: System::Windows::Forms::Label ^  label73;
private: System::Windows::Forms::TextBox ^  textBox50;
private: System::Windows::Forms::Label ^  label74;
private: System::Windows::Forms::Label ^  label75;
private: System::Windows::Forms::Button ^  TlgHeadbutton;
private: System::Windows::Forms::Label ^  label60;
private: System::Windows::Forms::GroupBox ^  HeatgroupBox;
private: System::Windows::Forms::GroupBox ^  TlgHeadStatusgroupBox;
private: System::Windows::Forms::Label ^  label52;
private: System::Windows::Forms::Label ^  label51;

private: System::Windows::Forms::GroupBox ^  LanceStatusgroupBox;
private: System::Windows::Forms::TextBox ^  textBox15;
private: System::Windows::Forms::Label ^  label40;
private: System::Windows::Forms::RadioButton ^  radioButton1;
private: System::Windows::Forms::RadioButton ^  radioButton2;


private: System::Windows::Forms::Label ^  label78;


private: System::Windows::Forms::Label ^  label79;
private: System::Windows::Forms::Label ^  label80;

private: System::Windows::Forms::Label ^  label81;

private: System::Windows::Forms::Label ^  label82;

private: System::Windows::Forms::GroupBox ^  FreespacegroupBox;
private: System::Windows::Forms::TextBox ^  textBoxPlantID;
private: System::Windows::Forms::TextBox ^  textBoxProductID;
private: System::Windows::Forms::TextBox ^  textBoxReserve;
private: System::Windows::Forms::TextBox ^  textBoxBlen;
private: System::Windows::Forms::TextBox ^  textBoxOrg;
private: System::Windows::Forms::TextBox ^  textBoxCreaTime;
private: System::Windows::Forms::TextBox ^  textBoxCreaDate;
private: System::Windows::Forms::TextBox ^  textBoxMsgID;



private: System::Windows::Forms::TextBox ^  textBoxFreespare5;
private: System::Windows::Forms::TextBox ^  textBoxFreespare4;
private: System::Windows::Forms::TextBox ^  textBoxFreespare3;
private: System::Windows::Forms::TextBox ^  textBoxFreespare2;
private: System::Windows::Forms::TextBox ^  textBoxFreespare1;
private: System::Windows::Forms::TextBox ^  textBoxHMLocation;
private: System::Windows::Forms::TextBox ^  textBoxMatWgt;
private: System::Windows::Forms::TextBox ^  textBoxWgtstat;
private: System::Windows::Forms::TextBox ^  textBoxLDINo;
private: System::Windows::Forms::TextBox ^  textBoxRetreatID;
private: System::Windows::Forms::TextBox ^  textBoxHeatNo;
private: System::Windows::Forms::TextBox ^  textBoxTime;
private: System::Windows::Forms::TextBox ^  textBoxDate;
private: System::Windows::Forms::Label ^  label76;
private: System::Windows::Forms::Label ^  label77;
private: System::Windows::Forms::TextBox ^  textBoxmessage;

  private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
    
    //...Variable
    Thread ^C_trd; 
    int C_imageIndex;
    Graphics ^C_p;
    Image ^C_image;
    String ^C_imagename;
    static int HeadStaFlag = 0;
    int Flag;

    String ^C_Pname;
    int C_prozessIndex;
    int C_obfileexsit;
    char *C_filename;
    L1SimulatorControls::Led ^ C_ledd;
    static array <String^>^ p = {"HA","CIP","SC","SSTART","HMC","H","LD","BSTART","BEND","IBN","RBSTART",
                           "RBEND","LU","T","TEND","D","DEND"};
    
    //private Attribut fuer Telegramm
	  CTlgInterfaceWrapper ^C_Wr;            //Objekt des Class TlgInterfaceWrapper von Wrapper
		CInterConnection ^C_Receiver;          //Objekt des Class CInterConnection von Socket
		CInterConnection ^C_Sender;            //Objekt des Class CInterConnection von Socket
	  CItemWrapper ^C_tlgWr;                  //Objeke des Class TlgWrapper von Wrapper
    CStdConverter ^C_Std;                 //Objekt des Class CStdConverte
    CTlgContainerWrapper ^C_TlgContainer;  //Objekt des Class CTlgContainerWrapper;
    CInterReceiverManager ^C_interReceiverMan;     
    String ^C_TlgName;
		String ^C_TlgBody;
    ArrayList^ C_ArrayTextBox;

    CLogWriterWrapper^ LogWriter;


private: System::Windows::Forms::Button ^  sendenbutton;


















private: System::Timers::Timer ^  timer1;
private: System::Windows::Forms::Button ^  buttonMakeTlg;
private: System::Windows::Forms::GroupBox ^  groupBox1;
private: System::Windows::Forms::Label ^  label18;
private: System::Windows::Forms::Label ^  label17;
private: System::Windows::Forms::Label ^  label16;
private: System::Windows::Forms::Label ^  label15;
private: System::Windows::Forms::Label ^  label14;
private: System::Windows::Forms::Label ^  label13;
private: System::Windows::Forms::Button ^  buttonSE;
private: System::Windows::Forms::Button ^  buttonDE;
private: System::Windows::Forms::Button ^  buttonDS;
private: System::Windows::Forms::Button ^  buttonTE;
private: System::Windows::Forms::Button ^  buttonTS;
private: L1SimulatorControls::Led ^  led18;
private: L1SimulatorControls::Led ^  led17;
private: L1SimulatorControls::Led ^  led16;
private: L1SimulatorControls::Led ^  led15;
private: L1SimulatorControls::Led ^  led14;
private: System::Windows::Forms::Button ^  buttonLU;
private: L1SimulatorControls::Led ^  led13;
private: System::Windows::Forms::Label ^  label12;
private: System::Windows::Forms::Label ^  label11;
private: System::Windows::Forms::Label ^  label10;
private: System::Windows::Forms::Label ^  label9;
private: System::Windows::Forms::Label ^  label8;
private: System::Windows::Forms::Label ^  label7;
private: System::Windows::Forms::Label ^  label6;
private: System::Windows::Forms::Label ^  label5;
private: System::Windows::Forms::Label ^  label4;
private: System::Windows::Forms::Label ^  label3;
private: System::Windows::Forms::Label ^  label2;
private: System::Windows::Forms::Label ^  label1;
private: System::Windows::Forms::Button ^  buttonRE;
private: System::Windows::Forms::Button ^  buttonRS;
private: System::Windows::Forms::Button ^  buttonTM;
private: System::Windows::Forms::Button ^  buttonBE;
private: System::Windows::Forms::Button ^  buttonBS;
private: System::Windows::Forms::Button ^  buttonLD;
private: System::Windows::Forms::Button ^  buttonHS;
private: System::Windows::Forms::Button ^  button5;
private: System::Windows::Forms::Button ^  buttonSS;
private: System::Windows::Forms::Button ^  buttonCIP;
private: System::Windows::Forms::Button ^  buttonHA;
private: L1SimulatorControls::Led ^  led12;
private: L1SimulatorControls::Led ^  led11;
private: L1SimulatorControls::Led ^  led10;
private: L1SimulatorControls::Led ^  led9;
private: L1SimulatorControls::Led ^  led8;
private: L1SimulatorControls::Led ^  led7;
private: L1SimulatorControls::Led ^  led6;
private: L1SimulatorControls::Led ^  led5;
private: L1SimulatorControls::Led ^  led4;
private: L1SimulatorControls::Led ^  led3;
private: L1SimulatorControls::Led ^  led2;
private: L1SimulatorControls::Led ^  led1;
private: System::Windows::Forms::Button ^  buttonSC;
private: System::Windows::Forms::Panel ^  panel6;
private: System::Windows::Forms::Label ^  label83;
private: System::Windows::Forms::Button ^  button1;
private: System::Windows::Forms::GroupBox ^  groupBox2;
private: System::Windows::Forms::Label ^  label84;
private: System::Windows::Forms::TextBox ^  textBox16;
private: System::Windows::Forms::TextBox ^  textBox17;
private: System::Windows::Forms::Label ^  label85;
private: System::Windows::Forms::Label ^  label86;
private: System::Windows::Forms::TextBox ^  textBox18;
private: System::Windows::Forms::GroupBox ^  groupBox4;
private: System::Windows::Forms::TextBox ^  textBox19;
private: System::Windows::Forms::TextBox ^  textBox20;
private: System::Windows::Forms::TextBox ^  textBox21;
private: System::Windows::Forms::TextBox ^  textBox22;
private: System::Windows::Forms::Label ^  label87;
private: System::Windows::Forms::Label ^  label88;
private: System::Windows::Forms::Label ^  label89;
private: System::Windows::Forms::Label ^  label90;
private: System::Windows::Forms::GroupBox ^  groupBox5;
private: System::Windows::Forms::Label ^  label91;
private: System::Windows::Forms::Label ^  label92;
private: System::Windows::Forms::Label ^  label93;
private: L1SimulatorControls::Led ^  led19;
private: L1SimulatorControls::Led ^  led20;
private: L1SimulatorControls::Led ^  led21;
private: System::Windows::Forms::GroupBox ^  groupBox6;
private: System::Windows::Forms::TextBox ^  textBox23;
private: System::Windows::Forms::TextBox ^  textBox24;
private: System::Windows::Forms::Label ^  label94;
private: System::Windows::Forms::Label ^  label95;
private: System::Windows::Forms::TextBox ^  textBox25;
private: System::Windows::Forms::TextBox ^  textBox28;
private: System::Windows::Forms::Label ^  label96;
private: System::Windows::Forms::Label ^  label97;
private: System::Windows::Forms::GroupBox ^  groupBox7;
private: System::Windows::Forms::TextBox ^  textBox29;
private: System::Windows::Forms::TextBox ^  textBox30;
private: System::Windows::Forms::TextBox ^  textBox31;
private: System::Windows::Forms::TextBox ^  textBox32;
private: System::Windows::Forms::TextBox ^  textBox51;
private: System::Windows::Forms::TextBox ^  textBox52;
private: System::Windows::Forms::TextBox ^  textBox53;
private: System::Windows::Forms::TextBox ^  textBox54;
private: System::Windows::Forms::Label ^  label98;
private: System::Windows::Forms::Label ^  label99;
private: System::Windows::Forms::Label ^  label100;
private: System::Windows::Forms::Label ^  label101;
private: System::Windows::Forms::Label ^  label102;
private: System::Windows::Forms::Label ^  label103;
private: System::Windows::Forms::Label ^  label104;
private: System::Windows::Forms::Label ^  label105;
private: System::Windows::Forms::GroupBox ^  groupBox8;
private: System::Windows::Forms::TextBox ^  textBox55;
private: System::Windows::Forms::Label ^  label106;
private: System::Windows::Forms::Label ^  label107;
private: System::Windows::Forms::TextBox ^  textBox56;
private: System::Windows::Forms::GroupBox ^  groupBox9;
private: System::Windows::Forms::TextBox ^  textBox57;
private: System::Windows::Forms::TextBox ^  textBox58;
private: System::Windows::Forms::TextBox ^  textBox59;
private: System::Windows::Forms::TextBox ^  textBox60;
private: System::Windows::Forms::Label ^  label108;
private: System::Windows::Forms::Label ^  label109;
private: System::Windows::Forms::Label ^  label110;
private: System::Windows::Forms::Label ^  label111;
private: System::Windows::Forms::GroupBox ^  groupBox10;
private: System::Windows::Forms::TextBox ^  textBox61;
private: System::Windows::Forms::Label ^  label112;
private: System::Windows::Forms::RadioButton ^  radioButton3;
private: System::Windows::Forms::RadioButton ^  radioButton4;

























































         ArrayList^ C_InterReceiverManList;

    /// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager((CBofMainForm::typeid)));
      this->panel1 = (gcnew System::Windows::Forms::Panel());
      this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->label18 = (gcnew System::Windows::Forms::Label());
      this->label17 = (gcnew System::Windows::Forms::Label());
      this->label16 = (gcnew System::Windows::Forms::Label());
      this->label15 = (gcnew System::Windows::Forms::Label());
      this->label14 = (gcnew System::Windows::Forms::Label());
      this->label13 = (gcnew System::Windows::Forms::Label());
      this->buttonSE = (gcnew System::Windows::Forms::Button());
      this->buttonDE = (gcnew System::Windows::Forms::Button());
      this->buttonDS = (gcnew System::Windows::Forms::Button());
      this->buttonTE = (gcnew System::Windows::Forms::Button());
      this->buttonTS = (gcnew System::Windows::Forms::Button());
      this->led18 = (gcnew L1SimulatorControls::Led());
      this->led17 = (gcnew L1SimulatorControls::Led());
      this->led16 = (gcnew L1SimulatorControls::Led());
      this->led15 = (gcnew L1SimulatorControls::Led());
      this->led14 = (gcnew L1SimulatorControls::Led());
      this->buttonLU = (gcnew System::Windows::Forms::Button());
      this->led13 = (gcnew L1SimulatorControls::Led());
      this->label12 = (gcnew System::Windows::Forms::Label());
      this->label11 = (gcnew System::Windows::Forms::Label());
      this->label10 = (gcnew System::Windows::Forms::Label());
      this->label9 = (gcnew System::Windows::Forms::Label());
      this->label8 = (gcnew System::Windows::Forms::Label());
      this->label7 = (gcnew System::Windows::Forms::Label());
      this->label6 = (gcnew System::Windows::Forms::Label());
      this->label5 = (gcnew System::Windows::Forms::Label());
      this->label4 = (gcnew System::Windows::Forms::Label());
      this->label3 = (gcnew System::Windows::Forms::Label());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->buttonRE = (gcnew System::Windows::Forms::Button());
      this->buttonRS = (gcnew System::Windows::Forms::Button());
      this->buttonTM = (gcnew System::Windows::Forms::Button());
      this->buttonBE = (gcnew System::Windows::Forms::Button());
      this->buttonBS = (gcnew System::Windows::Forms::Button());
      this->buttonLD = (gcnew System::Windows::Forms::Button());
      this->buttonHS = (gcnew System::Windows::Forms::Button());
      this->button5 = (gcnew System::Windows::Forms::Button());
      this->buttonSS = (gcnew System::Windows::Forms::Button());
      this->buttonCIP = (gcnew System::Windows::Forms::Button());
      this->buttonHA = (gcnew System::Windows::Forms::Button());
      this->led12 = (gcnew L1SimulatorControls::Led());
      this->led11 = (gcnew L1SimulatorControls::Led());
      this->led10 = (gcnew L1SimulatorControls::Led());
      this->led9 = (gcnew L1SimulatorControls::Led());
      this->led8 = (gcnew L1SimulatorControls::Led());
      this->led7 = (gcnew L1SimulatorControls::Led());
      this->led6 = (gcnew L1SimulatorControls::Led());
      this->led5 = (gcnew L1SimulatorControls::Led());
      this->led4 = (gcnew L1SimulatorControls::Led());
      this->led3 = (gcnew L1SimulatorControls::Led());
      this->led2 = (gcnew L1SimulatorControls::Led());
      this->led1 = (gcnew L1SimulatorControls::Led());
      this->buttonSC = (gcnew System::Windows::Forms::Button());
      this->sendenbutton = (gcnew System::Windows::Forms::Button());
      this->buttonMakeTlg = (gcnew System::Windows::Forms::Button());
      this->label52 = (gcnew System::Windows::Forms::Label());
      this->label51 = (gcnew System::Windows::Forms::Label());
      this->textBoxmessage = (gcnew System::Windows::Forms::TextBox());
      this->Receivenbutton = (gcnew System::Windows::Forms::Button());
      this->Sendbutton = (gcnew System::Windows::Forms::Button());
      this->panel2 = (gcnew System::Windows::Forms::Panel());
      this->panel6 = (gcnew System::Windows::Forms::Panel());
      this->label83 = (gcnew System::Windows::Forms::Label());
      this->button1 = (gcnew System::Windows::Forms::Button());
      this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
      this->label84 = (gcnew System::Windows::Forms::Label());
      this->textBox16 = (gcnew System::Windows::Forms::TextBox());
      this->textBox17 = (gcnew System::Windows::Forms::TextBox());
      this->label85 = (gcnew System::Windows::Forms::Label());
      this->label86 = (gcnew System::Windows::Forms::Label());
      this->textBox18 = (gcnew System::Windows::Forms::TextBox());
      this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
      this->textBox19 = (gcnew System::Windows::Forms::TextBox());
      this->textBox20 = (gcnew System::Windows::Forms::TextBox());
      this->textBox21 = (gcnew System::Windows::Forms::TextBox());
      this->textBox22 = (gcnew System::Windows::Forms::TextBox());
      this->label87 = (gcnew System::Windows::Forms::Label());
      this->label88 = (gcnew System::Windows::Forms::Label());
      this->label89 = (gcnew System::Windows::Forms::Label());
      this->label90 = (gcnew System::Windows::Forms::Label());
      this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
      this->label91 = (gcnew System::Windows::Forms::Label());
      this->label92 = (gcnew System::Windows::Forms::Label());
      this->label93 = (gcnew System::Windows::Forms::Label());
      this->led19 = (gcnew L1SimulatorControls::Led());
      this->led20 = (gcnew L1SimulatorControls::Led());
      this->led21 = (gcnew L1SimulatorControls::Led());
      this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
      this->textBox23 = (gcnew System::Windows::Forms::TextBox());
      this->textBox24 = (gcnew System::Windows::Forms::TextBox());
      this->label94 = (gcnew System::Windows::Forms::Label());
      this->label95 = (gcnew System::Windows::Forms::Label());
      this->textBox25 = (gcnew System::Windows::Forms::TextBox());
      this->textBox28 = (gcnew System::Windows::Forms::TextBox());
      this->label96 = (gcnew System::Windows::Forms::Label());
      this->label97 = (gcnew System::Windows::Forms::Label());
      this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
      this->textBox29 = (gcnew System::Windows::Forms::TextBox());
      this->textBox30 = (gcnew System::Windows::Forms::TextBox());
      this->textBox31 = (gcnew System::Windows::Forms::TextBox());
      this->textBox32 = (gcnew System::Windows::Forms::TextBox());
      this->textBox51 = (gcnew System::Windows::Forms::TextBox());
      this->textBox52 = (gcnew System::Windows::Forms::TextBox());
      this->textBox53 = (gcnew System::Windows::Forms::TextBox());
      this->textBox54 = (gcnew System::Windows::Forms::TextBox());
      this->label98 = (gcnew System::Windows::Forms::Label());
      this->label99 = (gcnew System::Windows::Forms::Label());
      this->label100 = (gcnew System::Windows::Forms::Label());
      this->label101 = (gcnew System::Windows::Forms::Label());
      this->label102 = (gcnew System::Windows::Forms::Label());
      this->label103 = (gcnew System::Windows::Forms::Label());
      this->label104 = (gcnew System::Windows::Forms::Label());
      this->label105 = (gcnew System::Windows::Forms::Label());
      this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
      this->textBox55 = (gcnew System::Windows::Forms::TextBox());
      this->label106 = (gcnew System::Windows::Forms::Label());
      this->label107 = (gcnew System::Windows::Forms::Label());
      this->textBox56 = (gcnew System::Windows::Forms::TextBox());
      this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
      this->textBox57 = (gcnew System::Windows::Forms::TextBox());
      this->textBox58 = (gcnew System::Windows::Forms::TextBox());
      this->textBox59 = (gcnew System::Windows::Forms::TextBox());
      this->textBox60 = (gcnew System::Windows::Forms::TextBox());
      this->label108 = (gcnew System::Windows::Forms::Label());
      this->label109 = (gcnew System::Windows::Forms::Label());
      this->label110 = (gcnew System::Windows::Forms::Label());
      this->label111 = (gcnew System::Windows::Forms::Label());
      this->groupBox10 = (gcnew System::Windows::Forms::GroupBox());
      this->textBox61 = (gcnew System::Windows::Forms::TextBox());
      this->label112 = (gcnew System::Windows::Forms::Label());
      this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
      this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
      this->labellancehigh = (gcnew System::Windows::Forms::Label());
      this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
      this->textBoxlancehigh = (gcnew System::Windows::Forms::TextBox());
      this->panel3 = (gcnew System::Windows::Forms::Panel());
      this->FreespacegroupBox = (gcnew System::Windows::Forms::GroupBox());
      this->textBoxFreespare5 = (gcnew System::Windows::Forms::TextBox());
      this->label78 = (gcnew System::Windows::Forms::Label());
      this->textBoxFreespare4 = (gcnew System::Windows::Forms::TextBox());
      this->textBoxFreespare3 = (gcnew System::Windows::Forms::TextBox());
      this->label79 = (gcnew System::Windows::Forms::Label());
      this->label80 = (gcnew System::Windows::Forms::Label());
      this->textBoxFreespare2 = (gcnew System::Windows::Forms::TextBox());
      this->label81 = (gcnew System::Windows::Forms::Label());
      this->textBoxFreespare1 = (gcnew System::Windows::Forms::TextBox());
      this->label82 = (gcnew System::Windows::Forms::Label());
      this->SampleTakengroupBox = (gcnew System::Windows::Forms::GroupBox());
      this->textBox44 = (gcnew System::Windows::Forms::TextBox());
      this->textBox45 = (gcnew System::Windows::Forms::TextBox());
      this->textBox46 = (gcnew System::Windows::Forms::TextBox());
      this->label68 = (gcnew System::Windows::Forms::Label());
      this->label69 = (gcnew System::Windows::Forms::Label());
      this->label70 = (gcnew System::Windows::Forms::Label());
      this->textBox47 = (gcnew System::Windows::Forms::TextBox());
      this->textBox48 = (gcnew System::Windows::Forms::TextBox());
      this->label71 = (gcnew System::Windows::Forms::Label());
      this->label72 = (gcnew System::Windows::Forms::Label());
      this->textBox49 = (gcnew System::Windows::Forms::TextBox());
      this->label73 = (gcnew System::Windows::Forms::Label());
      this->textBox50 = (gcnew System::Windows::Forms::TextBox());
      this->label74 = (gcnew System::Windows::Forms::Label());
      this->TappinggroupBox = (gcnew System::Windows::Forms::GroupBox());
      this->textBox41 = (gcnew System::Windows::Forms::TextBox());
      this->textBox42 = (gcnew System::Windows::Forms::TextBox());
      this->textBox43 = (gcnew System::Windows::Forms::TextBox());
      this->label65 = (gcnew System::Windows::Forms::Label());
      this->label66 = (gcnew System::Windows::Forms::Label());
      this->label67 = (gcnew System::Windows::Forms::Label());
      this->DeslagginggroupBox = (gcnew System::Windows::Forms::GroupBox());
      this->textBox40 = (gcnew System::Windows::Forms::TextBox());
      this->label64 = (gcnew System::Windows::Forms::Label());
      this->GasStatusgroupBox = (gcnew System::Windows::Forms::GroupBox());
      this->label21 = (gcnew System::Windows::Forms::Label());
      this->label38 = (gcnew System::Windows::Forms::Label());
      this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
      this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
      this->label39 = (gcnew System::Windows::Forms::Label());
      this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
      this->WaterGasgroupBox = (gcnew System::Windows::Forms::GroupBox());
      this->textBox13 = (gcnew System::Windows::Forms::TextBox());
      this->textBox12 = (gcnew System::Windows::Forms::TextBox());
      this->textBox11 = (gcnew System::Windows::Forms::TextBox());
      this->textBox10 = (gcnew System::Windows::Forms::TextBox());
      this->textBox9 = (gcnew System::Windows::Forms::TextBox());
      this->label33 = (gcnew System::Windows::Forms::Label());
      this->label34 = (gcnew System::Windows::Forms::Label());
      this->label35 = (gcnew System::Windows::Forms::Label());
      this->label36 = (gcnew System::Windows::Forms::Label());
      this->label37 = (gcnew System::Windows::Forms::Label());
      this->GasModelgroupBox = (gcnew System::Windows::Forms::GroupBox());
      this->textBox8 = (gcnew System::Windows::Forms::TextBox());
      this->textBox7 = (gcnew System::Windows::Forms::TextBox());
      this->textBox6 = (gcnew System::Windows::Forms::TextBox());
      this->textBox5 = (gcnew System::Windows::Forms::TextBox());
      this->label25 = (gcnew System::Windows::Forms::Label());
      this->label26 = (gcnew System::Windows::Forms::Label());
      this->label27 = (gcnew System::Windows::Forms::Label());
      this->label28 = (gcnew System::Windows::Forms::Label());
      this->textBox4 = (gcnew System::Windows::Forms::TextBox());
      this->textBox3 = (gcnew System::Windows::Forms::TextBox());
      this->label29 = (gcnew System::Windows::Forms::Label());
      this->label30 = (gcnew System::Windows::Forms::Label());
      this->textBox2 = (gcnew System::Windows::Forms::TextBox());
      this->label31 = (gcnew System::Windows::Forms::Label());
      this->textBox1 = (gcnew System::Windows::Forms::TextBox());
      this->label32 = (gcnew System::Windows::Forms::Label());
      this->panel4 = (gcnew System::Windows::Forms::Panel());
      this->label75 = (gcnew System::Windows::Forms::Label());
      this->TlgHeadbutton = (gcnew System::Windows::Forms::Button());
      this->BlowStartgroupBox = (gcnew System::Windows::Forms::GroupBox());
      this->label63 = (gcnew System::Windows::Forms::Label());
      this->textBox39 = (gcnew System::Windows::Forms::TextBox());
      this->textBox37 = (gcnew System::Windows::Forms::TextBox());
      this->label61 = (gcnew System::Windows::Forms::Label());
      this->label62 = (gcnew System::Windows::Forms::Label());
      this->textBox38 = (gcnew System::Windows::Forms::TextBox());
      this->HMCgroupBox = (gcnew System::Windows::Forms::GroupBox());
      this->textBoxHMLocation = (gcnew System::Windows::Forms::TextBox());
      this->textBoxMatWgt = (gcnew System::Windows::Forms::TextBox());
      this->textBoxWgtstat = (gcnew System::Windows::Forms::TextBox());
      this->textBoxLDINo = (gcnew System::Windows::Forms::TextBox());
      this->label53 = (gcnew System::Windows::Forms::Label());
      this->label54 = (gcnew System::Windows::Forms::Label());
      this->label55 = (gcnew System::Windows::Forms::Label());
      this->label56 = (gcnew System::Windows::Forms::Label());
      this->ReadyforBlowgroupBox = (gcnew System::Windows::Forms::GroupBox());
      this->label24 = (gcnew System::Windows::Forms::Label());
      this->label23 = (gcnew System::Windows::Forms::Label());
      this->label22 = (gcnew System::Windows::Forms::Label());
      this->led24 = (gcnew L1SimulatorControls::Led());
      this->led23 = (gcnew L1SimulatorControls::Led());
      this->led22 = (gcnew L1SimulatorControls::Led());
      this->HeatgroupBox = (gcnew System::Windows::Forms::GroupBox());
      this->textBoxTime = (gcnew System::Windows::Forms::TextBox());
      this->textBoxDate = (gcnew System::Windows::Forms::TextBox());
      this->label76 = (gcnew System::Windows::Forms::Label());
      this->label77 = (gcnew System::Windows::Forms::Label());
      this->textBoxRetreatID = (gcnew System::Windows::Forms::TextBox());
      this->textBoxHeatNo = (gcnew System::Windows::Forms::TextBox());
      this->label20 = (gcnew System::Windows::Forms::Label());
      this->label19 = (gcnew System::Windows::Forms::Label());
      this->TlgHeadStatusgroupBox = (gcnew System::Windows::Forms::GroupBox());
      this->textBoxPlantID = (gcnew System::Windows::Forms::TextBox());
      this->textBoxProductID = (gcnew System::Windows::Forms::TextBox());
      this->textBoxReserve = (gcnew System::Windows::Forms::TextBox());
      this->textBoxBlen = (gcnew System::Windows::Forms::TextBox());
      this->textBoxOrg = (gcnew System::Windows::Forms::TextBox());
      this->textBoxCreaTime = (gcnew System::Windows::Forms::TextBox());
      this->textBoxCreaDate = (gcnew System::Windows::Forms::TextBox());
      this->textBoxMsgID = (gcnew System::Windows::Forms::TextBox());
      this->label48 = (gcnew System::Windows::Forms::Label());
      this->label47 = (gcnew System::Windows::Forms::Label());
      this->label46 = (gcnew System::Windows::Forms::Label());
      this->label45 = (gcnew System::Windows::Forms::Label());
      this->label44 = (gcnew System::Windows::Forms::Label());
      this->label43 = (gcnew System::Windows::Forms::Label());
      this->label42 = (gcnew System::Windows::Forms::Label());
      this->label41 = (gcnew System::Windows::Forms::Label());
      this->ConposgroupBox = (gcnew System::Windows::Forms::GroupBox());
      this->textBox26 = (gcnew System::Windows::Forms::TextBox());
      this->label50 = (gcnew System::Windows::Forms::Label());
      this->label49 = (gcnew System::Windows::Forms::Label());
      this->textBox27 = (gcnew System::Windows::Forms::TextBox());
      this->lanceblowstatusgroupBox = (gcnew System::Windows::Forms::GroupBox());
      this->textBox33 = (gcnew System::Windows::Forms::TextBox());
      this->textBox34 = (gcnew System::Windows::Forms::TextBox());
      this->textBox35 = (gcnew System::Windows::Forms::TextBox());
      this->textBox36 = (gcnew System::Windows::Forms::TextBox());
      this->label57 = (gcnew System::Windows::Forms::Label());
      this->label58 = (gcnew System::Windows::Forms::Label());
      this->label59 = (gcnew System::Windows::Forms::Label());
      this->label60 = (gcnew System::Windows::Forms::Label());
      this->LanceStatusgroupBox = (gcnew System::Windows::Forms::GroupBox());
      this->textBox15 = (gcnew System::Windows::Forms::TextBox());
      this->label40 = (gcnew System::Windows::Forms::Label());
      this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
      this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
      this->weiterbutton = (gcnew System::Windows::Forms::Button());
      this->startbutton = (gcnew System::Windows::Forms::Button());
      this->textBox14 = (gcnew System::Windows::Forms::TextBox());
      this->stopbutton = (gcnew System::Windows::Forms::Button());
      this->splitter1 = (gcnew System::Windows::Forms::Splitter());
      this->panel5 = (gcnew System::Windows::Forms::Panel());
      this->timer1 = (gcnew System::Timers::Timer());
      this->panel1->SuspendLayout();
      this->groupBox3->SuspendLayout();
      this->groupBox1->SuspendLayout();
      this->panel2->SuspendLayout();
      this->panel6->SuspendLayout();
      this->groupBox2->SuspendLayout();
      this->groupBox4->SuspendLayout();
      this->groupBox5->SuspendLayout();
      this->groupBox6->SuspendLayout();
      this->groupBox7->SuspendLayout();
      this->groupBox8->SuspendLayout();
      this->groupBox9->SuspendLayout();
      this->groupBox10->SuspendLayout();
      (safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
      this->panel3->SuspendLayout();
      this->FreespacegroupBox->SuspendLayout();
      this->SampleTakengroupBox->SuspendLayout();
      this->TappinggroupBox->SuspendLayout();
      this->DeslagginggroupBox->SuspendLayout();
      this->GasStatusgroupBox->SuspendLayout();
      (safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown3))->BeginInit();
      (safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown2))->BeginInit();
      (safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
      this->WaterGasgroupBox->SuspendLayout();
      this->GasModelgroupBox->SuspendLayout();
      this->panel4->SuspendLayout();
      this->BlowStartgroupBox->SuspendLayout();
      this->HMCgroupBox->SuspendLayout();
      this->ReadyforBlowgroupBox->SuspendLayout();
      this->HeatgroupBox->SuspendLayout();
      this->TlgHeadStatusgroupBox->SuspendLayout();
      this->ConposgroupBox->SuspendLayout();
      this->lanceblowstatusgroupBox->SuspendLayout();
      this->LanceStatusgroupBox->SuspendLayout();
      this->panel5->SuspendLayout();
      (safe_cast<System::ComponentModel::ISupportInitialize^  >(this->timer1))->BeginInit();
      this->SuspendLayout();
      // 
      // panel1
      // 
      this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panel1->Controls->Add(this->groupBox3);
      this->panel1->Dock = System::Windows::Forms::DockStyle::Left;
      this->panel1->Location = System::Drawing::Point(0, 0);
      this->panel1->Name = "panel1";
      this->panel1->Size = System::Drawing::Size(216, 746);
      this->panel1->TabIndex = 0;
      // 
      // groupBox3
      // 
      this->groupBox3->Controls->Add(this->groupBox1);
      this->groupBox3->Controls->Add(this->sendenbutton);
      this->groupBox3->Controls->Add(this->buttonMakeTlg);
      this->groupBox3->Controls->Add(this->label52);
      this->groupBox3->Controls->Add(this->label51);
      this->groupBox3->Controls->Add(this->textBoxmessage);
      this->groupBox3->Controls->Add(this->Receivenbutton);
      this->groupBox3->Controls->Add(this->Sendbutton);
      this->groupBox3->Dock = System::Windows::Forms::DockStyle::Fill;
      this->groupBox3->Location = System::Drawing::Point(0, 0);
      this->groupBox3->Name = "groupBox3";
      this->groupBox3->Size = System::Drawing::Size(212, 742);
      this->groupBox3->TabIndex = 6;
      this->groupBox3->TabStop = false;
      this->groupBox3->Text = "groupBox3";
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->label18);
      this->groupBox1->Controls->Add(this->label17);
      this->groupBox1->Controls->Add(this->label16);
      this->groupBox1->Controls->Add(this->label15);
      this->groupBox1->Controls->Add(this->label14);
      this->groupBox1->Controls->Add(this->label13);
      this->groupBox1->Controls->Add(this->buttonSE);
      this->groupBox1->Controls->Add(this->buttonDE);
      this->groupBox1->Controls->Add(this->buttonDS);
      this->groupBox1->Controls->Add(this->buttonTE);
      this->groupBox1->Controls->Add(this->buttonTS);
      this->groupBox1->Controls->Add(this->led18);
      this->groupBox1->Controls->Add(this->led17);
      this->groupBox1->Controls->Add(this->led16);
      this->groupBox1->Controls->Add(this->led15);
      this->groupBox1->Controls->Add(this->led14);
      this->groupBox1->Controls->Add(this->buttonLU);
      this->groupBox1->Controls->Add(this->led13);
      this->groupBox1->Controls->Add(this->label12);
      this->groupBox1->Controls->Add(this->label11);
      this->groupBox1->Controls->Add(this->label10);
      this->groupBox1->Controls->Add(this->label9);
      this->groupBox1->Controls->Add(this->label8);
      this->groupBox1->Controls->Add(this->label7);
      this->groupBox1->Controls->Add(this->label6);
      this->groupBox1->Controls->Add(this->label5);
      this->groupBox1->Controls->Add(this->label4);
      this->groupBox1->Controls->Add(this->label3);
      this->groupBox1->Controls->Add(this->label2);
      this->groupBox1->Controls->Add(this->label1);
      this->groupBox1->Controls->Add(this->buttonRE);
      this->groupBox1->Controls->Add(this->buttonRS);
      this->groupBox1->Controls->Add(this->buttonTM);
      this->groupBox1->Controls->Add(this->buttonBE);
      this->groupBox1->Controls->Add(this->buttonBS);
      this->groupBox1->Controls->Add(this->buttonLD);
      this->groupBox1->Controls->Add(this->buttonHS);
      this->groupBox1->Controls->Add(this->button5);
      this->groupBox1->Controls->Add(this->buttonSS);
      this->groupBox1->Controls->Add(this->buttonCIP);
      this->groupBox1->Controls->Add(this->buttonHA);
      this->groupBox1->Controls->Add(this->led12);
      this->groupBox1->Controls->Add(this->led11);
      this->groupBox1->Controls->Add(this->led10);
      this->groupBox1->Controls->Add(this->led9);
      this->groupBox1->Controls->Add(this->led8);
      this->groupBox1->Controls->Add(this->led7);
      this->groupBox1->Controls->Add(this->led6);
      this->groupBox1->Controls->Add(this->led5);
      this->groupBox1->Controls->Add(this->led4);
      this->groupBox1->Controls->Add(this->led3);
      this->groupBox1->Controls->Add(this->led2);
      this->groupBox1->Controls->Add(this->led1);
      this->groupBox1->Controls->Add(this->buttonSC);
      this->groupBox1->Location = System::Drawing::Point(8, 16);
      this->groupBox1->Name = "groupBox1";
      this->groupBox1->Size = System::Drawing::Size(200, 320);
      this->groupBox1->TabIndex = 18;
      this->groupBox1->TabStop = false;
      this->groupBox1->Text = "Event";
      // 
      // label18
      // 
      this->label18->Location = System::Drawing::Point(40, 296);
      this->label18->Name = "label18";
      this->label18->Size = System::Drawing::Size(150, 16);
      this->label18->TabIndex = 60;
      this->label18->Text = "Stirring End";
      // 
      // label17
      // 
      this->label17->Location = System::Drawing::Point(40, 280);
      this->label17->Name = "label17";
      this->label17->Size = System::Drawing::Size(150, 16);
      this->label17->TabIndex = 59;
      this->label17->Text = "Delslag End";
      // 
      // label16
      // 
      this->label16->Location = System::Drawing::Point(40, 264);
      this->label16->Name = "label16";
      this->label16->Size = System::Drawing::Size(150, 16);
      this->label16->TabIndex = 58;
      this->label16->Text = "Delslag Start";
      // 
      // label15
      // 
      this->label15->Location = System::Drawing::Point(40, 248);
      this->label15->Name = "label15";
      this->label15->Size = System::Drawing::Size(150, 16);
      this->label15->TabIndex = 57;
      this->label15->Text = "Tapping End";
      // 
      // label14
      // 
      this->label14->Location = System::Drawing::Point(40, 232);
      this->label14->Name = "label14";
      this->label14->Size = System::Drawing::Size(150, 16);
      this->label14->TabIndex = 56;
      this->label14->Text = "Tapping Start";
      // 
      // label13
      // 
      this->label13->Location = System::Drawing::Point(40, 216);
      this->label13->Name = "label13";
      this->label13->Size = System::Drawing::Size(150, 16);
      this->label13->TabIndex = 55;
      this->label13->Text = "Lance Up";
      // 
      // buttonSE
      // 
      this->buttonSE->Location = System::Drawing::Point(24, 296);
      this->buttonSE->Name = "buttonSE";
      this->buttonSE->Size = System::Drawing::Size(8, 8);
      this->buttonSE->TabIndex = 51;
      this->buttonSE->Text = "button18";
      this->buttonSE->Click += gcnew System::EventHandler(this, &CBofMainForm::buttonSE_Click);
      // 
      // buttonDE
      // 
      this->buttonDE->Location = System::Drawing::Point(24, 280);
      this->buttonDE->Name = "buttonDE";
      this->buttonDE->Size = System::Drawing::Size(8, 8);
      this->buttonDE->TabIndex = 50;
      this->buttonDE->Text = "button17";
      this->buttonDE->Click += gcnew System::EventHandler(this, &CBofMainForm::buttonDE_Click);
      // 
      // buttonDS
      // 
      this->buttonDS->Location = System::Drawing::Point(24, 264);
      this->buttonDS->Name = "buttonD";
      this->buttonDS->Size = System::Drawing::Size(8, 8);
      this->buttonDS->TabIndex = 49;
      this->buttonDS->Text = "button16";
      this->buttonDS->Click += gcnew System::EventHandler(this, &CBofMainForm::buttonDS_Click);
      // 
      // buttonTE
      // 
      this->buttonTE->Location = System::Drawing::Point(24, 248);
      this->buttonTE->Name = "buttonTE";
      this->buttonTE->Size = System::Drawing::Size(8, 8);
      this->buttonTE->TabIndex = 48;
      this->buttonTE->Text = "button15";
      this->buttonTE->Click += gcnew System::EventHandler(this, &CBofMainForm::buttonTE_Click);
      // 
      // buttonTS
      // 
      this->buttonTS->Location = System::Drawing::Point(24, 232);
      this->buttonTS->Name = "buttonT";
      this->buttonTS->Size = System::Drawing::Size(8, 8);
      this->buttonTS->TabIndex = 47;
      this->buttonTS->Text = "button14";
      this->buttonTS->Click += gcnew System::EventHandler(this, &CBofMainForm::buttonTS_Click);
      // 
      // led18
      // 
      this->led18->Location = System::Drawing::Point(8, 296);
      this->led18->Name = "led18";
      this->led18->Size = System::Drawing::Size(10, 10);
      this->led18->Status = false;
      this->led18->TabIndex = 43;
      // 
      // led17
      // 
      this->led17->Location = System::Drawing::Point(8, 280);
      this->led17->Name = "led17";
      this->led17->Size = System::Drawing::Size(10, 10);
      this->led17->Status = false;
      this->led17->TabIndex = 42;
      // 
      // led16
      // 
      this->led16->Location = System::Drawing::Point(8, 264);
      this->led16->Name = "led16";
      this->led16->Size = System::Drawing::Size(10, 10);
      this->led16->Status = false;
      this->led16->TabIndex = 41;
      // 
      // led15
      // 
      this->led15->Location = System::Drawing::Point(8, 248);
      this->led15->Name = "led15";
      this->led15->Size = System::Drawing::Size(10, 10);
      this->led15->Status = false;
      this->led15->TabIndex = 40;
      // 
      // led14
      // 
      this->led14->Location = System::Drawing::Point(8, 232);
      this->led14->Name = "led14";
      this->led14->Size = System::Drawing::Size(10, 10);
      this->led14->Status = false;
      this->led14->TabIndex = 39;
      // 
      // buttonLU
      // 
      this->buttonLU->Location = System::Drawing::Point(24, 216);
      this->buttonLU->Name = "buttonLU";
      this->buttonLU->Size = System::Drawing::Size(8, 8);
      this->buttonLU->TabIndex = 38;
      this->buttonLU->Text = "button13";
      this->buttonLU->Click += gcnew System::EventHandler(this, &CBofMainForm::buttonLU_Click);
      // 
      // led13
      // 
      this->led13->Location = System::Drawing::Point(8, 216);
      this->led13->Name = "led13";
      this->led13->Size = System::Drawing::Size(10, 10);
      this->led13->Status = false;
      this->led13->TabIndex = 37;
      // 
      // label12
      // 
      this->label12->Location = System::Drawing::Point(40, 200);
      this->label12->Name = "label12";
      this->label12->Size = System::Drawing::Size(150, 16);
      this->label12->TabIndex = 36;
      this->label12->Text = "Reblow End";
      // 
      // label11
      // 
      this->label11->Location = System::Drawing::Point(40, 184);
      this->label11->Name = "label11";
      this->label11->Size = System::Drawing::Size(150, 16);
      this->label11->TabIndex = 35;
      this->label11->Text = "Reblow Start";
      // 
      // label10
      // 
      this->label10->Location = System::Drawing::Point(40, 168);
      this->label10->Name = "label10";
      this->label10->Size = System::Drawing::Size(150, 16);
      this->label10->TabIndex = 34;
      this->label10->Text = "Temperatur Measurement";
      // 
      // label9
      // 
      this->label9->Location = System::Drawing::Point(40, 152);
      this->label9->Name = "label9";
      this->label9->Size = System::Drawing::Size(150, 16);
      this->label9->TabIndex = 33;
      this->label9->Text = "Blow End";
      // 
      // label8
      // 
      this->label8->Location = System::Drawing::Point(40, 136);
      this->label8->Name = "label8";
      this->label8->Size = System::Drawing::Size(150, 16);
      this->label8->TabIndex = 32;
      this->label8->Text = "Blow Start";
      // 
      // label7
      // 
      this->label7->Location = System::Drawing::Point(40, 120);
      this->label7->Name = "label7";
      this->label7->Size = System::Drawing::Size(150, 16);
      this->label7->TabIndex = 31;
      this->label7->Text = "Lance Down";
      // 
      // label6
      // 
      this->label6->Location = System::Drawing::Point(40, 104);
      this->label6->Name = "label6";
      this->label6->Size = System::Drawing::Size(150, 16);
      this->label6->TabIndex = 30;
      this->label6->Text = "Heat Start";
      // 
      // label5
      // 
      this->label5->Location = System::Drawing::Point(40, 88);
      this->label5->Name = "label5";
      this->label5->Size = System::Drawing::Size(150, 16);
      this->label5->TabIndex = 29;
      this->label5->Text = "Hotmetal  Charging";
      // 
      // label4
      // 
      this->label4->Location = System::Drawing::Point(40, 72);
      this->label4->Name = "label4";
      this->label4->Size = System::Drawing::Size(150, 16);
      this->label4->TabIndex = 28;
      this->label4->Text = "Stirring Start";
      // 
      // label3
      // 
      this->label3->Location = System::Drawing::Point(40, 56);
      this->label3->Name = "label3";
      this->label3->Size = System::Drawing::Size(150, 18);
      this->label3->TabIndex = 27;
      this->label3->Text = "Scrap Carging";
      // 
      // label2
      // 
      this->label2->Location = System::Drawing::Point(40, 40);
      this->label2->Name = "label2";
      this->label2->Size = System::Drawing::Size(150, 16);
      this->label2->TabIndex = 26;
      this->label2->Text = "Converter in charging Pos.";
      // 
      // label1
      // 
      this->label1->Location = System::Drawing::Point(40, 24);
      this->label1->Name = "label1";
      this->label1->Size = System::Drawing::Size(150, 16);
      this->label1->TabIndex = 25;
      this->label1->Text = "Heat Announce ";
      // 
      // buttonRE
      // 
      this->buttonRE->Location = System::Drawing::Point(24, 200);
      this->buttonRE->Name = "buttonRE";
      this->buttonRE->Size = System::Drawing::Size(8, 8);
      this->buttonRE->TabIndex = 24;
      this->buttonRE->Text = "button12";
      this->buttonRE->Click += gcnew System::EventHandler(this, &CBofMainForm::buttonRE_Click);
      // 
      // buttonRS
      // 
      this->buttonRS->Location = System::Drawing::Point(24, 184);
      this->buttonRS->Name = "buttonR";
      this->buttonRS->Size = System::Drawing::Size(8, 8);
      this->buttonRS->TabIndex = 23;
      this->buttonRS->Text = "button11";
      this->buttonRS->Click += gcnew System::EventHandler(this, &CBofMainForm::buttonRS_Click);
      // 
      // buttonTM
      // 
      this->buttonTM->Location = System::Drawing::Point(24, 168);
      this->buttonTM->Name = "buttonTM";
      this->buttonTM->Size = System::Drawing::Size(8, 8);
      this->buttonTM->TabIndex = 22;
      this->buttonTM->Text = "button10";
      this->buttonTM->Click += gcnew System::EventHandler(this, &CBofMainForm::buttonTM_Click);
      // 
      // buttonBE
      // 
      this->buttonBE->Location = System::Drawing::Point(24, 152);
      this->buttonBE->Name = "buttonBE";
      this->buttonBE->Size = System::Drawing::Size(8, 8);
      this->buttonBE->TabIndex = 21;
      this->buttonBE->Text = "button9";
      this->buttonBE->Click += gcnew System::EventHandler(this, &CBofMainForm::buttonBE_Click);
      // 
      // buttonBS
      // 
      this->buttonBS->Location = System::Drawing::Point(24, 136);
      this->buttonBS->Name = "buttonB";
      this->buttonBS->Size = System::Drawing::Size(8, 8);
      this->buttonBS->TabIndex = 20;
      this->buttonBS->Text = "button8";
      this->buttonBS->Click += gcnew System::EventHandler(this, &CBofMainForm::buttonBS_Click);
      // 
      // buttonLD
      // 
      this->buttonLD->Location = System::Drawing::Point(24, 120);
      this->buttonLD->Name = "buttonLD";
      this->buttonLD->Size = System::Drawing::Size(8, 8);
      this->buttonLD->TabIndex = 19;
      this->buttonLD->Text = "button7";
      this->buttonLD->Click += gcnew System::EventHandler(this, &CBofMainForm::buttonLD_Click);
      // 
      // buttonHS
      // 
      this->buttonHS->Location = System::Drawing::Point(24, 104);
      this->buttonHS->Name = "buttonH";
      this->buttonHS->Size = System::Drawing::Size(8, 8);
      this->buttonHS->TabIndex = 18;
      this->buttonHS->Text = "button6";
      // 
      // button5
      // 
      this->button5->Location = System::Drawing::Point(24, 88);
      this->button5->Name = "button5";
      this->button5->Size = System::Drawing::Size(13, 10);
      this->button5->TabIndex = 17;
      this->button5->Text = "button5";
      this->button5->Click += gcnew System::EventHandler(this, &CBofMainForm::button5_Click);
      // 
      // buttonSS
      // 
      this->buttonSS->Location = System::Drawing::Point(24, 72);
      this->buttonSS->Name = "buttonS";
      this->buttonSS->Size = System::Drawing::Size(8, 8);
      this->buttonSS->TabIndex = 16;
      this->buttonSS->Text = "button4";
      this->buttonSS->Click += gcnew System::EventHandler(this, &CBofMainForm::buttonSS_Click);
      // 
      // buttonCIP
      // 
      this->buttonCIP->Location = System::Drawing::Point(24, 40);
      this->buttonCIP->Name = "buttonCIP";
      this->buttonCIP->Size = System::Drawing::Size(8, 8);
      this->buttonCIP->TabIndex = 14;
      this->buttonCIP->Text = "button2";
      this->buttonCIP->Click += gcnew System::EventHandler(this, &CBofMainForm::buttonCIP_Click);
      // 
      // buttonHA
      // 
      this->buttonHA->Location = System::Drawing::Point(24, 24);
      this->buttonHA->Name = "buttonHA";
      this->buttonHA->Size = System::Drawing::Size(8, 8);
      this->buttonHA->TabIndex = 13;
      this->buttonHA->Text = "button1";
      this->buttonHA->Click += gcnew System::EventHandler(this, &CBofMainForm::buttonHA_Click);
      // 
      // led12
      // 
      this->led12->Location = System::Drawing::Point(8, 200);
      this->led12->Name = "led12";
      this->led12->Size = System::Drawing::Size(10, 10);
      this->led12->Status = false;
      this->led12->TabIndex = 12;
      // 
      // led11
      // 
      this->led11->Location = System::Drawing::Point(8, 184);
      this->led11->Name = "led11";
      this->led11->Size = System::Drawing::Size(10, 10);
      this->led11->Status = false;
      this->led11->TabIndex = 11;
      // 
      // led10
      // 
      this->led10->Location = System::Drawing::Point(8, 168);
      this->led10->Name = "led10";
      this->led10->Size = System::Drawing::Size(10, 10);
      this->led10->Status = false;
      this->led10->TabIndex = 10;
      // 
      // led9
      // 
      this->led9->Location = System::Drawing::Point(8, 152);
      this->led9->Name = "led9";
      this->led9->Size = System::Drawing::Size(10, 10);
      this->led9->Status = false;
      this->led9->TabIndex = 9;
      // 
      // led8
      // 
      this->led8->Location = System::Drawing::Point(8, 136);
      this->led8->Name = "led8";
      this->led8->Size = System::Drawing::Size(10, 10);
      this->led8->Status = false;
      this->led8->TabIndex = 8;
      // 
      // led7
      // 
      this->led7->Location = System::Drawing::Point(8, 120);
      this->led7->Name = "led7";
      this->led7->Size = System::Drawing::Size(10, 10);
      this->led7->Status = false;
      this->led7->TabIndex = 7;
      // 
      // led6
      // 
      this->led6->Location = System::Drawing::Point(8, 104);
      this->led6->Name = "led6";
      this->led6->Size = System::Drawing::Size(10, 10);
      this->led6->Status = false;
      this->led6->TabIndex = 6;
      // 
      // led5
      // 
      this->led5->Location = System::Drawing::Point(8, 88);
      this->led5->Name = "led5";
      this->led5->Size = System::Drawing::Size(10, 10);
      this->led5->Status = false;
      this->led5->TabIndex = 5;
      // 
      // led4
      // 
      this->led4->Location = System::Drawing::Point(8, 72);
      this->led4->Name = "led4";
      this->led4->Size = System::Drawing::Size(10, 10);
      this->led4->Status = false;
      this->led4->TabIndex = 4;
      // 
      // led3
      // 
      this->led3->Location = System::Drawing::Point(8, 56);
      this->led3->Name = "led3";
      this->led3->Size = System::Drawing::Size(10, 10);
      this->led3->Status = false;
      this->led3->TabIndex = 3;
      // 
      // led2
      // 
      this->led2->Location = System::Drawing::Point(8, 40);
      this->led2->Name = "led2";
      this->led2->Size = System::Drawing::Size(10, 10);
      this->led2->Status = false;
      this->led2->TabIndex = 2;
      // 
      // led1
      // 
      this->led1->Location = System::Drawing::Point(8, 24);
      this->led1->Name = "led1";
      this->led1->Size = System::Drawing::Size(10, 10);
      this->led1->Status = false;
      this->led1->TabIndex = 1;
      // 
      // buttonSC
      // 
      this->buttonSC->Location = System::Drawing::Point(24, 56);
      this->buttonSC->Name = "buttonSC";
      this->buttonSC->Size = System::Drawing::Size(8, 8);
      this->buttonSC->TabIndex = 15;
      this->buttonSC->Text = "button3";
      this->buttonSC->Click += gcnew System::EventHandler(this, &CBofMainForm::buttonSC_Click);
      // 
      // sendenbutton
      // 
      this->sendenbutton->Location = System::Drawing::Point(96, 472);
      this->sendenbutton->Name = "sendenbutton";
      this->sendenbutton->Size = System::Drawing::Size(75, 23);
      this->sendenbutton->TabIndex = 17;
      this->sendenbutton->Text = "Senden";
      this->sendenbutton->Click += gcnew System::EventHandler(this, &CBofMainForm::sendeTlgnbutton_Click);
      // 
      // buttonMakeTlg
      // 
      this->buttonMakeTlg->Location = System::Drawing::Point(8, 472);
      this->buttonMakeTlg->Name = "buttonMakeTlg";
      this->buttonMakeTlg->Size = System::Drawing::Size(75, 23);
      this->buttonMakeTlg->TabIndex = 16;
      this->buttonMakeTlg->Text = "Make Tlg";
      this->buttonMakeTlg->Click += gcnew System::EventHandler(this, &CBofMainForm::buttonMakeTlg_Click);
      // 
      // label52
      // 
      this->label52->Location = System::Drawing::Point(16, 424);
      this->label52->Name = "label52";
      this->label52->Size = System::Drawing::Size(192, 16);
      this->label52->TabIndex = 15;
      this->label52->Text = "Telegramm ";
      this->label52->TextAlign = System::Drawing::ContentAlignment::TopCenter;
      // 
      // label51
      // 
      this->label51->Location = System::Drawing::Point(8, 440);
      this->label51->Name = "label51";
      this->label51->Size = System::Drawing::Size(40, 16);
      this->label51->TabIndex = 14;
      this->label51->Text = "Tlg:";
      this->label51->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // textBoxmessage
      // 
      this->textBoxmessage->Location = System::Drawing::Point(48, 440);
      this->textBoxmessage->Name = "textBoxmessage";
      this->textBoxmessage->Size = System::Drawing::Size(160, 20);
      this->textBoxmessage->TabIndex = 13;
      // 
      // Receivenbutton
      // 
      this->Receivenbutton->Location = System::Drawing::Point(112, 344);
      this->Receivenbutton->Name = "Receivenbutton";
      this->Receivenbutton->Size = System::Drawing::Size(96, 72);
      this->Receivenbutton->TabIndex = 4;
      this->Receivenbutton->Text = "Telegramm Receiven";
      this->Receivenbutton->Click += gcnew System::EventHandler(this, &CBofMainForm::Receivenbutton_Click);
      // 
      // Sendbutton
      // 
      this->Sendbutton->Location = System::Drawing::Point(8, 344);
      this->Sendbutton->Name = "Sendbutton";
      this->Sendbutton->Size = System::Drawing::Size(96, 72);
      this->Sendbutton->TabIndex = 3;
      this->Sendbutton->Text = "Telegramm Senden";
      this->Sendbutton->Click += gcnew System::EventHandler(this, &CBofMainForm::Sendbutton_Click);
      // 
      // panel2
      // 
      this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panel2->Controls->Add(this->panel6);
      this->panel2->Controls->Add(this->labellancehigh);
      this->panel2->Controls->Add(this->pictureBox1);
      this->panel2->Controls->Add(this->textBoxlancehigh);
      this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panel2->Location = System::Drawing::Point(216, 0);
      this->panel2->Name = "panel2";
      this->panel2->Size = System::Drawing::Size(792, 746);
      this->panel2->TabIndex = 1;
      // 
      // panel6
      // 
      this->panel6->BackColor = System::Drawing::SystemColors::ControlLight;
      this->panel6->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panel6->Controls->Add(this->label83);
      this->panel6->Controls->Add(this->button1);
      this->panel6->Controls->Add(this->groupBox2);
      this->panel6->Controls->Add(this->groupBox4);
      this->panel6->Controls->Add(this->groupBox5);
      this->panel6->Controls->Add(this->groupBox6);
      this->panel6->Controls->Add(this->groupBox7);
      this->panel6->Controls->Add(this->groupBox8);
      this->panel6->Controls->Add(this->groupBox9);
      this->panel6->Controls->Add(this->groupBox10);
      this->panel6->Dock = System::Windows::Forms::DockStyle::Left;
      this->panel6->ForeColor = System::Drawing::SystemColors::WindowText;
      this->panel6->Location = System::Drawing::Point(0, 0);
      this->panel6->Name = "panel6";
      this->panel6->Size = System::Drawing::Size(320, 742);
      this->panel6->TabIndex = 10;
      // 
      // label83
      // 
      this->label83->ForeColor = System::Drawing::SystemColors::Desktop;
      this->label83->Location = System::Drawing::Point(40, 8);
      this->label83->Name = "label83";
      this->label83->Size = System::Drawing::Size(128, 16);
      this->label83->TabIndex = 17;
      this->label83->Text = "Telegramm Head Statu";
      // 
      // button1
      // 
      this->button1->BackColor = System::Drawing::SystemColors::Desktop;
      this->button1->Location = System::Drawing::Point(8, 8);
      this->button1->Name = "button1";
      this->button1->Size = System::Drawing::Size(24, 16);
      this->button1->TabIndex = 16;
      this->button1->UseVisualStyleBackColor = false;
      // 
      // groupBox2
      // 
      this->groupBox2->Controls->Add(this->label84);
      this->groupBox2->Controls->Add(this->textBox16);
      this->groupBox2->Controls->Add(this->textBox17);
      this->groupBox2->Controls->Add(this->label85);
      this->groupBox2->Controls->Add(this->label86);
      this->groupBox2->Controls->Add(this->textBox18);
      this->groupBox2->Location = System::Drawing::Point(176, 296);
      this->groupBox2->Name = "groupBox2";
      this->groupBox2->Size = System::Drawing::Size(128, 128);
      this->groupBox2->TabIndex = 15;
      this->groupBox2->TabStop = false;
      this->groupBox2->Text = "BlowStart";
      // 
      // label84
      // 
      this->label84->Location = System::Drawing::Point(8, 88);
      this->label84->Name = "label84";
      this->label84->Size = System::Drawing::Size(64, 32);
      this->label84->TabIndex = 16;
      this->label84->Text = "AmountO2Tot";
      // 
      // textBox16
      // 
      this->textBox16->Location = System::Drawing::Point(72, 88);
      this->textBox16->Name = "textBox16";
      this->textBox16->Size = System::Drawing::Size(40, 20);
      this->textBox16->TabIndex = 17;
      // 
      // textBox17
      // 
      this->textBox17->Location = System::Drawing::Point(72, 24);
      this->textBox17->Name = "textBox17";
      this->textBox17->Size = System::Drawing::Size(40, 20);
      this->textBox17->TabIndex = 14;
      // 
      // label85
      // 
      this->label85->Location = System::Drawing::Point(8, 56);
      this->label85->Name = "label85";
      this->label85->Size = System::Drawing::Size(64, 24);
      this->label85->TabIndex = 13;
      this->label85->Text = "AmountO2";
      // 
      // label86
      // 
      this->label86->Location = System::Drawing::Point(8, 24);
      this->label86->Name = "label86";
      this->label86->Size = System::Drawing::Size(56, 24);
      this->label86->TabIndex = 12;
      this->label86->Text = "AmountO2Met";
      // 
      // textBox18
      // 
      this->textBox18->Location = System::Drawing::Point(72, 56);
      this->textBox18->Name = "textBox18";
      this->textBox18->Size = System::Drawing::Size(40, 20);
      this->textBox18->TabIndex = 15;
      // 
      // groupBox4
      // 
      this->groupBox4->Controls->Add(this->textBox19);
      this->groupBox4->Controls->Add(this->textBox20);
      this->groupBox4->Controls->Add(this->textBox21);
      this->groupBox4->Controls->Add(this->textBox22);
      this->groupBox4->Controls->Add(this->label87);
      this->groupBox4->Controls->Add(this->label88);
      this->groupBox4->Controls->Add(this->label89);
      this->groupBox4->Controls->Add(this->label90);
      this->groupBox4->Location = System::Drawing::Point(0, 184);
      this->groupBox4->Name = "groupBox4";
      this->groupBox4->Size = System::Drawing::Size(168, 120);
      this->groupBox4->TabIndex = 13;
      this->groupBox4->TabStop = false;
      this->groupBox4->Text = "Hot metal charging";
      // 
      // textBox19
      // 
      this->textBox19->Location = System::Drawing::Point(72, 88);
      this->textBox19->Name = "textBox19";
      this->textBox19->Size = System::Drawing::Size(72, 20);
      this->textBox19->TabIndex = 23;
      // 
      // textBox20
      // 
      this->textBox20->Location = System::Drawing::Point(72, 64);
      this->textBox20->Name = "textBox20";
      this->textBox20->Size = System::Drawing::Size(72, 20);
      this->textBox20->TabIndex = 22;
      // 
      // textBox21
      // 
      this->textBox21->Location = System::Drawing::Point(72, 40);
      this->textBox21->Name = "textBox21";
      this->textBox21->Size = System::Drawing::Size(72, 20);
      this->textBox21->TabIndex = 21;
      // 
      // textBox22
      // 
      this->textBox22->Location = System::Drawing::Point(72, 16);
      this->textBox22->Name = "textBox22";
      this->textBox22->Size = System::Drawing::Size(72, 20);
      this->textBox22->TabIndex = 20;
      // 
      // label87
      // 
      this->label87->Location = System::Drawing::Point(16, 96);
      this->label87->Name = "label87";
      this->label87->Size = System::Drawing::Size(56, 16);
      this->label87->TabIndex = 19;
      this->label87->Text = "HMLocation";
      // 
      // label88
      // 
      this->label88->Location = System::Drawing::Point(16, 72);
      this->label88->Name = "label88";
      this->label88->Size = System::Drawing::Size(56, 16);
      this->label88->TabIndex = 18;
      this->label88->Text = "MatWgt";
      // 
      // label89
      // 
      this->label89->Location = System::Drawing::Point(16, 48);
      this->label89->Name = "label89";
      this->label89->Size = System::Drawing::Size(56, 16);
      this->label89->TabIndex = 17;
      this->label89->Text = "WgtStat";
      // 
      // label90
      // 
      this->label90->Location = System::Drawing::Point(16, 24);
      this->label90->Name = "label90";
      this->label90->Size = System::Drawing::Size(56, 16);
      this->label90->TabIndex = 16;
      this->label90->Text = "LDI No.";
      // 
      // groupBox5
      // 
      this->groupBox5->Controls->Add(this->label91);
      this->groupBox5->Controls->Add(this->label92);
      this->groupBox5->Controls->Add(this->label93);
      this->groupBox5->Controls->Add(this->led19);
      this->groupBox5->Controls->Add(this->led20);
      this->groupBox5->Controls->Add(this->led21);
      this->groupBox5->Location = System::Drawing::Point(0, 104);
      this->groupBox5->Name = "groupBox5";
      this->groupBox5->Size = System::Drawing::Size(168, 80);
      this->groupBox5->TabIndex = 9;
      this->groupBox5->TabStop = false;
      this->groupBox5->Text = "Top Lance Ready for Blow";
      // 
      // label91
      // 
      this->label91->Location = System::Drawing::Point(40, 56);
      this->label91->Name = "label91";
      this->label91->Size = System::Drawing::Size(100, 16);
      this->label91->TabIndex = 60;
      this->label91->Text = "Cool Avail";
      // 
      // label92
      // 
      this->label92->Location = System::Drawing::Point(40, 40);
      this->label92->Name = "label92";
      this->label92->Size = System::Drawing::Size(100, 16);
      this->label92->TabIndex = 59;
      this->label92->Text = "Standby Avail";
      // 
      // label93
      // 
      this->label93->Location = System::Drawing::Point(40, 24);
      this->label93->Name = "label93";
      this->label93->Size = System::Drawing::Size(100, 16);
      this->label93->TabIndex = 58;
      this->label93->Text = "O2 Avail";
      // 
      // led19
      // 
      this->led19->Location = System::Drawing::Point(24, 56);
      this->led19->Name = "led19";
      this->led19->Size = System::Drawing::Size(10, 10);
      this->led19->Status = false;
      this->led19->TabIndex = 49;
      // 
      // led20
      // 
      this->led20->Location = System::Drawing::Point(24, 40);
      this->led20->Name = "led20";
      this->led20->Size = System::Drawing::Size(10, 10);
      this->led20->Status = false;
      this->led20->TabIndex = 48;
      // 
      // led21
      // 
      this->led21->Location = System::Drawing::Point(24, 24);
      this->led21->Name = "led21";
      this->led21->Size = System::Drawing::Size(10, 10);
      this->led21->Status = false;
      this->led21->TabIndex = 47;
      // 
      // groupBox6
      // 
      this->groupBox6->Controls->Add(this->textBox23);
      this->groupBox6->Controls->Add(this->textBox24);
      this->groupBox6->Controls->Add(this->label94);
      this->groupBox6->Controls->Add(this->label95);
      this->groupBox6->Controls->Add(this->textBox25);
      this->groupBox6->Controls->Add(this->textBox28);
      this->groupBox6->Controls->Add(this->label96);
      this->groupBox6->Controls->Add(this->label97);
      this->groupBox6->Location = System::Drawing::Point(0, 32);
      this->groupBox6->Name = "groupBox6";
      this->groupBox6->Size = System::Drawing::Size(304, 72);
      this->groupBox6->TabIndex = 7;
      this->groupBox6->TabStop = false;
      this->groupBox6->Text = "Heat No/Retreat ID";
      // 
      // textBox23
      // 
      this->textBox23->Location = System::Drawing::Point(208, 16);
      this->textBox23->Name = "textBox23";
      this->textBox23->Size = System::Drawing::Size(72, 20);
      this->textBox23->TabIndex = 14;
      // 
      // textBox24
      // 
      this->textBox24->Location = System::Drawing::Point(72, 16);
      this->textBox24->Name = "textBox24";
      this->textBox24->Size = System::Drawing::Size(72, 20);
      this->textBox24->TabIndex = 13;
      // 
      // label94
      // 
      this->label94->Location = System::Drawing::Point(152, 16);
      this->label94->Name = "label94";
      this->label94->Size = System::Drawing::Size(56, 16);
      this->label94->TabIndex = 12;
      this->label94->Text = "Time";
      // 
      // label95
      // 
      this->label95->Location = System::Drawing::Point(8, 16);
      this->label95->Name = "label95";
      this->label95->Size = System::Drawing::Size(56, 16);
      this->label95->TabIndex = 11;
      this->label95->Text = "Date";
      // 
      // textBox25
      // 
      this->textBox25->Location = System::Drawing::Point(208, 48);
      this->textBox25->Name = "textBox25";
      this->textBox25->Size = System::Drawing::Size(72, 20);
      this->textBox25->TabIndex = 10;
      // 
      // textBox28
      // 
      this->textBox28->Location = System::Drawing::Point(72, 48);
      this->textBox28->Name = "textBox28";
      this->textBox28->Size = System::Drawing::Size(72, 20);
      this->textBox28->TabIndex = 9;
      // 
      // label96
      // 
      this->label96->Location = System::Drawing::Point(152, 48);
      this->label96->Name = "label96";
      this->label96->Size = System::Drawing::Size(56, 16);
      this->label96->TabIndex = 2;
      this->label96->Text = "Retreat ID";
      // 
      // label97
      // 
      this->label97->Location = System::Drawing::Point(8, 48);
      this->label97->Name = "label97";
      this->label97->Size = System::Drawing::Size(56, 16);
      this->label97->TabIndex = 1;
      this->label97->Text = "Heat No";
      // 
      // groupBox7
      // 
      this->groupBox7->Controls->Add(this->textBox29);
      this->groupBox7->Controls->Add(this->textBox30);
      this->groupBox7->Controls->Add(this->textBox31);
      this->groupBox7->Controls->Add(this->textBox32);
      this->groupBox7->Controls->Add(this->textBox51);
      this->groupBox7->Controls->Add(this->textBox52);
      this->groupBox7->Controls->Add(this->textBox53);
      this->groupBox7->Controls->Add(this->textBox54);
      this->groupBox7->Controls->Add(this->label98);
      this->groupBox7->Controls->Add(this->label99);
      this->groupBox7->Controls->Add(this->label100);
      this->groupBox7->Controls->Add(this->label101);
      this->groupBox7->Controls->Add(this->label102);
      this->groupBox7->Controls->Add(this->label103);
      this->groupBox7->Controls->Add(this->label104);
      this->groupBox7->Controls->Add(this->label105);
      this->groupBox7->Location = System::Drawing::Point(0, 32);
      this->groupBox7->Name = "groupBox7";
      this->groupBox7->Size = System::Drawing::Size(304, 120);
      this->groupBox7->TabIndex = 6;
      this->groupBox7->TabStop = false;
      this->groupBox7->Text = "Tlg.Head Statu";
      // 
      // textBox29
      // 
      this->textBox29->Location = System::Drawing::Point(208, 88);
      this->textBox29->Name = "textBox29";
      this->textBox29->Size = System::Drawing::Size(72, 20);
      this->textBox29->TabIndex = 15;
      // 
      // textBox30
      // 
      this->textBox30->Location = System::Drawing::Point(208, 64);
      this->textBox30->Name = "textBox30";
      this->textBox30->Size = System::Drawing::Size(72, 20);
      this->textBox30->TabIndex = 14;
      // 
      // textBox31
      // 
      this->textBox31->Location = System::Drawing::Point(208, 40);
      this->textBox31->Name = "textBox31";
      this->textBox31->Size = System::Drawing::Size(72, 20);
      this->textBox31->TabIndex = 13;
      // 
      // textBox32
      // 
      this->textBox32->Location = System::Drawing::Point(208, 16);
      this->textBox32->Name = "textBox32";
      this->textBox32->Size = System::Drawing::Size(72, 20);
      this->textBox32->TabIndex = 12;
      // 
      // textBox51
      // 
      this->textBox51->Location = System::Drawing::Point(72, 88);
      this->textBox51->Name = "textBox51";
      this->textBox51->Size = System::Drawing::Size(72, 20);
      this->textBox51->TabIndex = 11;
      // 
      // textBox52
      // 
      this->textBox52->Location = System::Drawing::Point(72, 64);
      this->textBox52->Name = "textBox52";
      this->textBox52->Size = System::Drawing::Size(72, 20);
      this->textBox52->TabIndex = 10;
      // 
      // textBox53
      // 
      this->textBox53->Location = System::Drawing::Point(72, 40);
      this->textBox53->Name = "textBox53";
      this->textBox53->Size = System::Drawing::Size(72, 20);
      this->textBox53->TabIndex = 9;
      // 
      // textBox54
      // 
      this->textBox54->Location = System::Drawing::Point(72, 16);
      this->textBox54->Name = "textBox54";
      this->textBox54->Size = System::Drawing::Size(72, 20);
      this->textBox54->TabIndex = 8;
      // 
      // label98
      // 
      this->label98->Location = System::Drawing::Point(152, 96);
      this->label98->Name = "label98";
      this->label98->Size = System::Drawing::Size(56, 16);
      this->label98->TabIndex = 7;
      this->label98->Text = "PlantID";
      // 
      // label99
      // 
      this->label99->Location = System::Drawing::Point(152, 72);
      this->label99->Name = "label99";
      this->label99->Size = System::Drawing::Size(56, 16);
      this->label99->TabIndex = 6;
      this->label99->Text = "ProductID";
      // 
      // label100
      // 
      this->label100->Location = System::Drawing::Point(152, 48);
      this->label100->Name = "label100";
      this->label100->Size = System::Drawing::Size(56, 16);
      this->label100->TabIndex = 5;
      this->label100->Text = "Reserve";
      // 
      // label101
      // 
      this->label101->Location = System::Drawing::Point(152, 24);
      this->label101->Name = "label101";
      this->label101->Size = System::Drawing::Size(56, 16);
      this->label101->TabIndex = 4;
      this->label101->Text = "Blen";
      // 
      // label102
      // 
      this->label102->Location = System::Drawing::Point(8, 96);
      this->label102->Name = "label102";
      this->label102->Size = System::Drawing::Size(56, 16);
      this->label102->TabIndex = 3;
      this->label102->Text = "Org";
      // 
      // label103
      // 
      this->label103->Location = System::Drawing::Point(8, 72);
      this->label103->Name = "label103";
      this->label103->Size = System::Drawing::Size(56, 16);
      this->label103->TabIndex = 2;
      this->label103->Text = "CreaTime";
      // 
      // label104
      // 
      this->label104->Location = System::Drawing::Point(8, 48);
      this->label104->Name = "label104";
      this->label104->Size = System::Drawing::Size(56, 16);
      this->label104->TabIndex = 1;
      this->label104->Text = "Crea Date";
      // 
      // label105
      // 
      this->label105->Location = System::Drawing::Point(8, 24);
      this->label105->Name = "label105";
      this->label105->Size = System::Drawing::Size(56, 16);
      this->label105->TabIndex = 0;
      this->label105->Text = "MsgID";
      // 
      // groupBox8
      // 
      this->groupBox8->Controls->Add(this->textBox55);
      this->groupBox8->Controls->Add(this->label106);
      this->groupBox8->Controls->Add(this->label107);
      this->groupBox8->Controls->Add(this->textBox56);
      this->groupBox8->Location = System::Drawing::Point(176, 208);
      this->groupBox8->Name = "groupBox8";
      this->groupBox8->Size = System::Drawing::Size(128, 80);
      this->groupBox8->TabIndex = 8;
      this->groupBox8->TabStop = false;
      this->groupBox8->Text = "Converter pos.";
      // 
      // textBox55
      // 
      this->textBox55->Location = System::Drawing::Point(64, 24);
      this->textBox55->Name = "textBox55";
      this->textBox55->Size = System::Drawing::Size(40, 20);
      this->textBox55->TabIndex = 10;
      // 
      // label106
      // 
      this->label106->Location = System::Drawing::Point(8, 48);
      this->label106->Name = "label106";
      this->label106->Size = System::Drawing::Size(56, 16);
      this->label106->TabIndex = 2;
      this->label106->Text = "AngleConv";
      // 
      // label107
      // 
      this->label107->Location = System::Drawing::Point(8, 24);
      this->label107->Name = "label107";
      this->label107->Size = System::Drawing::Size(56, 16);
      this->label107->TabIndex = 1;
      this->label107->Text = "Conv.Po";
      // 
      // textBox56
      // 
      this->textBox56->Location = System::Drawing::Point(64, 48);
      this->textBox56->Name = "textBox56";
      this->textBox56->Size = System::Drawing::Size(40, 20);
      this->textBox56->TabIndex = 11;
      // 
      // groupBox9
      // 
      this->groupBox9->Controls->Add(this->textBox57);
      this->groupBox9->Controls->Add(this->textBox58);
      this->groupBox9->Controls->Add(this->textBox59);
      this->groupBox9->Controls->Add(this->textBox60);
      this->groupBox9->Controls->Add(this->label108);
      this->groupBox9->Controls->Add(this->label109);
      this->groupBox9->Controls->Add(this->label110);
      this->groupBox9->Controls->Add(this->label111);
      this->groupBox9->Location = System::Drawing::Point(0, 304);
      this->groupBox9->Name = "groupBox9";
      this->groupBox9->Size = System::Drawing::Size(168, 120);
      this->groupBox9->TabIndex = 14;
      this->groupBox9->TabStop = false;
      this->groupBox9->Text = "Lance Blow Statu";
      // 
      // textBox57
      // 
      this->textBox57->Location = System::Drawing::Point(80, 84);
      this->textBox57->Name = "textBox57";
      this->textBox57->Size = System::Drawing::Size(72, 20);
      this->textBox57->TabIndex = 31;
      // 
      // textBox58
      // 
      this->textBox58->Location = System::Drawing::Point(80, 60);
      this->textBox58->Name = "textBox58";
      this->textBox58->Size = System::Drawing::Size(72, 20);
      this->textBox58->TabIndex = 30;
      // 
      // textBox59
      // 
      this->textBox59->Location = System::Drawing::Point(80, 36);
      this->textBox59->Name = "textBox59";
      this->textBox59->Size = System::Drawing::Size(72, 20);
      this->textBox59->TabIndex = 29;
      // 
      // textBox60
      // 
      this->textBox60->Location = System::Drawing::Point(80, 12);
      this->textBox60->Name = "textBox60";
      this->textBox60->Size = System::Drawing::Size(72, 20);
      this->textBox60->TabIndex = 28;
      // 
      // label108
      // 
      this->label108->Location = System::Drawing::Point(4, 92);
      this->label108->Name = "label108";
      this->label108->Size = System::Drawing::Size(76, 16);
      this->label108->TabIndex = 27;
      this->label108->Text = "Blow Typ";
      // 
      // label109
      // 
      this->label109->Location = System::Drawing::Point(4, 68);
      this->label109->Name = "label109";
      this->label109->Size = System::Drawing::Size(76, 20);
      this->label109->TabIndex = 26;
      this->label109->Text = "TopLanceStat";
      // 
      // label110
      // 
      this->label110->Location = System::Drawing::Point(4, 44);
      this->label110->Name = "label110";
      this->label110->Size = System::Drawing::Size(76, 16);
      this->label110->TabIndex = 25;
      this->label110->Text = "Lance Pos.";
      // 
      // label111
      // 
      this->label111->Location = System::Drawing::Point(4, 20);
      this->label111->Name = "label111";
      this->label111->Size = System::Drawing::Size(76, 16);
      this->label111->TabIndex = 24;
      this->label111->Text = "Lance ID";
      // 
      // groupBox10
      // 
      this->groupBox10->Controls->Add(this->textBox61);
      this->groupBox10->Controls->Add(this->label112);
      this->groupBox10->Controls->Add(this->radioButton3);
      this->groupBox10->Controls->Add(this->radioButton4);
      this->groupBox10->Location = System::Drawing::Point(176, 104);
      this->groupBox10->Name = "groupBox10";
      this->groupBox10->Size = System::Drawing::Size(128, 104);
      this->groupBox10->TabIndex = 6;
      this->groupBox10->TabStop = false;
      this->groupBox10->Text = "Lance Statu";
      // 
      // textBox61
      // 
      this->textBox61->Location = System::Drawing::Point(72, 72);
      this->textBox61->Name = "textBox61";
      this->textBox61->Size = System::Drawing::Size(40, 20);
      this->textBox61->TabIndex = 11;
      // 
      // label112
      // 
      this->label112->BackColor = System::Drawing::SystemColors::ControlLight;
      this->label112->ForeColor = System::Drawing::SystemColors::WindowText;
      this->label112->Location = System::Drawing::Point(8, 64);
      this->label112->Name = "label112";
      this->label112->Size = System::Drawing::Size(56, 32);
      this->label112->TabIndex = 6;
      this->label112->Text = "Lance High :";
      // 
      // radioButton3
      // 
      this->radioButton3->BackColor = System::Drawing::SystemColors::ControlLight;
      this->radioButton3->ForeColor = System::Drawing::SystemColors::WindowText;
      this->radioButton3->Location = System::Drawing::Point(24, 16);
      this->radioButton3->Name = "radioButton3";
      this->radioButton3->Size = System::Drawing::Size(64, 16);
      this->radioButton3->TabIndex = 0;
      this->radioButton3->Text = "Top";
      this->radioButton3->UseVisualStyleBackColor = false;
      // 
      // radioButton4
      // 
      this->radioButton4->BackColor = System::Drawing::SystemColors::ControlLight;
      this->radioButton4->ForeColor = System::Drawing::SystemColors::WindowText;
      this->radioButton4->Location = System::Drawing::Point(24, 40);
      this->radioButton4->Name = "radioButton4";
      this->radioButton4->Size = System::Drawing::Size(64, 16);
      this->radioButton4->TabIndex = 1;
      this->radioButton4->Text = "Down";
      this->radioButton4->UseVisualStyleBackColor = false;
      // 
      // labellancehigh
      // 
      this->labellancehigh->BackColor = System::Drawing::SystemColors::Info;
      this->labellancehigh->Location = System::Drawing::Point(336, 108);
      this->labellancehigh->Name = "labellancehigh";
      this->labellancehigh->Size = System::Drawing::Size(68, 16);
      this->labellancehigh->TabIndex = 5;
      this->labellancehigh->Text = "Lance High :";
      // 
      // pictureBox1
      // 
      this->pictureBox1->BackColor = System::Drawing::SystemColors::ControlLightLight;
      this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->pictureBox1->Image = (safe_cast<System::Drawing::Image^  >(resources->GetObject("pictureBox1.Image")));
      this->pictureBox1->Location = System::Drawing::Point(324, 42);
      this->pictureBox1->Name = "pictureBox1";
      this->pictureBox1->Size = System::Drawing::Size(460, 500);
      this->pictureBox1->TabIndex = 4;
      this->pictureBox1->TabStop = false;
      // 
      // textBoxlancehigh
      // 
      this->textBoxlancehigh->BackColor = System::Drawing::SystemColors::InactiveCaptionText;
      this->textBoxlancehigh->ForeColor = System::Drawing::SystemColors::MenuText;
      this->textBoxlancehigh->Location = System::Drawing::Point(428, 108);
      this->textBoxlancehigh->Name = "textBoxlancehigh";
      this->textBoxlancehigh->Size = System::Drawing::Size(40, 20);
      this->textBoxlancehigh->TabIndex = 9;
      // 
      // panel3
      // 
      this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panel3->Controls->Add(this->FreespacegroupBox);
      this->panel3->Controls->Add(this->SampleTakengroupBox);
      this->panel3->Controls->Add(this->TappinggroupBox);
      this->panel3->Controls->Add(this->DeslagginggroupBox);
      this->panel3->Controls->Add(this->GasStatusgroupBox);
      this->panel3->Controls->Add(this->WaterGasgroupBox);
      this->panel3->Controls->Add(this->GasModelgroupBox);
      this->panel3->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->panel3->Location = System::Drawing::Point(216, 546);
      this->panel3->Name = "panel3";
      this->panel3->Size = System::Drawing::Size(792, 200);
      this->panel3->TabIndex = 2;
      // 
      // FreespacegroupBox
      // 
      this->FreespacegroupBox->Controls->Add(this->textBoxFreespare5);
      this->FreespacegroupBox->Controls->Add(this->label78);
      this->FreespacegroupBox->Controls->Add(this->textBoxFreespare4);
      this->FreespacegroupBox->Controls->Add(this->textBoxFreespare3);
      this->FreespacegroupBox->Controls->Add(this->label79);
      this->FreespacegroupBox->Controls->Add(this->label80);
      this->FreespacegroupBox->Controls->Add(this->textBoxFreespare2);
      this->FreespacegroupBox->Controls->Add(this->label81);
      this->FreespacegroupBox->Controls->Add(this->textBoxFreespare1);
      this->FreespacegroupBox->Controls->Add(this->label82);
      this->FreespacegroupBox->Location = System::Drawing::Point(672, 8);
      this->FreespacegroupBox->Name = "FreespacegroupBox";
      this->FreespacegroupBox->Size = System::Drawing::Size(115, 144);
      this->FreespacegroupBox->TabIndex = 13;
      this->FreespacegroupBox->TabStop = false;
      this->FreespacegroupBox->Text = "Freespare";
      // 
      // textBoxFreespare5
      // 
      this->textBoxFreespare5->Location = System::Drawing::Point(72, 112);
      this->textBoxFreespare5->Name = "textBoxFreespare5";
      this->textBoxFreespare5->Size = System::Drawing::Size(40, 20);
      this->textBoxFreespare5->TabIndex = 26;
      // 
      // label78
      // 
      this->label78->Location = System::Drawing::Point(4, 110);
      this->label78->Name = "label78";
      this->label78->Size = System::Drawing::Size(68, 20);
      this->label78->TabIndex = 23;
      this->label78->Text = "Freespare5";
      // 
      // textBoxFreespare4
      // 
      this->textBoxFreespare4->Location = System::Drawing::Point(72, 88);
      this->textBoxFreespare4->Name = "textBoxFreespare4";
      this->textBoxFreespare4->Size = System::Drawing::Size(40, 20);
      this->textBoxFreespare4->TabIndex = 22;
      // 
      // textBoxFreespare3
      // 
      this->textBoxFreespare3->Location = System::Drawing::Point(72, 64);
      this->textBoxFreespare3->Name = "textBoxFreespare3";
      this->textBoxFreespare3->Size = System::Drawing::Size(40, 20);
      this->textBoxFreespare3->TabIndex = 21;
      // 
      // label79
      // 
      this->label79->Location = System::Drawing::Point(4, 86);
      this->label79->Name = "label79";
      this->label79->Size = System::Drawing::Size(68, 20);
      this->label79->TabIndex = 20;
      this->label79->Text = "Freespare4";
      // 
      // label80
      // 
      this->label80->Location = System::Drawing::Point(4, 62);
      this->label80->Name = "label80";
      this->label80->Size = System::Drawing::Size(68, 20);
      this->label80->TabIndex = 19;
      this->label80->Text = "Freespare3";
      // 
      // textBoxFreespare2
      // 
      this->textBoxFreespare2->Location = System::Drawing::Point(72, 40);
      this->textBoxFreespare2->Name = "textBoxFreespare2";
      this->textBoxFreespare2->Size = System::Drawing::Size(40, 20);
      this->textBoxFreespare2->TabIndex = 18;
      // 
      // label81
      // 
      this->label81->Location = System::Drawing::Point(4, 38);
      this->label81->Name = "label81";
      this->label81->Size = System::Drawing::Size(68, 20);
      this->label81->TabIndex = 17;
      this->label81->Text = "Freespare2";
      // 
      // textBoxFreespare1
      // 
      this->textBoxFreespare1->Location = System::Drawing::Point(72, 16);
      this->textBoxFreespare1->Name = "textBoxFreespare1";
      this->textBoxFreespare1->Size = System::Drawing::Size(40, 20);
      this->textBoxFreespare1->TabIndex = 16;
      // 
      // label82
      // 
      this->label82->Location = System::Drawing::Point(4, 14);
      this->label82->Name = "label82";
      this->label82->Size = System::Drawing::Size(68, 20);
      this->label82->TabIndex = 15;
      this->label82->Text = "Freespare1";
      // 
      // SampleTakengroupBox
      // 
      this->SampleTakengroupBox->Controls->Add(this->textBox44);
      this->SampleTakengroupBox->Controls->Add(this->textBox45);
      this->SampleTakengroupBox->Controls->Add(this->textBox46);
      this->SampleTakengroupBox->Controls->Add(this->label68);
      this->SampleTakengroupBox->Controls->Add(this->label69);
      this->SampleTakengroupBox->Controls->Add(this->label70);
      this->SampleTakengroupBox->Controls->Add(this->textBox47);
      this->SampleTakengroupBox->Controls->Add(this->textBox48);
      this->SampleTakengroupBox->Controls->Add(this->label71);
      this->SampleTakengroupBox->Controls->Add(this->label72);
      this->SampleTakengroupBox->Controls->Add(this->textBox49);
      this->SampleTakengroupBox->Controls->Add(this->label73);
      this->SampleTakengroupBox->Controls->Add(this->textBox50);
      this->SampleTakengroupBox->Controls->Add(this->label74);
      this->SampleTakengroupBox->Location = System::Drawing::Point(384, 8);
      this->SampleTakengroupBox->Name = "SampleTakengroupBox";
      this->SampleTakengroupBox->Size = System::Drawing::Size(144, 184);
      this->SampleTakengroupBox->TabIndex = 12;
      this->SampleTakengroupBox->TabStop = false;
      this->SampleTakengroupBox->Text = "Sample/Taken";
      // 
      // textBox44
      // 
      this->textBox44->Location = System::Drawing::Point(88, 160);
      this->textBox44->Name = "textBox44";
      this->textBox44->Size = System::Drawing::Size(40, 20);
      this->textBox44->TabIndex = 28;
      // 
      // textBox45
      // 
      this->textBox45->Location = System::Drawing::Point(88, 136);
      this->textBox45->Name = "textBox45";
      this->textBox45->Size = System::Drawing::Size(40, 20);
      this->textBox45->TabIndex = 27;
      // 
      // textBox46
      // 
      this->textBox46->Location = System::Drawing::Point(88, 112);
      this->textBox46->Name = "textBox46";
      this->textBox46->Size = System::Drawing::Size(40, 20);
      this->textBox46->TabIndex = 26;
      // 
      // label68
      // 
      this->label68->Location = System::Drawing::Point(4, 158);
      this->label68->Name = "label68";
      this->label68->Size = System::Drawing::Size(84, 20);
      this->label68->TabIndex = 25;
      this->label68->Text = "CarbCont";
      // 
      // label69
      // 
      this->label69->Location = System::Drawing::Point(4, 134);
      this->label69->Name = "label69";
      this->label69->Size = System::Drawing::Size(84, 20);
      this->label69->TabIndex = 24;
      this->label69->Text = "OxyCont";
      // 
      // label70
      // 
      this->label70->Location = System::Drawing::Point(4, 110);
      this->label70->Name = "label70";
      this->label70->Size = System::Drawing::Size(84, 20);
      this->label70->TabIndex = 23;
      this->label70->Text = "Temp";
      // 
      // textBox47
      // 
      this->textBox47->Location = System::Drawing::Point(88, 88);
      this->textBox47->Name = "textBox47";
      this->textBox47->Size = System::Drawing::Size(40, 20);
      this->textBox47->TabIndex = 22;
      // 
      // textBox48
      // 
      this->textBox48->Location = System::Drawing::Point(88, 64);
      this->textBox48->Name = "textBox48";
      this->textBox48->Size = System::Drawing::Size(40, 20);
      this->textBox48->TabIndex = 21;
      // 
      // label71
      // 
      this->label71->Location = System::Drawing::Point(4, 86);
      this->label71->Name = "label71";
      this->label71->Size = System::Drawing::Size(84, 20);
      this->label71->TabIndex = 20;
      this->label71->Text = "SampleMode";
      // 
      // label72
      // 
      this->label72->Location = System::Drawing::Point(4, 62);
      this->label72->Name = "label72";
      this->label72->Size = System::Drawing::Size(84, 20);
      this->label72->TabIndex = 19;
      this->label72->Text = "Probe Type";
      // 
      // textBox49
      // 
      this->textBox49->Location = System::Drawing::Point(88, 40);
      this->textBox49->Name = "textBox49";
      this->textBox49->Size = System::Drawing::Size(40, 20);
      this->textBox49->TabIndex = 18;
      // 
      // label73
      // 
      this->label73->Location = System::Drawing::Point(4, 38);
      this->label73->Name = "label73";
      this->label73->Size = System::Drawing::Size(84, 20);
      this->label73->TabIndex = 17;
      this->label73->Text = "AmountO2";
      // 
      // textBox50
      // 
      this->textBox50->Location = System::Drawing::Point(88, 16);
      this->textBox50->Name = "textBox50";
      this->textBox50->Size = System::Drawing::Size(40, 20);
      this->textBox50->TabIndex = 16;
      // 
      // label74
      // 
      this->label74->Location = System::Drawing::Point(4, 14);
      this->label74->Name = "label74";
      this->label74->Size = System::Drawing::Size(84, 20);
      this->label74->TabIndex = 15;
      this->label74->Text = "AmountO2Met";
      // 
      // TappinggroupBox
      // 
      this->TappinggroupBox->Controls->Add(this->textBox41);
      this->TappinggroupBox->Controls->Add(this->textBox42);
      this->TappinggroupBox->Controls->Add(this->textBox43);
      this->TappinggroupBox->Controls->Add(this->label65);
      this->TappinggroupBox->Controls->Add(this->label66);
      this->TappinggroupBox->Controls->Add(this->label67);
      this->TappinggroupBox->Location = System::Drawing::Point(528, 8);
      this->TappinggroupBox->Name = "TappinggroupBox";
      this->TappinggroupBox->Size = System::Drawing::Size(144, 96);
      this->TappinggroupBox->TabIndex = 11;
      this->TappinggroupBox->TabStop = false;
      this->TappinggroupBox->Text = "Tapping";
      // 
      // textBox41
      // 
      this->textBox41->Location = System::Drawing::Point(84, 64);
      this->textBox41->Name = "textBox41";
      this->textBox41->Size = System::Drawing::Size(40, 20);
      this->textBox41->TabIndex = 13;
      // 
      // textBox42
      // 
      this->textBox42->Location = System::Drawing::Point(84, 40);
      this->textBox42->Name = "textBox42";
      this->textBox42->Size = System::Drawing::Size(40, 20);
      this->textBox42->TabIndex = 12;
      // 
      // textBox43
      // 
      this->textBox43->Location = System::Drawing::Point(84, 16);
      this->textBox43->Name = "textBox43";
      this->textBox43->Size = System::Drawing::Size(40, 20);
      this->textBox43->TabIndex = 11;
      // 
      // label65
      // 
      this->label65->Location = System::Drawing::Point(16, 64);
      this->label65->Name = "label65";
      this->label65->Size = System::Drawing::Size(64, 20);
      this->label65->TabIndex = 10;
      this->label65->Text = "PlugUsed";
      // 
      // label66
      // 
      this->label66->Location = System::Drawing::Point(16, 40);
      this->label66->Name = "label66";
      this->label66->Size = System::Drawing::Size(64, 20);
      this->label66->TabIndex = 9;
      this->label66->Text = "DartUsed";
      // 
      // label67
      // 
      this->label67->Location = System::Drawing::Point(16, 16);
      this->label67->Name = "label67";
      this->label67->Size = System::Drawing::Size(64, 20);
      this->label67->TabIndex = 8;
      this->label67->Text = "ActionFlag";
      // 
      // DeslagginggroupBox
      // 
      this->DeslagginggroupBox->Controls->Add(this->textBox40);
      this->DeslagginggroupBox->Controls->Add(this->label64);
      this->DeslagginggroupBox->Location = System::Drawing::Point(528, 104);
      this->DeslagginggroupBox->Name = "DeslagginggroupBox";
      this->DeslagginggroupBox->Size = System::Drawing::Size(144, 48);
      this->DeslagginggroupBox->TabIndex = 10;
      this->DeslagginggroupBox->TabStop = false;
      this->DeslagginggroupBox->Text = "Delslagging";
      // 
      // textBox40
      // 
      this->textBox40->Location = System::Drawing::Point(84, 18);
      this->textBox40->Name = "textBox40";
      this->textBox40->Size = System::Drawing::Size(44, 20);
      this->textBox40->TabIndex = 7;
      // 
      // label64
      // 
      this->label64->Location = System::Drawing::Point(8, 18);
      this->label64->Name = "label64";
      this->label64->Size = System::Drawing::Size(72, 20);
      this->label64->TabIndex = 6;
      this->label64->Text = "Delslag Sta.";
      // 
      // GasStatusgroupBox
      // 
      this->GasStatusgroupBox->Controls->Add(this->label21);
      this->GasStatusgroupBox->Controls->Add(this->label38);
      this->GasStatusgroupBox->Controls->Add(this->numericUpDown3);
      this->GasStatusgroupBox->Controls->Add(this->numericUpDown2);
      this->GasStatusgroupBox->Controls->Add(this->label39);
      this->GasStatusgroupBox->Controls->Add(this->numericUpDown1);
      this->GasStatusgroupBox->Location = System::Drawing::Point(208, 8);
      this->GasStatusgroupBox->Name = "GasStatusgroupBox";
      this->GasStatusgroupBox->Size = System::Drawing::Size(176, 96);
      this->GasStatusgroupBox->TabIndex = 9;
      this->GasStatusgroupBox->TabStop = false;
      this->GasStatusgroupBox->Text = "Gas Statu";
      // 
      // label21
      // 
      this->label21->Location = System::Drawing::Point(16, 72);
      this->label21->Name = "label21";
      this->label21->Size = System::Drawing::Size(56, 16);
      this->label21->TabIndex = 5;
      this->label21->Text = "N2";
      // 
      // label38
      // 
      this->label38->Location = System::Drawing::Point(16, 48);
      this->label38->Name = "label38";
      this->label38->Size = System::Drawing::Size(56, 16);
      this->label38->TabIndex = 4;
      this->label38->Text = "Ar";
      // 
      // numericUpDown3
      // 
      this->numericUpDown3->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 0});
      this->numericUpDown3->Location = System::Drawing::Point(80, 64);
      this->numericUpDown3->Name = "numericUpDown3";
      this->numericUpDown3->Size = System::Drawing::Size(72, 20);
      this->numericUpDown3->TabIndex = 3;
      // 
      // numericUpDown2
      // 
      this->numericUpDown2->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 0});
      this->numericUpDown2->Location = System::Drawing::Point(80, 40);
      this->numericUpDown2->Name = "numericUpDown2";
      this->numericUpDown2->Size = System::Drawing::Size(72, 20);
      this->numericUpDown2->TabIndex = 2;
      // 
      // label39
      // 
      this->label39->Location = System::Drawing::Point(16, 24);
      this->label39->Name = "label39";
      this->label39->Size = System::Drawing::Size(56, 16);
      this->label39->TabIndex = 1;
      this->label39->Text = "O2 folw";
      // 
      // numericUpDown1
      // 
      this->numericUpDown1->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 0});
      this->numericUpDown1->Location = System::Drawing::Point(80, 16);
      this->numericUpDown1->Name = "numericUpDown1";
      this->numericUpDown1->Size = System::Drawing::Size(72, 20);
      this->numericUpDown1->TabIndex = 0;
      // 
      // WaterGasgroupBox
      // 
      this->WaterGasgroupBox->Controls->Add(this->textBox13);
      this->WaterGasgroupBox->Controls->Add(this->textBox12);
      this->WaterGasgroupBox->Controls->Add(this->textBox11);
      this->WaterGasgroupBox->Controls->Add(this->textBox10);
      this->WaterGasgroupBox->Controls->Add(this->textBox9);
      this->WaterGasgroupBox->Controls->Add(this->label33);
      this->WaterGasgroupBox->Controls->Add(this->label34);
      this->WaterGasgroupBox->Controls->Add(this->label35);
      this->WaterGasgroupBox->Controls->Add(this->label36);
      this->WaterGasgroupBox->Controls->Add(this->label37);
      this->WaterGasgroupBox->Location = System::Drawing::Point(208, 104);
      this->WaterGasgroupBox->Name = "WaterGasgroupBox";
      this->WaterGasgroupBox->Size = System::Drawing::Size(176, 88);
      this->WaterGasgroupBox->TabIndex = 8;
      this->WaterGasgroupBox->TabStop = false;
      this->WaterGasgroupBox->Text = "Warte Ga";
      // 
      // textBox13
      // 
      this->textBox13->Location = System::Drawing::Point(128, 40);
      this->textBox13->Name = "textBox13";
      this->textBox13->Size = System::Drawing::Size(40, 20);
      this->textBox13->TabIndex = 9;
      // 
      // textBox12
      // 
      this->textBox12->Location = System::Drawing::Point(128, 16);
      this->textBox12->Name = "textBox12";
      this->textBox12->Size = System::Drawing::Size(40, 20);
      this->textBox12->TabIndex = 8;
      // 
      // textBox11
      // 
      this->textBox11->Location = System::Drawing::Point(48, 64);
      this->textBox11->Name = "textBox11";
      this->textBox11->Size = System::Drawing::Size(40, 20);
      this->textBox11->TabIndex = 7;
      // 
      // textBox10
      // 
      this->textBox10->Location = System::Drawing::Point(48, 40);
      this->textBox10->Name = "textBox10";
      this->textBox10->Size = System::Drawing::Size(40, 20);
      this->textBox10->TabIndex = 6;
      // 
      // textBox9
      // 
      this->textBox9->Location = System::Drawing::Point(48, 16);
      this->textBox9->Name = "textBox9";
      this->textBox9->Size = System::Drawing::Size(40, 20);
      this->textBox9->TabIndex = 5;
      // 
      // label33
      // 
      this->label33->Location = System::Drawing::Point(88, 40);
      this->label33->Name = "label33";
      this->label33->Size = System::Drawing::Size(40, 20);
      this->label33->TabIndex = 4;
      this->label33->Text = "T";
      // 
      // label34
      // 
      this->label34->Location = System::Drawing::Point(88, 16);
      this->label34->Name = "label34";
      this->label34->Size = System::Drawing::Size(40, 20);
      this->label34->TabIndex = 3;
      this->label34->Text = "Ar";
      // 
      // label35
      // 
      this->label35->Location = System::Drawing::Point(8, 64);
      this->label35->Name = "label35";
      this->label35->Size = System::Drawing::Size(40, 20);
      this->label35->TabIndex = 2;
      this->label35->Text = "N2";
      // 
      // label36
      // 
      this->label36->Location = System::Drawing::Point(8, 40);
      this->label36->Name = "label36";
      this->label36->Size = System::Drawing::Size(40, 20);
      this->label36->TabIndex = 1;
      this->label36->Text = "CO2";
      // 
      // label37
      // 
      this->label37->Location = System::Drawing::Point(8, 16);
      this->label37->Name = "label37";
      this->label37->Size = System::Drawing::Size(40, 20);
      this->label37->TabIndex = 0;
      this->label37->Text = "CO";
      // 
      // GasModelgroupBox
      // 
      this->GasModelgroupBox->Controls->Add(this->textBox8);
      this->GasModelgroupBox->Controls->Add(this->textBox7);
      this->GasModelgroupBox->Controls->Add(this->textBox6);
      this->GasModelgroupBox->Controls->Add(this->textBox5);
      this->GasModelgroupBox->Controls->Add(this->label25);
      this->GasModelgroupBox->Controls->Add(this->label26);
      this->GasModelgroupBox->Controls->Add(this->label27);
      this->GasModelgroupBox->Controls->Add(this->label28);
      this->GasModelgroupBox->Controls->Add(this->textBox4);
      this->GasModelgroupBox->Controls->Add(this->textBox3);
      this->GasModelgroupBox->Controls->Add(this->label29);
      this->GasModelgroupBox->Controls->Add(this->label30);
      this->GasModelgroupBox->Controls->Add(this->textBox2);
      this->GasModelgroupBox->Controls->Add(this->label31);
      this->GasModelgroupBox->Controls->Add(this->textBox1);
      this->GasModelgroupBox->Controls->Add(this->label32);
      this->GasModelgroupBox->Location = System::Drawing::Point(0, 8);
      this->GasModelgroupBox->Name = "GasModelgroupBox";
      this->GasModelgroupBox->Size = System::Drawing::Size(208, 184);
      this->GasModelgroupBox->TabIndex = 7;
      this->GasModelgroupBox->TabStop = false;
      this->GasModelgroupBox->Text = "Gas/Model Parameter";
      // 
      // textBox8
      // 
      this->textBox8->Location = System::Drawing::Point(144, 200);
      this->textBox8->Name = "textBox8";
      this->textBox8->Size = System::Drawing::Size(40, 20);
      this->textBox8->TabIndex = 15;
      // 
      // textBox7
      // 
      this->textBox7->Location = System::Drawing::Point(144, 160);
      this->textBox7->Name = "textBox7";
      this->textBox7->Size = System::Drawing::Size(40, 20);
      this->textBox7->TabIndex = 14;
      // 
      // textBox6
      // 
      this->textBox6->Location = System::Drawing::Point(144, 136);
      this->textBox6->Name = "textBox6";
      this->textBox6->Size = System::Drawing::Size(40, 20);
      this->textBox6->TabIndex = 13;
      // 
      // textBox5
      // 
      this->textBox5->Location = System::Drawing::Point(144, 112);
      this->textBox5->Name = "textBox5";
      this->textBox5->Size = System::Drawing::Size(40, 20);
      this->textBox5->TabIndex = 12;
      // 
      // label25
      // 
      this->label25->Location = System::Drawing::Point(16, 200);
      this->label25->Name = "label25";
      this->label25->Size = System::Drawing::Size(120, 20);
      this->label25->TabIndex = 11;
      this->label25->Text = "LanceHighMax";
      // 
      // label26
      // 
      this->label26->Location = System::Drawing::Point(16, 160);
      this->label26->Name = "label26";
      this->label26->Size = System::Drawing::Size(120, 20);
      this->label26->TabIndex = 10;
      this->label26->Text = "LanceHighMin";
      // 
      // label27
      // 
      this->label27->Location = System::Drawing::Point(16, 136);
      this->label27->Name = "label27";
      this->label27->Size = System::Drawing::Size(120, 20);
      this->label27->TabIndex = 9;
      this->label27->Text = "FlowButtonStirArMin";
      // 
      // label28
      // 
      this->label28->Location = System::Drawing::Point(16, 112);
      this->label28->Name = "label28";
      this->label28->Size = System::Drawing::Size(120, 20);
      this->label28->TabIndex = 8;
      this->label28->Text = "FlowButtonStirArMin";
      // 
      // textBox4
      // 
      this->textBox4->Location = System::Drawing::Point(144, 88);
      this->textBox4->Name = "textBox4";
      this->textBox4->Size = System::Drawing::Size(40, 20);
      this->textBox4->TabIndex = 7;
      // 
      // textBox3
      // 
      this->textBox3->Location = System::Drawing::Point(144, 64);
      this->textBox3->Name = "textBox3";
      this->textBox3->Size = System::Drawing::Size(40, 20);
      this->textBox3->TabIndex = 6;
      // 
      // label29
      // 
      this->label29->Location = System::Drawing::Point(16, 88);
      this->label29->Name = "label29";
      this->label29->Size = System::Drawing::Size(120, 20);
      this->label29->TabIndex = 5;
      this->label29->Text = "FlowButtonStirN2Min";
      // 
      // label30
      // 
      this->label30->Location = System::Drawing::Point(16, 64);
      this->label30->Name = "label30";
      this->label30->Size = System::Drawing::Size(120, 20);
      this->label30->TabIndex = 4;
      this->label30->Text = "FlowButtonStirN2Max";
      // 
      // textBox2
      // 
      this->textBox2->Location = System::Drawing::Point(144, 40);
      this->textBox2->Name = "textBox2";
      this->textBox2->Size = System::Drawing::Size(40, 20);
      this->textBox2->TabIndex = 3;
      // 
      // label31
      // 
      this->label31->Location = System::Drawing::Point(16, 40);
      this->label31->Name = "label31";
      this->label31->Size = System::Drawing::Size(120, 20);
      this->label31->TabIndex = 2;
      this->label31->Text = "FlowTopLanceO2Min";
      // 
      // textBox1
      // 
      this->textBox1->Location = System::Drawing::Point(144, 16);
      this->textBox1->Name = "textBox1";
      this->textBox1->Size = System::Drawing::Size(40, 20);
      this->textBox1->TabIndex = 1;
      // 
      // label32
      // 
      this->label32->Location = System::Drawing::Point(16, 16);
      this->label32->Name = "label32";
      this->label32->Size = System::Drawing::Size(120, 20);
      this->label32->TabIndex = 0;
      this->label32->Text = "FlowTopLanceO2Max";
      // 
      // panel4
      // 
      this->panel4->BackColor = System::Drawing::SystemColors::ControlLight;
      this->panel4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panel4->Controls->Add(this->label75);
      this->panel4->Controls->Add(this->TlgHeadbutton);
      this->panel4->Controls->Add(this->BlowStartgroupBox);
      this->panel4->Controls->Add(this->HMCgroupBox);
      this->panel4->Controls->Add(this->ReadyforBlowgroupBox);
      this->panel4->Controls->Add(this->HeatgroupBox);
      this->panel4->Controls->Add(this->TlgHeadStatusgroupBox);
      this->panel4->Controls->Add(this->ConposgroupBox);
      this->panel4->Controls->Add(this->lanceblowstatusgroupBox);
      this->panel4->Controls->Add(this->LanceStatusgroupBox);
      this->panel4->Dock = System::Windows::Forms::DockStyle::Left;
      this->panel4->ForeColor = System::Drawing::SystemColors::WindowText;
      this->panel4->Location = System::Drawing::Point(216, 0);
      this->panel4->Name = "panel4";
      this->panel4->Size = System::Drawing::Size(320, 546);
      this->panel4->TabIndex = 3;
      // 
      // label75
      // 
      this->label75->ForeColor = System::Drawing::SystemColors::Desktop;
      this->label75->Location = System::Drawing::Point(40, 8);
      this->label75->Name = "label75";
      this->label75->Size = System::Drawing::Size(128, 16);
      this->label75->TabIndex = 17;
      this->label75->Text = "Telegramm Head Statu";
      // 
      // TlgHeadbutton
      // 
      this->TlgHeadbutton->BackColor = System::Drawing::SystemColors::Desktop;
      this->TlgHeadbutton->Location = System::Drawing::Point(8, 8);
      this->TlgHeadbutton->Name = "TlgHeadbutton";
      this->TlgHeadbutton->Size = System::Drawing::Size(24, 16);
      this->TlgHeadbutton->TabIndex = 16;
      this->TlgHeadbutton->UseVisualStyleBackColor = false;
      this->TlgHeadbutton->Click += gcnew System::EventHandler(this, &CBofMainForm::TlgHeadbutton_Click);
      // 
      // BlowStartgroupBox
      // 
      this->BlowStartgroupBox->Controls->Add(this->label63);
      this->BlowStartgroupBox->Controls->Add(this->textBox39);
      this->BlowStartgroupBox->Controls->Add(this->textBox37);
      this->BlowStartgroupBox->Controls->Add(this->label61);
      this->BlowStartgroupBox->Controls->Add(this->label62);
      this->BlowStartgroupBox->Controls->Add(this->textBox38);
      this->BlowStartgroupBox->Location = System::Drawing::Point(176, 296);
      this->BlowStartgroupBox->Name = "BlowStartgroupBox";
      this->BlowStartgroupBox->Size = System::Drawing::Size(128, 128);
      this->BlowStartgroupBox->TabIndex = 15;
      this->BlowStartgroupBox->TabStop = false;
      this->BlowStartgroupBox->Text = "BlowStart";
      // 
      // label63
      // 
      this->label63->Location = System::Drawing::Point(8, 88);
      this->label63->Name = "label63";
      this->label63->Size = System::Drawing::Size(64, 32);
      this->label63->TabIndex = 16;
      this->label63->Text = "AmountO2Tot";
      // 
      // textBox39
      // 
      this->textBox39->Location = System::Drawing::Point(72, 88);
      this->textBox39->Name = "textBox39";
      this->textBox39->Size = System::Drawing::Size(40, 20);
      this->textBox39->TabIndex = 17;
      // 
      // textBox37
      // 
      this->textBox37->Location = System::Drawing::Point(72, 24);
      this->textBox37->Name = "textBox37";
      this->textBox37->Size = System::Drawing::Size(40, 20);
      this->textBox37->TabIndex = 14;
      // 
      // label61
      // 
      this->label61->Location = System::Drawing::Point(8, 56);
      this->label61->Name = "label61";
      this->label61->Size = System::Drawing::Size(64, 24);
      this->label61->TabIndex = 13;
      this->label61->Text = "AmountO2";
      // 
      // label62
      // 
      this->label62->Location = System::Drawing::Point(8, 24);
      this->label62->Name = "label62";
      this->label62->Size = System::Drawing::Size(56, 24);
      this->label62->TabIndex = 12;
      this->label62->Text = "AmountO2Met";
      // 
      // textBox38
      // 
      this->textBox38->Location = System::Drawing::Point(72, 56);
      this->textBox38->Name = "textBox38";
      this->textBox38->Size = System::Drawing::Size(40, 20);
      this->textBox38->TabIndex = 15;
      // 
      // HMCgroupBox
      // 
      this->HMCgroupBox->Controls->Add(this->textBoxHMLocation);
      this->HMCgroupBox->Controls->Add(this->textBoxMatWgt);
      this->HMCgroupBox->Controls->Add(this->textBoxWgtstat);
      this->HMCgroupBox->Controls->Add(this->textBoxLDINo);
      this->HMCgroupBox->Controls->Add(this->label53);
      this->HMCgroupBox->Controls->Add(this->label54);
      this->HMCgroupBox->Controls->Add(this->label55);
      this->HMCgroupBox->Controls->Add(this->label56);
      this->HMCgroupBox->Location = System::Drawing::Point(0, 184);
      this->HMCgroupBox->Name = "HMCgroupBox";
      this->HMCgroupBox->Size = System::Drawing::Size(168, 120);
      this->HMCgroupBox->TabIndex = 13;
      this->HMCgroupBox->TabStop = false;
      this->HMCgroupBox->Text = "Hot metal charging";
      // 
      // textBoxHMLocation
      // 
      this->textBoxHMLocation->Location = System::Drawing::Point(72, 88);
      this->textBoxHMLocation->Name = "textBoxHMLocation";
      this->textBoxHMLocation->Size = System::Drawing::Size(72, 20);
      this->textBoxHMLocation->TabIndex = 23;
      // 
      // textBoxMatWgt
      // 
      this->textBoxMatWgt->Location = System::Drawing::Point(72, 64);
      this->textBoxMatWgt->Name = "textBoxMatWgt";
      this->textBoxMatWgt->Size = System::Drawing::Size(72, 20);
      this->textBoxMatWgt->TabIndex = 22;
      // 
      // textBoxWgtstat
      // 
      this->textBoxWgtstat->Location = System::Drawing::Point(72, 40);
      this->textBoxWgtstat->Name = "textBoxWgtstat";
      this->textBoxWgtstat->Size = System::Drawing::Size(72, 20);
      this->textBoxWgtstat->TabIndex = 21;
      // 
      // textBoxLDINo
      // 
      this->textBoxLDINo->Location = System::Drawing::Point(72, 16);
      this->textBoxLDINo->Name = "textBoxLDINo";
      this->textBoxLDINo->Size = System::Drawing::Size(72, 20);
      this->textBoxLDINo->TabIndex = 20;
      // 
      // label53
      // 
      this->label53->Location = System::Drawing::Point(16, 96);
      this->label53->Name = "label53";
      this->label53->Size = System::Drawing::Size(56, 16);
      this->label53->TabIndex = 19;
      this->label53->Text = "HMLocation";
      // 
      // label54
      // 
      this->label54->Location = System::Drawing::Point(16, 72);
      this->label54->Name = "label54";
      this->label54->Size = System::Drawing::Size(56, 16);
      this->label54->TabIndex = 18;
      this->label54->Text = "MatWgt";
      // 
      // label55
      // 
      this->label55->Location = System::Drawing::Point(16, 48);
      this->label55->Name = "label55";
      this->label55->Size = System::Drawing::Size(56, 16);
      this->label55->TabIndex = 17;
      this->label55->Text = "WgtStat";
      // 
      // label56
      // 
      this->label56->Location = System::Drawing::Point(16, 24);
      this->label56->Name = "label56";
      this->label56->Size = System::Drawing::Size(56, 16);
      this->label56->TabIndex = 16;
      this->label56->Text = "LDI No.";
      // 
      // ReadyforBlowgroupBox
      // 
      this->ReadyforBlowgroupBox->Controls->Add(this->label24);
      this->ReadyforBlowgroupBox->Controls->Add(this->label23);
      this->ReadyforBlowgroupBox->Controls->Add(this->label22);
      this->ReadyforBlowgroupBox->Controls->Add(this->led24);
      this->ReadyforBlowgroupBox->Controls->Add(this->led23);
      this->ReadyforBlowgroupBox->Controls->Add(this->led22);
      this->ReadyforBlowgroupBox->Location = System::Drawing::Point(0, 104);
      this->ReadyforBlowgroupBox->Name = "ReadyforBlowgroupBox";
      this->ReadyforBlowgroupBox->Size = System::Drawing::Size(168, 80);
      this->ReadyforBlowgroupBox->TabIndex = 9;
      this->ReadyforBlowgroupBox->TabStop = false;
      this->ReadyforBlowgroupBox->Text = "Top Lance Ready for Blow";
      // 
      // label24
      // 
      this->label24->Location = System::Drawing::Point(40, 56);
      this->label24->Name = "label24";
      this->label24->Size = System::Drawing::Size(100, 16);
      this->label24->TabIndex = 60;
      this->label24->Text = "Cool Avail";
      // 
      // label23
      // 
      this->label23->Location = System::Drawing::Point(40, 40);
      this->label23->Name = "label23";
      this->label23->Size = System::Drawing::Size(100, 16);
      this->label23->TabIndex = 59;
      this->label23->Text = "Standby Avail";
      // 
      // label22
      // 
      this->label22->Location = System::Drawing::Point(40, 24);
      this->label22->Name = "label22";
      this->label22->Size = System::Drawing::Size(100, 16);
      this->label22->TabIndex = 58;
      this->label22->Text = "O2 Avail";
      // 
      // led24
      // 
      this->led24->Location = System::Drawing::Point(24, 56);
      this->led24->Name = "led24";
      this->led24->Size = System::Drawing::Size(10, 10);
      this->led24->Status = false;
      this->led24->TabIndex = 49;
      // 
      // led23
      // 
      this->led23->Location = System::Drawing::Point(24, 40);
      this->led23->Name = "led23";
      this->led23->Size = System::Drawing::Size(10, 10);
      this->led23->Status = false;
      this->led23->TabIndex = 48;
      // 
      // led22
      // 
      this->led22->Location = System::Drawing::Point(24, 24);
      this->led22->Name = "led22";
      this->led22->Size = System::Drawing::Size(10, 10);
      this->led22->Status = false;
      this->led22->TabIndex = 47;
      // 
      // HeatgroupBox
      // 
      this->HeatgroupBox->Controls->Add(this->textBoxTime);
      this->HeatgroupBox->Controls->Add(this->textBoxDate);
      this->HeatgroupBox->Controls->Add(this->label76);
      this->HeatgroupBox->Controls->Add(this->label77);
      this->HeatgroupBox->Controls->Add(this->textBoxRetreatID);
      this->HeatgroupBox->Controls->Add(this->textBoxHeatNo);
      this->HeatgroupBox->Controls->Add(this->label20);
      this->HeatgroupBox->Controls->Add(this->label19);
      this->HeatgroupBox->Location = System::Drawing::Point(0, 32);
      this->HeatgroupBox->Name = "HeatgroupBox";
      this->HeatgroupBox->Size = System::Drawing::Size(304, 72);
      this->HeatgroupBox->TabIndex = 7;
      this->HeatgroupBox->TabStop = false;
      this->HeatgroupBox->Text = "Heat No/Retreat ID";
      // 
      // textBoxTime
      // 
      this->textBoxTime->Location = System::Drawing::Point(208, 16);
      this->textBoxTime->Name = "textBoxTime";
      this->textBoxTime->Size = System::Drawing::Size(72, 20);
      this->textBoxTime->TabIndex = 14;
      // 
      // textBoxDate
      // 
      this->textBoxDate->Location = System::Drawing::Point(72, 16);
      this->textBoxDate->Name = "textBoxDate";
      this->textBoxDate->Size = System::Drawing::Size(72, 20);
      this->textBoxDate->TabIndex = 13;
      // 
      // label76
      // 
      this->label76->Location = System::Drawing::Point(152, 16);
      this->label76->Name = "label76";
      this->label76->Size = System::Drawing::Size(56, 16);
      this->label76->TabIndex = 12;
      this->label76->Text = "Time";
      // 
      // label77
      // 
      this->label77->Location = System::Drawing::Point(8, 16);
      this->label77->Name = "label77";
      this->label77->Size = System::Drawing::Size(56, 16);
      this->label77->TabIndex = 11;
      this->label77->Text = "Date";
      // 
      // textBoxRetreatID
      // 
      this->textBoxRetreatID->Location = System::Drawing::Point(208, 48);
      this->textBoxRetreatID->Name = "textBoxRetreatID";
      this->textBoxRetreatID->Size = System::Drawing::Size(72, 20);
      this->textBoxRetreatID->TabIndex = 10;
      // 
      // textBoxHeatNo
      // 
      this->textBoxHeatNo->Location = System::Drawing::Point(72, 48);
      this->textBoxHeatNo->Name = "textBoxHeatNo";
      this->textBoxHeatNo->Size = System::Drawing::Size(72, 20);
      this->textBoxHeatNo->TabIndex = 9;
      // 
      // label20
      // 
      this->label20->Location = System::Drawing::Point(152, 48);
      this->label20->Name = "label20";
      this->label20->Size = System::Drawing::Size(56, 16);
      this->label20->TabIndex = 2;
      this->label20->Text = "Retreat ID";
      // 
      // label19
      // 
      this->label19->Location = System::Drawing::Point(8, 48);
      this->label19->Name = "label19";
      this->label19->Size = System::Drawing::Size(56, 16);
      this->label19->TabIndex = 1;
      this->label19->Text = "Heat No";
      // 
      // TlgHeadStatusgroupBox
      // 
      this->TlgHeadStatusgroupBox->Controls->Add(this->textBoxPlantID);
      this->TlgHeadStatusgroupBox->Controls->Add(this->textBoxProductID);
      this->TlgHeadStatusgroupBox->Controls->Add(this->textBoxReserve);
      this->TlgHeadStatusgroupBox->Controls->Add(this->textBoxBlen);
      this->TlgHeadStatusgroupBox->Controls->Add(this->textBoxOrg);
      this->TlgHeadStatusgroupBox->Controls->Add(this->textBoxCreaTime);
      this->TlgHeadStatusgroupBox->Controls->Add(this->textBoxCreaDate);
      this->TlgHeadStatusgroupBox->Controls->Add(this->textBoxMsgID);
      this->TlgHeadStatusgroupBox->Controls->Add(this->label48);
      this->TlgHeadStatusgroupBox->Controls->Add(this->label47);
      this->TlgHeadStatusgroupBox->Controls->Add(this->label46);
      this->TlgHeadStatusgroupBox->Controls->Add(this->label45);
      this->TlgHeadStatusgroupBox->Controls->Add(this->label44);
      this->TlgHeadStatusgroupBox->Controls->Add(this->label43);
      this->TlgHeadStatusgroupBox->Controls->Add(this->label42);
      this->TlgHeadStatusgroupBox->Controls->Add(this->label41);
      this->TlgHeadStatusgroupBox->Location = System::Drawing::Point(0, 32);
      this->TlgHeadStatusgroupBox->Name = "TlgHeadStatusgroupBox";
      this->TlgHeadStatusgroupBox->Size = System::Drawing::Size(304, 120);
      this->TlgHeadStatusgroupBox->TabIndex = 6;
      this->TlgHeadStatusgroupBox->TabStop = false;
      this->TlgHeadStatusgroupBox->Text = "Tlg.Head Statu";
      // 
      // textBoxPlantID
      // 
      this->textBoxPlantID->Location = System::Drawing::Point(208, 88);
      this->textBoxPlantID->Name = "textBoxPlantID";
      this->textBoxPlantID->Size = System::Drawing::Size(72, 20);
      this->textBoxPlantID->TabIndex = 15;
      // 
      // textBoxProductID
      // 
      this->textBoxProductID->Location = System::Drawing::Point(208, 64);
      this->textBoxProductID->Name = "textBoxProductID";
      this->textBoxProductID->Size = System::Drawing::Size(72, 20);
      this->textBoxProductID->TabIndex = 14;
      // 
      // textBoxReserve
      // 
      this->textBoxReserve->Location = System::Drawing::Point(208, 40);
      this->textBoxReserve->Name = "textBoxReserve";
      this->textBoxReserve->Size = System::Drawing::Size(72, 20);
      this->textBoxReserve->TabIndex = 13;
      // 
      // textBoxBlen
      // 
      this->textBoxBlen->Location = System::Drawing::Point(208, 16);
      this->textBoxBlen->Name = "textBoxBlen";
      this->textBoxBlen->Size = System::Drawing::Size(72, 20);
      this->textBoxBlen->TabIndex = 12;
      // 
      // textBoxOrg
      // 
      this->textBoxOrg->Location = System::Drawing::Point(72, 88);
      this->textBoxOrg->Name = "textBoxOrg";
      this->textBoxOrg->Size = System::Drawing::Size(72, 20);
      this->textBoxOrg->TabIndex = 11;
      // 
      // textBoxCreaTime
      // 
      this->textBoxCreaTime->Location = System::Drawing::Point(72, 64);
      this->textBoxCreaTime->Name = "textBoxCreaTime";
      this->textBoxCreaTime->Size = System::Drawing::Size(72, 20);
      this->textBoxCreaTime->TabIndex = 10;
      // 
      // textBoxCreaDate
      // 
      this->textBoxCreaDate->Location = System::Drawing::Point(72, 40);
      this->textBoxCreaDate->Name = "textBoxCreaDate";
      this->textBoxCreaDate->Size = System::Drawing::Size(72, 20);
      this->textBoxCreaDate->TabIndex = 9;
      // 
      // textBoxMsgID
      // 
      this->textBoxMsgID->Location = System::Drawing::Point(72, 16);
      this->textBoxMsgID->Name = "textBoxMsgID";
      this->textBoxMsgID->Size = System::Drawing::Size(72, 20);
      this->textBoxMsgID->TabIndex = 8;
      // 
      // label48
      // 
      this->label48->Location = System::Drawing::Point(152, 96);
      this->label48->Name = "label48";
      this->label48->Size = System::Drawing::Size(56, 16);
      this->label48->TabIndex = 7;
      this->label48->Text = "PlantID";
      // 
      // label47
      // 
      this->label47->Location = System::Drawing::Point(152, 72);
      this->label47->Name = "label47";
      this->label47->Size = System::Drawing::Size(56, 16);
      this->label47->TabIndex = 6;
      this->label47->Text = "ProductID";
      // 
      // label46
      // 
      this->label46->Location = System::Drawing::Point(152, 48);
      this->label46->Name = "label46";
      this->label46->Size = System::Drawing::Size(56, 16);
      this->label46->TabIndex = 5;
      this->label46->Text = "Reserve";
      // 
      // label45
      // 
      this->label45->Location = System::Drawing::Point(152, 24);
      this->label45->Name = "label45";
      this->label45->Size = System::Drawing::Size(56, 16);
      this->label45->TabIndex = 4;
      this->label45->Text = "Blen";
      // 
      // label44
      // 
      this->label44->Location = System::Drawing::Point(8, 96);
      this->label44->Name = "label44";
      this->label44->Size = System::Drawing::Size(56, 16);
      this->label44->TabIndex = 3;
      this->label44->Text = "Org";
      // 
      // label43
      // 
      this->label43->Location = System::Drawing::Point(8, 72);
      this->label43->Name = "label43";
      this->label43->Size = System::Drawing::Size(56, 16);
      this->label43->TabIndex = 2;
      this->label43->Text = "CreaTime";
      // 
      // label42
      // 
      this->label42->Location = System::Drawing::Point(8, 48);
      this->label42->Name = "label42";
      this->label42->Size = System::Drawing::Size(56, 16);
      this->label42->TabIndex = 1;
      this->label42->Text = "Crea Date";
      // 
      // label41
      // 
      this->label41->Location = System::Drawing::Point(8, 24);
      this->label41->Name = "label41";
      this->label41->Size = System::Drawing::Size(56, 16);
      this->label41->TabIndex = 0;
      this->label41->Text = "MsgID";
      // 
      // ConposgroupBox
      // 
      this->ConposgroupBox->Controls->Add(this->textBox26);
      this->ConposgroupBox->Controls->Add(this->label50);
      this->ConposgroupBox->Controls->Add(this->label49);
      this->ConposgroupBox->Controls->Add(this->textBox27);
      this->ConposgroupBox->Location = System::Drawing::Point(176, 208);
      this->ConposgroupBox->Name = "ConposgroupBox";
      this->ConposgroupBox->Size = System::Drawing::Size(128, 80);
      this->ConposgroupBox->TabIndex = 8;
      this->ConposgroupBox->TabStop = false;
      this->ConposgroupBox->Text = "Converter pos.";
      // 
      // textBox26
      // 
      this->textBox26->Location = System::Drawing::Point(64, 24);
      this->textBox26->Name = "textBox26";
      this->textBox26->Size = System::Drawing::Size(40, 20);
      this->textBox26->TabIndex = 10;
      // 
      // label50
      // 
      this->label50->Location = System::Drawing::Point(8, 48);
      this->label50->Name = "label50";
      this->label50->Size = System::Drawing::Size(56, 16);
      this->label50->TabIndex = 2;
      this->label50->Text = "AngleConv";
      // 
      // label49
      // 
      this->label49->Location = System::Drawing::Point(8, 24);
      this->label49->Name = "label49";
      this->label49->Size = System::Drawing::Size(56, 16);
      this->label49->TabIndex = 1;
      this->label49->Text = "Conv.Po";
      // 
      // textBox27
      // 
      this->textBox27->Location = System::Drawing::Point(64, 48);
      this->textBox27->Name = "textBox27";
      this->textBox27->Size = System::Drawing::Size(40, 20);
      this->textBox27->TabIndex = 11;
      // 
      // lanceblowstatusgroupBox
      // 
      this->lanceblowstatusgroupBox->Controls->Add(this->textBox33);
      this->lanceblowstatusgroupBox->Controls->Add(this->textBox34);
      this->lanceblowstatusgroupBox->Controls->Add(this->textBox35);
      this->lanceblowstatusgroupBox->Controls->Add(this->textBox36);
      this->lanceblowstatusgroupBox->Controls->Add(this->label57);
      this->lanceblowstatusgroupBox->Controls->Add(this->label58);
      this->lanceblowstatusgroupBox->Controls->Add(this->label59);
      this->lanceblowstatusgroupBox->Controls->Add(this->label60);
      this->lanceblowstatusgroupBox->Location = System::Drawing::Point(0, 304);
      this->lanceblowstatusgroupBox->Name = "lanceblowstatusgroupBox";
      this->lanceblowstatusgroupBox->Size = System::Drawing::Size(168, 120);
      this->lanceblowstatusgroupBox->TabIndex = 14;
      this->lanceblowstatusgroupBox->TabStop = false;
      this->lanceblowstatusgroupBox->Text = "Lance Blow Statu";
      // 
      // textBox33
      // 
      this->textBox33->Location = System::Drawing::Point(80, 84);
      this->textBox33->Name = "textBox33";
      this->textBox33->Size = System::Drawing::Size(72, 20);
      this->textBox33->TabIndex = 31;
      // 
      // textBox34
      // 
      this->textBox34->Location = System::Drawing::Point(80, 60);
      this->textBox34->Name = "textBox34";
      this->textBox34->Size = System::Drawing::Size(72, 20);
      this->textBox34->TabIndex = 30;
      // 
      // textBox35
      // 
      this->textBox35->Location = System::Drawing::Point(80, 36);
      this->textBox35->Name = "textBox35";
      this->textBox35->Size = System::Drawing::Size(72, 20);
      this->textBox35->TabIndex = 29;
      // 
      // textBox36
      // 
      this->textBox36->Location = System::Drawing::Point(80, 12);
      this->textBox36->Name = "textBox36";
      this->textBox36->Size = System::Drawing::Size(72, 20);
      this->textBox36->TabIndex = 28;
      // 
      // label57
      // 
      this->label57->Location = System::Drawing::Point(4, 92);
      this->label57->Name = "label57";
      this->label57->Size = System::Drawing::Size(76, 16);
      this->label57->TabIndex = 27;
      this->label57->Text = "Blow Typ";
      // 
      // label58
      // 
      this->label58->Location = System::Drawing::Point(4, 68);
      this->label58->Name = "label58";
      this->label58->Size = System::Drawing::Size(76, 20);
      this->label58->TabIndex = 26;
      this->label58->Text = "TopLanceStat";
      // 
      // label59
      // 
      this->label59->Location = System::Drawing::Point(4, 44);
      this->label59->Name = "label59";
      this->label59->Size = System::Drawing::Size(76, 16);
      this->label59->TabIndex = 25;
      this->label59->Text = "Lance Pos.";
      // 
      // label60
      // 
      this->label60->Location = System::Drawing::Point(4, 20);
      this->label60->Name = "label60";
      this->label60->Size = System::Drawing::Size(76, 16);
      this->label60->TabIndex = 24;
      this->label60->Text = "Lance ID";
      // 
      // LanceStatusgroupBox
      // 
      this->LanceStatusgroupBox->Controls->Add(this->textBox15);
      this->LanceStatusgroupBox->Controls->Add(this->label40);
      this->LanceStatusgroupBox->Controls->Add(this->radioButton1);
      this->LanceStatusgroupBox->Controls->Add(this->radioButton2);
      this->LanceStatusgroupBox->Location = System::Drawing::Point(176, 104);
      this->LanceStatusgroupBox->Name = "LanceStatusgroupBox";
      this->LanceStatusgroupBox->Size = System::Drawing::Size(128, 104);
      this->LanceStatusgroupBox->TabIndex = 6;
      this->LanceStatusgroupBox->TabStop = false;
      this->LanceStatusgroupBox->Text = "Lance Statu";
      // 
      // textBox15
      // 
      this->textBox15->Location = System::Drawing::Point(72, 72);
      this->textBox15->Name = "textBox15";
      this->textBox15->Size = System::Drawing::Size(40, 20);
      this->textBox15->TabIndex = 11;
      // 
      // label40
      // 
      this->label40->BackColor = System::Drawing::SystemColors::ControlLight;
      this->label40->ForeColor = System::Drawing::SystemColors::WindowText;
      this->label40->Location = System::Drawing::Point(8, 64);
      this->label40->Name = "label40";
      this->label40->Size = System::Drawing::Size(56, 32);
      this->label40->TabIndex = 6;
      this->label40->Text = "Lance High :";
      // 
      // radioButton1
      // 
      this->radioButton1->BackColor = System::Drawing::SystemColors::ControlLight;
      this->radioButton1->ForeColor = System::Drawing::SystemColors::WindowText;
      this->radioButton1->Location = System::Drawing::Point(24, 16);
      this->radioButton1->Name = "radioButton1";
      this->radioButton1->Size = System::Drawing::Size(64, 16);
      this->radioButton1->TabIndex = 0;
      this->radioButton1->Text = "Top";
      this->radioButton1->UseVisualStyleBackColor = false;
      // 
      // radioButton2
      // 
      this->radioButton2->BackColor = System::Drawing::SystemColors::ControlLight;
      this->radioButton2->ForeColor = System::Drawing::SystemColors::WindowText;
      this->radioButton2->Location = System::Drawing::Point(24, 40);
      this->radioButton2->Name = "radioButton2";
      this->radioButton2->Size = System::Drawing::Size(64, 16);
      this->radioButton2->TabIndex = 1;
      this->radioButton2->Text = "Down";
      this->radioButton2->UseVisualStyleBackColor = false;
      // 
      // weiterbutton
      // 
      this->weiterbutton->Image = (safe_cast<System::Drawing::Image^  >(resources->GetObject("weiterbutton.Image")));
      this->weiterbutton->Location = System::Drawing::Point(120, 8);
      this->weiterbutton->Name = "weiterbutton";
      this->weiterbutton->Size = System::Drawing::Size(24, 23);
      this->weiterbutton->TabIndex = 8;
      this->weiterbutton->Click += gcnew System::EventHandler(this, &CBofMainForm::weiterbutton_Click);
      // 
      // startbutton
      // 
      this->startbutton->Location = System::Drawing::Point(8, 8);
      this->startbutton->Name = "startbutton";
      this->startbutton->Size = System::Drawing::Size(75, 23);
      this->startbutton->TabIndex = 7;
      this->startbutton->Text = "START";
      this->startbutton->Click += gcnew System::EventHandler(this, &CBofMainForm::startbutton_Click);
      // 
      // textBox14
      // 
      this->textBox14->Location = System::Drawing::Point(152, 8);
      this->textBox14->Name = "textBox14";
      this->textBox14->Size = System::Drawing::Size(196, 20);
      this->textBox14->TabIndex = 6;
      // 
      // stopbutton
      // 
      this->stopbutton->Image = (safe_cast<System::Drawing::Image^  >(resources->GetObject("stopbutton.Image")));
      this->stopbutton->Location = System::Drawing::Point(88, 8);
      this->stopbutton->Name = "stopbutton";
      this->stopbutton->Size = System::Drawing::Size(24, 23);
      this->stopbutton->TabIndex = 5;
      this->stopbutton->Click += gcnew System::EventHandler(this, &CBofMainForm::stopbutton_Click);
      // 
      // splitter1
      // 
      this->splitter1->Dock = System::Windows::Forms::DockStyle::Bottom;
      this->splitter1->Location = System::Drawing::Point(536, 543);
      this->splitter1->Name = "splitter1";
      this->splitter1->Size = System::Drawing::Size(472, 3);
      this->splitter1->TabIndex = 4;
      this->splitter1->TabStop = false;
      // 
      // panel5
      // 
      this->panel5->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panel5->Controls->Add(this->startbutton);
      this->panel5->Controls->Add(this->stopbutton);
      this->panel5->Controls->Add(this->weiterbutton);
      this->panel5->Controls->Add(this->textBox14);
      this->panel5->Dock = System::Windows::Forms::DockStyle::Top;
      this->panel5->Location = System::Drawing::Point(536, 0);
      this->panel5->Name = "panel5";
      this->panel5->Size = System::Drawing::Size(472, 40);
      this->panel5->TabIndex = 5;
      // 
      // timer1
      // 
      this->timer1->Interval = 1000;
      this->timer1->SynchronizingObject = this;
      this->timer1->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &CBofMainForm::timer_Elapsed);
      // 
      // CBofMainForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(1008, 746);
      this->Controls->Add(this->panel5);
      this->Controls->Add(this->splitter1);
      this->Controls->Add(this->panel4);
      this->Controls->Add(this->panel3);
      this->Controls->Add(this->panel2);
      this->Controls->Add(this->panel1);
      this->Location = System::Drawing::Point(0, 40);
      this->Name = "CBofMainForm";
      this->Text = "CBofMainForm";
      this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
      this->Load += gcnew System::EventHandler(this, &CBofMainForm::onLoad);
      this->Closed += gcnew System::EventHandler(this, &CBofMainForm::onClosed);
      this->Closing += gcnew System::ComponentModel::CancelEventHandler(this, &CBofMainForm::onClosing);
      this->panel1->ResumeLayout(false);
      this->groupBox3->ResumeLayout(false);
      this->groupBox3->PerformLayout();
      this->groupBox1->ResumeLayout(false);
      this->panel2->ResumeLayout(false);
      this->panel2->PerformLayout();
      this->panel6->ResumeLayout(false);
      this->groupBox2->ResumeLayout(false);
      this->groupBox2->PerformLayout();
      this->groupBox4->ResumeLayout(false);
      this->groupBox4->PerformLayout();
      this->groupBox5->ResumeLayout(false);
      this->groupBox6->ResumeLayout(false);
      this->groupBox6->PerformLayout();
      this->groupBox7->ResumeLayout(false);
      this->groupBox7->PerformLayout();
      this->groupBox8->ResumeLayout(false);
      this->groupBox8->PerformLayout();
      this->groupBox9->ResumeLayout(false);
      this->groupBox9->PerformLayout();
      this->groupBox10->ResumeLayout(false);
      this->groupBox10->PerformLayout();
      (safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
      this->panel3->ResumeLayout(false);
      this->FreespacegroupBox->ResumeLayout(false);
      this->FreespacegroupBox->PerformLayout();
      this->SampleTakengroupBox->ResumeLayout(false);
      this->SampleTakengroupBox->PerformLayout();
      this->TappinggroupBox->ResumeLayout(false);
      this->TappinggroupBox->PerformLayout();
      this->DeslagginggroupBox->ResumeLayout(false);
      this->DeslagginggroupBox->PerformLayout();
      this->GasStatusgroupBox->ResumeLayout(false);
      (safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown3))->EndInit();
      (safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown2))->EndInit();
      (safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
      this->WaterGasgroupBox->ResumeLayout(false);
      this->WaterGasgroupBox->PerformLayout();
      this->GasModelgroupBox->ResumeLayout(false);
      this->GasModelgroupBox->PerformLayout();
      this->panel4->ResumeLayout(false);
      this->BlowStartgroupBox->ResumeLayout(false);
      this->BlowStartgroupBox->PerformLayout();
      this->HMCgroupBox->ResumeLayout(false);
      this->HMCgroupBox->PerformLayout();
      this->ReadyforBlowgroupBox->ResumeLayout(false);
      this->HeatgroupBox->ResumeLayout(false);
      this->HeatgroupBox->PerformLayout();
      this->TlgHeadStatusgroupBox->ResumeLayout(false);
      this->TlgHeadStatusgroupBox->PerformLayout();
      this->ConposgroupBox->ResumeLayout(false);
      this->ConposgroupBox->PerformLayout();
      this->lanceblowstatusgroupBox->ResumeLayout(false);
      this->lanceblowstatusgroupBox->PerformLayout();
      this->LanceStatusgroupBox->ResumeLayout(false);
      this->LanceStatusgroupBox->PerformLayout();
      this->panel5->ResumeLayout(false);
      this->panel5->PerformLayout();
      (safe_cast<System::ComponentModel::ISupportInitialize^  >(this->timer1))->EndInit();
      this->ResumeLayout(false);

    }		


    
    //...System private Funktion
    private: System::Void onLoad(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void onClosed(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void onClosing(System::Object ^  sender, System::ComponentModel::CancelEventArgs ^  e);
    private: System::Void startbutton_Click(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void stopbutton_Click(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void weiterbutton_Click(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void Sendbutton_Click(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void Receivenbutton_Click(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void TlgHeadbutton_Click(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void sendeTlgnbutton_Click(System::Object ^  sender, System::EventArgs ^  e);
    private: System::Void buttonMakeTlg_Click(System::Object ^  sender, System::EventArgs ^  e);     
         
    //...Prozess Kontrolle Button
    /**1.Heat Announce**/
    private: System::Void buttonHA_Click(System::Object ^  sender, System::EventArgs ^  e);
    /**2.Converter in up Position**/
    private: System::Void buttonCIP_Click(System::Object ^  sender, System::EventArgs ^  e);
    /**3.Scrap Charging**/
    private: System::Void buttonSC_Click(System::Object ^  sender, System::EventArgs ^  e);
    /**4.Prozess Stirring start**/ 
    private: System::Void buttonSS_Click(System::Object ^  sender, System::EventArgs ^  e);
    /**5.Prozess Hot Metal Charging**/      
    private: System::Void button5_Click(System::Object ^  sender, System::EventArgs ^  e);
    /**6.Heat Start**/
    private: System::Void buttonHS_Click(System::Object ^  sender, System::EventArgs ^  e);
    /**7.Lance down**/
    private: System::Void buttonLD_Click(System::Object ^  sender, System::EventArgs ^  e);
    /**8.Blow Start**/
    private: System::Void buttonBS_Click(System::Object ^  sender, System::EventArgs ^  e);
    /**9.Blow End**/
    private: System::Void buttonBE_Click(System::Object ^  sender, System::EventArgs ^  e);
    /**10.Temperatur Measurement**/
    private: System::Void buttonTM_Click(System::Object ^  sender, System::EventArgs ^  e);
    /**11.Reblow start**/
    private: System::Void buttonRS_Click(System::Object ^  sender, System::EventArgs ^  e); 
    /**12.Reblow end**/
    private: System::Void buttonRE_Click(System::Object ^  sender, System::EventArgs ^  e);
    /**13.Lance up**/
    private: System::Void buttonLU_Click(System::Object ^  sender, System::EventArgs ^  e);
    /**14.Tapping start**/
    private: System::Void buttonTS_Click(System::Object ^  sender, System::EventArgs ^  e);
    /**15.Tapping end**/
    private: System::Void buttonTE_Click(System::Object ^  sender, System::EventArgs ^  e);
    /**16.Delslag start**/
    private: System::Void buttonDS_Click(System::Object ^  sender, System::EventArgs ^  e);
    /**17.Delslag end**/
    private: System::Void buttonDE_Click(System::Object ^  sender, System::EventArgs ^  e);
    /**18.Stirring end**/
    private: System::Void buttonSE_Click(System::Object ^  sender, System::EventArgs ^  e);
    
    //...Telegramm senden Timer
    private: System::Void timer_Elapsed(System::Object ^  sender, System::Timers::ElapsedEventArgs ^  e);
   
    //...private Funktion
    private: void ThreadTask();
    private: void repeat();
    //private: void animation(); 
    private: int file_exists(char  *filename);       
    private: char* stringtochar(String ^str);
    private: L1SimulatorControls::Led ^ getled(int i);
    private: void initgroupboxF();
    private: void initgroupboxT();
    private: void HeatStahide();
    private: void HeatStadisplay();
    private: void prozessbuttonEnableF();
    private: void prozessbuttonEnableT();
    private: void maketlgbody();
  };
}