#pragma once

#include "PublicManager.h"

#include "Plugin/Global.h"
#include "Plugin/Offsets.h"

#include "Plugin/Shop/ShopItem.h"

#include "Plugin/Abilities/DoubleJump.h"
#include "Plugin/Abilities/FastWalk.h"
#include "Plugin/Abilities/Invisibility.h"
#include "Plugin/Abilities/Blind.h"

class ShopItemCallback
{
public:
	static void Init()
	{
		BlindAbility::SetCallbackClass(&sBlindAbilityCallback);
	}

	static void TShopItemHammer(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_hammer");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotHammerHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t","GotHammerChat", name);
	}

	static void TShopSpanner(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_spanner");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotSpannerHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotSpannerChat", name);
	}

	static void TShopAxe(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_axe");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotAxeHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotAxeChat", name);
	}

	static void TShopKnife(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_knife");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotKnifeHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotKnifeChat", name);
	}

	static void TShopTaser(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_taser");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotTaserHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotTaserChat", name);
	}

	static void TShopHealhshot(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_healthshot");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotHealthshotHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotHealthshotChat", name);
	}

	static void TShopHEGrenade(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_hegrenade");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotHEGrenadeHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotHEGrenadeChat", name);
	}

	static void TShopFlashbang(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_flashbang");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotFlashbangHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotFlashbangChat", name);
	}

	static void TShopSmoke(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_smokegrenade");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotSmokeHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotSmokeChat", name);
	}

	static void TShopMolotov(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_molotov");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotMolotovHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotMolotovChat", name);
	}

	static void TShopTAGrenade(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_tagrenade");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotTAGrenadeHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotTAGrenadeChat", name);
	}

	static void TShopKevlar(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "item_kevlar");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotKevlarHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotKevlarChat", name);
	}

	static void TShopKevlarHelmet(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "item_assaultsuit");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotKevlarHelmetHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotKevlarHelmetChat", name);
	}

	static void TShopBreachCharge(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_breachcharge");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotBreachChargeHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotBreachChargeChat", name);
	}

	static void TShopDJump(int client, const ShopItem* item)
	{
		DoubleJump::Enable(client);
		NotifyHud(client, sDefaultHoldTime, "%t", "GotDoubleJumpHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotDoubleJumpChat", name);
	}

	static void TShopFastwalk(int client, const ShopItem* item)
	{
		FastWalk::SetUpdateCallback([](int client, float remains)
		{
			if (remains == 0.0f)
			{
				FastWalk::DisableEffect(client);
				NotifyHud(client, sDefaultHoldTime, "Done!");
				return false;
			}
			else
			{
				NotifyHud(client, sDefaultHoldTime, "%f remains", remains);
				return true;
			}
		});

		FastWalk::SetOnDisableCallback([](int client)
		{
			NotifyHud(client, sDefaultHoldTime, "");
		});

		FastWalk::Enable(client, item->GetDuration(), 1.5f);
		NotifyHud(client, sDefaultHoldTime, "%t", "GotFastwalkHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotFastwalkChat", name);
	}

	static void TShopInvisibility(int client, const ShopItem* item)
	{
		Invisibility::SetUpdateCallback([](int client, float remains)
		{
			if (remains == 0.0f)
			{
				Invisibility::DisableEffect(client);
				NotifyHud(client, sDefaultHoldTime, "Done!");
				return false;
			}
			else
			{
				NotifyHud(client, sDefaultHoldTime, "%f remains", remains);
				return true;
			}
		});

		Invisibility::SetOnDisableCallback([](int client)
		{
			NotifyHud(client, sDefaultHoldTime, "");
		});

		Invisibility::Enable(client, item->GetDuration());
		NotifyHud(client, sDefaultHoldTime, "%t", "GotInvisibilityHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotInvisibilityChat", name);
	}

	static void TShopChangeskin(int client, const ShopItem* item)
	{
		// TODO:
		NotifyHud(client, sDefaultHoldTime, "%t", "GotChangeSkinHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotChangeSkinChat", name);
	}

	static void TShopBlind(int client, const ShopItem* item)
	{
		BlindAbility::Enable(&client, 1, 7.0f);
		NotifyHud(client, sDefaultHoldTime, "%t", "GotBlindHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotBlindChat", name);
	}

	static void TShopOpen(int client, const ShopItem* item)
	{
		// TODO:
		NotifyHud(client, sDefaultHoldTime, "%t", "GotOpenDoorsHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotOpenDoorsChat", name);
	}

	static void TShopFortune(int client, const ShopItem* item)
	{
		// TODO:
		NotifyHud(client, sDefaultHoldTime, "%t", "GotWheelOfFortuneHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotWheelOfFortuneChat", name);
	}

	static void CTShopHelmet(int client, const ShopItem* item)
	{
		PublicManager::SetEntData(client, Offset::m_bHasHelmet, true);
		NotifyHud(client, sDefaultHoldTime, "%t", "GotHelmetHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotHelmetChat", name);
	}

	static void CTShopTAGrenade(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_tagrenade");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotTAGrenadeHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotTAGrenadeChat", name);
	}

	static void CTShopHealthshot(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_healthshot");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotHealthshotHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotHealtshotChat", name);
	}

	static void CTShopShield(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "weapon_shield");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotShieldHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotShieldChat", name);
	}

	static void CTShopDJump(int client, const ShopItem* item)
	{
		DoubleJump::Enable(client);
		NotifyHud(client, sDefaultHoldTime, "%t", "GotDoubleJumpHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotDoubleJumpChat", name);
	}

	static void CTShopHeavySuit(int client, const ShopItem* item)
	{
		PublicManager::GivePlayerItem(client, "item_heavyassaultsuit");
		NotifyHud(client, sDefaultHoldTime, "%t", "GotHeavySuitHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotHeavySuitChat", name);
	}
private:
	template<typename ... Args>
	static void NotifyHud(int client, float holdTime, const char* format, Args ... args)
	{
		PublicManager::SetHudTextParams(-1.0, holdTime, 5.0, 255, 255, 255, 255, 0);
		PublicManager::ShowHudText(client, Globals::shopItemReceiveChannel, format, args...);
	}

	template<typename ... Args>
	static void NotifyTeamChat(int team, int clientToExclude, const char* format, Args ... args)
	{
		for (int i = 1; i <= PublicManager::GetMaxClients(); ++i)
			if (PublicManager::IsClientInGame(i) && PublicManager::GetClientTeam(i) == team && clientToExclude != i)
				PublicManager::PrintToChat(i, format, args...);
	}

	class BlindCallbackClass : public BlindAbilityCallback
	{
	public:
		virtual void OnStart(float remainingTime) override
		{
			NotifyTeamChat(CS_TEAM_T, 0, "CSs are blind now!");
			OnUpdate(remainingTime);
		}

		virtual void OnUpdate(float remainingTime) override
		{
			for (int i = 1; i < PublicManager::GetMaxClients(); ++i)
			{
				if (PublicManager::IsClientInGame(i) && PublicManager::GetClientTeam(i) == CS_TEAM_T)
					NotifyHud(i, 1.0f, "Blind: %f remains", remainingTime);
			}
		}

		virtual void OnEnd(int client) override
		{
			NotifyHud(client, 1.0f, "");
		}
	};
private:
	static constexpr float sDefaultHoldTime = 5.0f;
	static BlindCallbackClass sBlindAbilityCallback;
};
