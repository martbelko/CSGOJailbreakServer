#pragma once

#include "PublicManager.h"

#include "Plugin/Offsets.h"

static void TShopItemHammer(int client)
{
	PublicManager::GivePlayerItem(client, "weapon_hammer");
}

static void TShopSpanner(int client)
{
	PublicManager::GivePlayerItem(client, "weapon_spanner");
}

static void TShopAxe(int client)
{
	PublicManager::GivePlayerItem(client, "weapon_axe");
}

static void TShopKnife(int client)
{
	PublicManager::GivePlayerItem(client, "weapon_knife");
}

static void TShopTaser(int client)
{
	PublicManager::GivePlayerItem(client, "weapon_taser");
}

static void TShopHealhshot(int client)
{
	PublicManager::GivePlayerItem(client, "weapon_healthshot");
}

static void TShopHEGrenade(int client)
{
	PublicManager::GivePlayerItem(client, "weapon_hegrenade");
}

static void TShopFlashbang(int client)
{
	PublicManager::GivePlayerItem(client, "weapon_flashbang");
}

static void TShopSmoke(int client)
{
	PublicManager::GivePlayerItem(client, "weapon_smokegrenade");
}

static void TShopMolotov(int client)
{
	PublicManager::GivePlayerItem(client, "weapon_molotov");
}

static void TShopTAGrenade(int client)
{
	PublicManager::GivePlayerItem(client, "weapon_tagrenade");
}

static void TShopKevlar(int client)
{
	PublicManager::GivePlayerItem(client, "item_kevlar");
}

static void TShopKevlarHelmet(int client)
{
	PublicManager::GivePlayerItem(client, "item_assaultsuit");
}

static void TShopBreachCharge(int client)
{
	PublicManager::GivePlayerItem(client, "weapon_breachcharge");
}

static void TShopDJump(int client)
{
	// TODO:
}

static void TShopFastwalk(int client)
{
	// TODO:
}

static void TShopInvisibility(int client)
{
	// TODO:
}

static void TShopChangeskin(int client)
{
	// TODO:
}

static void TShopBlind(int client)
{
	// TODO:
}

static void TShopOpen(int client)
{
	// TODO:
}

static void TShopFortune(int client)
{
	// TODO:
}

static void CTShopHelmet(int client)
{
	PublicManager::SetEntData(client, Offset::m_bHasHelmet, true);
}

static void CTShopTAGrenade(int client)
{
	PublicManager::GivePlayerItem(client, "weapon_tagrenade");
}

static void CTShopHealthshot(int client)
{
	PublicManager::GivePlayerItem(client, "weapon_healthshot");
}

static void CTShopShield(int client)
{
	PublicManager::GivePlayerItem(client, "weapon_shield");
}

static void CTShopDJump(int client)
{
	// TODO:
}

static void CTShopHeavySuit(int client)
{
	PublicManager::GivePlayerItem(client, "item_heavyassaultsuit");
}
