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
#include "Plugin/Abilities/Blind.h"

#include "Plugin/Admin/AdminMenu.h"

class Plugin : public BasePlugin
{
public:
	virtual void OnPluginStart() override;
	virtual void OnPluginEnd() override;

	virtual void OnMapStart() override;
	virtual void OnMapEnd() override;

	virtual void OnClientPostAdminCheck(int client) override;
	virtual void OnClientDisconnect(int client) override
	{
		BlindAbility::OnClientDisconnect(client);
		FastWalk::OnClientDisconnect(client);
		Invisibility::OnClientDisconnect(client);
		DoubleJump::OnClientDisconnect(client);

		Utils::HidePlayerFromScoreboard(client, false);
	}

	virtual void OnGameFrame() override;
public:
	static Shop& GetTShop();
	static Shop& GetCTShop();
private:
	static Action OnRoundStartPost(EventHandle eventHandle, const char* name, bool dontBroadcast);
	static Action OnPlayerDeathEventPost(EventHandle eventHandle, const char* name, bool dontBroadcast);
	static Action OnPlayerTeamChange(EventHandle eventHandle, const char* name, bool dontBroadcast);

	static void OnSpawnPost(int client);
	static Action OnWeaponDrop(int client, int weapon);
	static Action OnWeaponCanUse(int client, int weapon);
	static void OnWeaponEquipPost(int client, int weapon);
	static Action OnTakeDamage(int victim, int& attacker, int& inflictor, float& damage, int& damagetype, int& weapon, float damageForce[3], float damagePosition[3], int damagecustom);
	static Action OnTakeDamageAlive(int victim, int& attacker, int& inflictor, float& damage, int& damagetype, int& weapon, float damageForce[3], float damagePosition[3], int damagecustom);
	static void OnTakeDamageAlivePost(int victim, int attacker, int inflictor, float damage, int damagetype, int weapon, const float damageForce[3], const float damagePosition[3], int damagecustom);
	static Action SetTransmit(int entity, int other);

	static Action CMDShopCallback(int client, std::string& command, int argc);
	static Action CMDLastRequestCallback(int client, std::string& command, int argc);

	static Action AdminTestCallback(int client, std::string& command, int argc);
private:
	Shop m_TShop;
	Shop m_CTShop;

	Handle m_ShopDisableTimer = INVALID_HANDLE;
	bool m_AllowDropWeapons;

	struct OrigOwnerWeapon
	{
		int userid;
		int weapon;
		int team;
	};
	std::vector<OrigOwnerWeapon> m_OriginalOwners;

	AdminMenu* mAdminMenu;

	Timer mThreadTimer; // Used for callbacks of async threads into main thread
private:
	static constexpr float ThreadTimerRate = 0.1f;
};
