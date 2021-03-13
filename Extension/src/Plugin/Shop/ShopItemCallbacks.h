#pragma once

#include "PublicManager.h"

#include "Plugin/Global.h"
#include "Plugin/Offsets.h"
#include "Plugin/DoorManager.h"

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
		static ShopBlindCallback blindCallback = ShopBlindCallback();
		static ShopFastWalkCallback fastWalkCallback = ShopFastWalkCallback();
		static ShopInvisibilityCallback invisibilityCallback = ShopInvisibilityCallback();

		BlindAbility::SetCallbackClass(&blindCallback);
		FastWalk::SetCallbackClass(&fastWalkCallback);
		Invisibility::SetCallbackClass(&invisibilityCallback);
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
		FastWalk::Enable(client, item->GetDuration(), 1.5f);
	}

	static void TShopInvisibility(int client, const ShopItem* item)
	{
		Invisibility::Enable(client, item->GetDuration());
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
		BlindAbility::Enable(item->GetDuration());
	}

	static void TShopOpen(int client, const ShopItem* item)
	{
		DoorManager::OpenCellDoors();
		NotifyHud(client, sDefaultHoldTime, "%t", "GotOpenDoorsHud");
		char name[MAX_NAME_LENGTH];
		PublicManager::GetClientName(client, name, sizeof(name));
		NotifyTeamChat(CS_TEAM_T, client, "%t", "GotOpenDoorsChat", name);
	}

	static void TShopFortune(int client, const ShopItem* item);

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
		PublicManager::SetHudTextParams(-1.0f, -1.0f, holdTime, 255, 255, 255, 255);
		PublicManager::ShowHudText(client, Globals::shopItemReceiveChannel, format, args...);
	}

	template<typename ... Args>
	static void NotifyTeamChat(int team, int clientToExclude, const char* format, Args ... args)
	{
		for (int i = 1; i <= PublicManager::GetMaxClients(); ++i)
			if (PublicManager::IsClientInGame(i) && PublicManager::GetClientTeam(i) == team && clientToExclude != i)
				PublicManager::PrintToChat(i, format, args...);
	}

	class ShopBlindCallback : public BlindAbility::BlindAbilityCallback
	{
	public:
		virtual void OnStart(float remainingTime) override
		{
			// TODO: NotifyTeamChat(CS_TEAM_T, client, "%t", "GotChangeSkinChat", name);
			for (int i = 1; i < PM::GetMaxClients(); ++i)
				if (PM::IsClientInGame(i) && PM::GetClientTeam(i) == CS_TEAM_T)
					NotifyHud(i, 1.0f, "CTs are blind for %f seconds", remainingTime);
		}

		virtual void OnUpdate(float remainingTime) override
		{
			for (int i = 1; i < PM::GetMaxClients(); ++i)
				if (PM::IsClientInGame(i) && PM::GetClientTeam(i) == CS_TEAM_T)
					NotifyHud(i, 1.0f, "Blind: %f remains", remainingTime);
		}

		virtual void OnEnd() override
		{
			for (int i = 1; i < PM::GetMaxClients(); ++i)
				if (PM::IsClientInGame(i) && PM::GetClientTeam(i) == CS_TEAM_T)
					NotifyHud(i, 1.0f, "");
		}
	};

	class ShopFastWalkCallback : public FastWalk::FastWalkCallback
	{
	public:
		virtual void OnStart(int client, float remainingTime) override
		{
			NotifyHud(client, sDefaultHoldTime, "%t", "GotFastwalkHud");
			char name[MAX_NAME_LENGTH];
			PublicManager::GetClientName(client, name, sizeof(name));
			NotifyTeamChat(CS_TEAM_T, client, "%t", "GotFastwalkChat", name);
		}

		virtual void OnUpdate(int client, float remainingTime) override
		{
			NotifyHud(client, 1.0f, "FastWalk: %f remains", remainingTime);
		}

		virtual void OnEnd(int client) override
		{
			NotifyHud(client, 1.0f, "");
		}
	};

	class ShopInvisibilityCallback : public Invisibility::InvisibilityCallback
	{
		virtual void OnStart(int client, float remainingTime) override
		{
			NotifyHud(client, sDefaultHoldTime, "%t", "GotInvisibilityHud");
			char name[MAX_NAME_LENGTH];
			PublicManager::GetClientName(client, name, sizeof(name));
			NotifyTeamChat(CS_TEAM_T, client, "%t", "GotInvisibilityChat", name);
		}

		virtual void OnUpdate(int client, float remainingTime) override
		{
			NotifyHud(client, 1.0f, "Invisibility: %f remains", remainingTime);
		}

		virtual void OnEnd(int client) override
		{
			NotifyHud(client, 1.0f, "");
		}
	};
private:
	static constexpr float sDefaultHoldTime = 5.0f;
	static constexpr float sBlindTime = 5.0f;
};
