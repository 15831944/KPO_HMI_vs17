// This is the main DLL file.

#include "Meltshop.h"
#include "MeltshopTelegram.h"
#include "DlgSelectConnection.h"
#include "DlgConfigureSource.h"

Comani::Telegram^ Meltshop::MeltshopPlugin::createTelegram(LibTelcom::TelegramDefinition ^definition)
{
  DlgSelectConnection^ connDlg = gcnew DlgSelectConnection(contextName, connDict);
  if (connDlg->ShowDialog() == DialogResult::OK)
  {
    IBASConnection^ conn = connDlg->SelectedConnection;
    return gcnew Meltshop::MeltshopTelegram(definition, conn);
  }
  return nullptr;
}
bool Meltshop::MeltshopPlugin::configureSource()
{
  DlgConfigureSource^ dlgSource = gcnew DlgConfigureSource();
  if (dlgSource->ShowDialog() == DialogResult::OK)
  {
    this->contextName = dlgSource->ContextName;
    return true;
  }
  return false;
}

Meltshop::MeltshopPlugin::MeltshopPlugin()
{
  connDict = gcnew Dictionary<String^, IBASConnection^>();
}

String^ Meltshop::MeltshopPlugin::getSourceName()
{
  return "Meltshop IBAS";
}
