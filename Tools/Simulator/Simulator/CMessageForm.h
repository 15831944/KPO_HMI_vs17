#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace simulator
{
	/// <summary> 
	/// Zusammenfassung für CMessageForm
	///
	/// Achtung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie die Eigenschaft
	///          'Ressourcendateiname' für das Compilertool für verwaltete Ressourcen ändern, 
	///          das allen .resx-Dateien zugewiesen ist, von denen diese Klasse abhängt. 
	///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
	///          arbeiten, die diesem Formular zugewiesen sind.
	/// </summary>
	public ref class CMessageForm : public System::Windows::Forms::Form
	{
	public: 
    CMessageForm(void)
    {
      InitializeComponent();
      this->TopLevel = false;
      this->Dock = DockStyle::Fill;
			this->FormBorderStyle = ::FormBorderStyle::None;
    }
		CMessageForm(Panel^ parent)
		{
			InitializeComponent();

      this->TopLevel = false;
    	this->Parent = parent;
    	this->Dock = DockStyle::Fill;
    	this->FormBorderStyle = ::FormBorderStyle::None;
		}
    enum class MessTyp {Info,Warning,Error};
    enum class TextCaption {None,Sender,Receiver,LogFile,Szenario,SendTelegrams,LoadInterfaces,LoadLogFile,LoadSzenario};
    
    //static CMessageForm^ getMessageForm();
    //void setParent(Panel^ pan);
    void writeLine(System::String^ txt,MessTyp typ);
    void setActionName(String^ str);
    void setActionName(TextCaption caption);
    void setShowModi(int mode);
	protected: 
		//void Dispose(Boolean disposing)
		//{
		//	//if (disposing && components)
		//	//{
		//	//	components->Dispose();
		//	//}
		//	__super::Dispose(disposing);
		//}
		//CMessageForm(void);
		//CMessageForm(Panel^ parent);
	private: System::Windows::Forms::Panel ^  panBackGround;
	private: System::Windows::Forms::Panel ^  panTitel;
	private: System::Windows::Forms::ContextMenu ^  PopUpMenu;
	private: System::Windows::Forms::MenuItem ^  menuItemClear;
	private: System::Windows::Forms::MenuItem ^  menuItemSave;
	private: System::Windows::Forms::Label ^  labTitel;
  private: System::Windows::Forms::Panel ^  panHin;
  private: System::Windows::Forms::Panel ^  panMessage;
  private: System::Windows::Forms::RichTextBox ^  richTxtBxEdit;

	System::Void OnTextChanged(System::Object ^  sender, System::EventArgs ^  e);
	System::Void OnClickPopUpMenuClear(System::Object ^  sender, System::EventArgs ^  e); 
  System::Void OnClickPopUpMenuSave(System::Object ^  sender, System::EventArgs ^  e);

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container^ components;

		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung. 
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
      this->panBackGround = (gcnew System::Windows::Forms::Panel());
      this->panHin = (gcnew System::Windows::Forms::Panel());
      this->panMessage = (gcnew System::Windows::Forms::Panel());
      this->richTxtBxEdit = (gcnew System::Windows::Forms::RichTextBox());
      this->PopUpMenu = (gcnew System::Windows::Forms::ContextMenu());
      this->menuItemClear = (gcnew System::Windows::Forms::MenuItem());
      this->menuItemSave = (gcnew System::Windows::Forms::MenuItem());
      this->panTitel = (gcnew System::Windows::Forms::Panel());
      this->labTitel = (gcnew System::Windows::Forms::Label());
      this->panBackGround->SuspendLayout();
      this->panHin->SuspendLayout();
      this->panMessage->SuspendLayout();
      this->panTitel->SuspendLayout();
      this->SuspendLayout();
      // 
      // panBackGround
      // 
      this->panBackGround->Controls->Add(this->panHin);
      this->panBackGround->Controls->Add(this->panTitel);
      this->panBackGround->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panBackGround->Location = System::Drawing::Point(0, 0);
      this->panBackGround->Name = "panBackGround";
      this->panBackGround->Size = System::Drawing::Size(440, 273);
      this->panBackGround->TabIndex = 0;
      // 
      // panHin
      // 
      this->panHin->AutoScroll = true;
      this->panHin->Controls->Add(this->panMessage);
      this->panHin->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panHin->Location = System::Drawing::Point(0, 20);
      this->panHin->Name = "panHin";
      this->panHin->Size = System::Drawing::Size(440, 253);
      this->panHin->TabIndex = 1;
      // 
      // panMessage
      // 
      this->panMessage->AutoSize = true;
      this->panMessage->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
      this->panMessage->Controls->Add(this->richTxtBxEdit);
      this->panMessage->Dock = System::Windows::Forms::DockStyle::Fill;
      this->panMessage->Location = System::Drawing::Point(0, 0);
      this->panMessage->Name = "panMessage";
      this->panMessage->Size = System::Drawing::Size(440, 253);
      this->panMessage->TabIndex = 2;
      // 
      // richTxtBxEdit
      // 
      this->richTxtBxEdit->AutoWordSelection = true;
      this->richTxtBxEdit->BackColor = System::Drawing::SystemColors::ControlLightLight;
      this->richTxtBxEdit->BorderStyle = System::Windows::Forms::BorderStyle::None;
      this->richTxtBxEdit->ContextMenu = this->PopUpMenu;
      this->richTxtBxEdit->Dock = System::Windows::Forms::DockStyle::Fill;
      this->richTxtBxEdit->Font = (gcnew System::Drawing::Font("Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
        (System::Byte)0));
      this->richTxtBxEdit->Location = System::Drawing::Point(0, 0);
      this->richTxtBxEdit->Name = "richTxtBxEdit";
      this->richTxtBxEdit->ReadOnly = true;
      this->richTxtBxEdit->Size = System::Drawing::Size(436, 249);
      this->richTxtBxEdit->TabIndex = 0;
      this->richTxtBxEdit->Text = "";
      this->richTxtBxEdit->TextChanged += gcnew System::EventHandler(this, &CMessageForm::OnTextChanged);
      // 
      // PopUpMenu
      // 
      array <System::Windows::Forms::MenuItem^>^ __mcTemp__1 = gcnew array  <System::Windows::Forms::MenuItem^>(2);
      __mcTemp__1[0] = this->menuItemClear;
      __mcTemp__1[1] = this->menuItemSave;
      this->PopUpMenu->MenuItems->AddRange(__mcTemp__1);
      // 
      // menuItemClear
      // 
      this->menuItemClear->Index = 0;
      this->menuItemClear->Text = "Clear";
      this->menuItemClear->Click += gcnew System::EventHandler(this, &CMessageForm::OnClickPopUpMenuClear);
      // 
      // menuItemSave
      // 
      this->menuItemSave->Index = 1;
      this->menuItemSave->Text = "Save";
      this->menuItemSave->Click += gcnew System::EventHandler(this, &CMessageForm::OnClickPopUpMenuSave);
      // 
      // panTitel
      // 
      this->panTitel->Controls->Add(this->labTitel);
      this->panTitel->Dock = System::Windows::Forms::DockStyle::Top;
      this->panTitel->Location = System::Drawing::Point(0, 0);
      this->panTitel->Name = "panTitel";
      this->panTitel->Size = System::Drawing::Size(440, 20);
      this->panTitel->TabIndex = 0;
      // 
      // labTitel
      // 
      this->labTitel->BackColor = System::Drawing::Color::FromArgb((System::Int32)(System::Byte)192, (System::Int32)(System::Byte)192, (System::Int32)(System::Byte)255);
      this->labTitel->ContextMenu = this->PopUpMenu;
      this->labTitel->Dock = System::Windows::Forms::DockStyle::Fill;
      this->labTitel->Font = (gcnew System::Drawing::Font("Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
        (System::Byte)0));
      this->labTitel->Location = System::Drawing::Point(0, 0);
      this->labTitel->Name = "labTitel";
      this->labTitel->Size = System::Drawing::Size(440, 20);
      this->labTitel->TabIndex = 0;
      this->labTitel->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
      // 
      // CMessageForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(440, 273);
      this->Controls->Add(this->panBackGround);
      this->Name = "CMessageForm";
      this->Text = "CMessageForm";
      this->panBackGround->ResumeLayout(false);
      this->panHin->ResumeLayout(false);
      this->panHin->PerformLayout();
      this->panMessage->ResumeLayout(false);
      this->panTitel->ResumeLayout(false);
      this->ResumeLayout(false);

    }		
		//static CMessageForm^ Edit = 0;
    System::Drawing::Color getColor(MessTyp typ);	 
};
}
