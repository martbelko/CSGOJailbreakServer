#include "CloseFight.h"

#include "PublicManager.h"
#include "Plugin/Utils.h"

constexpr const char* KnifeInfoStr = "1";
constexpr const char* FistsInfoStr = "2";

constexpr const char* Health1InfoStr = "1";
constexpr const char* Health35InfoStr = "2";
constexpr const char* Health100InfoStr = "3";

int CloseFightLastRequest::WeaponMenuHandler(Menu* menu, MenuAction action, int param1, int param2)
{
	return 0;
}

int CloseFightLastRequest::StartHealthMenuHandler(Menu* menu, MenuAction action, int param1, int param2)
{
	return 0;
}

CloseFightLastRequest::CloseFightLastRequest(int client)
{
	// TODO: Translate
	mWeaponMenu = Menu(WeaponMenuHandler);
	mWeaponMenu.AddItem(KnifeInfoStr, "Knife");
	mWeaponMenu.AddItem(FistsInfoStr, "Fists");

	mStartHealthMenu = Menu(StartHealthMenuHandler);
	mWeaponMenu.AddItem(Health1InfoStr, "1 HP");
	mWeaponMenu.AddItem(Health35InfoStr, "35 HP");
	mWeaponMenu.AddItem(Health100InfoStr, "100 HP");
}

CloseFightLastRequest::CloseFightLastRequest(int playerT, int playerCT, const char* weaponName, int startHealth)
	: mPlayerT(playerT), mPlayerCT(playerCT), mWeaponName(weaponName), mStartHealth(startHealth)
{
	Utils::DisarmPlayer(playerT);
	Utils::DisarmPlayer(playerCT);
	PM::SetEntityHealth(playerT, startHealth);
	PM::SetEntityHealth(playerCT, startHealth);
	Utils::SetPlayerArmor(playerT, 0);
	Utils::SetPlayerArmor(playerCT, 0);
	Utils::SetPlayerHelmet(playerT, false);
	Utils::SetPlayerHelmet(playerCT, false);

	PM::GivePlayerItem(playerT, weaponName);
	PM::GivePlayerItem(playerCT, weaponName);

	PM::PrintToChatAll("Starting LR...");

	// TODO: Set beacon or other mark
}

CloseFightLastRequest::~CloseFightLastRequest()
{
	mWeaponMenu.Delete();
	mStartHealthMenu.Delete();
}

void CloseFightLastRequest::StartWithMenu(int client)
{
	mWeaponMenu.DisplayToClient(client, 20);
}

void CloseFightLastRequest::OnEnd(int loser, int winner)
{
	// TODO: Remove beacon etc

	PM::PrintToChatAll("Canceling LR...");
}