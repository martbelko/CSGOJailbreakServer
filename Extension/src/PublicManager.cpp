#include "PublicManager.h"

int PublicManager::s_MaxClients = 0;

// OWN
IPluginFunction* PublicManager::s_SDKCallSmoke3Func;
IPluginFunction* PublicManager::s_SDKCallSmoke4Func;

// CONVARS.INC
IPluginFunction* PublicManager::s_CreateConVarFunc;
IPluginFunction* PublicManager::s_FindConVarFunc;
IPluginFunction* PublicManager::s_HookConVarChangeFunc;
IPluginFunction* PublicManager::s_UnhookConVarChangeFunc;
IPluginFunction* PublicManager::s_GetConVarBoolFunc;
IPluginFunction* PublicManager::s_SetConVarBoolFunc;
IPluginFunction* PublicManager::s_GetConVarIntFunc;
IPluginFunction* PublicManager::s_SetConVarIntFunc;
IPluginFunction* PublicManager::s_GetConVarFloatFunc;
IPluginFunction* PublicManager::s_SetConVarFloatFunc;
IPluginFunction* PublicManager::s_GetConVarStringFunc;
IPluginFunction* PublicManager::s_SetConVarStringFunc;
IPluginFunction* PublicManager::s_ResetConVarFunc;
IPluginFunction* PublicManager::s_GetConVarDefaultFunc;
IPluginFunction* PublicManager::s_GetConVarFlagsFunc;
IPluginFunction* PublicManager::s_SetConVarFlagsFunc;
IPluginFunction* PublicManager::s_GetConVarBoundsFunc;
IPluginFunction* PublicManager::s_SetConVarBoundsFunc;
IPluginFunction* PublicManager::s_GetConVarNameFunc;
IPluginFunction* PublicManager::s_SendConVarValueFunc;
IPluginFunction* PublicManager::s_QueryClientConVarFunc;

// SOURCEMOD.INC
IPluginFunction* PublicManager::s_GetMyHandleFunc;
IPluginFunction* PublicManager::s_GetPluginIteratorFunc;
IPluginFunction* PublicManager::s_MorePluginsFunc;
IPluginFunction* PublicManager::s_ReadPluginFunc;
IPluginFunction* PublicManager::s_GetPluginStatusFunc;
IPluginFunction* PublicManager::s_GetPluginFilenameFunc;
IPluginFunction* PublicManager::s_IsPluginDebuggingFunc;
IPluginFunction* PublicManager::s_GetPluginInfoFunc;
IPluginFunction* PublicManager::s_FindPluginByNumberFunc;
IPluginFunction* PublicManager::s_SetFailStateFunc;
IPluginFunction* PublicManager::s_ThrowErrorFunc;
IPluginFunction* PublicManager::s_LogStackTraceFunc;
IPluginFunction* PublicManager::s_GetTimeFunc;
IPluginFunction* PublicManager::s_FormatTimeFunc;
IPluginFunction* PublicManager::s_LoadGameConfigFileFunc;
IPluginFunction* PublicManager::s_GameConfGetOffsetFunc;
IPluginFunction* PublicManager::s_GameConfGetKeyValueFunc;
IPluginFunction* PublicManager::s_GameConfGetAddressFunc;
IPluginFunction* PublicManager::s_GetSysTickCountFunc;
IPluginFunction* PublicManager::s_AutoExecConfigFunc;
IPluginFunction* PublicManager::s_RegPluginLibraryFunc;
IPluginFunction* PublicManager::s_LibraryExistsFunc;
IPluginFunction* PublicManager::s_GetExtensionFileStatusFunc;
IPluginFunction* PublicManager::s_ReadMapListFunc;
IPluginFunction* PublicManager::s_SetMapListCompatBindFunc;
IPluginFunction* PublicManager::s_GetFeatureStatusFunc;
IPluginFunction* PublicManager::s_RequireFeatureFunc;
IPluginFunction* PublicManager::s_LoadFromAddressFunc;
IPluginFunction* PublicManager::s_StoreToAddressFunc;

// SDKTOOLS.INC
IPluginFunction* PublicManager::s_StartPrepSDKCallFunc;
IPluginFunction* PublicManager::s_PrepSDKCall_SetVirtualFunc;
IPluginFunction* PublicManager::s_PrepSDKCall_SetSignatureFunc;
IPluginFunction* PublicManager::s_PrepSDKCall_SetAddressFunc;
IPluginFunction* PublicManager::s_PrepSDKCall_SetFromConfFunc;
IPluginFunction* PublicManager::s_PrepSDKCall_SetReturnInfoFunc;
IPluginFunction* PublicManager::s_PrepSDKCall_AddParameterFunc;
IPluginFunction* PublicManager::s_EndPrepSDKCallFunc;
IPluginFunction* PublicManager::s_SDKCall0Func;
IPluginFunction* PublicManager::s_SDKCall1Func;
IPluginFunction* PublicManager::s_SDKCall2Func;
IPluginFunction* PublicManager::s_SDKCall3Func;
IPluginFunction* PublicManager::s_SDKCall4Func;
IPluginFunction* PublicManager::s_SDKCall5Func;
IPluginFunction* PublicManager::s_SDKCall6Func;
IPluginFunction* PublicManager::s_SDKCall7Func;
IPluginFunction* PublicManager::s_SDKCall8Func;
IPluginFunction* PublicManager::s_SDKCall9Func;
IPluginFunction* PublicManager::s_SDKCall10Func;
IPluginFunction* PublicManager::s_GetPlayerResourceEntityFunc;

// SDKTOOLS_SOUND.INC
IPluginFunction* PublicManager::s_PrefetchSoundFunc;
IPluginFunction* PublicManager::s_EmitAmbientSoundFunc;
IPluginFunction* PublicManager::s_FadeClientVolumeFunc;
IPluginFunction* PublicManager::s_StopSoundFunc;
IPluginFunction* PublicManager::s_EmitSoundFunc;
IPluginFunction* PublicManager::s_EmitSoundEntryFunc;
IPluginFunction* PublicManager::s_EmitSentenceFunc;
IPluginFunction* PublicManager::s_GetDistGainFromSoundLevelFunc;
IPluginFunction* PublicManager::s_AddAmbientSoundHookFunc;
IPluginFunction* PublicManager::s_AddNormalSoundHookFunc;
IPluginFunction* PublicManager::s_RemoveAmbientSoundHookFunc;
IPluginFunction* PublicManager::s_RemoveNormalSoundHookFunc;
IPluginFunction* PublicManager::s_GetGameSoundParamsFunc;
IPluginFunction* PublicManager::s_PrecacheScriptSoundFunc;

// COMMANDFILTERS.INC
IPluginFunction* PublicManager::s_ProcessTargetStringFunc;
IPluginFunction* PublicManager::s_AddMultiTargetFilterFunc;
IPluginFunction* PublicManager::s_RemoveMultiTargetFilterFunc;

// ADT_ARRAY.INC
IPluginFunction* PublicManager::s_CreateArrayFunc;
IPluginFunction* PublicManager::s_ClearArrayFunc;
IPluginFunction* PublicManager::s_CloneArrayFunc;
IPluginFunction* PublicManager::s_ResizeArrayFunc;
IPluginFunction* PublicManager::s_GetArraySizeFunc;
IPluginFunction* PublicManager::s_PushArrayCellFunc;
IPluginFunction* PublicManager::s_PushArrayStringFunc;
IPluginFunction* PublicManager::s_PushArrayArrayFunc;
IPluginFunction* PublicManager::s_GetArrayCellFunc;
IPluginFunction* PublicManager::s_GetArrayStringFunc;
IPluginFunction* PublicManager::s_GetArrayArrayFunc;
IPluginFunction* PublicManager::s_SetArrayCellFunc;
IPluginFunction* PublicManager::s_SetArrayStringFunc;
IPluginFunction* PublicManager::s_SetArrayArrayFunc;
IPluginFunction* PublicManager::s_ShiftArrayUpFunc;
IPluginFunction* PublicManager::s_RemoveFromArrayFunc;
IPluginFunction* PublicManager::s_SwapArrayItemsFunc;
IPluginFunction* PublicManager::s_FindStringInArrayFunc;
IPluginFunction* PublicManager::s_FindValueInArrayFunc;
IPluginFunction* PublicManager::s_GetArrayBlockSizeFunc;

// LANG.INC
IPluginFunction* PublicManager::s_LoadTranslationsFunc;
IPluginFunction* PublicManager::s_SetGlobalTransTargetFunc;
IPluginFunction* PublicManager::s_GetClientLanguageFunc;
IPluginFunction* PublicManager::s_GetServerLanguageFunc;
IPluginFunction* PublicManager::s_GetLanguageCountFunc;
IPluginFunction* PublicManager::s_GetLanguageInfoFunc;
IPluginFunction* PublicManager::s_SetClientLanguageFunc;
IPluginFunction* PublicManager::s_GetLanguageByCodeFunc;
IPluginFunction* PublicManager::s_GetLanguageByNameFunc;
IPluginFunction* PublicManager::s_TranslationPhraseExistsFunc;
IPluginFunction* PublicManager::s_IsTranslatedForLanguageFunc;

// SDKTOOLS_VOICE.INC
IPluginFunction* PublicManager::s_SetClientListeningFlagsFunc;
IPluginFunction* PublicManager::s_GetClientListeningFlagsFunc;
IPluginFunction* PublicManager::s_SetListenOverrideFunc;
IPluginFunction* PublicManager::s_GetListenOverrideFunc;
IPluginFunction* PublicManager::s_IsClientMutedFunc;

// STRING.INC
IPluginFunction* PublicManager::s_FormatFunc;

// GEOIP.INC
IPluginFunction* PublicManager::s_GeoipCode2Func;
IPluginFunction* PublicManager::s_GeoipCode3Func;
IPluginFunction* PublicManager::s_GeoipCountryFunc;

// SDKTOOLS_CLIENT.INC
IPluginFunction* PublicManager::s_InactivateClientFunc;
IPluginFunction* PublicManager::s_ReconnectClientFunc;

// SDKTOOLS_ENGINE.INC
IPluginFunction* PublicManager::s_SetClientViewEntityFunc;
IPluginFunction* PublicManager::s_SetLightStyleFunc;
IPluginFunction* PublicManager::s_GetClientEyePositionFunc;

// SDKTOOLS_TRACE.INC
IPluginFunction* PublicManager::s_TR_GetPointContentsFunc;
IPluginFunction* PublicManager::s_TR_GetPointContentsEntFunc;
IPluginFunction* PublicManager::s_TR_TraceRayFunc;
IPluginFunction* PublicManager::s_TR_TraceHullFunc;
IPluginFunction* PublicManager::s_TR_EnumerateEntitiesFunc;
IPluginFunction* PublicManager::s_TR_EnumerateEntitiesHullFunc;
IPluginFunction* PublicManager::s_TR_EnumerateEntitiesSphereFunc;
IPluginFunction* PublicManager::s_TR_EnumerateEntitiesBoxFunc;
IPluginFunction* PublicManager::s_TR_EnumerateEntitiesPointFunc;
IPluginFunction* PublicManager::s_TR_TraceRayFilterFunc;
IPluginFunction* PublicManager::s_TR_TraceHullFilterFunc;
IPluginFunction* PublicManager::s_TR_ClipRayToEntityFunc;
IPluginFunction* PublicManager::s_TR_ClipRayHullToEntityFunc;
IPluginFunction* PublicManager::s_TR_ClipCurrentRayToEntityFunc;
IPluginFunction* PublicManager::s_TR_TraceRayExFunc;
IPluginFunction* PublicManager::s_TR_TraceHullExFunc;
IPluginFunction* PublicManager::s_TR_TraceRayFilterExFunc;
IPluginFunction* PublicManager::s_TR_TraceHullFilterExFunc;
IPluginFunction* PublicManager::s_TR_ClipRayToEntityExFunc;
IPluginFunction* PublicManager::s_TR_ClipRayHullToEntityExFunc;
IPluginFunction* PublicManager::s_TR_ClipCurrentRayToEntityExFunc;
IPluginFunction* PublicManager::s_TR_GetFractionFunc;
IPluginFunction* PublicManager::s_TR_GetFractionLeftSolidFunc;
IPluginFunction* PublicManager::s_TR_GetStartPositionFunc;
IPluginFunction* PublicManager::s_TR_GetEndPositionFunc;
IPluginFunction* PublicManager::s_TR_GetEntityIndexFunc;
IPluginFunction* PublicManager::s_TR_GetDisplacementFlagsFunc;
IPluginFunction* PublicManager::s_TR_GetSurfaceNameFunc;
IPluginFunction* PublicManager::s_TR_GetSurfacePropsFunc;
IPluginFunction* PublicManager::s_TR_GetSurfaceFlagsFunc;
IPluginFunction* PublicManager::s_TR_GetPhysicsBoneFunc;
IPluginFunction* PublicManager::s_TR_AllSolidFunc;
IPluginFunction* PublicManager::s_TR_StartSolidFunc;
IPluginFunction* PublicManager::s_TR_DidHitFunc;
IPluginFunction* PublicManager::s_TR_GetHitGroupFunc;
IPluginFunction* PublicManager::s_TR_GetHitBoxIndexFunc;
IPluginFunction* PublicManager::s_TR_GetPlaneNormalFunc;
IPluginFunction* PublicManager::s_TR_PointOutsideWorldFunc;

// BITBUFFER.INC
IPluginFunction* PublicManager::s_BfWriteBoolFunc;
IPluginFunction* PublicManager::s_BfWriteByteFunc;
IPluginFunction* PublicManager::s_BfWriteCharFunc;
IPluginFunction* PublicManager::s_BfWriteShortFunc;
IPluginFunction* PublicManager::s_BfWriteWordFunc;
IPluginFunction* PublicManager::s_BfWriteNumFunc;
IPluginFunction* PublicManager::s_BfWriteFloatFunc;
IPluginFunction* PublicManager::s_BfWriteStringFunc;
IPluginFunction* PublicManager::s_BfWriteEntityFunc;
IPluginFunction* PublicManager::s_BfWriteAngleFunc;
IPluginFunction* PublicManager::s_BfWriteCoordFunc;
IPluginFunction* PublicManager::s_BfWriteVecCoordFunc;
IPluginFunction* PublicManager::s_BfWriteVecNormalFunc;
IPluginFunction* PublicManager::s_BfWriteAnglesFunc;
IPluginFunction* PublicManager::s_BfReadBoolFunc;
IPluginFunction* PublicManager::s_BfReadByteFunc;
IPluginFunction* PublicManager::s_BfReadCharFunc;
IPluginFunction* PublicManager::s_BfReadShortFunc;
IPluginFunction* PublicManager::s_BfReadWordFunc;
IPluginFunction* PublicManager::s_BfReadNumFunc;
IPluginFunction* PublicManager::s_BfReadFloatFunc;
IPluginFunction* PublicManager::s_BfReadStringFunc;
IPluginFunction* PublicManager::s_BfReadEntityFunc;
IPluginFunction* PublicManager::s_BfReadAngleFunc;
IPluginFunction* PublicManager::s_BfReadCoordFunc;
IPluginFunction* PublicManager::s_BfReadVecCoordFunc;
IPluginFunction* PublicManager::s_BfReadVecNormalFunc;
IPluginFunction* PublicManager::s_BfReadAnglesFunc;
IPluginFunction* PublicManager::s_BfGetNumBytesLeftFunc;

// LOGGING.INC
IPluginFunction* PublicManager::s_LogMessageFunc;
IPluginFunction* PublicManager::s_LogToFileFunc;
IPluginFunction* PublicManager::s_LogToFileExFunc;
IPluginFunction* PublicManager::s_LogActionFunc;
IPluginFunction* PublicManager::s_LogErrorFunc;
IPluginFunction* PublicManager::s_AddGameLogHookFunc;
IPluginFunction* PublicManager::s_RemoveGameLogHookFunc;

// SDKTOOLS_TEMPENTS.INC
IPluginFunction* PublicManager::s_AddTempEntHookFunc;
IPluginFunction* PublicManager::s_RemoveTempEntHookFunc;
IPluginFunction* PublicManager::s_TE_StartFunc;
IPluginFunction* PublicManager::s_TE_IsValidPropFunc;
IPluginFunction* PublicManager::s_TE_WriteNumFunc;
IPluginFunction* PublicManager::s_TE_ReadNumFunc;
IPluginFunction* PublicManager::s_TE_WriteFloatFunc;
IPluginFunction* PublicManager::s_TE_ReadFloatFunc;
IPluginFunction* PublicManager::s_TE_WriteVectorFunc;
IPluginFunction* PublicManager::s_TE_ReadVectorFunc;
IPluginFunction* PublicManager::s_TE_WriteAnglesFunc;
IPluginFunction* PublicManager::s_TE_WriteFloatArrayFunc;
IPluginFunction* PublicManager::s_TE_SendFunc;

// SDKTOOLS_GAMERULES.INC
IPluginFunction* PublicManager::s_GameRules_GetPropFunc;
IPluginFunction* PublicManager::s_GameRules_SetPropFunc;
IPluginFunction* PublicManager::s_GameRules_GetPropFloatFunc;
IPluginFunction* PublicManager::s_GameRules_SetPropFloatFunc;
IPluginFunction* PublicManager::s_GameRules_GetPropEntFunc;
IPluginFunction* PublicManager::s_GameRules_SetPropEntFunc;
IPluginFunction* PublicManager::s_GameRules_GetPropVectorFunc;
IPluginFunction* PublicManager::s_GameRules_SetPropVectorFunc;
IPluginFunction* PublicManager::s_GameRules_GetPropStringFunc;
IPluginFunction* PublicManager::s_GameRules_SetPropStringFunc;

// SDKTOOLS_ENTINPUT.INC
IPluginFunction* PublicManager::s_AcceptEntityInputFunc;

// SDKTOOLS_ENTOUTPUT.INC
IPluginFunction* PublicManager::s_HookEntityOutputFunc;
IPluginFunction* PublicManager::s_UnhookEntityOutputFunc;
IPluginFunction* PublicManager::s_HookSingleEntityOutputFunc;
IPluginFunction* PublicManager::s_UnhookSingleEntityOutputFunc;
IPluginFunction* PublicManager::s_FireEntityOutputFunc;

// HANDLES.INC
IPluginFunction* PublicManager::s_CloseHandleFunc;
IPluginFunction* PublicManager::s_CloneHandleFunc;

// ENTITY_PROP_STOCKS.INC
IPluginFunction* PublicManager::s_GetEntityFlagsFunc;
IPluginFunction* PublicManager::s_SetEntityFlagsFunc;
IPluginFunction* PublicManager::s_GetEntityMoveTypeFunc;
IPluginFunction* PublicManager::s_SetEntityMoveTypeFunc;
IPluginFunction* PublicManager::s_GetEntityRenderModeFunc;
IPluginFunction* PublicManager::s_SetEntityRenderModeFunc;
IPluginFunction* PublicManager::s_GetEntityRenderFxFunc;
IPluginFunction* PublicManager::s_SetEntityRenderFxFunc;
IPluginFunction* PublicManager::s_GetEntityRenderColorFunc;
IPluginFunction* PublicManager::s_SetEntityRenderColorFunc;
IPluginFunction* PublicManager::s_GetEntityGravityFunc;
IPluginFunction* PublicManager::s_SetEntityGravityFunc;
IPluginFunction* PublicManager::s_SetEntityHealthFunc;
IPluginFunction* PublicManager::s_GetClientButtonsFunc;

// HALFLIFE.INC
IPluginFunction* PublicManager::s_LogToGameFunc;
IPluginFunction* PublicManager::s_SetRandomSeedFunc;
IPluginFunction* PublicManager::s_IsMapValidFunc;
IPluginFunction* PublicManager::s_FindMapFunc;
IPluginFunction* PublicManager::s_GetMapDisplayNameFunc;
IPluginFunction* PublicManager::s_IsDedicatedServerFunc;
IPluginFunction* PublicManager::s_GetEngineTimeFunc;
IPluginFunction* PublicManager::s_GetGameTimeFunc;
IPluginFunction* PublicManager::s_GetGameTickCountFunc;
IPluginFunction* PublicManager::s_GetGameFrameTimeFunc;
IPluginFunction* PublicManager::s_GetGameDescriptionFunc;
IPluginFunction* PublicManager::s_GetGameFolderNameFunc;
IPluginFunction* PublicManager::s_GetCurrentMapFunc;
IPluginFunction* PublicManager::s_PrecacheModelFunc;
IPluginFunction* PublicManager::s_PrecacheSentenceFileFunc;
IPluginFunction* PublicManager::s_PrecacheDecalFunc;
IPluginFunction* PublicManager::s_PrecacheGenericFunc;
IPluginFunction* PublicManager::s_IsModelPrecachedFunc;
IPluginFunction* PublicManager::s_IsDecalPrecachedFunc;
IPluginFunction* PublicManager::s_IsGenericPrecachedFunc;
IPluginFunction* PublicManager::s_PrecacheSoundFunc;
IPluginFunction* PublicManager::s_CreateDialogFunc;
IPluginFunction* PublicManager::s_GetEngineVersionFunc;
IPluginFunction* PublicManager::s_PrintToChatFunc;
IPluginFunction* PublicManager::s_PrintCenterTextFunc;
IPluginFunction* PublicManager::s_PrintHintTextFunc;
IPluginFunction* PublicManager::s_ShowVGUIPanelFunc;
IPluginFunction* PublicManager::s_CreateHudSynchronizerFunc;
IPluginFunction* PublicManager::s_SetHudTextParamsFunc;
IPluginFunction* PublicManager::s_SetHudTextParamsExFunc;
IPluginFunction* PublicManager::s_ShowSyncHudTextFunc;
IPluginFunction* PublicManager::s_ClearSyncHudFunc;
IPluginFunction* PublicManager::s_ShowHudTextFunc;
IPluginFunction* PublicManager::s_EntIndexToEntRefFunc;
IPluginFunction* PublicManager::s_EntRefToEntIndexFunc;
IPluginFunction* PublicManager::s_MakeCompatEntRefFunc;
IPluginFunction* PublicManager::s_GetClientsInRangeFunc;
IPluginFunction* PublicManager::s_GetServerAuthIdFunc;
IPluginFunction* PublicManager::s_GetServerSteamAccountIdFunc;

// TIMERS.INC
IPluginFunction* PublicManager::s_CreateTimerFunc;
IPluginFunction* PublicManager::s_KillTimerFunc;
IPluginFunction* PublicManager::s_TriggerTimerFunc;
IPluginFunction* PublicManager::s_GetTickedTimeFunc;
IPluginFunction* PublicManager::s_GetMapTimeLeftFunc;
IPluginFunction* PublicManager::s_GetMapTimeLimitFunc;
IPluginFunction* PublicManager::s_ExtendMapTimeLimitFunc;
IPluginFunction* PublicManager::s_GetTickIntervalFunc;
IPluginFunction* PublicManager::s_IsServerProcessingFunc;

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
IPluginFunction* PublicManager::s_FireEventToClientFunc;
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

std::unordered_map<Handle, ConVarChangedFunc> PublicManager::s_ConVarChangedCallbacks;
std::unordered_map<std::pair<int, std::string>, ConVarQueryFinishedFunc, pair_hash> PublicManager::s_ConVarFinishedCallbacks;

AmbientSHookFunc PublicManager::s_AmbientSHookCallback;
NormalSHookFunc PublicManager::s_NormalSHookCallback;

std::unordered_map<std::string, MultiTargetFilterFunc> PublicManager::s_MultiTargetFilterCallbacks;

int PublicManager::s_TraceEntityFilterIndex = 0;
std::unordered_map<int, TraceEntityFilterFunc> PublicManager::s_TraceEntityFilterCallbacks;
std::unordered_map<int, void*> PublicManager::s_TraceEntityFilterData;

int PublicManager::s_TraceEntityEnumeratorIndex = 0;
std::unordered_map<int, TraceEntityEnumeratorFunc> PublicManager::s_TraceEntityEnumeratorCallbacks;
std::unordered_map<int, void*> PublicManager::s_TraceEntityEnumeratorData;

GameLogHookFunc PublicManager::s_GameLogHookCallback;

std::unordered_map<std::string, TEHookFunc> PublicManager::s_TEHooksCallbacks;

std::unordered_map<std::pair<std::string, std::string>, EntityOutputFunc, pair_hash> PublicManager::s_EntityOutputCallbacks;
std::unordered_map<std::pair<int, std::string>, EntityOutputFunc, pair_hash> PublicManager::s_SingleEntityOutputCallbacks;

std::unordered_map<Handle, TimerCallbackFunc> PublicManager::s_TimerCallbacks;

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

std::unordered_map<std::string, ConCmdFunc> PublicManager::s_ConCmdCallbacks;
std::unordered_map<std::string, SrvCmdFunc> PublicManager::s_SrvCmdCallbacks;
std::unordered_map<std::string, CommandListenerFunc> PublicManager::s_CommandListenerCallbacks;

#define STR(a) #a
#define LOAD_PTR(NAME) s_##NAME##Func = pContext->GetFunctionByName(STR(public_##NAME))

void PublicManager::InitOnPluginStart(IPluginContext* pContext)
{
	IPluginFunction* GetMaxClientsFunc = pContext->GetFunctionByName("public_GetMaxClients");
	GetMaxClientsFunc->Execute(&s_MaxClients);

	// OWN
	LOAD_PTR(SDKCallSmoke3);
	LOAD_PTR(SDKCallSmoke4);

	// CONVARS.INC
	LOAD_PTR(CreateConVar);
	LOAD_PTR(FindConVar);
	LOAD_PTR(HookConVarChange);
	LOAD_PTR(UnhookConVarChange);
	LOAD_PTR(GetConVarBool);
	LOAD_PTR(SetConVarBool);
	LOAD_PTR(GetConVarInt);
	LOAD_PTR(SetConVarInt);
	LOAD_PTR(GetConVarFloat);
	LOAD_PTR(SetConVarFloat);
	LOAD_PTR(GetConVarString);
	LOAD_PTR(SetConVarString);
	LOAD_PTR(ResetConVar);
	LOAD_PTR(GetConVarDefault);
	LOAD_PTR(GetConVarFlags);
	LOAD_PTR(SetConVarFlags);
	LOAD_PTR(GetConVarBounds);
	LOAD_PTR(SetConVarBounds);
	LOAD_PTR(GetConVarName);
	LOAD_PTR(SendConVarValue);
	LOAD_PTR(QueryClientConVar);

	// SOURCEMOD.INC
	LOAD_PTR(GetMyHandle);
	LOAD_PTR(GetPluginIterator);
	LOAD_PTR(MorePlugins);
	LOAD_PTR(ReadPlugin);
	LOAD_PTR(GetPluginStatus);
	LOAD_PTR(GetPluginFilename);
	LOAD_PTR(IsPluginDebugging);
	LOAD_PTR(GetPluginInfo);
	LOAD_PTR(FindPluginByNumber);
	LOAD_PTR(SetFailState);
	LOAD_PTR(ThrowError);
	LOAD_PTR(LogStackTrace);
	LOAD_PTR(GetTime);
	LOAD_PTR(FormatTime);
	LOAD_PTR(LoadGameConfigFile);
	LOAD_PTR(GameConfGetOffset);
	LOAD_PTR(GameConfGetKeyValue);
	LOAD_PTR(GameConfGetAddress);
	LOAD_PTR(GetSysTickCount);
	LOAD_PTR(AutoExecConfig);
	LOAD_PTR(RegPluginLibrary);
	LOAD_PTR(LibraryExists);
	LOAD_PTR(GetExtensionFileStatus);
	LOAD_PTR(ReadMapList);
	LOAD_PTR(SetMapListCompatBind);
	LOAD_PTR(GetFeatureStatus);
	LOAD_PTR(RequireFeature);
	LOAD_PTR(LoadFromAddress);
	LOAD_PTR(StoreToAddress);

	// SDKTOOLS.INC
	LOAD_PTR(StartPrepSDKCall);
	LOAD_PTR(PrepSDKCall_SetVirtual);
	LOAD_PTR(PrepSDKCall_SetSignature);
	LOAD_PTR(PrepSDKCall_SetAddress);
	LOAD_PTR(PrepSDKCall_SetFromConf);
	LOAD_PTR(PrepSDKCall_SetReturnInfo);
	LOAD_PTR(PrepSDKCall_AddParameter);
	LOAD_PTR(EndPrepSDKCall);
	LOAD_PTR(SDKCall0);
	LOAD_PTR(SDKCall1);
	LOAD_PTR(SDKCall2);
	LOAD_PTR(SDKCall3);
	LOAD_PTR(SDKCall4);
	LOAD_PTR(SDKCall5);
	LOAD_PTR(SDKCall6);
	LOAD_PTR(SDKCall7);
	LOAD_PTR(SDKCall8);
	LOAD_PTR(SDKCall9);
	LOAD_PTR(SDKCall10);
	LOAD_PTR(GetPlayerResourceEntity);

	// SDKTOOLS_SOUND.INC
	LOAD_PTR(PrefetchSound);
	LOAD_PTR(EmitAmbientSound);
	LOAD_PTR(FadeClientVolume);
	LOAD_PTR(StopSound);
	LOAD_PTR(EmitSound);
	LOAD_PTR(EmitSoundEntry);
	LOAD_PTR(EmitSentence);
	LOAD_PTR(GetDistGainFromSoundLevel);
	LOAD_PTR(AddAmbientSoundHook);
	LOAD_PTR(AddNormalSoundHook);
	LOAD_PTR(RemoveAmbientSoundHook);
	LOAD_PTR(RemoveNormalSoundHook);
	LOAD_PTR(GetGameSoundParams);
	LOAD_PTR(PrecacheScriptSound);

	// COMMANDFILTERS.INC
	LOAD_PTR(ProcessTargetString);
	LOAD_PTR(AddMultiTargetFilter);
	LOAD_PTR(RemoveMultiTargetFilter);

	// ADT_ARRAY.INC
	LOAD_PTR(CreateArray);
	LOAD_PTR(ClearArray);
	LOAD_PTR(CloneArray);
	LOAD_PTR(ResizeArray);
	LOAD_PTR(GetArraySize);
	LOAD_PTR(PushArrayCell);
	LOAD_PTR(PushArrayString);
	LOAD_PTR(PushArrayArray);
	LOAD_PTR(GetArrayCell);
	LOAD_PTR(GetArrayString);
	LOAD_PTR(GetArrayArray);
	LOAD_PTR(SetArrayCell);
	LOAD_PTR(SetArrayString);
	LOAD_PTR(SetArrayArray);
	LOAD_PTR(ShiftArrayUp);
	LOAD_PTR(RemoveFromArray);
	LOAD_PTR(SwapArrayItems);
	LOAD_PTR(FindStringInArray);
	LOAD_PTR(FindValueInArray);
	LOAD_PTR(GetArrayBlockSize);

	// LANG.INC
	LOAD_PTR(LoadTranslations);
	LOAD_PTR(SetGlobalTransTarget);
	LOAD_PTR(GetClientLanguage);
	LOAD_PTR(GetServerLanguage);
	LOAD_PTR(GetLanguageCount);
	LOAD_PTR(GetLanguageInfo);
	LOAD_PTR(SetClientLanguage);
	LOAD_PTR(GetLanguageByCode);
	LOAD_PTR(GetLanguageByName);
	LOAD_PTR(TranslationPhraseExists);
	LOAD_PTR(IsTranslatedForLanguage);

	// SDKTOOLS_VOICE.INC
	LOAD_PTR(SetClientListeningFlags);
	LOAD_PTR(GetClientListeningFlags);
	LOAD_PTR(SetListenOverride);
	LOAD_PTR(GetListenOverride);
	LOAD_PTR(IsClientMuted);

	// STRING.INC
	LOAD_PTR(Format);

	// GEOIP.INC
	LOAD_PTR(GeoipCode2);
	LOAD_PTR(GeoipCode3);
	LOAD_PTR(GeoipCountry);

	// SDKTOOLS_CLIENT.INC
	LOAD_PTR(InactivateClient);
	LOAD_PTR(ReconnectClient);

	// SDKTOOLS_ENGINE.INC
	LOAD_PTR(SetClientViewEntity);
	LOAD_PTR(SetLightStyle);
	LOAD_PTR(GetClientEyePosition);

	// SDKTOOLS_TRACE.INC
	LOAD_PTR(TR_GetPointContents);
	LOAD_PTR(TR_GetPointContentsEnt);
	LOAD_PTR(TR_TraceRay);
	LOAD_PTR(TR_TraceHull);
	LOAD_PTR(TR_EnumerateEntities);
	LOAD_PTR(TR_EnumerateEntitiesHull);
	LOAD_PTR(TR_EnumerateEntitiesSphere);
	LOAD_PTR(TR_EnumerateEntitiesBox);
	LOAD_PTR(TR_EnumerateEntitiesPoint);
	LOAD_PTR(TR_TraceRayFilter);
	LOAD_PTR(TR_TraceHullFilter);
	LOAD_PTR(TR_ClipRayToEntity);
	LOAD_PTR(TR_ClipRayHullToEntity);
	LOAD_PTR(TR_ClipCurrentRayToEntity);
	LOAD_PTR(TR_TraceRayEx);
	LOAD_PTR(TR_TraceHullEx);
	LOAD_PTR(TR_TraceRayFilterEx);
	LOAD_PTR(TR_TraceHullFilterEx);
	LOAD_PTR(TR_ClipRayToEntityEx);
	LOAD_PTR(TR_ClipRayHullToEntityEx);
	LOAD_PTR(TR_ClipCurrentRayToEntityEx);
	LOAD_PTR(TR_GetFraction);
	LOAD_PTR(TR_GetFractionLeftSolid);
	LOAD_PTR(TR_GetStartPosition);
	LOAD_PTR(TR_GetEndPosition);
	LOAD_PTR(TR_GetEntityIndex);
	LOAD_PTR(TR_GetDisplacementFlags);
	LOAD_PTR(TR_GetSurfaceName);
	LOAD_PTR(TR_GetSurfaceProps);
	LOAD_PTR(TR_GetSurfaceFlags);
	LOAD_PTR(TR_GetPhysicsBone);
	LOAD_PTR(TR_AllSolid);
	LOAD_PTR(TR_StartSolid);
	LOAD_PTR(TR_DidHit);
	LOAD_PTR(TR_GetHitGroup);
	LOAD_PTR(TR_GetHitBoxIndex);
	LOAD_PTR(TR_GetPlaneNormal);
	LOAD_PTR(TR_PointOutsideWorld);

	// BITBUFFER.INC
	LOAD_PTR(BfWriteBool);
	LOAD_PTR(BfWriteByte);
	LOAD_PTR(BfWriteChar);
	LOAD_PTR(BfWriteShort);
	LOAD_PTR(BfWriteWord);
	LOAD_PTR(BfWriteNum);
	LOAD_PTR(BfWriteFloat);
	LOAD_PTR(BfWriteString);
	LOAD_PTR(BfWriteEntity);
	LOAD_PTR(BfWriteAngle);
	LOAD_PTR(BfWriteCoord);
	LOAD_PTR(BfWriteVecCoord);
	LOAD_PTR(BfWriteVecNormal);
	LOAD_PTR(BfWriteAngles);
	LOAD_PTR(BfReadBool);
	LOAD_PTR(BfReadByte);
	LOAD_PTR(BfReadChar);
	LOAD_PTR(BfReadShort);
	LOAD_PTR(BfReadWord);
	LOAD_PTR(BfReadNum);
	LOAD_PTR(BfReadFloat);
	LOAD_PTR(BfReadString);
	LOAD_PTR(BfReadEntity);
	LOAD_PTR(BfReadAngle);
	LOAD_PTR(BfReadCoord);
	LOAD_PTR(BfReadVecCoord);
	LOAD_PTR(BfReadVecNormal);
	LOAD_PTR(BfReadAngles);
	LOAD_PTR(BfGetNumBytesLeft);


	// LOGGING.INC
	LOAD_PTR(LogMessage);
	LOAD_PTR(LogToFile);
	LOAD_PTR(LogToFileEx);
	LOAD_PTR(LogAction);
	LOAD_PTR(LogError);
	LOAD_PTR(AddGameLogHook);
	LOAD_PTR(RemoveGameLogHook);

	// SDKTOOLS_TEMPENTS.INC
	LOAD_PTR(AddTempEntHook);
	LOAD_PTR(RemoveTempEntHook);
	LOAD_PTR(TE_Start);
	LOAD_PTR(TE_IsValidProp);
	LOAD_PTR(TE_WriteNum);
	LOAD_PTR(TE_ReadNum);
	LOAD_PTR(TE_WriteFloat);
	LOAD_PTR(TE_ReadFloat);
	LOAD_PTR(TE_WriteVector);
	LOAD_PTR(TE_ReadVector);
	LOAD_PTR(TE_WriteAngles);
	LOAD_PTR(TE_WriteFloatArray);
	LOAD_PTR(TE_Send);

	// SDKTOOLS_GAMERULES.INC
	LOAD_PTR(GameRules_GetProp);
	LOAD_PTR(GameRules_SetProp);
	LOAD_PTR(GameRules_GetPropFloat);
	LOAD_PTR(GameRules_SetPropFloat);
	LOAD_PTR(GameRules_GetPropEnt);
	LOAD_PTR(GameRules_SetPropEnt);
	LOAD_PTR(GameRules_GetPropVector);
	LOAD_PTR(GameRules_SetPropVector);
	LOAD_PTR(GameRules_GetPropString);
	LOAD_PTR(GameRules_SetPropString);

	// SDKTOOLS_ENTINPUT.INC
	LOAD_PTR(AcceptEntityInput);

	// SDKTOOLS_ENTOUTPUT.INC
	LOAD_PTR(HookEntityOutput);
	LOAD_PTR(UnhookEntityOutput);
	LOAD_PTR(HookSingleEntityOutput);
	LOAD_PTR(UnhookSingleEntityOutput);
	LOAD_PTR(FireEntityOutput);

	// HANDLES.INC
	LOAD_PTR(CloseHandle);
	LOAD_PTR(CloneHandle);

	// ENTITY_PROP_STOCKS.INC
	LOAD_PTR(GetEntityFlags);
	LOAD_PTR(SetEntityFlags);
	LOAD_PTR(GetEntityMoveType);
	LOAD_PTR(SetEntityMoveType);
	LOAD_PTR(GetEntityRenderMode);
	LOAD_PTR(SetEntityRenderMode);
	LOAD_PTR(GetEntityRenderFx);
	LOAD_PTR(SetEntityRenderFx);
	LOAD_PTR(GetEntityRenderColor);
	LOAD_PTR(SetEntityRenderColor);
	LOAD_PTR(GetEntityGravity);
	LOAD_PTR(SetEntityGravity);
	LOAD_PTR(SetEntityHealth);
	LOAD_PTR(GetClientButtons);

	// HALFLIFE.INC
	LOAD_PTR(LogToGame);
	LOAD_PTR(SetRandomSeed);
	LOAD_PTR(IsMapValid);
	LOAD_PTR(FindMap);
	LOAD_PTR(GetMapDisplayName);
	LOAD_PTR(IsDedicatedServer);
	LOAD_PTR(GetEngineTime);
	LOAD_PTR(GetGameTime);
	LOAD_PTR(GetGameTickCount);
	LOAD_PTR(GetGameFrameTime);
	LOAD_PTR(GetGameDescription);
	LOAD_PTR(GetGameFolderName);
	LOAD_PTR(GetCurrentMap);
	LOAD_PTR(PrecacheModel);
	LOAD_PTR(PrecacheSentenceFile);
	LOAD_PTR(PrecacheDecal);
	LOAD_PTR(PrecacheGeneric);
	LOAD_PTR(IsModelPrecached);
	LOAD_PTR(IsDecalPrecached);
	LOAD_PTR(IsGenericPrecached);
	LOAD_PTR(PrecacheSound);
	LOAD_PTR(CreateDialog);
	LOAD_PTR(GetEngineVersion);
	LOAD_PTR(PrintToChat);
	LOAD_PTR(PrintCenterText);
	LOAD_PTR(PrintHintText);
	LOAD_PTR(ShowVGUIPanel);
	LOAD_PTR(CreateHudSynchronizer);
	LOAD_PTR(SetHudTextParams);
	LOAD_PTR(SetHudTextParamsEx);
	LOAD_PTR(ShowSyncHudText);
	LOAD_PTR(ClearSyncHud);
	LOAD_PTR(ShowHudText);
	LOAD_PTR(EntIndexToEntRef);
	LOAD_PTR(EntRefToEntIndex);
	LOAD_PTR(MakeCompatEntRef);
	LOAD_PTR(GetClientsInRange);
	LOAD_PTR(GetServerAuthId);
	LOAD_PTR(GetServerSteamAccountId);

	// TIMERS.INC
	LOAD_PTR(CreateTimer);
	LOAD_PTR(KillTimer);
	LOAD_PTR(TriggerTimer);
	LOAD_PTR(GetTickedTime);
	LOAD_PTR(GetMapTimeLeft);
	LOAD_PTR(GetMapTimeLimit);
	LOAD_PTR(ExtendMapTimeLimit);
	LOAD_PTR(GetTickInterval);
	LOAD_PTR(IsServerProcessing);

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
	LOAD_PTR(FireEventToClient);
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
