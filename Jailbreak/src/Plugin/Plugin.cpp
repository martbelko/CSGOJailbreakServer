#include "Plugin.h"

#include "Plugin/DoorManager.h"

#include "Plugin/Shop/ShopItemCallbacks.h"

#include "Plugin/LastRequest/LastRequestManager.h"
#include "Plugin/LastRequest/CloseFight.h"

#include "Plugin/Admin/AdminMenu.h"

#include <CSGOExtension.h>

#include <tao/json.hpp>
#include <tao/json/contrib/traits.hpp>

Plugin& plugin = *(new Plugin());
BasePlugin* GetPlugin()
{
	return &plugin;
}

static bool FilterClientsFunc(int entity, int contentsMask, void* data)
{
	if (entity > PM::GetMaxClients())
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
		Handle hGameConf = PM::LoadGameConfigFile("LineGoesThroughSmoke.games");
		if (!hGameConf)
		{
			PM::SetFailState("Could not read LineGoesThroughSmoke.games.txt");
			return false;
		}

		OS = PM::GameConfGetOffset(hGameConf, "OS");

		TheBots = PM::GameConfGetAddress(hGameConf, "TheBots");
		if (!TheBots)
		{
			PM::CloseHandle(hGameConf);
			PM::SetFailState("TheBots == null");
			return false;
		}

		PM::StartPrepSDKCall(SDKCall_Raw);
		PM::PrepSDKCall_SetFromConf(hGameConf, SDKConf_Signature, "CBotManager::IsLineBlockedBySmoke");
		PM::PrepSDKCall_AddParameter(SDKType_Vector, SDKPass_Pointer);
		PM::PrepSDKCall_AddParameter(SDKType_Vector, SDKPass_Pointer);
		if (OS == 1)
			PM::PrepSDKCall_AddParameter(SDKType_Float, SDKPass_Plain);
		PM::PrepSDKCall_SetReturnInfo(SDKType_Bool, SDKPass_Plain);
		if (!(CBotManager_IsLineBlockedBySmoke = PM::EndPrepSDKCall()))
		{
			PM::CloseHandle(hGameConf);
			PM::SetFailState("Failed to get CBotManager::IsLineBlockedBySmoke function");
			return false;
		}

		PM::CloseHandle(hGameConf);
	}

	if (OS == 1)
		return PM::SDKCallSmoke4(CBotManager_IsLineBlockedBySmoke, TheBots, from, to, 1.0f);
	return PM::SDKCallSmoke3(CBotManager_IsLineBlockedBySmoke, TheBots, from, to);
}

static void OnSQLTConnectCallbackBanlist(Handle owner, Handle hndl, const char* error, int data)
{
	rootconsole->ConsolePrint("Connected to BanList %d", hndl);
	if (hndl == INVALID_HANDLE)
		PM::PrintToServer("Failed to connect to Banlist database: ERROR: %s", (const char*)error);
	else
		PM::PrintToServer("Connection to Banlist successful");
}

/* PLUGIN */

void Plugin::OnPluginStart()
{
	rootconsole->ConsolePrint("Plugin Start");

	PM::LoadTranslations("shop.phrases.txt");

	Offset::OnPluginStart();
	Utils::OnPluginStart();

	mThreadTimer = Timer(ThreadTimerRate, [](Timer* timer, void* data) -> Action
	{
		Server::Run();
		return Plugin_Continue;
	},
	nullptr, TIMER_REPEAT);

	mAdminMenu = new AdminMenu();
	PM::RegAdminCmd("sm_adminTest", AdminTestCallback, ADMFLAG_GENERIC);

	PM::HookEvent("round_start", OnRoundStartPost, EventHookMode::EventHookMode_Post);
	PM::HookEvent("player_death", OnPlayerDeathEventPost, EventHookMode::EventHookMode_Post);
	PM::HookEvent("player_team", OnPlayerTeamChange, EventHookMode::EventHookMode_Post);

	PM::RegConsoleCmd("sm_shop", CMDShopCallback);
	PM::RegConsoleCmd("sm_lastrequest", CMDLastRequestCallback);
	PM::RegConsoleCmd("sm_lr", CMDLastRequestCallback);

	ShopItemCallback::Init();
	std::vector<ShopItem> tItems;
	tItems.emplace_back("spanner", 10, &ShopItemCallback::TShopSpanner, VipMode::NONE);
	tItems.emplace_back("hammer", 12, &ShopItemCallback::TShopItemHammer, VipMode::NONE);
	tItems.emplace_back("axe", 15, &ShopItemCallback::TShopAxe, VipMode::NONE);
	tItems.emplace_back("Knife", 20, &ShopItemCallback::TShopKnife, VipMode::NONE);
	tItems.emplace_back("taser", 50, &ShopItemCallback::TShopTaser, VipMode::VIP);
	tItems.emplace_back("healthshot", 20, &ShopItemCallback::TShopHealhshot, VipMode::NONE);
	tItems.emplace_back("hegrenade", 15, &ShopItemCallback::TShopHEGrenade, VipMode::NONE);
	tItems.emplace_back("flashbang", 12, &ShopItemCallback::TShopFlashbang, VipMode::NONE);
	tItems.emplace_back("molotov", 10, &ShopItemCallback::TShopMolotov, VipMode::NONE);
	tItems.emplace_back("tagrenade", 12, &ShopItemCallback::TShopTAGrenade, VipMode::NONE);
	tItems.emplace_back("kevlar", 20, &ShopItemCallback::TShopKevlar, VipMode::NONE);
	tItems.emplace_back("kevlarhelmet", 30, &ShopItemCallback::TShopKevlarHelmet, VipMode::NONE);
	tItems.emplace_back("breachcharge", 70, &ShopItemCallback::TShopBreachCharge, VipMode::EXTRA_VIP);
	tItems.emplace_back("djump", 40, &ShopItemCallback::TShopDJump, VipMode::NONE);
	tItems.emplace_back("fastwalk", 50, &ShopItemCallback::TShopFastwalk, VipMode::NONE, 5.0f);
	tItems.emplace_back("invisibility", 80, &ShopItemCallback::TShopInvisibility, VipMode::NONE, 5.0f);
	tItems.emplace_back("changeskin", 60, &ShopItemCallback::TShopChangeskin, VipMode::NONE);
	tItems.emplace_back("blind", 200, &ShopItemCallback::TShopBlind, VipMode::VIP, 5.0f);
	tItems.emplace_back("openchance", 60, &ShopItemCallback::TShopOpen, VipMode::VIP);
	tItems.emplace_back("fortune", 30, &ShopItemCallback::TShopFortune, VipMode::NONE);
	m_TShop = Shop("tshop", tItems);

	std::vector<ShopItem> ctItems;
	ctItems.emplace_back("helmet", 20, &ShopItemCallback::CTShopHelmet);
	ctItems.emplace_back("tagrenade", 20, &ShopItemCallback::CTShopTAGrenade);
	ctItems.emplace_back("healthshot", 30, &ShopItemCallback::CTShopHealthshot);
	ctItems.emplace_back("djump", 30, &ShopItemCallback::CTShopDJump);
	ctItems.emplace_back("shield", 50, &ShopItemCallback::CTShopShield, VipMode::VIP);
	ctItems.emplace_back("heavy", 70, &ShopItemCallback::CTShopHeavySuit, VipMode::EXTRA_VIP);
	m_CTShop = Shop("ctshop", ctItems);

	LastRequestManager::Init();

	for (int i = 1; i <= PM::GetMaxClients(); ++i)
		if (PM::IsClientInGame(i))
			OnClientPostAdminCheck(i);

	//PublicManager::SQL_TConnect(OnSQLTConnectCallbackBanlist, "banlist", 0);
}

void Plugin::OnPluginEnd()
{
	delete mAdminMenu;

	delete this;
}

void Plugin::OnMapStart()
{
	int PMIndex = PM::FindEntityByClassname(0, "cs_player_manager");
	PM::SDKHook(PMIndex, SDKHook_ThinkPost, Utils::OnThinkPostCSPlayerManager);

	DoorManager::OnMapStart();
}

void Plugin::OnMapEnd()
{
	DoorManager::OnMapEnd();
}

void Plugin::OnClientPostAdminCheck(int client)
{
	// TODO: Check for bans HERE!!!

	Shop::SetPlayerPoints(client, 0);
	if (!PM::IsClientSourceTV(client) && !PM::IsFakeClient(client))
	{
		mAdminMenu->Translate(client);

		char tshopName[32], ctshopName[32];
		PM::Format(tshopName, sizeof(tshopName), "%T", "tshop", client);
		PM::Format(ctshopName, sizeof(ctshopName), "%T", "ctshop", client);
		m_TShop.RefreshMenusForClient(tshopName, client);
		m_CTShop.RefreshMenusForClient(ctshopName, client);

		LastRequestManager::TranslateLastRequestMainMenu(client);
	}

	PM::SDKHook(client, SDKHookType::SDKHook_SpawnPost, OnSpawnPost);
	PM::SDKHook(client, SDKHookType::SDKHook_WeaponDrop, OnWeaponDrop);
	PM::SDKHook(client, SDKHookType::SDKHook_WeaponCanUse, OnWeaponCanUse);
	PM::SDKHook(client, SDKHookType::SDKHook_WeaponEquipPost, OnWeaponEquipPost);
	PM::SDKHook(client, SDKHookType::SDKHook_OnTakeDamage, OnTakeDamage);
	PM::SDKHook(client, SDKHookType::SDKHook_OnTakeDamageAlive, OnTakeDamageAlive);
	PM::SDKHook(client, SDKHookType::SDKHook_OnTakeDamageAlivePost, OnTakeDamageAlivePost);
	PM::SDKHook(client, SDKHookType::SDKHook_SetTransmit, SetTransmit);

	// Utils::HidePlayerFromScoreboard(client, Admin::IsClientAdmin(client));
}

void Plugin::OnGameFrame()
{
	DoubleJump::OnGameFrame();
}

Action Plugin::OnRoundStartPost(EventHandle eventHandle, const char* name, bool dontBroadcast)
{
	plugin.m_AllowDropWeapons = false;
	if (plugin.m_ShopDisableTimer != INVALID_HANDLE)
	{
		PM::KillTimer(plugin.m_ShopDisableTimer);
		plugin.m_ShopDisableTimer = INVALID_HANDLE;
	}

	plugin.m_TShop.SetEnable(true);
	plugin.m_CTShop.SetEnable(true);
	plugin.m_TShop.EnableAllItems();
	plugin.m_CTShop.EnableAllItems();

	plugin.m_ShopDisableTimer = PM::CreateTimer(Globals::shopTime, [](Handle, void* value)
	{
		plugin.m_TShop.SetEnable(false);
		plugin.m_CTShop.SetEnable(false);
		return Plugin_Continue;
	},
	nullptr, TIMER_FLAG_NO_MAPCHANGE);

	PM::CreateTimer(Globals::disarmTimerLength, [](Handle, void*)
	{
		plugin.m_AllowDropWeapons = true;
		return Plugin_Handled;
	},
	nullptr, TIMER_FLAG_NO_MAPCHANGE);

	return Plugin_Continue;
}

Action Plugin::OnPlayerDeathEventPost(EventHandle eventHandle, const char* name, bool dontBroadcast)
{
	int client = PM::GetClientOfUserId(PM::GetEventInt(eventHandle, "userid"));

	BlindAbility::OnClientDeath(client);
	FastWalk::OnClientDeath(client);
	Invisibility::OnClientDeath(client);
	DoubleJump::OnClientDeath(client);

	return Plugin_Continue;

}

Action Plugin::OnPlayerTeamChange(EventHandle eventHandle, const char* name, bool dontBroadcast)
{
	int client = PM::GetClientOfUserId(PM::GetEventInt(eventHandle, "userid"));
	int team = PM::GetEventInt(eventHandle, "team");
	int oldTeam = PM::GetEventInt(eventHandle, "oldteam");

	BlindAbility::OnClientTeamChange(client, team, oldTeam);
	FastWalk::OnClientTeamChange(client, team, oldTeam);
	Invisibility::OnClientTeamChange(client, team, oldTeam);
	DoubleJump::OnClientTeamChange(client, team, oldTeam);

	return Plugin_Continue;
}

void Plugin::OnSpawnPost(int client)
{
	/*Utils::DisarmPlayer(client);
	PM::CreateTimer(Globals::disarmTimerLength, [](Handle, void* data)
	{
		int userid = reinterpret_cast<int>(data);
		int client = PM::GetClientOfUserId(userid);
		Utils::DisarmPlayer(client);
		PM::GivePlayerItem(client, "weapon_fists");
		if (PM::GetClientTeam(client) == CS_TEAM_T)
			plugin.m_TShop.DisplayToClient(client, 20);
		else
			plugin.m_CTShop.DisplayToClient(client, 20);
		return Plugin_Continue;
	},
	reinterpret_cast<void*>(PM::GetClientUserId(client)));*/
}

Action Plugin::OnWeaponDrop(int client, int weapon)
{
	if (!plugin.m_AllowDropWeapons)
		return Plugin_Stop;
	return Plugin_Continue;
}

Action Plugin::OnWeaponCanUse(int client, int weapon)
{
	char classname[64];
	PM::GetEntityClassname(weapon, classname, sizeof(classname));
	if ((PM::StrEqualCaseSensitive(classname, "weapon_melee") || PM::StrEqualCaseSensitive(classname, "weapon_knife")) &&
		((!Utils::HasWeapon(client, "weapon_melee") && !Utils::HasWeapon(client, "weapon_knife"))))
	{
		PM::EquipPlayerWeapon(client, weapon);
		return Plugin_Continue;
	}
	else if (PM::StrEqualCaseSensitive(classname, "weapon_fists") && !Utils::HasWeapon(client, "weapon_fists"))
	{
		PM::EquipPlayerWeapon(client, weapon);
		return Plugin_Continue;
	}

	return Plugin_Continue;
}

void Plugin::OnWeaponEquipPost(int client, int weapon)
{
	if (PM::IsValidEntity(weapon))
	{
		char name[32];
		PM::GetEntityClassname(weapon, name, sizeof(name));
		if (PM::StrEqualCaseSensitive(name, "weapon_melee"))
		{
			// Try to find weapon index in dropped weapons
			for (auto& owner : plugin.m_OriginalOwners)
			{
				if (owner.weapon == weapon)
				{
					owner.userid = PM::GetClientUserId(client);
					owner.team = PM::GetClientTeam(client);
					return;
				}
			}

			// If its new weapon, create object and push it
			OrigOwnerWeapon owner;
			owner.userid = PM::GetClientUserId(client);
			owner.team = PM::GetClientTeam(client);
			owner.weapon = weapon;
			plugin.m_OriginalOwners.push_back(owner);
		}
	}
}

Action Plugin::OnTakeDamage(int victim, int& attacker, int& inflictor, float& damage, int& damagetype, int& weapon, float damageForce[3], float damagePosition[3], int damagecustom)
{
	return Plugin_Changed;
}

Action Plugin::OnTakeDamageAlive(int victim, int& attacker, int& inflictor, float& damage, int& damagetype, int& weapon, float damageForce[3], float damagePosition[3], int damagecustom)
{
	if (victim == attacker || attacker == 0)
		return Plugin_Continue;

	if (!Utils::IsClientValid(attacker) && Utils::IsClientValid(victim) && PM::IsValidEntity(attacker))
	{
		char name[32];
		PM::GetEntityClassname(attacker, name, sizeof(name));
		if (PM::StrEqualCaseSensitive(name, "weapon_melee"))
		{
			for (const auto& owner : plugin.m_OriginalOwners)
			{
				if (owner.weapon == attacker)
				{
					int client = PM::GetClientOfUserId(owner.userid);
					if (Utils::IsClientValid(client))
					{
						attacker = client;
						float damageDone = 30.0f;
						int armor = PM::GetClientArmor(victim);
						if (armor < 15)
							damageDone += (15 - armor) * 2.0f;

						if (owner.team == PM::GetClientTeam(victim))
						{
							if (/* TODO: Add check for friendly-fire here */false)
								damageDone *= 0.5f;
							else
								damageDone = 0.0f;
						}

						damage = damageDone;
						return Plugin_Changed;
					}
				}
			}
		}
	}

	return Plugin_Continue;
}

void Plugin::OnTakeDamageAlivePost(int victim, int attacker, int inflictor, float damage, int damagetype, int weapon, const float damageForce[3], const float damagePosition[3], int damagecustom)
{
	if (victim == attacker || attacker == 0 || damage == 0.0f)
		return;

	int healthLeft = PM::GetClientHealth(victim) - damage;
	PM::PrintCenterText(attacker, "You hit <font color='#0000ff'> %N </font> for <font color='#ff0000'> %d </font> HP\n%d HP left", victim, damage, healthLeft);
	if (healthLeft <= 0)
	{
		// TODO:
		//AddPointsForFrag(victim, client);
	}
}

Action Plugin::SetTransmit(int entity, int client)
{
	return Plugin_Continue;
}

Action Plugin::CMDShopCallback(int client, std::string& command, int argc)
{
	if (PM::GetClientTeam(client) == CS_TEAM_T)
	{
		if (plugin.m_TShop.IsEnabled())
			plugin.m_TShop.DisplayToClient(client, 20);
		else
			PM::PrintCenterText(client, "[URNA SHOP] Sorry, shop is disabled");
	}
	else if (PM::GetClientTeam(client) == CS_TEAM_CT)
	{
		if (plugin.m_CTShop.IsEnabled())
			plugin.m_CTShop.DisplayToClient(client, 20);
		else
			PM::PrintCenterText(client, "[URNA SHOP] Sorry, shop is disabled");
	}

	/*if (client == 0)
		++client;
	float pos[3];
	PM::GetClientEyePosition(client, pos);
	float angles[3];
	PM::GetClientEyeAngles(client, angles);

	Handle trace = PM::TR_TraceRayFilterEx(pos, angles, MASK_VISIBLE, RayType::RayType_Infinite, FilterClientsFunc, reinterpret_cast<void*>(client));
	if (PM::TR_DidHit(trace))
	{
		float endpos[3];
		PM::TR_GetEndPosition(pos, trace);
		int ts = LineGoesThroughSmoke(pos, endpos);
		int hitClient = PM::TR_GetEntityIndex(trace);
		if (hitClient > 0 && hitClient <= PM::GetMaxClients() && PM::IsClientInGame(hitClient))
		{
			char name[MAX_NAME_LENGTH];
			PM::GetClientName(hitClient, name, sizeof(name));
			PM::PrintToChatAll("%s, %d", name, ts);
		}
	}

	PM::CloseHandle(trace);

	MenuHandle menu = PublicManager::CreateMenu(TestMenuHandler, MENU_ACTIONS_DEFAULT);
	PublicManager::SetMenuTitle(menu, "Menu Title here");
	PublicManager::AddMenuItem(menu, "1", "Choice1", ITEMDRAW_DEFAULT);
	PublicManager::AddMenuItem(menu, "2", "Choice2", ITEMDRAW_DEFAULT);
	PublicManager::AddMenuItem(menu, "3", "Choice3", ITEMDRAW_DEFAULT);
	PublicManager::SetMenuExitButton(menu, false);
	PublicManager::DisplayMenu(menu, client + 1, 20);*/

	return Plugin_Handled;
}

Action Plugin::CMDLastRequestCallback(int client, std::string& command, int argc)
{
	LastRequestManager::DisplayLastRequestMainMenu(client, [](int client, LastRequest::Type type)
	{
			LastRequest* lastRequest = nullptr;
			switch (type)
			{
			case LastRequest::Type::CloseFight:
				lastRequest = new CloseFightLastRequest(client);
			case LastRequest::Type::Shot4Shot:
				break;
			case LastRequest::Type::GunToss:
				break;
			case LastRequest::Type::ChickenFight:
				break;
			case LastRequest::Type::Noscope:
				break;
			case LastRequest::Type::HotPotato:
				break;
			case LastRequest::Type::DodgeBall:
				break;
			case LastRequest::Type::Rebel:
				break;
			}

			if (lastRequest)
				lastRequest->StartWithMenu(client);
	});

	return Plugin_Handled;
}

#include <limits>
#undef max

Action Plugin::AdminTestCallback(int client, std::string& command, int argc)
{
	Server::GetAllBansAsync([](std::vector<Ban>& bans)
	{
		for (Ban& ban : bans)
			PM::PrintToChatAll("%s", std::to_string(ban.length));
	});

	/*Server::GetAllAdminsAsync([](std::vector<Admin>& admins)
	{
		for (const Admin& admin : admins)
			rootconsole->ConsolePrint(admin.steamID.c_str());
	});*/

	if (Utils::IsClientValid(client))
		plugin.mAdminMenu->ShowMenu(client);
	return Plugin_Handled;
}

Shop& Plugin::GetTShop()
{
	return plugin.m_TShop;
}

Shop& Plugin::GetCTShop()
{
	return plugin.m_CTShop;
}
