#include "Extension.h"

#include "NativeManager.h"

const sp_nativeinfo_t MyNatives[] =
{
	// USERMESSAGES.INC
	{ "native_MsgHookCallback", NativeManager::MsgHookCallback },
	{ "native_MsgPostHookCallback", NativeManager::MsgPostHookCallback },
	// CONVARS.INC
	{ "native_ConVarChangedCallback", NativeManager::ConVarChangedCallback },
	{ "native_ConVarQueryFinishedCallback", NativeManager::ConVarQueryFinishedCallback },
	// SOURCEMOD.INC
	{ "native_OnPluginStart", NativeManager::OnPluginStart },
	{ "native_OnPluginEnd", NativeManager::OnPluginEnd },
	{ "native_OnPluginPauseChange", NativeManager::OnPluginPauseChange },
	{ "native_OnGameFrame", NativeManager::OnGameFrame },
	{ "native_OnMapStart", NativeManager::OnMapStart },
	{ "native_OnMapEnd", NativeManager::OnMapEnd },
	{ "native_OnConfigsExecuted", NativeManager::OnConfigsExecuted },
	{ "native_OnAutoConfigsBuffered", NativeManager::OnAutoConfigsBuffered },
	{ "native_OnAllPluginsLoaded", NativeManager::OnAllPluginsLoaded },
	{ "native_OnLibraryAdded", NativeManager::OnLibraryAdded },
	{ "native_OnLibraryRemoved", NativeManager::OnLibraryRemoved },
	{ "native_OnClientFloodCheck", NativeManager::OnClientFloodCheck },
	{ "native_OnClientFloodResult", NativeManager::OnClientFloodResult },
	// SDKTOOLS_SOUND.INC
	{ "native_AmbientSHookCallback", NativeManager::AmbientSHookCallback },
	{ "native_NormalSHookCallback", NativeManager::NormalSHookCallback },
	// COMMANDFILTERS.INC
	{ "native_MultiTargetFilterCallback", NativeManager::MultiTargetFilterCallback },
	// SDKTOOLS_VOICE.INC
	{ "native_OnClientSpeaking", NativeManager::OnClientSpeaking },
	{ "native_OnClientSpeakingEnd", NativeManager::OnClientSpeakingEnd },
	// SDKTOOLS_TRACE.INC
	{ "native_TraceEntityFilterCallback", NativeManager::TraceEntityFilterCallback },
	{ "native_TraceEntityEnumeratorCallback", NativeManager::TraceEntityEnumeratorCallback },
	// LOGGING.INC
	{ "native_OnLogAction", NativeManager::OnLogAction },
	{ "native_GameLogHookCallback", NativeManager::GameLogHookCallback },
	// SDKTOOLS_TEMPENTS.INC
	{ "native_TEHookCallback", NativeManager::TEHookCallback },
	// SDKTOOLS_ENTOUTPUT.INC
	{ "native_EntityOutputCallback", NativeManager::EntityOutputCallback },
	{ "native_SingleEntityOutputCallback", NativeManager::SingleEntityOutputCallback },
	// TIMERS.INC
	{ "native_TimerCallback", NativeManager::TimerCallback },
	{ "native_OnMapTimeLeftChanged", NativeManager::OnMapTimeLeftChanged },
	// SDKTOOLS_HOOKS.INC
	{ "native_OnPlayerRunCmd", NativeManager::OnPlayerRunCmd },
	{ "native_OnPlayerRunCmdPost", NativeManager::OnPlayerRunCmdPost },
	// SDKHOOKS.INC
	{ "native_OnEntityCreated", NativeManager::OnEntityCreated },
	{ "native_OnEntitySpawned", NativeManager::OnEntitySpawned },
	{ "native_OnEntityDestroyed", NativeManager::OnEntityDestroyed },
	{ "native_OnGetGameDescription", NativeManager::OnGetGameDescription },
	{ "native_OnLevelInit", NativeManager::OnLevelInit },
	// callbacks
	{ "native_SDKHooksPreThink", NativeManager::SDKHooksPreThink },
	{ "native_SDKHooksPreThinkPost", NativeManager::SDKHooksPreThinkPost },
	{ "native_SDKHooksPostThink", NativeManager::SDKHooksPostThink },
	{ "native_SDKHooksPostThinkPost", NativeManager::SDKHooksPostThinkPost },
	{ "native_SDKHooksGroundEntChanged", NativeManager::SDKHooksGroundEntChanged },
	{ "native_SDKHooksSpawnPost", NativeManager::SDKHooksSpawnPost },
	{ "native_SDKHooksThink", NativeManager::SDKHooksThink },
	{ "native_SDKHooksThinkPost", NativeManager::SDKHooksThinkPost },
	{ "native_SDKHooksVPhysicsUpdate", NativeManager::SDKHooksVPhysicsUpdate },
	{ "native_SDKHooksVPhysicsUpdatePost", NativeManager::SDKHooksVPhysicsUpdatePost },
	{ "native_SDKHooksSpawn", NativeManager::SDKHooksSpawn },
	{ "native_SDKHooksReload", NativeManager::SDKHooksReload },
	{ "native_SDKHooksEndTouch", NativeManager::SDKHooksEndTouch },
	{ "native_SDKHooksStartTouch", NativeManager::SDKHooksStartTouch },
	{ "native_SDKHooksTouch", NativeManager::SDKHooksTouch },
	{ "native_SDKHooksBlocked", NativeManager::SDKHooksBlocked },
	{ "native_SDKHooksSetTransmit", NativeManager::SDKHooksSetTransmit },
	{ "native_SDKHooksWeaponCanSwitchTo", NativeManager::SDKHooksWeaponCanSwitchTo },
	{ "native_SDKHooksWeaponCanUse", NativeManager::SDKHooksWeaponCanUse },
	{ "native_SDKHooksWeaponDrop", NativeManager::SDKHooksWeaponDrop },
	{ "native_SDKHooksWeaponEquip", NativeManager::SDKHooksWeaponEquip },
	{ "native_SDKHooksWeaponSwitch", NativeManager::SDKHooksWeaponSwitch },
	{ "native_SDKHooksEndTouchPost", NativeManager::SDKHooksEndTouchPost },
	{ "native_SDKHooksStartTouchPost", NativeManager::SDKHooksStartTouchPost },
	{ "native_SDKHooksTouchPost", NativeManager::SDKHooksTouchPost },
	{ "native_SDKHooksBlockedPost", NativeManager::SDKHooksBlockedPost },
	{ "native_SDKHooksWeaponCanSwitchToPost", NativeManager::SDKHooksWeaponCanSwitchToPost },
	{ "native_SDKHooksWeaponCanUsePost", NativeManager::SDKHooksWeaponCanUsePost },
	{ "native_SDKHooksWeaponDropPost", NativeManager::SDKHooksWeaponDropPost },
	{ "native_SDKHooksWeaponEquipPost", NativeManager::SDKHooksWeaponEquipPost },
	{ "native_SDKHooksWeaponSwitchPost", NativeManager::SDKHooksWeaponSwitchPost },
	{ "native_SDKHooksGetMaxHealth", NativeManager::SDKHooksGetMaxHealth },
	{ "native_SDKHooksOnTakeDamage", NativeManager::SDKHooksOnTakeDamage },
	{ "native_SDKHooksOnTakeDamageAlive", NativeManager::SDKHooksOnTakeDamageAlive },
	{ "native_SDKHooksOnTakeDamagePost", NativeManager::SDKHooksOnTakeDamagePost },
	{ "native_SDKHooksOnTakeDamageAlivePost", NativeManager::SDKHooksOnTakeDamageAlivePost },
	{ "native_SDKHooksFireBulletsPost", NativeManager::SDKHooksFireBulletsPost },
	{ "native_SDKHooksTraceAttack", NativeManager::SDKHooksTraceAttack },
	{ "native_SDKHooksTraceAttackPost", NativeManager::SDKHooksTraceAttackPost },
	{ "native_SDKHooksShouldCollide", NativeManager::SDKHooksShouldCollide },
	{ "native_SDKHooksUse", NativeManager::SDKHooksUse },
	{ "native_SDKHooksUsePost", NativeManager::SDKHooksUsePost },
	{ "native_SDKHooksReloadPost", NativeManager::SDKHooksReloadPost },
	{ "native_SDKHooksCanBeAutobalanced", NativeManager::SDKHooksCanBeAutobalanced },
	// MENUS.INC
	{ "native_MenuHandlerCallback", NativeManager::MenuHandlerCallback },
	{ "native_VoteHandlerCallback", NativeManager::VoteHandlerCallback },
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
	// CONSOLE.inc
	{ "native_OnClientSayCommand", NativeManager::OnClientSayCommand },
	{ "native_OnClientSayCommand_Post", NativeManager::OnClientSayCommandPost },
	{ "native_ConCmdCallback", NativeManager::ConCmdCallback },
	{ "native_SrvCmdCallback", NativeManager::SrvCmdCallback },
	{ "native_CmdListenerCallback", NativeManager::CmdListenerCallback },
	// CLIENT.inc
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

void CSGOExtension::SDK_OnAllLoaded()
{
	sharesys->AddNatives(myself, MyNatives);
}
