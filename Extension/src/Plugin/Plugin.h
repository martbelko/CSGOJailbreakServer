#pragma once

#include "BasePlugin.h"
#include "Menu.h"

#include "Plugin/Global.h"
#include "Plugin/Offsets.h"
#include "Plugin/Utils.h"

#include "Plugin/Shop/Shop.h"
#include "Plugin/VIP.h"

#include "Plugin/Abilities/DoubleJump.h"
#include "Plugin/Abilities/FastWalk.h"
#include "Plugin/Abilities/Invisibility.h"

#include "Plugin/Admin/Admin.h"

class Plugin : public BasePlugin
{
public:
	virtual void OnPluginStart() override;
	virtual void OnPluginEnd() override;

	virtual void OnMapStart() override;

	virtual void OnClientPostAdminCheck(int client) override;
	virtual void OnClientDisconnect(int client) override
	{
		ClearAllAbilitiesForClient(client);
		Utils::HidePlayerFromScoreboard(client, false);
	}

	virtual void OnGameFrame() override;
private:
	static Action OnRoundStartPost(EventHandle eventHandle, const char* name, bool dontBroadcast);
	static Action OnPlayerDeathEventPost(EventHandle eventHandle, const char* name, bool dontBroadcast);

	static void OnSpawnPost(int client);
	static Action OnWeaponDrop(int client, int weapon);
	static Action OnWeaponCanUse(int client, int weapon);
	static void OnWeaponEquipPost(int client, int weapon);
	static Action OnTakeDamage(int victim, int& attacker, int& inflictor, float& damage, int& damagetype, int& weapon, float damageForce[3], float damagePosition[3], int damagecustom);
	static Action OnTakeDamageAlive(int victim, int& attacker, int& inflictor, float& damage, int& damagetype, int& weapon, float damageForce[3], float damagePosition[3], int damagecustom);
	static void OnTakeDamageAlivePost(int victim, int attacker, int inflictor, float damage, int damagetype, int weapon, const float damageForce[3], const float damagePosition[3], int damagecustom);
	static Action SetTransmit(int entity, int other);
	static void OnThinkPostCSPlayerManager(int client);

	static Action CMDShopCallbackStatic(int client, std::string& command, int argc);
private:
	static void ClearAllAbilitiesForClient(int client)
	{
		DoubleJump::Disable(client);
		FastWalk::Disable(client);
		Invisibility::Disable(client);
	}
private:
	Shop m_TShop;
	Shop m_CTShop;

	Handle m_ShopDisableTimer = INVALID_HANDLE;
	bool m_AllowDropWeapons = true;

	struct OrigOwnerWeapon
	{
		int userid;
		int weapon;
		int team;
	};
	std::vector<OrigOwnerWeapon> m_OriginalOwners;
};
