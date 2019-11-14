#pragma once

#include "CItemBaseContainerWrapper.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
//--------------------------------------
public delegate void SelectProzessEvent(CItemWrapper^ wrp);
public delegate void SelectAnimationEvent(String^ pname);

namespace simulator
{
	/// <summary> 
	/// Summary for CBofProzessForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CBofProzessForm : public System::Windows::Forms::Form
	{
	public: 
		CBofProzessForm(void)
		{
			InitializeComponent();
      prozessevent = nullptr;
      animationevent = nullptr;
		}
    CBofProzessForm(Panel^ parent);    
    void setProzessEvent(SelectProzessEvent^ event);

	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
  private: System::Windows::Forms::GroupBox ^  groupBox1;
  private: System::Windows::Forms::GroupBox ^  groupBox2;
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

  private: System::Windows::Forms::Button ^  buttonSS;
  private: System::Windows::Forms::Button ^  buttonCIP;
  private: System::Windows::Forms::Button ^  buttonHA;
  private: System::Windows::Forms::Button ^  buttonSC;
  private: System::Windows::Forms::Button ^  buttonHMC;
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
  
 
  private: System::Void buttonHMC_Click(System::Object ^  sender, System::EventArgs ^  e);

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
   
    CItemBaseContainerWrapper^ TlgContainer;
    SelectProzessEvent^ prozessevent;
    SelectAnimationEvent^ animationevent;
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->groupBox1 = gcnew System::Windows::Forms::GroupBox();
      this->groupBox2 = gcnew System::Windows::Forms::GroupBox();
      this->label18 = gcnew System::Windows::Forms::Label();
      this->label17 = gcnew System::Windows::Forms::Label();
      this->label16 = gcnew System::Windows::Forms::Label();
      this->label15 = gcnew System::Windows::Forms::Label();
      this->label14 = gcnew System::Windows::Forms::Label();
      this->label13 = gcnew System::Windows::Forms::Label();
      this->buttonSE = gcnew System::Windows::Forms::Button();
      this->buttonDE = gcnew System::Windows::Forms::Button();
      this->buttonDS = gcnew System::Windows::Forms::Button();
      this->buttonTE = gcnew System::Windows::Forms::Button();
      this->buttonTS = gcnew System::Windows::Forms::Button();
      this->led18 = gcnew L1SimulatorControls::Led();
      this->led17 = gcnew L1SimulatorControls::Led();
      this->led16 = gcnew L1SimulatorControls::Led();
      this->led15 = gcnew L1SimulatorControls::Led();
      this->led14 = gcnew L1SimulatorControls::Led();
      this->buttonLU = gcnew System::Windows::Forms::Button();
      this->led13 = gcnew L1SimulatorControls::Led();
      this->label12 = gcnew System::Windows::Forms::Label();
      this->label11 = gcnew System::Windows::Forms::Label();
      this->label10 = gcnew System::Windows::Forms::Label();
      this->label9 = gcnew System::Windows::Forms::Label();
      this->label8 = gcnew System::Windows::Forms::Label();
      this->label7 = gcnew System::Windows::Forms::Label();
      this->label6 = gcnew System::Windows::Forms::Label();
      this->label5 = gcnew System::Windows::Forms::Label();
      this->label4 = gcnew System::Windows::Forms::Label();
      this->label3 = gcnew System::Windows::Forms::Label();
      this->label2 = gcnew System::Windows::Forms::Label();
      this->label1 = gcnew System::Windows::Forms::Label();
      this->buttonRE = gcnew System::Windows::Forms::Button();
      this->buttonRS = gcnew System::Windows::Forms::Button();
      this->buttonTM = gcnew System::Windows::Forms::Button();
      this->buttonBE = gcnew System::Windows::Forms::Button();
      this->buttonBS = gcnew System::Windows::Forms::Button();
      this->buttonLD = gcnew System::Windows::Forms::Button();
      this->buttonHS = gcnew System::Windows::Forms::Button();
      this->buttonHMC = gcnew System::Windows::Forms::Button();
      this->buttonSS = gcnew System::Windows::Forms::Button();
      this->buttonCIP = gcnew System::Windows::Forms::Button();
      this->buttonHA = gcnew System::Windows::Forms::Button();
      this->led12 = gcnew L1SimulatorControls::Led();
      this->led11 = gcnew L1SimulatorControls::Led();
      this->led10 = gcnew L1SimulatorControls::Led();
      this->led9 = gcnew L1SimulatorControls::Led();
      this->led8 = gcnew L1SimulatorControls::Led();
      this->led7 = gcnew L1SimulatorControls::Led();
      this->led6 = gcnew L1SimulatorControls::Led();
      this->led5 = gcnew L1SimulatorControls::Led();
      this->led4 = gcnew L1SimulatorControls::Led();
      this->led3 = gcnew L1SimulatorControls::Led();
      this->led2 = gcnew L1SimulatorControls::Led();
      this->led1 = gcnew L1SimulatorControls::Led();
      this->buttonSC = gcnew System::Windows::Forms::Button();
      this->groupBox1->SuspendLayout();
      this->groupBox2->SuspendLayout();
      this->SuspendLayout();
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->groupBox2);
      this->groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
      this->groupBox1->Location = System::Drawing::Point(0, 0);
      this->groupBox1->Name = "groupBox1";
      this->groupBox1->Size = System::Drawing::Size(208, 404);
      this->groupBox1->TabIndex = 0;
      this->groupBox1->TabStop = false;
      this->groupBox1->Text = "groupBox1";
      // 
      // groupBox2
      // 
      this->groupBox2->Controls->Add(this->label18);
      this->groupBox2->Controls->Add(this->label17);
      this->groupBox2->Controls->Add(this->label16);
      this->groupBox2->Controls->Add(this->label15);
      this->groupBox2->Controls->Add(this->label14);
      this->groupBox2->Controls->Add(this->label13);
      this->groupBox2->Controls->Add(this->buttonSE);
      this->groupBox2->Controls->Add(this->buttonDE);
      this->groupBox2->Controls->Add(this->buttonDS);
      this->groupBox2->Controls->Add(this->buttonTE);
      this->groupBox2->Controls->Add(this->buttonTS);
      this->groupBox2->Controls->Add(this->led18);
      this->groupBox2->Controls->Add(this->led17);
      this->groupBox2->Controls->Add(this->led16);
      this->groupBox2->Controls->Add(this->led15);
      this->groupBox2->Controls->Add(this->led14);
      this->groupBox2->Controls->Add(this->buttonLU);
      this->groupBox2->Controls->Add(this->led13);
      this->groupBox2->Controls->Add(this->label12);
      this->groupBox2->Controls->Add(this->label11);
      this->groupBox2->Controls->Add(this->label10);
      this->groupBox2->Controls->Add(this->label9);
      this->groupBox2->Controls->Add(this->label8);
      this->groupBox2->Controls->Add(this->label7);
      this->groupBox2->Controls->Add(this->label6);
      this->groupBox2->Controls->Add(this->label5);
      this->groupBox2->Controls->Add(this->label4);
      this->groupBox2->Controls->Add(this->label3);
      this->groupBox2->Controls->Add(this->label2);
      this->groupBox2->Controls->Add(this->label1);
      this->groupBox2->Controls->Add(this->buttonRE);
      this->groupBox2->Controls->Add(this->buttonRS);
      this->groupBox2->Controls->Add(this->buttonTM);
      this->groupBox2->Controls->Add(this->buttonBE);
      this->groupBox2->Controls->Add(this->buttonBS);
      this->groupBox2->Controls->Add(this->buttonLD);
      this->groupBox2->Controls->Add(this->buttonHS);
      this->groupBox2->Controls->Add(this->buttonHMC);
      this->groupBox2->Controls->Add(this->buttonSS);
      this->groupBox2->Controls->Add(this->buttonCIP);
      this->groupBox2->Controls->Add(this->buttonHA);
      this->groupBox2->Controls->Add(this->led12);
      this->groupBox2->Controls->Add(this->led11);
      this->groupBox2->Controls->Add(this->led10);
      this->groupBox2->Controls->Add(this->led9);
      this->groupBox2->Controls->Add(this->led8);
      this->groupBox2->Controls->Add(this->led7);
      this->groupBox2->Controls->Add(this->led6);
      this->groupBox2->Controls->Add(this->led5);
      this->groupBox2->Controls->Add(this->led4);
      this->groupBox2->Controls->Add(this->led3);
      this->groupBox2->Controls->Add(this->led2);
      this->groupBox2->Controls->Add(this->led1);
      this->groupBox2->Controls->Add(this->buttonSC);
      this->groupBox2->Location = System::Drawing::Point(4, 16);
      this->groupBox2->Name = "groupBox2";
      this->groupBox2->Size = System::Drawing::Size(200, 320);
      this->groupBox2->TabIndex = 19;
      this->groupBox2->TabStop = false;
      this->groupBox2->Text = "Event";
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
      // 
      // buttonDE
      // 
      this->buttonDE->Location = System::Drawing::Point(24, 280);
      this->buttonDE->Name = "buttonDE";
      this->buttonDE->Size = System::Drawing::Size(8, 8);
      this->buttonDE->TabIndex = 50;
      this->buttonDE->Text = "button17";
      // 
      // buttonDS
      // 
      this->buttonDS->Location = System::Drawing::Point(24, 264);
      this->buttonDS->Name = "buttonD";
      this->buttonDS->Size = System::Drawing::Size(8, 8);
      this->buttonDS->TabIndex = 49;
      this->buttonDS->Text = "button16";
      // 
      // buttonTE
      // 
      this->buttonTE->Location = System::Drawing::Point(24, 248);
      this->buttonTE->Name = "buttonTE";
      this->buttonTE->Size = System::Drawing::Size(8, 8);
      this->buttonTE->TabIndex = 48;
      this->buttonTE->Text = "button15";
      // 
      // buttonTS
      // 
      this->buttonTS->Location = System::Drawing::Point(24, 232);
      this->buttonTS->Name = "buttonT";
      this->buttonTS->Size = System::Drawing::Size(8, 8);
      this->buttonTS->TabIndex = 47;
      this->buttonTS->Text = "button14";
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
      // 
      // buttonRS
      // 
      this->buttonRS->Location = System::Drawing::Point(24, 184);
      this->buttonRS->Name = "buttonR";
      this->buttonRS->Size = System::Drawing::Size(8, 8);
      this->buttonRS->TabIndex = 23;
      this->buttonRS->Text = "button11";
      // 
      // buttonTM
      // 
      this->buttonTM->Location = System::Drawing::Point(24, 168);
      this->buttonTM->Name = "buttonTM";
      this->buttonTM->Size = System::Drawing::Size(8, 8);
      this->buttonTM->TabIndex = 22;
      this->buttonTM->Text = "button10";
      // 
      // buttonBE
      // 
      this->buttonBE->Location = System::Drawing::Point(24, 152);
      this->buttonBE->Name = "buttonBE";
      this->buttonBE->Size = System::Drawing::Size(8, 8);
      this->buttonBE->TabIndex = 21;
      this->buttonBE->Text = "button9";
      // 
      // buttonBS
      // 
      this->buttonBS->Location = System::Drawing::Point(24, 136);
      this->buttonBS->Name = "buttonB";
      this->buttonBS->Size = System::Drawing::Size(8, 8);
      this->buttonBS->TabIndex = 20;
      this->buttonBS->Text = "button8";
      // 
      // buttonLD
      // 
      this->buttonLD->Location = System::Drawing::Point(24, 120);
      this->buttonLD->Name = "buttonLD";
      this->buttonLD->Size = System::Drawing::Size(8, 8);
      this->buttonLD->TabIndex = 19;
      this->buttonLD->Text = "button7";
      // 
      // buttonHS
      // 
      this->buttonHS->Location = System::Drawing::Point(24, 104);
      this->buttonHS->Name = "buttonH";
      this->buttonHS->Size = System::Drawing::Size(8, 8);
      this->buttonHS->TabIndex = 18;
      this->buttonHS->Text = "button6";
      // 
      // buttonHMC
      // 
      this->buttonHMC->Location = System::Drawing::Point(24, 88);
      this->buttonHMC->Name = "buttonHMC";
      this->buttonHMC->Size = System::Drawing::Size(8, 8);
      this->buttonHMC->TabIndex = 17;
      this->buttonHMC->Text = "button5";
      this->buttonHMC->Click += gcnew System::EventHandler(this, &CBofProzessForm::buttonHMC_Click);
      // 
      // buttonSS
      // 
      this->buttonSS->Location = System::Drawing::Point(24, 72);
      this->buttonSS->Name = "buttonS";
      this->buttonSS->Size = System::Drawing::Size(8, 8);
      this->buttonSS->TabIndex = 16;
      this->buttonSS->Text = "button4";
      // 
      // buttonCIP
      // 
      this->buttonCIP->Location = System::Drawing::Point(24, 40);
      this->buttonCIP->Name = "buttonCIP";
      this->buttonCIP->Size = System::Drawing::Size(8, 8);
      this->buttonCIP->TabIndex = 14;
      this->buttonCIP->Text = "button2";
      // 
      // buttonHA
      // 
      this->buttonHA->Location = System::Drawing::Point(24, 24);
      this->buttonHA->Name = "buttonHA";
      this->buttonHA->Size = System::Drawing::Size(8, 8);
      this->buttonHA->TabIndex = 13;
      this->buttonHA->Text = "button1";
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
      // 
      // CBofProzessForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(208, 404);
      this->Controls->Add(this->groupBox1);
      this->Name = "CBofProzessForm";
      this->Text = "CBofProzessForm";
      this->groupBox1->ResumeLayout(false);
      this->groupBox2->ResumeLayout(false);
      this->ResumeLayout(false);

    }		

    
  
           
};
}