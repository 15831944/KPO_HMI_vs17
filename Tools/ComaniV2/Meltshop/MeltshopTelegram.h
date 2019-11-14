#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace Meltshop {

	/// <summary>
	/// Summary for MeltshopTelegram
	/// </summary>
  public ref class MeltshopTelegram : public Comani::Telegram
	{
	public:
    MeltshopTelegram(LibTelcom::TelegramDefinition^ def, Comani::ISourceConnection^ source)
      : Comani::Telegram(def, source)
    {
      InitializeComponent();
    }

    virtual void addItem(LibTelcom::TelegramItem^ item) override
    {
      String^ name = String::Concat(telegramDef->TelegramName, ".", item->Name);
      if (item->Count == 1)
        addItem(name, item);
      else
      {
        for (int i = 0; i < item->Count; i++)
          addItem(String::Concat(name,"[",Convert::ToString(i),"]"), item);
      }
    }

    virtual void addItem(String^ name, LibTelcom::TelegramItem^ item) override
    {
      tableLayoutPanel1->RowCount++;      
      int rowNo = tableLayoutPanel1->RowCount - 2;
      String^ itemText = name->Substring(name->IndexOf(".") + 1);
      addItemLabel(rowNo, itemText, item->Comment);
      Comani::TextValueControl^ val = gcnew Comani::TextValueControl();
      addItemControl(rowNo, val);
      //if (item->GetType()->IsAssignableFrom())
      //  addUnitLabel(rowNo, ((LibTelcom::PrimitiveItem) item)->Unit);
      itemControls->Add(name, val);
      itemDefs->Add(name, item);
    }

  

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MeltshopTelegram()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		}
#pragma endregion
	};
}
