#include "Extension.h"

#include "NativeManager.h"

JailbreakExtension g_Extension;
SMEXT_LINK(&g_Extension);

const sp_nativeinfo_t MyNatives[] =
{
	{ "native_ConCmdCallback", NativeManager::ConCmdCallback },
	{ "native_SrvCmdCallback", NativeManager::SrvCmdCallback },
	{ "native_CmdListenerCallback", NativeManager::CmdListenerCallback },
	{ "native_OnPluginStart", NativeManager::OnPluginStart },
	{ "native_OnPluginEnd", NativeManager::OnPluginEnd },
	{ "native_OnMapStart", NativeManager::OnMapStart },
	{ "native_OnMapEnd", NativeManager::OnMapEnd },
	// EVENTS.INC
	{ "native_EventHookCallbackPre", NativeManager::EventHookCallbackPre },
	{ "native_EventHookCallbackPost", NativeManager::EventHookCallbackPost },
	{ "native_EventHookCallbackPostNoCopy", NativeManager::EventHookCallbackPostNoCopy },
	// DBI.INC
	{ "native_SQLTxnSuccessCallback", NativeManager::SQLTxnSuccessCallback },
	{ "native_SQLTxnFailureCallback", NativeManager::SQLTxnFailureCallback },
	{ "native_SQLTCallbackConnect", NativeManager::SQLTCallbackConnect },
	{ "native_SQLTCallbackQuery", NativeManager::SQLTCallbackQuery },
	// CSTRIKE.INC
	{ "native_CS_OnBuyCommand", NativeManager::CS_OnBuyCommand },
	{ "native_CS_OnCSWeaponDrop", NativeManager::CS_OnCSWeaponDrop },
	{ "native_CS_OnGetWeaponPrice", NativeManager::CS_OnGetWeaponPrice },
	{ "native_CS_OnTerminateRound", NativeManager::CS_OnTerminateRound },
	// Console.inc
	{ "native_OnClientSayCommand", NativeManager::OnClientSayCommand },
	{ "native_OnClientSayCommand_Post", NativeManager::OnClientSayCommandPost },
	// Client.inc
	{ "native_OnClientConnect", NativeManager::OnClientConnect },
	{ "native_OnClientConnected", NativeManager::OnClientConnected },
	{ "native_OnClientPutInServer", NativeManager::OnClientPutInServer },
	{ "native_OnClientDisconnect", NativeManager::OnClientDisconnect },
	{ "native_OnClientDisconnect_Post", NativeManager::OnClientDisconnectPost },
	{ "native_OnClientCommand", NativeManager::OnClientCommand },
	{ "native_OnClientCommandKeyValues", NativeManager::OnClientCommandKeyValues },
	{ "native_OnClientCommandKeyValues_Post", NativeManager::OnClientCommandKeyValuesPost },
	{ "native_OnClientSettingsChanged", NativeManager::OnClientSettingsChanged },
	{ "native_OnClientAuthorized", NativeManager::OnClientAuthorized },
	{ "native_OnClientPreAdminCheck", NativeManager::OnClientPreAdminCheck },
	{ "native_OnClientPostAdminFilter", NativeManager::OnClientPostAdminFilter },
	{ "native_OnClientPostAdminCheck", NativeManager::OnClientPostAdminCheck },
	// NULL
	{ NULL, NULL }
};

void JailbreakExtension::SDK_OnAllLoaded()
{
	sharesys->AddNatives(myself, MyNatives);
}
