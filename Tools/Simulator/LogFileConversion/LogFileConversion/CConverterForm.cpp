#include "StdAfx.h"
#include "CConverterForm.h"
#include "CTlgLogFileContainer.h"
//-----------------------------------------------------------------------------
using namespace LogFileConversion;
//-----------------------------------------------------------------------------
System::Void CConverterForm::OnButtOpenClick(System::Object ^  sender, System::EventArgs ^  e)
{
    openFileDialog->Title = "Convert Log-File";
    openFileDialog->Filter = "Log File(*.log)|*.log";
    if(openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        String^ pathLogFile = openFileDialog->FileName;
        if(pathLogFile)
        {
            if(InterAssignment != nullptr)
            {
                LogFileContainer->readLogFile(pathLogFile,InterAssignment);
                showLogFileContainer();
            }
        }

    }
}
//-----------------------------------------------------------------------------
System::Void CConverterForm::OnButtSaveClick(System::Object ^  sender, System::EventArgs ^  e)
{
    saveFileDialog->Title = "Save Log - File";
    saveFileDialog->Filter = "Log File(*.log)|*.log";
    if(saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
         String^ pathLogFile = saveFileDialog->FileName;
         if(pathLogFile)
         {
             //LogFileContainer->writeLogFile(pathLogFile);
             //showConvertedFile(pathLogFile);
             richTextBox->SaveFile(pathLogFile,RichTextBoxStreamType::PlainText);
         }
    }
}
//-----------------------------------------------------------------------------
void CConverterForm::setInterfaceAssignment(CInterAssignment^ interAss)
{
    this->InterAssignment = interAss;
}
//-----------------------------------------------------------------------------
void CConverterForm::showConvertedFile(String^ path)
{
    String^ logFileLine = nullptr;
    String^ line = nullptr;
    int secOffset = 1;
    System::IO::StreamReader^ sr = gcnew System::IO::StreamReader(path);
    DateTime timeDay = DateTime::Now;
    //timeStr=time.get_TimeOfDay().ToString();
    while((logFileLine = sr->ReadLine()) != nullptr)
    {
        line=timeDay.TimeOfDay.ToString();
        line=String::Concat(line," ",logFileLine,"\n");
        richTextBox->AppendText(line);
        timeDay.AddSeconds(1.0);
    }
}
//-----------------------------------------------------------------------------
void CConverterForm::showLogFileContainer()
{
    int count,i;
    String^ line = nullptr;
    richTextBox->Clear();
    count = LogFileContainer->getTlgCount();
    DateTime timeDay = DateTime::Now;
    for(i=1;i<=count;i++)
    {
        line = System::Convert::ToString(timeDay.Year);
        line = String::Concat(line,"-");
        line = String::Concat(line,System::Convert::ToString(timeDay.Month),"-");
        line = String::Concat(line,System::Convert::ToString(timeDay.Day)," ");
        line = String::Concat(line,System::Convert::ToString(timeDay.Hour),":");
        line = String::Concat(line,System::Convert::ToString(timeDay.Minute),":");
        line = String::Concat(line,System::Convert::ToString(timeDay.Second),".");
        line = String::Concat(line,"00");
        line = String::Concat(line," [INF]: TYPE;",LogFileContainer->getDestTlgName(i));
        line = String::Concat(line,";SENDER;  ;");
       
        line = String::Concat(line," ",LogFileContainer->getTlgAsString(i));
        line = String::Concat(line,"\n");
        richTextBox->AppendText(line);
        timeDay.AddSeconds(1.0);
    }
}
//-----------------------------------------------------------------------------