#pragma once

#include "CMessageForm.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

//#pragma warning( disable : 4691 )
//#pragma warning( disable : 4945 )

namespace simulator
{
	/// <summary> 
	/// Summary for CAnalyzeSubElemForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CAnalyzeSubElemForm : public System::Windows::Forms::Form
	{
	public: 
		CAnalyzeSubElemForm(Panel^ parent,double TlgNullTime,double maxTime)
		{
			InitializeComponent();
      initViewComponent(parent,TlgNullTime,maxTime);
		}
    
    void setStartTime(double TlgTime);
    void addToSeries(String^ tlgName,String^ elemName,double tlgTime,double elemValue);
    void removeFromSeries(String^ TlgName,String^ elemName);
    void setPointerOfMessage(CMessageForm^ MessageForm);
    String^ getSeriesValueNames(int index);
    void set3DMode(bool mode);
    bool get3DMode(void);
    void removeAll();
    void setCursorTool(bool mode);
   

	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
  private: System::ComponentModel::IContainer^  components;
  protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


    double minTime;
    double maxTime;
    CMessageForm^ MessageForm;
    Steema::TeeChart::Commander^  commander1;
    Steema::TeeChart::TChart^  axTChartValueDiagram;
    void createNewSeries(String^ tlgName,String^ elemName);
    void initViewComponent(Panel^ parent,double TlgNullTime,double maxTime);

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->components = (gcnew System::ComponentModel::Container());
      this->commander1 = (gcnew Steema::TeeChart::Commander());
      this->axTChartValueDiagram = (gcnew Steema::TeeChart::TChart());
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
      this->commander1->Size = System::Drawing::Size(371, 37);
      this->commander1->TabIndex = 0;
      // 
      // axTChartValueDiagram
      // 
      // 
      // 
      // 
      this->axTChartValueDiagram->Aspect->ColorPaletteIndex = 9;
      this->axTChartValueDiagram->Aspect->ElevationFloat = 345;
      this->axTChartValueDiagram->Aspect->RotationFloat = 345;
      // 
      // 
      // 
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->Bottom->Automatic = true;
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->Bottom->Grid->Color = System::Drawing::Color::Gray;
      this->axTChartValueDiagram->Axes->Bottom->Grid->Style = System::Drawing::Drawing2D::DashStyle::Dash;
      this->axTChartValueDiagram->Axes->Bottom->Grid->ZPosition = 0;
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->Bottom->Ticks->Length = 2;
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->Depth->Automatic = true;
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->Depth->Grid->Color = System::Drawing::Color::Gray;
      this->axTChartValueDiagram->Axes->Depth->Grid->Style = System::Drawing::Drawing2D::DashStyle::Dash;
      this->axTChartValueDiagram->Axes->Depth->Grid->ZPosition = 0;
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->Depth->Ticks->Length = 2;
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->DepthTop->Automatic = true;
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->DepthTop->Grid->Color = System::Drawing::Color::Gray;
      this->axTChartValueDiagram->Axes->DepthTop->Grid->Style = System::Drawing::Drawing2D::DashStyle::Dash;
      this->axTChartValueDiagram->Axes->DepthTop->Grid->ZPosition = 0;
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->DepthTop->Ticks->Length = 2;
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->Left->Automatic = true;
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->Left->Grid->Color = System::Drawing::Color::Gray;
      this->axTChartValueDiagram->Axes->Left->Grid->Style = System::Drawing::Drawing2D::DashStyle::Dash;
      this->axTChartValueDiagram->Axes->Left->Grid->ZPosition = 0;
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->Left->Ticks->Length = 2;
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->Right->Automatic = true;
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->Right->Grid->Color = System::Drawing::Color::Gray;
      this->axTChartValueDiagram->Axes->Right->Grid->Style = System::Drawing::Drawing2D::DashStyle::Dash;
      this->axTChartValueDiagram->Axes->Right->Grid->ZPosition = 0;
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->Right->Ticks->Length = 2;
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->Top->Automatic = true;
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->Top->Grid->Color = System::Drawing::Color::Gray;
      this->axTChartValueDiagram->Axes->Top->Grid->Style = System::Drawing::Drawing2D::DashStyle::Dash;
      this->axTChartValueDiagram->Axes->Top->Grid->ZPosition = 0;
      // 
      // 
      // 
      this->axTChartValueDiagram->Axes->Top->Ticks->Length = 2;
      this->axTChartValueDiagram->Dock = System::Windows::Forms::DockStyle::Fill;
      // 
      // 
      //
			this->axTChartValueDiagram->Header->Lines= (gcnew array< System::String^>(1) {""});
      this->axTChartValueDiagram->Header->Visible = false;
      // 
      // 
      // 
      // 
      // 
      // 
      // 
      // 
      // 
      this->axTChartValueDiagram->Legend->Gradient->EndColor = System::Drawing::Color::Yellow;
      this->axTChartValueDiagram->Legend->Gradient->MiddleColor = System::Drawing::Color::Empty;
      this->axTChartValueDiagram->Legend->Gradient->StartColor = System::Drawing::Color::White;
      this->axTChartValueDiagram->Legend->Gradient->Visible = true;
      this->axTChartValueDiagram->Legend->LegendStyle = Steema::TeeChart::LegendStyles::Series;
      // 
      // 
      // 
      // 
      // 
      // 
      this->axTChartValueDiagram->Legend->Shadow->Brush->Color = System::Drawing::Color::FromArgb((System::Int32)(System::Byte)0, (System::Int32)(System::Byte)0, 
        (System::Int32)(System::Byte)0);
      this->axTChartValueDiagram->Legend->Shadow->Visible = true;
      // 
      // 
      // 
      // 
      // 
      // 
      this->axTChartValueDiagram->Legend->Title->Font->Bold = true;
      // 
      // 
      // 
      this->axTChartValueDiagram->Legend->Title->Pen->Visible = false;
      this->axTChartValueDiagram->Location = System::Drawing::Point(0, 37);
      this->axTChartValueDiagram->Name = "axTChartValueDiagram";
      // 
      // 
      // 
      // 
      // 
      // 
      this->axTChartValueDiagram->Panel->Bevel->Outer = Steema::TeeChart::Drawing::BevelStyles::None;
      this->axTChartValueDiagram->Panel->BorderRound = 10;
      // 
      // 
      // 
      // 
      // 
      // 
      this->axTChartValueDiagram->Panel->Gradient->EndColor = System::Drawing::Color::DarkGray;
      this->axTChartValueDiagram->Panel->Gradient->MiddleColor = System::Drawing::Color::Empty;
      this->axTChartValueDiagram->Panel->Gradient->StartColor = System::Drawing::Color::White;
      this->axTChartValueDiagram->Panel->Gradient->Visible = true;
      // 
      // 
      // 
      this->axTChartValueDiagram->Panel->Pen->Color = System::Drawing::Color::Navy;
      this->axTChartValueDiagram->Panel->Pen->Visible = true;
      this->axTChartValueDiagram->Panel->Pen->Width = 6;
      // 
      // 
      // 
      this->axTChartValueDiagram->Panel->Shadow->Height = 0;
      this->axTChartValueDiagram->Panel->Shadow->Width = 0;
      this->axTChartValueDiagram->Size = System::Drawing::Size(371, 242);
      this->axTChartValueDiagram->TabIndex = 1;
      // 
      // 
      // 
      // 
      // 
      // 
      this->axTChartValueDiagram->Walls->Back->AutoHide = false;
      // 
      // 
      // 
      this->axTChartValueDiagram->Walls->Bottom->AutoHide = false;
      // 
      // 
      // 
      this->axTChartValueDiagram->Walls->Left->AutoHide = false;
      // 
      // 
      // 
      this->axTChartValueDiagram->Walls->Left->Brush->Color = System::Drawing::Color::FromArgb((System::Int32)(System::Byte)255, (System::Int32)(System::Byte)255, 
        (System::Int32)(System::Byte)128);
      // 
      // 
      // 
      this->axTChartValueDiagram->Walls->Right->AutoHide = false;
      // 
      // 
      // 
      this->axTChartValueDiagram->Walls->Right->Brush->Color = System::Drawing::Color::Silver;
      // 
      // CAnalyzeSubElemForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(371, 279);
      this->Controls->Add(this->axTChartValueDiagram);
      this->Controls->Add(this->commander1);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
      this->Name = "CAnalyzeSubElemForm";
      this->Text = "CAnalyzeSubElemForm";
      this->ResumeLayout(false);
      this->PerformLayout();

    }		
	};
}