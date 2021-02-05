#include "PublicManager.h"

int PublicManager::s_MaxClients = 0;\

// ENTITY.INC
IPluginFunction* PublicManager::s_GetMaxEntitiesFunc;
IPluginFunction* PublicManager::s_GetEntityCountFunc;
IPluginFunction* PublicManager::s_IsValidEntityFunc;
IPluginFunction* PublicManager::s_IsValidEdictFunc;
IPluginFunction* PublicManager::s_IsEntNetworkableFunc;
IPluginFunction* PublicManager::s_CreateEdictFunc;
IPluginFunction* PublicManager::s_RemoveEdictFunc;
IPluginFunction* PublicManager::s_RemoveEntityFunc;
IPluginFunction* PublicManager::s_GetEdictFlagsFunc;
IPluginFunction* PublicManager::s_SetEdictFlagsFunc;
IPluginFunction* PublicManager::s_GetEdictClassnameFunc;
IPluginFunction* PublicManager::s_GetEntityNetClassFunc;
IPluginFunction* PublicManager::s_ChangeEdictStateFunc;
IPluginFunction* PublicManager::s_GetEntDataFunc;
IPluginFunction* PublicManager::s_SetEntDataFunc;
IPluginFunction* PublicManager::s_GetEntDataFloatFunc;
IPluginFunction* PublicManager::s_SetEntDataFloatFunc;
IPluginFunction* PublicManager::s_GetEntDataEnt2Func;
IPluginFunction* PublicManager::s_SetEntDataEnt2Func;
IPluginFunction* PublicManager::s_GetEntDataVectorFunc;
IPluginFunction* PublicManager::s_SetEntDataVectorFunc;
IPluginFunction* PublicManager::s_GetEntDataStringFunc;
IPluginFunction* PublicManager::s_SetEntDataStringFunc;
IPluginFunction* PublicManager::s_FindSendPropInfoFunc;
IPluginFunction* PublicManager::s_FindDataMapInfoFunc;
IPluginFunction* PublicManager::s_GetEntPropFunc;
IPluginFunction* PublicManager::s_SetEntPropFunc;
IPluginFunction* PublicManager::s_GetEntPropFloatFunc;
IPluginFunction* PublicManager::s_SetEntPropFloatFunc;
IPluginFunction* PublicManager::s_GetEntPropEntFunc;
IPluginFunction* PublicManager::s_SetEntPropEntFunc;
IPluginFunction* PublicManager::s_GetEntPropVectorFunc;
IPluginFunction* PublicManager::s_SetEntPropVectorFunc;
IPluginFunction* PublicManager::s_GetEntPropStringFunc;
IPluginFunction* PublicManager::s_SetEntPropStringFunc;
IPluginFunction* PublicManager::s_GetEntPropArraySizeFunc;
IPluginFunction* PublicManager::s_GetEntityAddressFunc;

// SDKTOOLS_FUNCTIONS.INC
IPluginFunction* PublicManager::s_RemovePlayerItemFunc;
IPluginFunction* PublicManager::s_GivePlayerItemFunc;
IPluginFunction* PublicManager::s_GetPlayerWeaponSlotFunc;
IPluginFunction* PublicManager::s_IgniteEntityFunc;
IPluginFunction* PublicManager::s_ExtinguishEntityFunc;
IPluginFunction* PublicManager::s_TeleportEntityFunc;
IPluginFunction* PublicManager::s_ForcePlayerSuicideFunc;
IPluginFunction* PublicManager::s_SlapPlayerFunc;
IPluginFunction* PublicManager::s_FindEntityByClassnameFunc;
IPluginFunction* PublicManager::s_GetClientEyeAnglesFunc;
IPluginFunction* PublicManager::s_CreateEntityByNameFunc;
IPluginFunction* PublicManager::s_DispatchSpawnFunc;
IPluginFunction* PublicManager::s_DispatchKeyValueFunc;
IPluginFunction* PublicManager::s_DispatchKeyValueFloatFunc;
IPluginFunction* PublicManager::s_DispatchKeyValueVectorFunc;
IPluginFunction* PublicManager::s_GetClientAimTargetFunc;
IPluginFunction* PublicManager::s_GetTeamCountFunc;
IPluginFunction* PublicManager::s_GetTeamNameFunc;
IPluginFunction* PublicManager::s_GetTeamScoreFunc;
IPluginFunction* PublicManager::s_SetTeamScoreFunc;
IPluginFunction* PublicManager::s_GetTeamClientCountFunc;
IPluginFunction* PublicManager::s_GetTeamEntityFunc;
IPluginFunction* PublicManager::s_SetEntityModelFunc;
IPluginFunction* PublicManager::s_GetPlayerDecalFileFunc;
IPluginFunction* PublicManager::s_GetPlayerJingleFileFunc;
IPluginFunction* PublicManager::s_GetServerNetStatsFunc;
IPluginFunction* PublicManager::s_EquipPlayerWeaponFunc;
IPluginFunction* PublicManager::s_ActivateEntityFunc;
IPluginFunction* PublicManager::s_SetClientInfoFunc;
IPluginFunction* PublicManager::s_SetClientNameFunc;
IPluginFunction* PublicManager::s_GivePlayerAmmoFunc;

// SDKHOOKS.INC
IPluginFunction* PublicManager::s_SDKHookFunc;
IPluginFunction* PublicManager::s_SDKHookExFunc;
IPluginFunction* PublicManager::s_SDKUnhookFunc;
IPluginFunction* PublicManager::s_SDKHooks_TakeDamageFunc;
IPluginFunction* PublicManager::s_SDKHooks_DropWeaponFunc;

// MENUS.INC
IPluginFunction* PublicManager::s_CreateMenuFunc;
IPluginFunction* PublicManager::s_DisplayMenuFunc;
IPluginFunction* PublicManager::s_DisplayMenuAtItemFunc;
IPluginFunction* PublicManager::s_AddMenuItemFunc;
IPluginFunction* PublicManager::s_InsertMenuItemFunc;
IPluginFunction* PublicManager::s_RemoveMenuItemFunc;
IPluginFunction* PublicManager::s_RemoveAllMenuItemsFunc;
IPluginFunction* PublicManager::s_GetMenuItemFunc;
IPluginFunction* PublicManager::s_MenuShufflePerClientFunc;
IPluginFunction* PublicManager::s_MenuSetClientMappingFunc;
IPluginFunction* PublicManager::s_GetMenuSelectionPositionFunc;
IPluginFunction* PublicManager::s_GetMenuItemCountFunc;
IPluginFunction* PublicManager::s_SetMenuPaginationFunc;
IPluginFunction* PublicManager::s_GetMenuPaginationFunc;
IPluginFunction* PublicManager::s_GetMenuStyleFunc;
IPluginFunction* PublicManager::s_SetMenuTitleFunc;
IPluginFunction* PublicManager::s_GetMenuTitleFunc;
IPluginFunction* PublicManager::s_CreatePanelFromMenuFunc;
IPluginFunction* PublicManager::s_GetMenuExitButtonFunc;
IPluginFunction* PublicManager::s_SetMenuExitButtonFunc;
IPluginFunction* PublicManager::s_GetMenuExitBackButtonFunc;
IPluginFunction* PublicManager::s_SetMenuExitBackButtonFunc;
IPluginFunction* PublicManager::s_SetMenuNoVoteButtonFunc;
IPluginFunction* PublicManager::s_CancelMenuFunc;
IPluginFunction* PublicManager::s_GetMenuOptionFlagsFunc;
IPluginFunction* PublicManager::s_SetMenuOptionFlagsFunc;
IPluginFunction* PublicManager::s_IsVoteInProgressFunc;
IPluginFunction* PublicManager::s_CancelVoteFunc;
IPluginFunction* PublicManager::s_VoteMenuFunc;
IPluginFunction* PublicManager::s_SetVoteResultCallbackFunc;
IPluginFunction* PublicManager::s_CheckVoteDelayFunc;
IPluginFunction* PublicManager::s_IsClientInVotePoolFunc;
IPluginFunction* PublicManager::s_RedrawClientVoteMenuFunc;
IPluginFunction* PublicManager::s_GetMenuStyleHandleFunc;
IPluginFunction* PublicManager::s_CreatePanelFunc;
IPluginFunction* PublicManager::s_CreateMenuExFunc;
IPluginFunction* PublicManager::s_GetClientMenuFunc;
IPluginFunction* PublicManager::s_CancelClientMenuFunc;
IPluginFunction* PublicManager::s_GetMaxPageItemsFunc;
IPluginFunction* PublicManager::s_GetPanelStyleFunc;
IPluginFunction* PublicManager::s_SetPanelTitleFunc;
IPluginFunction* PublicManager::s_DrawPanelItemFunc;
IPluginFunction* PublicManager::s_DrawPanelTextFunc;
IPluginFunction* PublicManager::s_CanPanelDrawFlagsFunc;
IPluginFunction* PublicManager::s_SetPanelKeysFunc;
IPluginFunction* PublicManager::s_SendPanelToClientFunc;
IPluginFunction* PublicManager::s_GetPanelTextRemainingFunc;
IPluginFunction* PublicManager::s_GetPanelCurrentKeyFunc;
IPluginFunction* PublicManager::s_SetPanelCurrentKeyFunc;
IPluginFunction* PublicManager::s_RedrawMenuItemFunc;
IPluginFunction* PublicManager::s_InternalShowMenuFunc;

// EVENTS.INC
IPluginFunction* PublicManager::s_HookEventFunc;
IPluginFunction* PublicManager::s_HookEventExFunc;
IPluginFunction* PublicManager::s_UnhookEventFunc;
IPluginFunction* PublicManager::s_CreateEventFunc;
IPluginFunction* PublicManager::s_FireEventFunc;
IPluginFunction* PublicManager::s_CancelCreatedEventFunc;
IPluginFunction* PublicManager::s_GetEventBoolFunc;
IPluginFunction* PublicManager::s_SetEventBoolFunc;
IPluginFunction* PublicManager::s_GetEventIntFunc;
IPluginFunction* PublicManager::s_SetEventIntFunc;
IPluginFunction* PublicManager::s_GetEventFloatFunc;
IPluginFunction* PublicManager::s_SetEventFloatFunc;
IPluginFunction* PublicManager::s_GetEventStringFunc;
IPluginFunction* PublicManager::s_SetEventStringFunc;
IPluginFunction* PublicManager::s_GetEventNameFunc;
IPluginFunction* PublicManager::s_SetEventBroadcastFunc;

// DBI.INC
IPluginFunction* PublicManager::s_SQL_ConnectFunc;
IPluginFunction* PublicManager::s_SQL_ConnectCustomFunc;
IPluginFunction* PublicManager::s_SQL_CheckConfigFunc;
IPluginFunction* PublicManager::s_SQL_GetDriverFunc;
IPluginFunction* PublicManager::s_SQL_ReadDriverFunc;
IPluginFunction* PublicManager::s_SQL_GetDriverIdentFunc;
IPluginFunction* PublicManager::s_SQL_GetDriverProductFunc;
IPluginFunction* PublicManager::s_SQL_SetCharsetFunc;
IPluginFunction* PublicManager::s_SQL_GetAffectedRowsFunc;
IPluginFunction* PublicManager::s_SQL_GetInsertIdFunc;
IPluginFunction* PublicManager::s_SQL_GetErrorFunc;
IPluginFunction* PublicManager::s_SQL_EscapeStringFunc;
IPluginFunction* PublicManager::s_SQL_FormatQueryFunc;
IPluginFunction* PublicManager::s_SQL_FastQueryFunc;
IPluginFunction* PublicManager::s_SQL_QueryFunc;
IPluginFunction* PublicManager::s_SQL_PrepareQueryFunc;
IPluginFunction* PublicManager::s_SQL_FetchMoreResultsFunc;
IPluginFunction* PublicManager::s_SQL_HasResultSetFunc;
IPluginFunction* PublicManager::s_SQL_GetRowCountFunc;
IPluginFunction* PublicManager::s_SQL_GetFieldCountFunc;
IPluginFunction* PublicManager::s_SQL_FieldNumToNameFunc;
IPluginFunction* PublicManager::s_SQL_FieldNameToNumFunc;
IPluginFunction* PublicManager::s_SQL_FetchRowFunc;
IPluginFunction* PublicManager::s_SQL_MoreRowsFunc;
IPluginFunction* PublicManager::s_SQL_RewindFunc;
IPluginFunction* PublicManager::s_SQL_FetchStringFunc;
IPluginFunction* PublicManager::s_SQL_FetchFloatFunc;
IPluginFunction* PublicManager::s_SQL_FetchIntFunc;
IPluginFunction* PublicManager::s_SQL_IsFieldNullFunc;
IPluginFunction* PublicManager::s_SQL_FetchSizeFunc;
IPluginFunction* PublicManager::s_SQL_BindParamIntFunc;
IPluginFunction* PublicManager::s_SQL_BindParamFloatFunc;
IPluginFunction* PublicManager::s_SQL_BindParamStringFunc;
IPluginFunction* PublicManager::s_SQL_ExecuteFunc;
IPluginFunction* PublicManager::s_SQL_LockDatabaseFunc;
IPluginFunction* PublicManager::s_SQL_UnlockDatabaseFunc;
IPluginFunction* PublicManager::s_SQL_IsSameConnectionFunc;
IPluginFunction* PublicManager::s_SQL_TConnectFunc;
IPluginFunction* PublicManager::s_SQL_TQueryFunc;
IPluginFunction* PublicManager::s_SQL_CreateTransactionFunc;
IPluginFunction* PublicManager::s_SQL_AddQueryFunc;
IPluginFunction* PublicManager::s_SQL_ExecuteTransactionFunc;

// CSTRIKE.INC
IPluginFunction* PublicManager::s_CS_RespawnPlayerFunc;
IPluginFunction* PublicManager::s_CS_SwitchTeamFunc;
IPluginFunction* PublicManager::s_CS_DropWeaponFunc;
IPluginFunction* PublicManager::s_CS_TerminateRoundFunc;
IPluginFunction* PublicManager::s_CS_GetTranslatedWeaponAliasFunc;
IPluginFunction* PublicManager::s_CS_GetWeaponPriceFunc;
IPluginFunction* PublicManager::s_CS_GetClientClanTagFunc;
IPluginFunction* PublicManager::s_CS_SetClientClanTagFunc;
IPluginFunction* PublicManager::s_CS_GetTeamScoreFunc;
IPluginFunction* PublicManager::s_CS_SetTeamScoreFunc;
IPluginFunction* PublicManager::s_CS_GetMVPCountFunc;
IPluginFunction* PublicManager::s_CS_SetMVPCountFunc;
IPluginFunction* PublicManager::s_CS_GetClientContributionScoreFunc;
IPluginFunction* PublicManager::s_CS_SetClientContributionScoreFunc;
IPluginFunction* PublicManager::s_CS_GetClientAssistsFunc;
IPluginFunction* PublicManager::s_CS_SetClientAssistsFunc;
IPluginFunction* PublicManager::s_CS_AliasToWeaponIDFunc;
IPluginFunction* PublicManager::s_CS_WeaponIDToAliasFunc;
IPluginFunction* PublicManager::s_CS_IsValidWeaponIDFunc;
IPluginFunction* PublicManager::s_CS_UpdateClientModelFunc;
IPluginFunction* PublicManager::s_CS_ItemDefIndexToIDFunc;
IPluginFunction* PublicManager::s_CS_WeaponIDToItemDefIndexFunc;

// CONSOLE.INC
IPluginFunction* PublicManager::s_ServerCommandFunc = nullptr;
IPluginFunction* PublicManager::s_ServerCommandExFunc = nullptr;
IPluginFunction* PublicManager::s_InsertServerCommandFunc = nullptr;
IPluginFunction* PublicManager::s_ServerExecuteFunc = nullptr;
IPluginFunction* PublicManager::s_ClientCommandFunc = nullptr;
IPluginFunction* PublicManager::s_FakeClientCommandFunc = nullptr;
IPluginFunction* PublicManager::s_FakeClientCommandExFunc = nullptr;
IPluginFunction* PublicManager::s_FakeClientCommandKeyValuesFunc = nullptr;
IPluginFunction* PublicManager::s_PrintToServerFunc = nullptr;
IPluginFunction* PublicManager::s_PrintToConsoleFunc = nullptr;
IPluginFunction* PublicManager::s_ReplyToCommandFunc = nullptr;
IPluginFunction* PublicManager::s_GetCmdReplySourceFunc = nullptr;
IPluginFunction* PublicManager::s_SetCmdReplySourceFunc = nullptr;
IPluginFunction* PublicManager::s_IsChatTriggerFunc = nullptr;
IPluginFunction* PublicManager::s_ShowActivity2Func = nullptr;
IPluginFunction* PublicManager::s_ShowActivityFunc = nullptr;
IPluginFunction* PublicManager::s_ShowActivityExFunc = nullptr;
IPluginFunction* PublicManager::s_FormatActivitySourceFunc = nullptr;
IPluginFunction* PublicManager::s_RegServerCmdFunc = nullptr;
IPluginFunction* PublicManager::s_RegConsoleCmdFunc = nullptr;
IPluginFunction* PublicManager::s_RegAdminCmdFunc = nullptr;
IPluginFunction* PublicManager::s_GetCmdArgsFunc = nullptr;
IPluginFunction* PublicManager::s_GetCmdArgFunc = nullptr;
IPluginFunction* PublicManager::s_GetCmdArgStringFunc = nullptr;
IPluginFunction* PublicManager::s_GetCommandIteratorFunc = nullptr;
IPluginFunction* PublicManager::s_ReadCommandIteratorFunc = nullptr;
IPluginFunction* PublicManager::s_CheckCommandAccessFunc = nullptr;
IPluginFunction* PublicManager::s_CheckAccessFunc = nullptr;
IPluginFunction* PublicManager::s_GetCommandFlagsFunc = nullptr;
IPluginFunction* PublicManager::s_SetCommandFlagsFunc = nullptr;
IPluginFunction* PublicManager::s_FindFirstConCommandFunc = nullptr;
IPluginFunction* PublicManager::s_FindNextConCommandFunc = nullptr;
IPluginFunction* PublicManager::s_AddServerTagFunc = nullptr;
IPluginFunction* PublicManager::s_RemoveServerTagFunc = nullptr;
IPluginFunction* PublicManager::s_AddCommandListenerFunc = nullptr;
IPluginFunction* PublicManager::s_RemoveCommandListenerFunc = nullptr;

// CLIENT.INC
IPluginFunction* PublicManager::s_GetMaxHumanPlayersFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientCountFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientNameFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientIPFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientAuthIdFunc = nullptr;
IPluginFunction* PublicManager::s_GetSteamAccountIDFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientUserIdFunc = nullptr;
IPluginFunction* PublicManager::s_IsClientConnectedFunc = nullptr;
IPluginFunction* PublicManager::s_IsClientInGameFunc = nullptr;
IPluginFunction* PublicManager::s_IsClientInKickQueueFunc = nullptr;
IPluginFunction* PublicManager::s_IsClientAuthorizedFunc = nullptr;
IPluginFunction* PublicManager::s_IsFakeClientFunc = nullptr;
IPluginFunction* PublicManager::s_IsClientSourceTVFunc = nullptr;
IPluginFunction* PublicManager::s_IsClientReplayFunc = nullptr;
IPluginFunction* PublicManager::s_IsClientObserverFunc = nullptr;
IPluginFunction* PublicManager::s_IsPlayerAliveFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientInfoFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientTeamFunc = nullptr;
IPluginFunction* PublicManager::s_SetUserAdminFunc = nullptr;
IPluginFunction* PublicManager::s_GetUserAdminFunc = nullptr;
IPluginFunction* PublicManager::s_AddUserFlagsFunc = nullptr;
IPluginFunction* PublicManager::s_RemoveUserFlagsFunc = nullptr;
IPluginFunction* PublicManager::s_SetUserFlagBitsFunc = nullptr;
IPluginFunction* PublicManager::s_GetUserFlagBitsFunc = nullptr;
IPluginFunction* PublicManager::s_CanUserTargetFunc = nullptr;
IPluginFunction* PublicManager::s_RunAdminCacheChecksFunc = nullptr;
IPluginFunction* PublicManager::s_NotifyPostAdminCheckFunc = nullptr;
IPluginFunction* PublicManager::s_CreateFakeClientFunc = nullptr;
IPluginFunction* PublicManager::s_SetFakeClientConVarFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientHealthFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientModelFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientWeaponFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientMaxsFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientMinsFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientAbsAnglesFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientAbsOriginFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientArmorFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientDeathsFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientFragsFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientDataRateFunc = nullptr;
IPluginFunction* PublicManager::s_IsClientTimingOutFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientTimeFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientLatencyFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientAvgLatencyFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientAvgLossFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientAvgChokeFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientAvgDataFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientAvgPacketsFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientOfUserIdFunc = nullptr;
IPluginFunction* PublicManager::s_KickClientFunc = nullptr;
IPluginFunction* PublicManager::s_KickClientExFunc = nullptr;
IPluginFunction* PublicManager::s_ChangeClientTeamFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientSerialFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientFromSerialFunc = nullptr;

std::unordered_map<std::pair<int, SDKHookType>, void*, pair_hash> PublicManager::s_SDKHooksCallbacks;

std::unordered_map<Handle, MenuHandler> PublicManager::s_MenuHandlers;
std::unordered_map<Handle, VoteHandler> PublicManager::s_VoteHandlers;

std::unordered_map<std::string, EventHookCallback> PublicManager::s_EventHookCallbacksPre;
std::unordered_map<std::string, EventHookCallback> PublicManager::s_EventHookCallbacksPost;
std::unordered_map<std::string, EventHookCallback> PublicManager::s_EventHookCallbacksPostNoCopy;

std::unordered_map<int, SQLTCallbackFunc> PublicManager::s_SQLTConnectCallbacks;
std::unordered_map<int, int> PublicManager::s_SQLTConnectCallbacksData;
std::unordered_map<int, SQLTCallbackFunc> PublicManager::s_SQLTQueryCallbacks;
std::unordered_map<int, int> PublicManager::s_SQLTQueryCallbacksData;

#define STR(a) #a
#define LOAD_PTR(NAME) s_##NAME##Func = pContext->GetFunctionByName(STR(public_##NAME))

void PublicManager::InitOnPluginStart(IPluginContext* pContext)
{
	IPluginFunction* GetMaxClientsFunc = pContext->GetFunctionByName("public_GetMaxClients");
	GetMaxClientsFunc->Execute(&s_MaxClients);

	// ENTITY.INC
	LOAD_PTR(GetMaxEntities);
	LOAD_PTR(GetEntityCount);
	LOAD_PTR(IsValidEntity);
	LOAD_PTR(IsValidEdict);
	LOAD_PTR(IsEntNetworkable);
	LOAD_PTR(CreateEdict);
	LOAD_PTR(RemoveEdict);
	LOAD_PTR(RemoveEntity);
	LOAD_PTR(GetEdictFlags);
	LOAD_PTR(SetEdictFlags);
	LOAD_PTR(GetEdictClassname);
	LOAD_PTR(GetEntityNetClass);
	LOAD_PTR(ChangeEdictState);
	LOAD_PTR(GetEntData);
	LOAD_PTR(SetEntData);
	LOAD_PTR(GetEntDataFloat);
	LOAD_PTR(SetEntDataFloat);
	LOAD_PTR(GetEntDataEnt2);
	LOAD_PTR(SetEntDataEnt2);
	LOAD_PTR(GetEntDataVector);
	LOAD_PTR(SetEntDataVector);
	LOAD_PTR(GetEntDataString);
	LOAD_PTR(SetEntDataString);
	LOAD_PTR(FindSendPropInfo);
	LOAD_PTR(FindDataMapInfo);
	LOAD_PTR(GetEntProp);
	LOAD_PTR(SetEntProp);
	LOAD_PTR(GetEntPropFloat);
	LOAD_PTR(SetEntPropFloat);
	LOAD_PTR(GetEntPropEnt);
	LOAD_PTR(SetEntPropEnt);
	LOAD_PTR(GetEntPropVector);
	LOAD_PTR(SetEntPropVector);
	LOAD_PTR(GetEntPropString);
	LOAD_PTR(SetEntPropString);
	LOAD_PTR(GetEntPropArraySize);
	LOAD_PTR(GetEntityAddress);

	// SDKTOOLS_FUNCTIONS.INC
	LOAD_PTR(RemovePlayerItem);
	LOAD_PTR(GivePlayerItem);
	LOAD_PTR(GetPlayerWeaponSlot);
	LOAD_PTR(IgniteEntity);
	LOAD_PTR(ExtinguishEntity);
	LOAD_PTR(TeleportEntity);
	LOAD_PTR(ForcePlayerSuicide);
	LOAD_PTR(SlapPlayer);
	LOAD_PTR(FindEntityByClassname);
	LOAD_PTR(GetClientEyeAngles);
	LOAD_PTR(CreateEntityByName);
	LOAD_PTR(DispatchSpawn);
	LOAD_PTR(DispatchKeyValue);
	LOAD_PTR(DispatchKeyValueFloat);
	LOAD_PTR(DispatchKeyValueVector);
	LOAD_PTR(GetClientAimTarget);
	LOAD_PTR(GetTeamCount);
	LOAD_PTR(GetTeamName);
	LOAD_PTR(GetTeamScore);
	LOAD_PTR(SetTeamScore);
	LOAD_PTR(GetTeamClientCount);
	LOAD_PTR(GetTeamEntity);
	LOAD_PTR(SetEntityModel);
	LOAD_PTR(GetPlayerDecalFile);
	LOAD_PTR(GetPlayerJingleFile);
	LOAD_PTR(GetServerNetStats);
	LOAD_PTR(EquipPlayerWeapon);
	LOAD_PTR(ActivateEntity);
	LOAD_PTR(SetClientInfo);
	LOAD_PTR(SetClientName);
	LOAD_PTR(GivePlayerAmmo);

	// SDKHOOKS.INC
	LOAD_PTR(SDKHook);
	LOAD_PTR(SDKHookEx);
	LOAD_PTR(SDKUnhook);
	LOAD_PTR(SDKHooks_TakeDamage);
	LOAD_PTR(SDKHooks_DropWeapon);

	// MENUS.INC
	LOAD_PTR(CreateMenu);
	LOAD_PTR(DisplayMenu);
	LOAD_PTR(DisplayMenuAtItem);
	LOAD_PTR(AddMenuItem);
	LOAD_PTR(InsertMenuItem);
	LOAD_PTR(RemoveMenuItem);
	LOAD_PTR(RemoveAllMenuItems);
	LOAD_PTR(GetMenuItem);
	LOAD_PTR(MenuShufflePerClient);
	LOAD_PTR(MenuSetClientMapping);
	LOAD_PTR(GetMenuSelectionPosition);
	LOAD_PTR(GetMenuItemCount);
	LOAD_PTR(SetMenuPagination);
	LOAD_PTR(GetMenuPagination);
	LOAD_PTR(GetMenuStyle);
	LOAD_PTR(SetMenuTitle);
	LOAD_PTR(GetMenuTitle);
	LOAD_PTR(CreatePanelFromMenu);
	LOAD_PTR(GetMenuExitButton);
	LOAD_PTR(SetMenuExitButton);
	LOAD_PTR(GetMenuExitBackButton);
	LOAD_PTR(SetMenuExitBackButton);
	LOAD_PTR(SetMenuNoVoteButton);
	LOAD_PTR(CancelMenu);
	LOAD_PTR(GetMenuOptionFlags);
	LOAD_PTR(SetMenuOptionFlags);
	LOAD_PTR(IsVoteInProgress);
	LOAD_PTR(CancelVote);
	LOAD_PTR(VoteMenu);
	LOAD_PTR(SetVoteResultCallback);
	LOAD_PTR(CheckVoteDelay);
	LOAD_PTR(IsClientInVotePool);
	LOAD_PTR(RedrawClientVoteMenu);
	LOAD_PTR(GetMenuStyleHandle);
	LOAD_PTR(CreatePanel);
	LOAD_PTR(CreateMenuEx);
	LOAD_PTR(GetClientMenu);
	LOAD_PTR(CancelClientMenu);
	LOAD_PTR(GetMaxPageItems);
	LOAD_PTR(GetPanelStyle);
	LOAD_PTR(SetPanelTitle);
	LOAD_PTR(DrawPanelItem);
	LOAD_PTR(DrawPanelText);
	LOAD_PTR(CanPanelDrawFlags);
	LOAD_PTR(SetPanelKeys);
	LOAD_PTR(SendPanelToClient);
	LOAD_PTR(GetPanelTextRemaining);
	LOAD_PTR(GetPanelCurrentKey);
	LOAD_PTR(SetPanelCurrentKey);
	LOAD_PTR(RedrawMenuItem);
	LOAD_PTR(InternalShowMenu);

	// EVENTS.INC
	LOAD_PTR(HookEvent);
	LOAD_PTR(HookEventEx);
	LOAD_PTR(UnhookEvent);
	LOAD_PTR(CreateEvent);
	LOAD_PTR(FireEvent);
	LOAD_PTR(CancelCreatedEvent);
	LOAD_PTR(GetEventBool);
	LOAD_PTR(SetEventBool);
	LOAD_PTR(GetEventInt);
	LOAD_PTR(SetEventInt);
	LOAD_PTR(GetEventFloat);
	LOAD_PTR(SetEventFloat);
	LOAD_PTR(GetEventString);
	LOAD_PTR(SetEventString);
	LOAD_PTR(GetEventName);
	LOAD_PTR(SetEventBroadcast);

	// DBI.INC
	LOAD_PTR(SQL_Connect);
	LOAD_PTR(SQL_ConnectCustom);
	LOAD_PTR(SQL_CheckConfig);
	LOAD_PTR(SQL_GetDriver);
	LOAD_PTR(SQL_ReadDriver);
	LOAD_PTR(SQL_GetDriverIdent);
	LOAD_PTR(SQL_GetDriverProduct);
	LOAD_PTR(SQL_SetCharset);
	LOAD_PTR(SQL_GetAffectedRows);
	LOAD_PTR(SQL_GetInsertId);
	LOAD_PTR(SQL_GetError);
	LOAD_PTR(SQL_EscapeString);
	LOAD_PTR(SQL_FormatQuery);
	LOAD_PTR(SQL_FastQuery);
	LOAD_PTR(SQL_Query);
	LOAD_PTR(SQL_PrepareQuery);
	LOAD_PTR(SQL_FetchMoreResults);
	LOAD_PTR(SQL_HasResultSet);
	LOAD_PTR(SQL_GetRowCount);
	LOAD_PTR(SQL_GetFieldCount);
	LOAD_PTR(SQL_FieldNumToName);
	LOAD_PTR(SQL_FieldNameToNum);
	LOAD_PTR(SQL_FetchRow);
	LOAD_PTR(SQL_MoreRows);
	LOAD_PTR(SQL_Rewind);
	LOAD_PTR(SQL_FetchString);
	LOAD_PTR(SQL_FetchFloat);
	LOAD_PTR(SQL_FetchInt);
	LOAD_PTR(SQL_IsFieldNull);
	LOAD_PTR(SQL_FetchSize);
	LOAD_PTR(SQL_BindParamInt);
	LOAD_PTR(SQL_BindParamFloat);
	LOAD_PTR(SQL_BindParamString);
	LOAD_PTR(SQL_Execute);
	LOAD_PTR(SQL_LockDatabase);
	LOAD_PTR(SQL_UnlockDatabase);
	LOAD_PTR(SQL_IsSameConnection);
	LOAD_PTR(SQL_TConnect);
	LOAD_PTR(SQL_TQuery);
	LOAD_PTR(SQL_CreateTransaction);
	LOAD_PTR(SQL_AddQuery);
	LOAD_PTR(SQL_ExecuteTransaction);

	// CSTRIKE.INC
	LOAD_PTR(CS_RespawnPlayer);
	LOAD_PTR(CS_SwitchTeam);
	LOAD_PTR(CS_DropWeapon);
	LOAD_PTR(CS_TerminateRound);
	LOAD_PTR(CS_GetTranslatedWeaponAlias);
	LOAD_PTR(CS_GetWeaponPrice);
	LOAD_PTR(CS_GetClientClanTag);
	LOAD_PTR(CS_SetClientClanTag);
	LOAD_PTR(CS_GetTeamScore);
	LOAD_PTR(CS_SetTeamScore);
	LOAD_PTR(CS_GetMVPCount);
	LOAD_PTR(CS_SetMVPCount);
	LOAD_PTR(CS_GetClientContributionScore);
	LOAD_PTR(CS_SetClientContributionScore);
	LOAD_PTR(CS_GetClientAssists);
	LOAD_PTR(CS_SetClientAssists);
	LOAD_PTR(CS_AliasToWeaponID);
	LOAD_PTR(CS_WeaponIDToAlias);
	LOAD_PTR(CS_IsValidWeaponID);
	LOAD_PTR(CS_UpdateClientModel);
	LOAD_PTR(CS_ItemDefIndexToID);
	LOAD_PTR(CS_WeaponIDToItemDefIndex);

	// CONSOLE.INC
	LOAD_PTR(ServerCommand);
	LOAD_PTR(ServerCommandEx);
	LOAD_PTR(InsertServerCommand);
	LOAD_PTR(ServerExecute);
	LOAD_PTR(ClientCommand);
	LOAD_PTR(FakeClientCommand);
	LOAD_PTR(FakeClientCommandEx);
	LOAD_PTR(FakeClientCommandKeyValues);
	LOAD_PTR(PrintToServer);
	LOAD_PTR(PrintToConsole);
	LOAD_PTR(ReplyToCommand);
	LOAD_PTR(GetCmdReplySource);
	LOAD_PTR(SetCmdReplySource);
	LOAD_PTR(IsChatTrigger);
	LOAD_PTR(ShowActivity2);
	LOAD_PTR(ShowActivity);
	LOAD_PTR(ShowActivityEx);
	LOAD_PTR(FormatActivitySource);
	LOAD_PTR(RegServerCmd);
	LOAD_PTR(RegConsoleCmd);
	LOAD_PTR(RegAdminCmd);
	LOAD_PTR(GetCmdArgs);
	LOAD_PTR(GetCmdArg);
	LOAD_PTR(GetCmdArgString);
	LOAD_PTR(GetCommandIterator);
	LOAD_PTR(ReadCommandIterator);
	LOAD_PTR(CheckCommandAccess);
	LOAD_PTR(CheckAccess);
	LOAD_PTR(GetCommandFlags);
	LOAD_PTR(SetCommandFlags);
	LOAD_PTR(FindFirstConCommand);
	LOAD_PTR(FindNextConCommand);
	LOAD_PTR(AddServerTag);
	LOAD_PTR(RemoveServerTag);
	LOAD_PTR(AddCommandListener);
	LOAD_PTR(RemoveCommandListener);

	// CLIENT.INC
	LOAD_PTR(GetMaxHumanPlayers); LOAD_PTR(GetClientCount); LOAD_PTR(GetClientName);
	LOAD_PTR(GetClientIP); LOAD_PTR(GetClientAuthId); LOAD_PTR(GetSteamAccountID);
	LOAD_PTR(GetClientUserId); LOAD_PTR(IsClientConnected); LOAD_PTR(IsClientInGame);
	LOAD_PTR(IsClientInKickQueue); LOAD_PTR(IsClientAuthorized); LOAD_PTR(IsFakeClient);
	LOAD_PTR(IsClientSourceTV);
	LOAD_PTR(IsClientReplay);
	LOAD_PTR(IsClientObserver);
	LOAD_PTR(IsPlayerAlive);
	LOAD_PTR(GetClientInfo);
	LOAD_PTR(GetClientTeam);
	LOAD_PTR(SetUserAdmin);
	LOAD_PTR(GetUserAdmin);
	LOAD_PTR(AddUserFlags);
	LOAD_PTR(RemoveUserFlags);
	LOAD_PTR(SetUserFlagBits);
	LOAD_PTR(GetUserFlagBits);
	LOAD_PTR(CanUserTarget);
	LOAD_PTR(RunAdminCacheChecks);
	LOAD_PTR(NotifyPostAdminCheck);
	LOAD_PTR(CreateFakeClient);
	LOAD_PTR(SetFakeClientConVar);
	LOAD_PTR(GetClientHealth);
	LOAD_PTR(GetClientModel);
	LOAD_PTR(GetClientWeapon);
	LOAD_PTR(GetClientMaxs);
	LOAD_PTR(GetClientMins);
	LOAD_PTR(GetClientAbsAngles);
	LOAD_PTR(GetClientAbsOrigin);
	LOAD_PTR(GetClientArmor);
	LOAD_PTR(GetClientDeaths);
	LOAD_PTR(GetClientFrags);
	LOAD_PTR(GetClientDataRate);
	LOAD_PTR(IsClientTimingOut);
	LOAD_PTR(GetClientTime);
	LOAD_PTR(GetClientLatency);
	LOAD_PTR(GetClientAvgLatency);
	LOAD_PTR(GetClientAvgLoss);
	LOAD_PTR(GetClientAvgChoke);
	LOAD_PTR(GetClientAvgData);
	LOAD_PTR(GetClientAvgPackets);
	LOAD_PTR(GetClientOfUserId);
	LOAD_PTR(KickClient);
	LOAD_PTR(KickClientEx);
	LOAD_PTR(ChangeClientTeam);
	LOAD_PTR(GetClientSerial);
	LOAD_PTR(GetClientFromSerial);
}

// CSTRIKE.INC
void PublicManager::CS_RespawnPlayer(int client) { ExecFunc(s_CS_RespawnPlayerFunc, client); }
void PublicManager::CS_SwitchTeam(int client, int team) { ExecFunc(s_CS_SwitchTeamFunc, client, team); }
void PublicManager::CS_DropWeapon(int client, int weaponIndex, bool toss, bool blockhook) { ExecFunc(s_CS_DropWeaponFunc, client, weaponIndex, toss, blockhook); }
void PublicManager::CS_TerminateRound(float delay, CSRoundEndReason reason, bool blockhook) { ExecFunc(s_CS_TerminateRoundFunc, delay, reason, blockhook); }
void PublicManager::CS_GetTranslatedWeaponAlias(const char* alias, char* weapon, int size)
{
	s_CS_GetTranslatedWeaponAliasFunc->PushString(alias);
	s_CS_GetTranslatedWeaponAliasFunc->PushStringEx(weapon, size, 0, 1);
	s_CS_GetTranslatedWeaponAliasFunc->PushCell(size);
	ExecAndReturn(s_CS_GetTranslatedWeaponAliasFunc);
}
int PublicManager::CS_GetWeaponPrice(int client, CSWeaponID id, bool defaultprice) { return ExecFunc(s_CS_GetWeaponPriceFunc, client, id, defaultprice); }
int PublicManager::CS_GetClientClanTag(int client, char* buffer, int size)
{
	s_CS_GetClientClanTagFunc->PushCell(client);
	s_CS_GetClientClanTagFunc->PushStringEx(buffer, size, 0, 1);
	s_CS_GetClientClanTagFunc->PushCell(size);
	return ExecAndReturn(s_CS_GetClientClanTagFunc);
}
void PublicManager::CS_SetClientClanTag(int client, const char* tag) { ExecFunc(s_CS_SetClientClanTagFunc, client, tag); }
int PublicManager::CS_GetTeamScore(int team) { return ExecFunc(s_CS_GetTeamScoreFunc, team); }
void PublicManager::CS_SetTeamScore(int team, int value) { ExecFunc(s_CS_SetTeamScoreFunc, team, value); }
int PublicManager::CS_GetMVPCount(int client) { return ExecFunc(s_CS_GetMVPCountFunc, client); }
void PublicManager::CS_SetMVPCount(int client, int value) { ExecFunc(s_CS_SetMVPCountFunc, client, value); }
int PublicManager::CS_GetClientContributionScore(int client) { return ExecFunc(s_CS_GetClientContributionScoreFunc, client); }
void PublicManager::CS_SetClientContributionScore(int client, int value) { ExecFunc(s_CS_SetClientContributionScoreFunc, client, value); }
int PublicManager::CS_GetClientAssists(int client) { return ExecFunc(s_CS_GetClientAssistsFunc, client); }
void PublicManager::CS_SetClientAssists(int client, int value) { ExecFunc(s_CS_SetClientAssistsFunc, client, value); }
CSWeaponID PublicManager::CS_AliasToWeaponID(const char* alias) { return static_cast<CSWeaponID>(ExecFunc(s_CS_AliasToWeaponIDFunc, alias)); }
int PublicManager::CS_WeaponIDToAlias(CSWeaponID weaponID, char* destination, int len) { return ExecFunc(s_CS_WeaponIDToAliasFunc, weaponID, destination, len); }
bool PublicManager::CS_IsValidWeaponID(CSWeaponID id) { return static_cast<bool>(ExecFunc(s_CS_IsValidWeaponIDFunc, id)); }
void PublicManager::CS_UpdateClientModel(int client) { ExecFunc(s_CS_UpdateClientModelFunc, client); }
CSWeaponID PublicManager::CS_ItemDefIndexToID(int iDefIndex) { return static_cast<CSWeaponID>(ExecFunc(s_CS_ItemDefIndexToIDFunc, iDefIndex)); }
int PublicManager::CS_WeaponIDToItemDefIndex(CSWeaponID id) { return ExecFunc(s_CS_WeaponIDToItemDefIndexFunc, id); }

// CONSOLE.INC
void PublicManager::ServerExecute() { ExecFunc(s_ServerExecuteFunc); }
ReplySource PublicManager::GetCmdReplySource() { return static_cast<ReplySource>(ExecFunc(s_GetCmdReplySourceFunc)); }
ReplySource PublicManager::SetCmdReplySource(ReplySource source) { return static_cast<ReplySource>(ExecFunc(s_SetCmdReplySourceFunc, source)); }
bool PublicManager::IsChatTrigger() { return ExecFunc(s_IsChatTriggerFunc); }
bool PublicManager::FormatActivitySource(int client, int target, const char* namebuf, int maxlength) { return ExecFunc(s_FormatActivitySourceFunc, client, target, namebuf, maxlength); }
void PublicManager::RegServerCmd(const char* cmd, const char* description, int flags) { ExecFunc(s_RegServerCmdFunc, cmd, description, flags); }
void PublicManager::RegConsoleCmd(const char* command, const char* description, int flags) { ExecFunc(s_RegConsoleCmdFunc, command, description, flags); }
void PublicManager::RegAdminCmd(const char* cmd, int adminflags, const char* description, const char* group, int flags) { ExecFunc(s_RegAdminCmdFunc, cmd, adminflags, description, group, flags); }
int PublicManager::GetCmdArgs() { return ExecFunc(s_GetCmdArgsFunc); }
int PublicManager::GetCmdArg(int argnum, char* buffer, int maxlength) { return ExecFunc(s_GetCmdArgFunc, argnum, buffer, maxlength); }
int PublicManager::GetCmdArgString(char* buffer, int maxlength) { return ExecFunc(s_GetCmdArgStringFunc, buffer, maxlength); }
Handle PublicManager::GetCommandIterator() { return ExecFunc(s_GetCommandIteratorFunc); }
bool PublicManager::ReadCommandIterator(Handle iter, char* name, int nameLen, int& eflags, char* desc, int descLen)
{
	PushArg(s_ReadCommandIteratorFunc, iter);
	PushArg(s_ReadCommandIteratorFunc, name);
	PushArg(s_ReadCommandIteratorFunc, nameLen);
	PushArgRef(s_ReadCommandIteratorFunc, eflags);
	PushArg(s_ReadCommandIteratorFunc, desc);
	PushArg(s_ReadCommandIteratorFunc, descLen);
	return ExecAndReturn(s_ReadCommandIteratorFunc);
}
bool PublicManager::CheckCommandAccess(int client, const char* command, int flags, bool override_only) { return ExecFunc(s_CheckCommandAccessFunc, client, command, flags, override_only); }
bool PublicManager::CheckAccess(AdminId id, const char* command, int flags, bool override_only) { return ExecFunc(s_CheckAccessFunc, id, command, flags, override_only); }
int PublicManager::GetCommandFlags(const char* name) { return ExecFunc(s_GetCommandFlagsFunc, name); }
bool PublicManager::SetCommandFlags(const char* name, int flags) { return ExecFunc(s_SetCommandFlagsFunc, name, flags); }
Handle PublicManager::FindFirstConCommand(char* buffer, int max_size, bool& isCommand, int& flags, char* description, int descrmax_size)
{
	PushArg(s_FindFirstConCommandFunc, buffer);
	PushArg(s_FindFirstConCommandFunc, max_size);
	PushArgRef(s_FindFirstConCommandFunc, reinterpret_cast<int&>(isCommand));
	PushArgRef(s_FindFirstConCommandFunc, flags);
	PushArg(s_FindFirstConCommandFunc, description);
	PushArg(s_FindFirstConCommandFunc, descrmax_size);
	return ExecAndReturn(s_FindFirstConCommandFunc);
}
bool PublicManager::FindNextConCommand(Handle search, char* buffer, int max_size, bool& isCommand, int& flags, char* description, int descrmax_size)
{
	PushArg(s_FindFirstConCommandFunc, search);
	PushArg(s_FindFirstConCommandFunc, buffer);
	PushArg(s_FindFirstConCommandFunc, max_size);
	PushArgRef(s_FindFirstConCommandFunc, reinterpret_cast<int&>(isCommand));
	PushArgRef(s_FindFirstConCommandFunc, flags);
	PushArg(s_FindFirstConCommandFunc, description);
	PushArg(s_FindFirstConCommandFunc, descrmax_size);
	return ExecAndReturn(s_FindNextConCommandFunc);
}
void PublicManager::AddServerTag(const char* tag) { ExecFunc(s_AddServerTagFunc, tag); }
void PublicManager::RemoveServerTag(const char* tag) { ExecFunc(s_RemoveServerTagFunc, tag); }
bool PublicManager::AddCommandListener(const char* command) { return ExecFunc(s_AddCommandListenerFunc, command); }
void PublicManager::RemoveCommandListener(const char* command) { ExecFunc(s_RemoveCommandListenerFunc, command); }

// CLIENTS.INC
int     PublicManager::GetMaxHumanPlayers() { return ExecFunc(s_GetMaxHumanPlayersFunc); }
int     PublicManager::GetClientCount(bool inGameOnly) { return ExecFunc(s_GetClientCountFunc, inGameOnly); }
bool    PublicManager::GetClientName(int client, char* name, int maxlen) { return ExecFunc(s_GetClientNameFunc, client, name, maxlen); }
bool    PublicManager::GetClientIP(int client, char* ip, int maxlen, bool remport) { return ExecFunc(s_GetClientIPFunc, client, ip, maxlen, remport); }
bool    PublicManager::GetClientAuthId(int client, AuthIdType authType, char* auth, int maxlen, bool validate) { return ExecFunc(s_GetClientAuthIdFunc, client, authType, auth, maxlen, validate); }
int     PublicManager::GetSteamAccountID(int client, bool validate) { return ExecFunc(s_GetSteamAccountIDFunc, client, validate); }
int     PublicManager::GetClientUserId(int client) { return ExecFunc(s_GetClientUserIdFunc, client); }
bool    PublicManager::IsClientConnected(int client) { return ExecFunc(s_IsClientConnectedFunc, client); }
bool    PublicManager::IsClientInGame(int client) { return ExecFunc(s_IsClientInGameFunc, client); }
bool    PublicManager::IsClientInKickQueue(int client) { return ExecFunc(s_IsClientInKickQueueFunc, client); }
bool    PublicManager::IsClientAuthorized(int client) { return ExecFunc(s_IsClientAuthorizedFunc, client); }
bool    PublicManager::IsFakeClient(int client) { return ExecFunc(s_IsFakeClientFunc, client); }
bool    PublicManager::IsClientSourceTV(int client) { return ExecFunc(s_IsClientSourceTVFunc, client); }
bool    PublicManager::IsClientReplay(int client) { return ExecFunc(s_IsClientReplayFunc, client); }
bool    PublicManager::IsClientObserver(int client) { return ExecFunc(s_IsClientObserverFunc, client); }
bool    PublicManager::IsPlayerAlive(int client) { return ExecFunc(s_IsPlayerAliveFunc, client); }
bool    PublicManager::GetClientInfo(int client, const char* key, char* value, int maxlen) { return ExecFunc(s_GetClientInfoFunc, client, key, value, maxlen); }
int     PublicManager::GetClientTeam(int client) { return ExecFunc(s_GetClientTeamFunc, client); }
void    PublicManager::SetUserAdmin(int client, AdminId id, bool temp) { ExecFunc(s_SetUserAdminFunc, client, id, temp); }
AdminId PublicManager::GetUserAdmin(int client) { return ExecFunc(s_GetUserAdminFunc, client); }
void    PublicManager::SetUserFlagBits(int client, int flags) { ExecFunc(s_SetUserFlagBitsFunc, client, flags); }
int     PublicManager::GetUserFlagBits(int client) { return ExecFunc(s_GetUserFlagBitsFunc, client); }
bool    PublicManager::CanUserTarget(int client, int target) { return ExecFunc(s_CanUserTargetFunc, client, target); }
bool    PublicManager::RunAdminCacheChecks(int client) { return ExecFunc(s_RunAdminCacheChecksFunc, client); }
void    PublicManager::NotifyPostAdminCheck(int client) { ExecFunc(s_NotifyPostAdminCheckFunc, client); }
int     PublicManager::CreateFakeClient(const char* name) { return ExecFunc(s_CreateFakeClientFunc, name); }
void    PublicManager::SetFakeClientConVar(int client, const char* cvar, const char* value) { ExecFunc(s_SetFakeClientConVarFunc, client, cvar, value); }
int     PublicManager::GetClientHealth(int client) { return ExecFunc(s_GetClientHealthFunc, client); }
void    PublicManager::GetClientModel(int client, char* model, int maxlen)
{
	PushArg(s_GetClientModelFunc, client);
	s_GetClientModelFunc->PushStringEx(model, maxlen, 0, 1);
	PushArg(s_GetClientModelFunc, maxlen);
	ExecAndReturn(s_GetClientModelFunc);
}
void    PublicManager::GetClientWeapon(int client, char* weapon, int maxlen)
{
	PushArg(s_GetClientWeaponFunc, client);
	s_GetClientWeaponFunc->PushStringEx(weapon, maxlen, 0, 1);
	PushArg(s_GetClientWeaponFunc, maxlen);
	ExecAndReturn(s_GetClientWeaponFunc);
}
void    PublicManager::GetClientMaxs(int client, float vec[3]) { ExecFunc(s_GetClientMaxsFunc, client, vec); }
void    PublicManager::GetClientMins(int client, float vec[3]) { ExecFunc(s_GetClientMinsFunc, client, vec); }
void    PublicManager::GetClientAbsAngles(int client, float ang[3]) { ExecFunc(s_GetClientAbsAnglesFunc, client, ang); }
void    PublicManager::GetClientAbsOrigin(int client, float vec[3]) { ExecFunc(s_GetClientAbsOriginFunc, client, vec); }
int     PublicManager::GetClientArmor(int client) { return ExecFunc(s_GetClientArmorFunc, client); }
int     PublicManager::GetClientDeaths(int client) { return ExecFunc(s_GetClientDeathsFunc, client); }
int     PublicManager::GetClientFrags(int client) { return ExecFunc(s_GetClientFragsFunc, client); }
int     PublicManager::GetClientDataRate(int client) { return ExecFunc(s_GetClientDataRateFunc, client); }
bool    PublicManager::IsClientTimingOut(int client) { return ExecFunc(s_IsClientTimingOutFunc, client); }
float   PublicManager::GetClientTime(int client) { return sp_ctof(ExecFunc(s_GetClientTimeFunc, client)); }
float   PublicManager::GetClientLatency(int client, NetFlow flow) { return sp_ctof(ExecFunc(s_GetClientLatencyFunc, client, flow)); }
float   PublicManager::GetClientAvgLatency(int client, NetFlow flow) { return sp_ctof(ExecFunc(s_GetClientAvgLatencyFunc, client, flow)); }
float   PublicManager::GetClientAvgLoss(int client, NetFlow flow) { return sp_ctof(ExecFunc(s_GetClientAvgLossFunc, client, flow)); }
float   PublicManager::GetClientAvgChoke(int client, NetFlow flow) { return sp_ctof(ExecFunc(s_GetClientAvgChokeFunc, client, flow)); }
float   PublicManager::GetClientAvgData(int client, NetFlow flow) { return sp_ctof(ExecFunc(s_GetClientAvgDataFunc, client, flow)); }
float   PublicManager::GetClientAvgPackets(int client, NetFlow flow) { return sp_ctof(ExecFunc(s_GetClientAvgPacketsFunc, client, flow)); }
int     PublicManager::GetClientOfUserId(int userid) { return ExecFunc(s_GetClientOfUserIdFunc, userid); }
void    PublicManager::KickClient(int client, const char* message) { ExecFunc(s_KickClientFunc, client, message); }
void    PublicManager::KickClientEx(int client, const char* message) { ExecFunc(s_KickClientExFunc, client, message); }
void    PublicManager::ChangeClientTeam(int client, int team) { ExecFunc(s_ChangeClientTeamFunc, client, team); }
int     PublicManager::GetClientSerial(int client) { return ExecFunc(s_GetClientSerialFunc, client); }
int     PublicManager::GetClientFromSerial(int serial) { return ExecFunc(s_GetClientFromSerialFunc, serial); }
