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
  /// Zusammenfassung für CInfoForm
  ///
  /// Achtung: Wenn Sie den Namen dieser Klasse ändern, müssen Sie die Eigenschaft
  ///          'Ressourcendateiname' für das Compilertool für verwaltete Ressourcen ändern, 
  ///          das allen .resx-Dateien zugewiesen ist, von denen diese Klasse abhängt. 
  ///          Anderenfalls können die Designer nicht korrekt mit den lokalisierten Ressourcen
  ///          arbeiten, die diesem Formular zugewiesen sind.
  /// </summary>
  public ref class CInfoForm : public System::Windows::Forms::Form
  {
  public: 
    CInfoForm(void)
    {
      InitializeComponent();
      Chouse = true;
    }
    void setMessage(String^ mess);
    bool getAnswer();
  protected: 
    //void Dispose(Boolean disposing)
    //{
    //  if (disposing && components)
    //  {
    //    components->Dispose();
    //  }
    //  __super::Dispose(disposing);
    //}
    private: System::Windows::Forms::Button ^  button1;
    private: System::Windows::Forms::Label ^  labMessage;
    private: System::Windows::Forms::Button ^  button2;

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
      this->button1 = gcnew System::Windows::Forms::Button();
      this->labMessage = gcnew System::Windows::Forms::Label();
      this->button2 = gcnew System::Windows::Forms::Button();
      this->SuspendLayout();
      // 
      // button1
      // 
      this->button1->Location = System::Drawing::Point(65, 88);
      this->button1->Name = "button1";
      this->button1->Size = System::Drawing::Size(75, 24);
      this->button1->TabIndex = 0;
      this->button1->Text = "Ye";
	  this->button1->Click += gcnew System::EventHandler(this, &CInfoForm::OnClickYes);
      // 
      // labMessage
      // 
      this->labMessage->Location = System::Drawing::Point(15, 8);
      this->labMessage->Name = "labMessage";
      this->labMessage->Size = System::Drawing::Size(270, 72);
      this->labMessage->TabIndex = 2;
      this->labMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
      // 
      // button2
      // 
      this->button2->Location = System::Drawing::Point(145, 88);
      this->button2->Name = "button2";
      this->button2->Size = System::Drawing::Size(75, 24);
      this->button2->TabIndex = 1;
      this->button2->Text = "No";
	  this->button2->Click += gcnew System::EventHandler(this, &CInfoForm::OnClickNo);
      // 
      // CInfoForm
      // 
      this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
      this->ClientSize = System::Drawing::Size(294, 122);
      this->Controls->Add(this->button2);
      this->Controls->Add(this->labMessage);
      this->Controls->Add(this->button1);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
      this->Name = "CInfoForm";
      this->ShowInTaskbar = false;
      this->ResumeLayout(false);

    }    

    System::Void OnClickYes(System::Object ^  sender, System::EventArgs ^  e);
    bool  Chouse;
    System::Void OnClickNo(System::Object ^  sender, System::EventArgs ^  e);
};
}
