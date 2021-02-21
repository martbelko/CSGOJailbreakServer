#include "Plugin.h"

#include "Plugin/Shop/ShopItemCallbacks.h"

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

	P::LoadTranslations("shop.phrases.txt");

	Offset::OnPluginStart();
	Utils::OnPluginStart();

	P::HookEvent("round_start", OnRoundStartPost, EventHookMode::EventHookMode_Post);
	P::HookEvent("player_death", OnPlayerDeathEventPost, EventHookMode::EventHookMode_Post);
	P::RegConsoleCmd("sm_shop", CMDShopCallbackStatic);

	std::vector<ShopItem> items;
	items.emplace_back("spanner", 10, &ShopItemCallback::TShopSpanner, VipMode::NONE);
	items.emplace_back("hammer", 12, &ShopItemCallback::TShopItemHammer, VipMode::NONE);
	items.emplace_back("axe", 15, &ShopItemCallback::TShopAxe, VipMode::NONE);
	items.emplace_back("Knife", 20, &ShopItemCallback::TShopKnife, VipMode::NONE);
	items.emplace_back("taser", 50, &ShopItemCallback::TShopTaser, VipMode::VIP);
	items.emplace_back("healthshot", 20, &ShopItemCallback::TShopHealhshot, VipMode::NONE);
	items.emplace_back("hegrenade", 15, &ShopItemCallback::TShopHEGrenade, VipMode::NONE);
	items.emplace_back("flashbang", 12, &ShopItemCallback::TShopFlashbang, VipMode::NONE);
	items.emplace_back("molotov", 10, &ShopItemCallback::TShopMolotov, VipMode::NONE);
	items.emplace_back("tagrenade", 12, &ShopItemCallback::TShopTAGrenade, VipMode::NONE);
	items.emplace_back("kevlar", 20, &ShopItemCallback::TShopKevlar, VipMode::NONE);
	items.emplace_back("kevlarhelmet", 30, &ShopItemCallback::TShopKevlarHelmet, VipMode::NONE);
	items.emplace_back("breachcharge", 70, &ShopItemCallback::TShopBreachCharge, VipMode::EXTRA_VIP);
	items.emplace_back("djump", 40, &ShopItemCallback::TShopDJump, VipMode::NONE);
	items.emplace_back("fastwalk", 50, &ShopItemCallback::TShopFastwalk, VipMode::NONE, 5.0f);
	items.emplace_back("invisibility", 80, &ShopItemCallback::TShopInvisibility, VipMode::NONE, 5.0f);
	items.emplace_back("changeskin", 60, &ShopItemCallback::TShopChangeskin, VipMode::NONE);
	items.emplace_back("blind", 200, &ShopItemCallback::TShopBlind, VipMode::VIP, 10.0f);
	items.emplace_back("openchance", 60, &ShopItemCallback::TShopOpen, VipMode::VIP);
	items.emplace_back("fortune", 30, &ShopItemCallback::TShopFortune, VipMode::NONE);
	m_TShop = Shop("tshop", items);

	std::vector<ShopItem> ctItems;
	ctItems.emplace_back("helmet", 20, &ShopItemCallback::CTShopHelmet);
	ctItems.emplace_back("tagrenade", 20, &ShopItemCallback::CTShopTAGrenade);
	ctItems.emplace_back("healthshot", 30, &ShopItemCallback::CTShopHealthshot);
	ctItems.emplace_back("djump", 30, &ShopItemCallback::CTShopDJump);
	ctItems.emplace_back("shield", 50, &ShopItemCallback::CTShopShield, VipMode::VIP);
	ctItems.emplace_back("heavy", 70, &ShopItemCallback::CTShopHeavySuit, VipMode::EXTRA_VIP);
	m_CTShop = Shop("ctshop", ctItems);

	for (int i = 1; i <= P::GetMaxClients(); ++i)
		if (P::IsClientInGame(i))
			OnClientPostAdminCheck(i);

	//PublicManager::SQL_TConnect(OnSQLTConnectCallbackBanlist, "banlist", 0);
}

void Plugin::OnPluginEnd()
{
	m_TShop.Delete();
	m_CTShop.Delete();
}

void Plugin::OnMapStart()
{
	int PMIndex = P::FindEntityByClassname(0, "cs_player_manager");
	P::SDKHook(PMIndex, SDKHook_ThinkPost, OnThinkPostCSPlayerManager);
}

void Plugin::OnClientPostAdminCheck(int client)
{
	Shop::SetPlayerPoints(client, 0);
	char tshopName[32], ctshopName[32];
	P::Format(tshopName, sizeof(tshopName), "%T", "tshop", client);
	P::Format(ctshopName, sizeof(ctshopName), "%T", "ctshop", client);
	m_TShop.RefreshMenusForClient(tshopName, client);
	m_CTShop.RefreshMenusForClient(ctshopName, client);

	P::SDKHook(client, SDKHookType::SDKHook_SpawnPost, OnSpawnPost);
	P::SDKHook(client, SDKHookType::SDKHook_WeaponDrop, OnWeaponDrop);
	P::SDKHook(client, SDKHookType::SDKHook_WeaponCanUse, OnWeaponCanUse);
	P::SDKHook(client, SDKHookType::SDKHook_WeaponEquipPost, OnWeaponEquipPost);
	P::SDKHook(client, SDKHookType::SDKHook_OnTakeDamage, OnTakeDamage);
	P::SDKHook(client, SDKHookType::SDKHook_OnTakeDamageAlive, OnTakeDamageAlive);
	P::SDKHook(client, SDKHookType::SDKHook_OnTakeDamageAlivePost, OnTakeDamageAlivePost);
	P::SDKHook(client, SDKHookType::SDKHook_SetTransmit, SetTransmit);

	Utils::HidePlayerFromScoreboard(client, Admin::IsClientAdmin(client));
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
		P::KillTimer(plugin.m_ShopDisableTimer);
		plugin.m_ShopDisableTimer = INVALID_HANDLE;
	}

	plugin.m_TShop.SetEnable(true);
	plugin.m_CTShop.SetEnable(true);

	plugin.m_ShopDisableTimer = P::CreateTimer(Globals::shopTime, [](Handle, void* value)
	{
		plugin.m_TShop.SetEnable(false);
		plugin.m_CTShop.SetEnable(false);
		return Plugin_Continue;
	},
	nullptr, TIMER_FLAG_NO_MAPCHANGE);

	P::CreateTimer(Globals::disarmTimerLength, [](Handle, void*)
	{
		plugin.m_AllowDropWeapons = true;
		return Plugin_Handled;
	},
	nullptr, TIMER_FLAG_NO_MAPCHANGE);

	return Plugin_Continue;
}

Action Plugin::OnPlayerDeathEventPost(EventHandle eventHandle, const char* name, bool dontBroadcast)
{
	int client = P::GetClientOfUserId(P::GetEventInt(eventHandle, "userid"));
	ClearAllAbilitiesForClient(client);
	return Plugin_Continue;
}

void Plugin::OnSpawnPost(int client)
{
	Utils::DisarmPlayer(client);
	P::CreateTimer(Globals::disarmTimerLength, [](Handle, void* data)
	{
		int userid = reinterpret_cast<int>(data);
		int client = P::GetClientOfUserId(userid);
		Utils::DisarmPlayer(client);
		P::GivePlayerItem(client, "weapon_fists");
		if (P::GetClientTeam(client) == CS_TEAM_T)
			plugin.m_TShop.DisplayToClient(client, 20);
		else
			plugin.m_CTShop.DisplayToClient(client, 20);
		return Plugin_Continue;
	},
	reinterpret_cast<void*>(P::GetClientUserId(client)));
}

Action Plugin::OnWeaponDrop(int client, int weapon)
{
	if (!plugin.m_AllowDropWeapons)
		return Plugin_Handled;
	return Plugin_Continue;
}

Action Plugin::OnWeaponCanUse(int client, int weapon)
{
	char classname[64];
	P::GetEntityClassname(weapon, classname, sizeof(classname));
	if ((P::StrEqualCaseSensitive(classname, "weapon_melee") || P::StrEqualCaseSensitive(classname, "weapon_knife")) &&
		((!Utils::HasWeapon(client, "weapon_melee") && !Utils::HasWeapon(client, "weapon_knife"))))
	{
		P::EquipPlayerWeapon(client, weapon);
		return Plugin_Continue;
	}
	else if (P::StrEqualCaseSensitive(classname, "weapon_fists") && !Utils::HasWeapon(client, "weapon_fists"))
	{
		P::EquipPlayerWeapon(client, weapon);
		return Plugin_Continue;
	}

	return Plugin_Continue;
}

void Plugin::OnWeaponEquipPost(int client, int weapon)
{
	if (P::IsValidEntity(weapon))
	{
		char name[32];
		P::GetEntityClassname(weapon, name, sizeof(name));
		if (P::StrEqualCaseSensitive(name, "weapon_melee"))
		{
			// Try to find weapon index in dropped weapons
			for (auto& owner : plugin.m_OriginalOwners)
			{
				if (owner.weapon == weapon)
				{
					owner.userid = P::GetClientUserId(client);
					owner.team = P::GetClientTeam(client);
					return;
				}
			}

			// If its new weapon, create object and push it
			OrigOwnerWeapon owner;
			owner.userid = P::GetClientUserId(client);
			owner.team = P::GetClientTeam(client);
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

	if (!Utils::IsClientValid(attacker) && Utils::IsClientValid(victim) && P::IsValidEntity(attacker))
	{
		char name[32];
		P::GetEntityClassname(attacker, name, sizeof(name));
		if (P::StrEqualCaseSensitive(name, "weapon_melee"))
		{
			for (const auto& owner : plugin.m_OriginalOwners)
			{
				if (owner.weapon == attacker)
				{
					int client = P::GetClientOfUserId(owner.userid);
					if (Utils::IsClientValid(client))
					{
						attacker = client;
						float damageDone = 30.0f;
						int armor = P::GetClientArmor(victim);
						if (armor < 15)
							damageDone += (15 - armor) * 2.0f;

						if (owner.team == P::GetClientTeam(victim))
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

	int healthLeft = P::GetClientHealth(victim) - damage;
	P::PrintCenterText(attacker, "You hit <font color='#0000ff'> %N </font> for <font color='#ff0000'> %d </font> HP\n%d HP left", victim, damage, healthLeft);
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

void Plugin::OnThinkPostCSPlayerManager(int manager)
{
	Utils::OnThinkPostCSPlayerManager(manager);
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
