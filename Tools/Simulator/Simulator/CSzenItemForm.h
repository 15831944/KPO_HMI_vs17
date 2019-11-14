
#ifndef _CSzenItemForm_H
#define _CSzenItemForm_H

#include "CSzenItem.h"
#include "CTlgViewForm.h"
using namespace simulator;



using namespace System::Windows::Forms;

//__delegate void LabelClick(void);
__delegate void NotifyLabelClick(void); 

__gc class CSzenItemForm
{
    public:
           CSzenItemForm();
           ~CSzenItemForm();

           Panel* createSzenItemForm(CSzenItem* item,ImageList* image);
           Panel* getPanel();
           void updateTime(double delay);
           void setLabelColor(System::Drawing::Color color);
           void setDelegateLabClick(NotifyLabelClick* del);
           void setTlgViewForm(CTlgViewForm* tlgView);
		   void setFocuc(bool f);
		   bool getFocus();
		   void erase();
    private:
           System::Void OnClickButton(System::Object *  sender, System::EventArgs *  e);
           System::Void OnValidatedTextBox(System::Object *  sender, System::EventArgs *  e);
           System::Void OnTextChanged(System::Object *  sender, System::EventArgs *  e);
           System::Void OnLabelClick(System::Object *  sender, System::EventArgs *  e);

           Panel* pan;
           Button* but;
           Label* lab;
           TextBox* txtBx;
           ImageList* Image;

           CSzenItem* Item;
           bool Focuced;
           NotifyLabelClick* Del;
           CTlgViewForm* TlgViewForm;
           //CSzenariumForm* PaternForm;

};

#endif