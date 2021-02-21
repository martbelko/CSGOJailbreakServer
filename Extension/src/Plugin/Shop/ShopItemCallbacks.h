#pragma once

#include "PublicManager.h"

#include "Plugin/Global.h"
#include "Plugin/Offsets.h"

#include "Plugin/Shop/ShopItem.h"

#include "Plugin/Abilities/DoubleJump.h"
#include "Plugin/Abilities/FastWalk.h"
#include "Plugin/Abilities/Invisibility.h"

class ShopItemCallback
{
public:
	static void TShopItemHammer(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_hammer");
		NotifyHud(client, "%t", "GotHammerHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t","GotHammerChat", name);
	}

	static void TShopSpanner(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_spanner");
		NotifyHud(client, "%t", "GotSpannerHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotSpannerChat", name);
	}

	static void TShopAxe(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_axe");
		NotifyHud(client, "%t", "GotAxeHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotAxeChat", name);
	}

	static void TShopKnife(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_knife");
		NotifyHud(client, "%t", "GotKnifeHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotKnifeChat", name);
	}

	static void TShopTaser(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_taser");
		NotifyHud(client, "%t", "GotTaserHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotTaserChat", name);
	}

	static void TShopHealhshot(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_healthshot");
		NotifyHud(client, "%t", "GotHealthshotHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotHealthshotChat", name);
	}

	static void TShopHEGrenade(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_hegrenade");
		NotifyHud(client, "%t", "GotHEGrenadeHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotHEGrenadeChat", name);
	}

	static void TShopFlashbang(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_flashbang");
		NotifyHud(client, "%t", "GotFlashbangHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotFlashbangChat", name);
	}

	static void TShopSmoke(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_smokegrenade");
		NotifyHud(client, "%t", "GotSmokeHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotSmokeChat", name);
	}

	static void TShopMolotov(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_molotov");
		NotifyHud(client, "%t", "GotMolotovHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotMolotovChat", name);
	}

	static void TShopTAGrenade(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_tagrenade");
		NotifyHud(client, "%t", "GotTAGrenadeHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotTAGrenadeChat", name);
	}

	static void TShopKevlar(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "item_kevlar");
		NotifyHud(client, "%t", "GotKevlarHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotKevlarChat", name);
	}

	static void TShopKevlarHelmet(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "item_assaultsuit");
		NotifyHud(client, "%t", "GotKevlarHelmetHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotKevlarHelmetChat", name);
	}

	static void TShopBreachCharge(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_breachcharge");
		NotifyHud(client, "%t", "GotBreachChargeHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotBreachChargeChat", name);
	}

	static void TShopDJump(int client, const ShopItem* item)
	{
		DoubleJump::Enable(client);
		NotifyHud(client, "%t", "GotDoubleJumpHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotDoubleJumpChat", name);
	}

	static void TShopFastwalk(int client, const ShopItem* item)
	{
		FastWalk::SetUpdateCallback([](int client, float remains)
		{
			if (remains == 0.0f)
			{
				FastWalk::DisableEffect(client);
				NotifyHud(client, "Done!");
				return false;
			}
			else
			{
				NotifyHud(client, "%f remains", remains);
				return true;
			}
		});

		FastWalk::SetOnDisableCallback([](int client)
		{
			NotifyHud(client, "");
		});

		FastWalk::Enable(client, item->GetDuration(), 1.5f);
		NotifyHud(client, "%t", "GotFastwalkHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotFastwalkChat", name);
	}

	static void TShopInvisibility(int client, const ShopItem* item)
	{
		Invisibility::SetUpdateCallback([](int client, float remains)
		{
			if (remains == 0.0f)
			{
				Invisibility::DisableEffect(client);
				NotifyHud(client, "Done!");
				return false;
			}
			else
			{
				NotifyHud(client, "%f remains", remains);
				return true;
			}
		});

		Invisibility::SetOnDisableCallback([](int client)
		{
			NotifyHud(client, "");
		});

		Invisibility::Enable(client, item->GetDuration());
		NotifyHud(client, "%t", "GotInvisibilityHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotInvisibilityChat", name);
	}

	static void TShopChangeskin(int client, const ShopItem* item)
	{
		// TODO:
		NotifyHud(client, "%t", "GotChangeSkinHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotChangeSkinChat", name);
	}

	static void TShopBlind(int client, const ShopItem* item)
	{
		// TODO:
		NotifyHud(client, "%t", "GotBlindHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotBlindChat", name);
	}

	static void TShopOpen(int client, const ShopItem* item)
	{
		// TODO:
		NotifyHud(client, "%t", "GotOpenDoorsHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotOpenDoorsChat", name);
	}

	static void TShopFortune(int client, const ShopItem* item)
	{
		// TODO:
		NotifyHud(client, "%t", "GotWheelOfFortuneHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotWheelOfFortuneChat", name);
	}

	static void CTShopHelmet(int client, const ShopItem* item)
	{
		PublicManager::SetEntData(client, Offset::m_bHasHelmet, true);
		NotifyHud(client, "%t", "GotHelmetHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotHelmetChat", name);
	}

	static void CTShopTAGrenade(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_tagrenade");
		NotifyHud(client, "%t", "GotTAGrenadeHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotTAGrenadeChat", name);
	}

	static void CTShopHealthshot(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_healthshot");
		NotifyHud(client, "%t", "GotHealthshotHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotHealtshotChat", name);
	}

	static void CTShopShield(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_shield");
		NotifyHud(client, "%t", "GotShieldHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotShieldChat", name);
	}

	static void CTShopDJump(int client, const ShopItem* item)
	{
		DoubleJump::Enable(client);
		NotifyHud(client, "%t", "GotDoubleJumpHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotDoubleJumpChat", name);
	}

	static void CTShopHeavySuit(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "item_heavyassaultsuit");
		NotifyHud(client, "%t", "GotHeavySuitHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(client, "%t", "GotHeavySuitChat", name);
	}
private:
	template<typename ... Args>
	static void NotifyHud(int client, const char* format, Args ... args)
	{
		PublicManager::SetHudTextParams(-1.0, 0.4, 5.0, 255, 255, 255, 255, 0);
		PublicManager::ShowHudText(client, Globals::shopItemReceiveChannel, format, args...);
	}

	template<typename ... Args>
	static void NotifyTeamChat(int client, const char* format, Args ... args)
	{
		int clientTeam = P::GetClientTeam(client);
		for (int i = 1; i <= PublicManager::GetMaxClients(); ++i)
			if (P::IsClientInGame(i) && P::GetClientTeam(i) == clientTeam && client != i)
				P::PrintToChat(i, format, args...);
	}
};
