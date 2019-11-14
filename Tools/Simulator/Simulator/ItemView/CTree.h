#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;

using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace System::Text;

namespace simulator {

	/// <summary>
	/// Zusammenfassung für CTree
	/// </summary>
	public ref class CTree :  public CommonTools::TreeListView
	{
	public:
		CTree(void)
		{
			TreeListView::RowOptions->ItemHeight = 18;
      InitializeComponent();
			/*m_contextMenu = new System::Windows::Forms::ContextMenu();*/
		
     //TreeListView::ColumnsOptions->set_HeaderHeight(18);
     
     /* TreeListView::Columns->Options->set_LeftMargin(33);*/
     /* CommonTools::ColorListBox(System::Drawing::Color::Blue);*/

			/*m_contextMenu->MenuItems->Add(new MenuItem("Collapse All Children", new EventHandler(this,&CTree::OnCollapseAllChildren)));
			m_contextMenu->MenuItems->Add(new MenuItem("Expand All Children", new EventHandler(this,&CTree::OnExpandAllChildren)));
			m_contextMenu->MenuItems->Add(new MenuItem("Delete Selected Node", new EventHandler(this,&CTree::OnDeleteSelectedNode)));*/
		  
      /*container->Add(this);*/
      RowSetting = nullptr;
    }
    
    int getColumnsCount();
    int getColumnsWidht();
    int getColumnsHeight();
    int getColumnWidht(int index);
		int getColumnsHeaderHeight();
    int getHScrollValue();
		/*System::Void OnCollapseAllChildren(System::Object * sender,System::EventArgs * e);
		System::Void OnExpandAllChildren(System::Object * sender,System::EventArgs * e);
		System::Void OnDeleteSelectedNode(System::Object * sender,System::EventArgs * e);*/

		/*CTree(System::ComponentModel::IContainer *container)
		{
			/// <summary>
			/// Erforderlich für die Unterstützung des Windows.Forms-Klassenkompositions-Designers
			/// </summary>

			container->Add(this);
      RowSetting = new CommonTools::TreeList::RowSetting(this);
			InitializeComponent();
		}*/

	protected:
		 /*void BeforeShowContextMenu();*/
		 /*System::Object* GetData(CommonTools::Node *node, CommonTools::TreeListColumn *column);*/
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		/*~CTree()
		{
			if (components)
			{
				delete components;
			}
		}*/

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		/*System::ComponentModel::Container *components;*/
		/*System::Windows::Forms::ContextMenu* m_contextMenu;*/
    CommonTools::TreeList::RowSetting^ RowSetting;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			/*components = new System::ComponentModel::Container();*/
		}
#pragma endregion
	};
}
