#pragma once

#include "CMessageForm.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
//
//#pragma warning( disable : 4691 )
//#pragma warning( disable : 4945 )

namespace simulator
{
	/// <summary> 
	/// Summary for CAnalyzeTlgForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CAnalyzeTlgForm : public System::Windows::Forms::Form
	{
	public: 
		CAnalyzeTlgForm(Panel^ parent,double TlgNullTime,double maxTime)
		{
			InitializeComponent();
      initViewComponent(parent,TlgNullTime,maxTime);
		}
  
  public:
    void addToSeries(String^ TlgName,double TlgTime,bool newTlg);
    ArrayList^ removeFromSeries(String^ TlgName);
    void createNewSeries(String^ TlgName);
    void setPointerOfMessage(CMessageForm^ MessageForm);
    void setStartTime(double TlgTime);
    String^ getSeriesTlgNames(int index);
    void set3DMode(bool mode);
    bool get3DMode(void);
    void removeAll(void);
    void setCursor(bool edit);
    void setCustomAxisMode(bool mode);
        
	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
  private: 
           //AxTeeChart::AxTChart^ axTChartTlgDiagram;
           double minTime;
           double maxTime;
           Hashtable^ numOfSeries;
           double leftAxisMax;
           CMessageForm^ MessageForm;
           void ResumeZoom();
           System::Void axTChartTlgDiagram_Zoomed(System::Object^  sender, System::EventArgs^  e); 
           System::Void axTChartTlgDiagram_UndoneZoom(System::Object^  sender, System::EventArgs^  e);
 
  private: Steema::TeeChart::TChart^  axTChartTlgDiagram;
  private: Steema::TeeChart::Commander^  commander1;
  private: System::ComponentModel::IContainer^  components;

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
      this->commander1 = (gcnew Steema::TeeChart::Commander());
      this->axTChartTlgDiagram = (gcnew Steema::TeeChart::TChart());
      this->SuspendLayout();
      // 
      // commander1
      // 
      this->commander1->Appearance = System::Windows::Forms::ToolBarAppearance::Flat;
      this->commander1->DropDownArrows = true;
      this->commander1->LabelValues = true;
      this->commander1->Location = System::Drawing::Point(0, 0);
      this->commander1->Name = "commander1";
      this->commander1->ShowToolTips = true;
      this->commander1->Size = System::Drawing::Size(543, 37);
      this->commander1->TabIndex = 0;
      // 
      // axTChartTlgDiagram
      // 
      // 
      // 
      // 
      this->axTChartTlgDiagram->Aspect->Chart3DPercent = 0;
      this->axTChartTlgDiagram->Aspect->ElevationFloat = 345;
      this->axTChartTlgDiagram->Aspect->RotationFloat = 345;
      // 
      // 
      // 
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->Bottom->Automatic = true;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->Bottom->AxisPen->Color = System::Drawing::Color::FromArgb((System::Int32)(System::Byte)127, (System::Int32)(System::Byte)0, 
        (System::Int32)(System::Byte)0, (System::Int32)(System::Byte)255);
      this->axTChartTlgDiagram->Axes->Bottom->AxisPen->Transparency = 50;
      this->axTChartTlgDiagram->Axes->Bottom->AxisPen->Width = 1;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->Bottom->Grid->Style = System::Drawing::Drawing2D::DashStyle::Dash;
      this->axTChartTlgDiagram->Axes->Bottom->Grid->ZPosition = 0;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->Bottom->Ticks->Length = 2;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->Depth->Automatic = true;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->Depth->Grid->Style = System::Drawing::Drawing2D::DashStyle::Dash;
      this->axTChartTlgDiagram->Axes->Depth->Grid->ZPosition = 0;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->Depth->Ticks->Length = 2;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->DepthTop->Automatic = true;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->DepthTop->Grid->Style = System::Drawing::Drawing2D::DashStyle::Dash;
      this->axTChartTlgDiagram->Axes->DepthTop->Grid->ZPosition = 0;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->DepthTop->Ticks->Length = 2;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->Left->Automatic = true;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->Left->Grid->Style = System::Drawing::Drawing2D::DashStyle::Dash;
      this->axTChartTlgDiagram->Axes->Left->Grid->ZPosition = 0;
      this->axTChartTlgDiagram->Axes->Left->MinimumOffset = 5;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->Left->Ticks->Length = 2;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->Right->Automatic = true;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->Right->Grid->Style = System::Drawing::Drawing2D::DashStyle::Dash;
      this->axTChartTlgDiagram->Axes->Right->Grid->ZPosition = 0;
      this->axTChartTlgDiagram->Axes->Right->MinimumOffset = 5;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->Right->Ticks->Length = 2;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->Top->Automatic = true;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->Top->Grid->Style = System::Drawing::Drawing2D::DashStyle::Dash;
      this->axTChartTlgDiagram->Axes->Top->Grid->ZPosition = 0;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Axes->Top->Ticks->Length = 2;
      this->axTChartTlgDiagram->BackColor = System::Drawing::Color::Transparent;
      this->axTChartTlgDiagram->Cursor = System::Windows::Forms::Cursors::Default;
      this->axTChartTlgDiagram->Dock = System::Windows::Forms::DockStyle::Fill;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Header->Lines = (gcnew array< System::String^>(1) {""});
      this->axTChartTlgDiagram->Header->Visible = false;
      // 
      // 
      // 
      // 
      // 
      // 
      // 
      // 
      // 
      this->axTChartTlgDiagram->Legend->Gradient->EndColor = System::Drawing::Color::Yellow;
      this->axTChartTlgDiagram->Legend->Gradient->MiddleColor = System::Drawing::Color::Empty;
      this->axTChartTlgDiagram->Legend->Gradient->StartColor = System::Drawing::Color::White;
      this->axTChartTlgDiagram->Legend->Gradient->Visible = true;
      this->axTChartTlgDiagram->Legend->LegendStyle = Steema::TeeChart::LegendStyles::Series;
      // 
      // 
      // 
      // 
      // 
      // 
      this->axTChartTlgDiagram->Legend->Shadow->Brush->Color = System::Drawing::Color::FromArgb((System::Int32)(System::Byte)0, (System::Int32)(System::Byte)0, 
        (System::Int32)(System::Byte)0);
      this->axTChartTlgDiagram->Legend->Shadow->Visible = true;
      // 
      // 
      // 
      // 
      // 
      // 
      this->axTChartTlgDiagram->Legend->Title->Font->Bold = true;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Legend->Title->Pen->Visible = false;
      this->axTChartTlgDiagram->Location = System::Drawing::Point(0, 37);
      this->axTChartTlgDiagram->Name = "axTChartTlgDiagram";
      // 
      // 
      // 
      // 
      // 
      // 
      this->axTChartTlgDiagram->Panel->Bevel->Outer = Steema::TeeChart::Drawing::BevelStyles::None;
      this->axTChartTlgDiagram->Panel->BorderRound = 10;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Panel->Brush->Color = System::Drawing::Color::FromArgb((System::Int32)(System::Byte)236, (System::Int32)(System::Byte)233, 
        (System::Int32)(System::Byte)216);
      // 
      // 
      // 
      this->axTChartTlgDiagram->Panel->Gradient->EndColor = System::Drawing::Color::DarkGray;
      this->axTChartTlgDiagram->Panel->Gradient->MiddleColor = System::Drawing::Color::Empty;
      this->axTChartTlgDiagram->Panel->Gradient->StartColor = System::Drawing::Color::White;
      this->axTChartTlgDiagram->Panel->Gradient->Visible = true;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Panel->Pen->Color = System::Drawing::Color::Navy;
      this->axTChartTlgDiagram->Panel->Pen->Visible = true;
      this->axTChartTlgDiagram->Panel->Pen->Width = 6;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Panel->Shadow->Height = 0;
      this->axTChartTlgDiagram->Panel->Shadow->Width = 0;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Panning->Allow = Steema::TeeChart::ScrollModes::None;
      this->axTChartTlgDiagram->Size = System::Drawing::Size(543, 374);
      this->axTChartTlgDiagram->TabIndex = 1;
      // 
      // 
      // 
      // 
      // 
      // 
      this->axTChartTlgDiagram->Walls->Back->AutoHide = false;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Walls->Bottom->AutoHide = false;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Walls->Left->AutoHide = false;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Walls->Left->Brush->Color = System::Drawing::Color::FromArgb((System::Int32)(System::Byte)255, (System::Int32)(System::Byte)255, 
        (System::Int32)(System::Byte)128);
      // 
      // 
      // 
      this->axTChartTlgDiagram->Walls->Right->AutoHide = false;
      // 
      // 
      // 
      this->axTChartTlgDiagram->Walls->Right->Brush->Color = System::Drawing::Color::Silver;
      this->axTChartTlgDiagram->UndoneZoom += gcnew System::EventHandler(this, &CAnalyzeTlgForm::axTChartTlgDiagram_UndoneZoom);
      this->axTChartTlgDiagram->Zoomed += gcnew System::EventHandler(this, &CAnalyzeTlgForm::axTChartTlgDiagram_Zoomed);
      // 
      // CAnalyzeTlgForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(543, 411);
      this->Controls->Add(this->axTChartTlgDiagram);
      this->Controls->Add(this->commander1);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
      this->Name = "CAnalyzeTlgForm";
      this->Text = "CAnalyzeTlgForm";
      this->ResumeLayout(false);
      this->PerformLayout();

    }		
	  void initViewComponent(Panel^ parent,double TlgNullTime,double maxTime);
};
}