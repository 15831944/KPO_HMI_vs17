#pragma once

#include "CItemWrapper.h"
#include "CMessageForm.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace simulator {

	/// <summary>
	/// Summary for CDataGridContainerForm1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class CDataGridContainerForm : public System::Windows::Forms::Form
	{
	  public:
		CDataGridContainerForm(Panel^ parent,CMessageForm^ MessageForm)
		  {
			  InitializeComponent();
        DataGridCon = gcnew Hashtable();
        TabPagesCon = gcnew ArrayList();
        this->Dock = DockStyle::Fill;
        this->TopLevel = false;
        this->Parent = parent;
        //tabControl1->TabPages[0)->Name;
        this->MessageForm = MessageForm;
		  }

    void addItem(CItemWrapper^ item);
    void addItemValue(CItemWrapper^ item);
    ArrayList^ getItemNames();
    int getCountOfRows(String^ name);
    void setFilter(String^ name);
    void ShowDataGrid(String^ name);
    bool IsItemInside(String^ name);
    void removeItem(String^ name);
    void setPointerOfMessage(CMessageForm^ MessageForm);
    void CloseSelectedTabPage();

	  protected:
		  ///// <summary>
		  ///// Clean up any resources being used.
		  ///// </summary>
		  //~CDataGridContainerForm1()
		  //{
		  //	if (components)
		  //	{
		  //		delete components;
		  //	}
		  //}

	  private:
      void AddNewTabPage(CItemWrapper^ item);
      Hashtable^ DataGridCon;
      ArrayList^ TabPagesCon;
      CMessageForm^ MessageForm;
      System::Windows::Forms::TabControl^  tabControl1;

		  /// <summary>
		  /// Required designer variable.
		  /// </summary>
		  System::ComponentModel::Container ^components;

		  /// <summary>
		  /// Required method for Designer support - do not modify
		  /// the contents of this method with the code editor.
		  /// </summary>
		  void InitializeComponent(void)
		  {
        this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
        this->SuspendLayout();
        // 
        // tabControl1
        // 
        this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
        this->tabControl1->Location = System::Drawing::Point(0, 0);
        this->tabControl1->Name = "tabControl1";
        this->tabControl1->SelectedIndex = 0;
        this->tabControl1->Size = System::Drawing::Size(292, 266);
        this->tabControl1->TabIndex = 0;
        // 
        // CDataGridContainerForm
        // 
        this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
        this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
        this->ClientSize = System::Drawing::Size(292, 266);
        this->Controls->Add(this->tabControl1);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
        this->Name = "CDataGridContainerForm";
        this->Text = "CDataGridContainerForm";
        this->ResumeLayout(false);

      }
};
}
