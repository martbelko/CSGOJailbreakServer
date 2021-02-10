#include "Plugin.h"

Plugin plugin;
BasePlugin* GetPlugin()
{
	return &plugin;
}

static bool FilterClientsFunc(int entity, int contentsMask, void* data)
{
	if (entity > PublicManager::GetMaxClients())
		return false;
	int caller = reinterpret_cast<int>(data);
	return caller != entity;
}

static bool LineGoesThroughSmoke(float from[3], float to[3])
{
	static Address TheBots;
	static Handle CBotManager_IsLineBlockedBySmoke;
	static int OS = 0;
	if (OS == 0)
	{
		Handle hGameConf = P::LoadGameConfigFile("LineGoesThroughSmoke.games");
		if (!hGameConf)
		{
			P::SetFailState("Could not read LineGoesThroughSmoke.games.txt");
			return false;
		}

		OS = P::GameConfGetOffset(hGameConf, "OS");

		TheBots = P::GameConfGetAddress(hGameConf, "TheBots");
		if (!TheBots)
		{
			P::CloseHandle(hGameConf);
			P::SetFailState("TheBots == null");
			return false;
		}

		P::StartPrepSDKCall(SDKCall_Raw);
		P::PrepSDKCall_SetFromConf(hGameConf, SDKConf_Signature, "CBotManager::IsLineBlockedBySmoke");
		P::PrepSDKCall_AddParameter(SDKType_Vector, SDKPass_Pointer);
		P::PrepSDKCall_AddParameter(SDKType_Vector, SDKPass_Pointer);
		if (OS == 1)
			P::PrepSDKCall_AddParameter(SDKType_Float, SDKPass_Plain);
		P::PrepSDKCall_SetReturnInfo(SDKType_Bool, SDKPass_Plain);
		if (!(CBotManager_IsLineBlockedBySmoke = P::EndPrepSDKCall()))
		{
			P::CloseHandle(hGameConf);
			P::SetFailState("Failed to get CBotManager::IsLineBlockedBySmoke function");
			return false;
		}

		P::CloseHandle(hGameConf);
	}

	if (OS == 1)
		return P::SDKCallSmoke4(CBotManager_IsLineBlockedBySmoke, TheBots, from, to, 1.0f);
	return P::SDKCallSmoke3(CBotManager_IsLineBlockedBySmoke, TheBots, from, to);
}

static Action OnEventHookPreStatic(EventHandle eventHandle, const char* name, bool dontBroadcast)
{
	return plugin.OnEventHookPre(eventHandle, name, dontBroadcast);
}

static Action OnEventHookPostStatic(EventHandle eventHandle, const char* name, bool dontBroadcast)
{
	return plugin.OnEventHookPost(eventHandle, name, dontBroadcast);
}

static Action ConCmdCallbackStatic(int client, std::string& command, int argc)
{
	return plugin.ConCmdCallback(client, command, argc);
}

/* PLUGIN */

void Plugin::OnPluginStart()
{
	rootconsole->ConsolePrint("Plugin Start");

	P::HookEvent(OnEventHookPreStatic, "round_start", EventHookMode::EventHookMode_Pre);
	P::HookEvent(OnEventHookPostStatic, "round_start", EventHookMode::EventHookMode_Post);

	P::RegConsoleCmd("sm_test", ConCmdCallbackStatic);

	for (int i = 1; i <= P::GetMaxClients(); ++i)
		if (P::IsClientInGame(i))
			OnClientPutInServer(i);

	// PublicManager::SQL_TConnect(MainPlugin::OnSQLTConnectCallbackBanlist, "banlist", 0);
	// PublicManager::SQL_TConnect(MainPlugin::OnSQLTConnectCallbackDefault, "default", 0);
}

void Plugin::OnClientPutInServer(int client)
{
	//PublicManager::PrintToChatAll("Hello, %d", client);
}

Action Plugin::OnEventHookPre(EventHandle eventHandle, const char* name, bool dontBroadcast)
{
	rootconsole->ConsolePrint("Event PRE: %s", name);
	return Plugin_Continue;
}

Action Plugin::OnEventHookPost(EventHandle eventHandle, const char* name, bool dontBroadcast)
{
	rootconsole->ConsolePrint("Event POST: %s", name);
	return Plugin_Continue;
}

Action Plugin::ConCmdCallback(int client, std::string& command, int argc)
{
	/*std::string r = "%d %d %d %N %s %s %f %f";
	int x = 5;
	int y = 6;
	int z = 8;
	float w = 61.49f;
	float w2 = 0.01f;
	PublicManager::PrintToConsole(client + 1, r.c_str(), x, y, z, client, "LOL", "WTF", 58.0f, w + 1);
	PublicManager::PrintToConsole(client + 1, "Bye Bye");
	float v[3] = { 0, 0, 0 };
	PublicManager::GetClientAbsOrigin(client + 1, v);
	PublicManager::PrintToConsole(client + 1, "%f, %f, %f", v[0], v[1], v[2]);
	for (int i = 1; i <= PublicManager::GetMaxClients(); ++i)
	{
		if (PublicManager::IsClientInGame(i) && PublicManager::IsFakeClient(i))
			PublicManager::KickClient(i, "Bye BOTT");
	}

	PublicManager::ReplyToCommand(client, "LOL YOU NOOB %d", 10);
	PublicManager::FakeClientCommand(client + 1, "say WTF %s", "ALL");
	PublicManager::FakeClientCommand(client + 1, "say_team WTF %s", "TEAM");
	PublicManager::CS_RespawnPlayer(client + 1);*/

	P::ReplyToCommand(client, command.c_str());

	if (client == 0)
		++client;
	float pos[3];
	P::GetClientEyePosition(client, pos);
	float angles[3];
	P::GetClientEyeAngles(client, angles);

	Handle trace = P::TR_TraceRayFilterEx(pos, angles, MASK_VISIBLE, RayType::RayType_Infinite, FilterClientsFunc, reinterpret_cast<void*>(client));
	if (P::TR_DidHit(trace))
	{
		float endpos[3];
		P::TR_GetEndPosition(pos, trace);
		int ts = LineGoesThroughSmoke(pos, endpos);
		int hitClient = P::TR_GetEntityIndex(trace);
		if (hitClient > 0 && hitClient <= P::GetMaxClients() && P::IsClientInGame(hitClient))
		{
			char name[MAX_NAME_LENGTH];
			P::GetClientName(hitClient, name, sizeof(name));
			P::PrintToChatAll("%s, %d", name, ts);
		}
	}

	P::CloseHandle(trace);

	/*float origin[3];
	PM::GetClientAbsOrigin(client + 1, origin);
	int* clients = new int[PM::GetMaxClients()];
	PM::GetClientsInRange(origin, ClientRangeType::RangeType_Audibility, clients, PM::GetMaxClients());

	for (int i = 0; i < PM::GetMaxClients(); ++i)
	{
		int c = clients[i];
		if (c > 0 && c <= PM::GetMaxClients() && PM::IsClientInGame(c))
		{
			char name[MAX_PLAYER_NAME_LENGTH];
			PM::GetClientName(c, name, sizeof(name));
			rootconsole->ConsolePrint(name);
		}
	}

	delete[] clients;

	PublicManager::SetClientName(client + 1, "LOOLUNOOB");
	PublicManager::ForcePlayerSuicide(client + 2);
	PublicManager::IgniteEntity(client + 1, 5.0f);
	PublicManager::SlapPlayer(client + 1, 20);

	PublicManager::SetEntityHealth(client + 1, 300);

	char className[64];
	PublicManager::GetEdictClassname(client + 1, className, sizeof(className));
	rootconsole->ConsolePrint("Class Name: %s", className);

	char weapon[64];
	PublicManager::GetClientWeapon(client + 1, weapon, sizeof(weapon));
	rootconsole->ConsolePrint("Weapon: %s", weapon);

	PublicManager::CS_SetClientClanTag(client + 1, "LOL");

	char clanTag[32];
	PublicManager::CS_GetClientClanTag(client + 1, clanTag, sizeof(clanTag));
	rootconsole->ConsolePrint("Clan: %s", clanTag);

	MenuHandle menu = PublicManager::CreateMenu(TestMenuHandler, MENU_ACTIONS_DEFAULT);
	PublicManager::SetMenuTitle(menu, "Menu Title here");
	PublicManager::AddMenuItem(menu, "1", "Choice1", ITEMDRAW_DEFAULT);
	PublicManager::AddMenuItem(menu, "2", "Choice2", ITEMDRAW_DEFAULT);
	PublicManager::AddMenuItem(menu, "3", "Choice3", ITEMDRAW_DEFAULT);
	PublicManager::SetMenuExitButton(menu, false);
	PublicManager::DisplayMenu(menu, client + 1, 20);

	rootconsole->ConsolePrint("Sizeof(KeyValues) = %d", sizeof(KeyValues));*/

	return Plugin_Handled;
}
