#include "Extension.h"

#include "NativeManager.h"

JailbreakExtension g_Extension;
SMEXT_LINK(&g_Extension);

/*
native_OnClientConnect,
native_OnClientConnected,
native_OnClientPutInServer,
native_OnClientDisconnect,
native_OnClientDisconnect_Post,
native_OnClientCommand,
native_OnClientCommandKeyValues,
native_OnClientCommandKeyValues_Post,
native_OnClientSettingsChanged,
native_OnClientAuthorized,
native_OnClientPreAdminCheck,
native_OnClientPostAdminFilter,
native_OnClientPostAdminCheck,
*/

const sp_nativeinfo_t MyNatives[] =
{
	{ "native_OnRoundStartPre", NativeManager::OnRoundStartPre },
	{ "native_OnRoundStartPost", NativeManager::OnRoundStartPost },
	{ "native_CMDCallback", NativeManager::CMDCallback },
	{ "native_OnPluginStart", NativeManager::OnPluginStart },
	{ "native_OnPluginEnd", NativeManager::OnPluginEnd },
	{ "native_OnMapStart", NativeManager::OnMapStart },
	{ "native_OnMapEnd", NativeManager::OnMapEnd },
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
