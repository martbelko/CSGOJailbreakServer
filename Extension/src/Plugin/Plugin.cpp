#include "Plugin.h"

#include "Plugin/Shop/ShopItemCallbacks.h"

#include "Plugin/Offsets.h"
#include "Plugin/Utils.h"

static constexpr float s_ShopTime = 120.0f; // After this amount of seconds, shop will be disabled

using P = PublicManager;

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

static void OnSQLTConnectCallbackBanlist(Handle owner, Handle hndl, const char* error, int data)
{
	rootconsole->ConsolePrint("Connected to BanList %d", hndl);
	if (hndl == INVALID_HANDLE)
		PublicManager::PrintToServer("Failed to connect to Banlist database: ERROR: %s", (const char*)error);
	else
		PublicManager::PrintToServer("Connection to Banlist successful");
}

/* PLUGIN */

void Plugin::OnPluginStart()
{
	rootconsole->ConsolePrint("Plugin Start");
	Offset::OnPluginStart();

	P::HookEvent("round_start", OnRoundStartPost, EventHookMode::EventHookMode_Post);
	P::RegConsoleCmd("sm_shop", CMDShopCallbackStatic);

	std::vector<ShopItem> items;
	items.emplace_back("hammer", 10, &TShopItemHammer, VipMode::NONE);
	items.emplace_back("spanner", 12, &TShopSpanner, VipMode::NONE);
	items.emplace_back("axe", 15, &TShopAxe, VipMode::NONE);
	items.emplace_back("Knife", 20, &TShopKnife, VipMode::NONE);
	items.emplace_back("taser", 50, &TShopTaser, VipMode::VIP);
	items.emplace_back("healthshot", 20, &TShopHealhshot, VipMode::NONE);
	items.emplace_back("hegrenade", 15, &TShopHEGrenade, VipMode::NONE);
	items.emplace_back("flashbang", 12, &TShopFlashbang, VipMode::NONE);
	items.emplace_back("molotov", 10, &TShopMolotov, VipMode::NONE);
	items.emplace_back("tagrenade", 12, &TShopTAGrenade, VipMode::NONE);
	items.emplace_back("kevlar", 20, &TShopKevlar, VipMode::NONE);
	items.emplace_back("kevlarhelmet", 30, &TShopKevlarHelmet, VipMode::NONE);
	items.emplace_back("breachcharge", 70, &TShopBreachCharge, VipMode::EXTRA_VIP);
	items.emplace_back("djump", 40, &TShopDJump, VipMode::NONE);
	items.emplace_back("fastwalk", 50, &TShopFastwalk, VipMode::NONE, 5.0f);
	items.emplace_back("invisibility", 80, &TShopInvisibility, VipMode::NONE, 5.0f);
	items.emplace_back("changeskin", 60, &TShopChangeskin, VipMode::NONE);
	items.emplace_back("blind", 200, &TShopBlind, VipMode::VIP, 10.0f);
	items.emplace_back("openchance", 60, &TShopOpen, VipMode::VIP);
	items.emplace_back("fortune", 30, &TShopFortune, VipMode::NONE);
	m_TShop = Shop("tshop", items);

	std::vector<ShopItem> ctItems;
	ctItems.emplace_back("helmet", 20, &CTShopHelmet);
	ctItems.emplace_back("tagrenade", 20, &CTShopTAGrenade);
	ctItems.emplace_back("healthshot", 30, &CTShopHealthshot);
	ctItems.emplace_back("djump", 30, &CTShopDJump);
	ctItems.emplace_back("shield", 50, &CTShopShield, VipMode::VIP);
	ctItems.emplace_back("heavy", 70, &CTShopHeavySuit, VipMode::EXTRA_VIP);
	m_CTShop = Shop("ctshop", ctItems);

	for (int i = 1; i <= P::GetMaxClients(); ++i)
		if (P::IsClientInGame(i))
			OnClientPutInServer(i);

	//PublicManager::SQL_TConnect(OnSQLTConnectCallbackBanlist, "banlist", 0);
}

void Plugin::OnPluginEnd()
{
	m_TShop.Delete();
	m_CTShop.Delete();
}

void Plugin::OnClientPutInServer(int client)
{
	Shop::OnClientPutInServer(client);
	P::SDKHook(client, SDKHookType::SDKHook_SpawnPost, OnSpawnPost);
}

Action Plugin::OnRoundStartPost(EventHandle eventHandle, const char* name, bool dontBroadcast)
{
	if (plugin.m_ShopDisableTimer != INVALID_HANDLE)
	{
		P::KillTimer(plugin.m_ShopDisableTimer);
		plugin.m_ShopDisableTimer = INVALID_HANDLE;
	}

	plugin.m_TShop.SetEnable(true);
	plugin.m_CTShop.SetEnable(true);

	plugin.m_ShopDisableTimer = P::CreateTimer(s_ShopTime, [](Handle, void* value)
	{
		plugin.m_TShop.SetEnable(false);
		plugin.m_CTShop.SetEnable(false);
		return Plugin_Continue;
	},
	nullptr, TIMER_FLAG_NO_MAPCHANGE);
	return Plugin_Continue;
}

void Plugin::OnSpawnPost(int client)
{
	Utils::DisarmPlayer(client);
	P::CreateTimer(0.5f, [](Handle, void* data)
	{
		int userid = reinterpret_cast<int>(data);
		int client = P::GetClientOfUserId(userid);
		Utils::DisarmPlayer(client);
		if (P::GetClientTeam(client) == CS_TEAM_T)
			plugin.m_TShop.DisplayToClient(client, 20);
		else
			plugin.m_CTShop.DisplayToClient(client, 20);
		return Plugin_Continue;
	},
	reinterpret_cast<void*>(P::GetClientUserId(client)));
}

Action Plugin::CMDShopCallbackStatic(int client, std::string& command, int argc)
{
	if (P::GetClientTeam(client) == CS_TEAM_T)
	{
		if (plugin.m_TShop.IsEnabled())
			plugin.m_TShop.DisplayToClient(client, 20);
		else
			P::PrintCenterText(client, "[URNA SHOP] Sorry, shop is disabled");
	}
	else if (P::GetClientTeam(client) == CS_TEAM_CT)
	{
		if (plugin.m_CTShop.IsEnabled())
			plugin.m_CTShop.DisplayToClient(client, 20);
		else
			P::PrintCenterText(client, "[URNA SHOP] Sorry, shop is disabled");
	}

	P::ReplyToCommand(client, command.c_str());

	/*if (client == 0)
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

	MenuHandle menu = PublicManager::CreateMenu(TestMenuHandler, MENU_ACTIONS_DEFAULT);
	PublicManager::SetMenuTitle(menu, "Menu Title here");
	PublicManager::AddMenuItem(menu, "1", "Choice1", ITEMDRAW_DEFAULT);
	PublicManager::AddMenuItem(menu, "2", "Choice2", ITEMDRAW_DEFAULT);
	PublicManager::AddMenuItem(menu, "3", "Choice3", ITEMDRAW_DEFAULT);
	PublicManager::SetMenuExitButton(menu, false);
	PublicManager::DisplayMenu(menu, client + 1, 20);*/

	return Plugin_Handled;
}
