#pragma once

//--------------------------------------------------------
#include "CTlgInterfaceWrapper.h"
#include "CInterAssignment.h"
//--------------------------------------------------------
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#undef GetObject

namespace LogFileConversion
{
	/// <summary> 
	/// Summary for CInterConvertForm
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CInterConvertForm : public System::Windows::Forms::Form
	{
	public: 
		CInterConvertForm(void)
		{
			InitializeComponent();
      SourceInter=nullptr;
      DestinationInter=nullptr;
      InterAssignment=nullptr;
      TelColor = System::Drawing::Color::FromKnownColor(KnownColor::InactiveCaption);
			SimpleElemColor = System::Drawing::Color::FromKnownColor(KnownColor::Window);
      ComplexElemColor = System::Drawing::Color::FromKnownColor(KnownColor::Control);
      ComboBoxChose = gcnew ComboBox();
      ComboBoxChose->Width = 160;
      ComboBoxChose->DrawMode = System::Windows::Forms::DrawMode::OwnerDrawFixed;
      ComboBoxChose->Parent = listViewInterConv;
      ComboBoxChose->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
      ComboBoxChose->SelectedIndexChanged += gcnew System::EventHandler(this, &CInterConvertForm::OnSelIndexChange);
      ComboBoxChose->DrawItem += gcnew System::Windows::Forms::DrawItemEventHandler(this, &CInterConvertForm::OnDrawItemComBx);
      ComboBoxChose->Visible = false;
      TopItemIndex=0;
		}
    void setInterAssignment(CInterAssignment^ interAss);
    CInterAssignment^ getInterAssignment();
    void clearAssignment();
    //void updateSourceInterView(CTlgInterfaceWrapper^ inter);
    //void updateDestInterView(CTlgInterfaceWrapper^ inter);
    //---Typs-----------------------------
    enum class NodeTyp{None,Simple,Array,Rekords};
    value struct ItemStateInfoTyp
    {
	    NodeTyp ElemTyp;
      String^ TlgName;
      String^ ElemName;
      bool Extendet;
    };

	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	if (disposing && components)
		//	{
		//		components->Dispose();
		//	}
		//	__super::Dispose(disposing);
		//}
    private: System::Windows::Forms::ListView ^  listViewInterConv;
    private: System::Windows::Forms::ColumnHeader ^  colHeaderInterSource;
    private: System::Windows::Forms::ColumnHeader ^  colHeaderInterDestin;
    private: System::Windows::Forms::ImageList ^  imageListTlg;
    private: System::Windows::Forms::ImageList ^  imageListElem;
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
      this->components = gcnew System::ComponentModel::Container();
      System::Resources::ResourceManager ^  resources = gcnew System::Resources::ResourceManager(LogFileConversion::CInterConvertForm::typeid);
      this->listViewInterConv = gcnew System::Windows::Forms::ListView();
      this->colHeaderInterSource = gcnew System::Windows::Forms::ColumnHeader();
      this->colHeaderInterDestin = gcnew System::Windows::Forms::ColumnHeader();
      this->imageListTlg = gcnew System::Windows::Forms::ImageList(this->components);
      this->imageListElem = gcnew System::Windows::Forms::ImageList(this->components);
      this->SuspendLayout();
      // 
      // listViewInterConv
      // 
      this->listViewInterConv->BorderStyle = System::Windows::Forms::BorderStyle::None;
      this->listViewInterConv->Columns->AddRange(gcnew array< System::Windows::Forms::ColumnHeader^ >(2) {colHeaderInterSource,colHeaderInterDestin});
      this->listViewInterConv->Dock = System::Windows::Forms::DockStyle::Fill;
      this->listViewInterConv->FullRowSelect = true;
      this->listViewInterConv->GridLines = true;
      this->listViewInterConv->Location = System::Drawing::Point(0, 0);
      this->listViewInterConv->MultiSelect = false;
      this->listViewInterConv->Name = "listViewInterConv";
      this->listViewInterConv->Size = System::Drawing::Size(384, 301);
      this->listViewInterConv->SmallImageList = this->imageListTlg;
      this->listViewInterConv->TabIndex = 0;
      this->listViewInterConv->View = System::Windows::Forms::View::Details;
      this->listViewInterConv->Resize += gcnew System::EventHandler(this, &CInterConvertForm::OnResizeListView);
      this->listViewInterConv->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &CInterConvertForm::OnMouseDownTreeView);
      this->listViewInterConv->SizeChanged += gcnew System::EventHandler(this, &CInterConvertForm::OnSizeChanged);
      // 
      // colHeaderInterSource
      // 
      this->colHeaderInterSource->Text = "Source Interface";
      // 
      // colHeaderInterDestin
      // 
      this->colHeaderInterDestin->Text = "Destination Interface";
      // 
      // imageListTlg
      // 
      this->imageListTlg->ImageSize = System::Drawing::Size(16, 16);
      this->imageListTlg->ImageStream = (safe_cast<System::Windows::Forms::ImageListStreamer ^  >(resources->GetObject("imageListTlg.ImageStream")));
      this->imageListTlg->TransparentColor = System::Drawing::Color::Transparent;
      // 
      // imageListElem
      // 
      this->imageListElem->ImageSize = System::Drawing::Size(16, 16);
      this->imageListElem->ImageStream = (safe_cast<System::Windows::Forms::ImageListStreamer ^  >(resources->GetObject("imageListElem.ImageStream")));
      this->imageListElem->TransparentColor = System::Drawing::Color::Transparent;
      // 
      // CInterConvertForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(384, 301);
      this->Controls->Add(this->listViewInterConv);
      this->Name = "CInterConvertForm";
      this->ShowInTaskbar = false;
      this->Text = "CInterConvertForm";
      this->Resize += gcnew System::EventHandler(this, &CInterConvertForm::OnResizeForm);
      this->ResumeLayout(false);

    }		

    System::Void OnResizeForm(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnResizeListView(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnSizeChanged(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnMouseDownTreeView(System::Object ^  sender, System::Windows::Forms::MouseEventArgs ^  e);
    System::Void CInterConvertForm::OnSelIndexChange(System::Object ^  sender, System::EventArgs ^  e);
    System::Void OnDrawItemComBx(System::Object ^  sender, System::Windows::Forms::DrawItemEventArgs ^  e);

		void extendItem(int index);
		void collapsItem(int index);
		void extendItemAsTlg(CTlgWrapper^ tlg,int index);
		int extendItemAsTlgElem(CTlgWrapper^ tlg,String^ elem,int index);
    void collapsItemAsTlg(int index);
    void collapsItemAsTlgElem(CTlgWrapper^ tlg,String^ elemName,int index);
    void showComboBoxChose();
    void updateView();
    int getTlgElemFromItem(ListViewItem^ item,String^& tlgName,String^& elemName,String^& subElemName);
    void setComboBoxItem();
    void initComboBoxAsTlg(String^ sourceTlgName);
    void initComboBoxAsTlgElem(String^ sourceTlg,String^ sourceElem,String^ sourceSubElem);
    String^ findItem(String^ name);
    bool isSimpleTlgElem(String^ tlgName,String^ elemName);
        
    //---Attributs------------------------
    CInterAssignment^ InterAssignment;
    CTlgInterfaceWrapper^ SourceInter;
    CTlgInterfaceWrapper^ DestinationInter;

    ComboBox^ ComboBoxChose;
		System::Drawing::Color TelColor;
		System::Drawing::Color SimpleElemColor;
		System::Drawing::Color ComplexElemColor;
    int TopItemIndex;
};
}