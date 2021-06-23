#include "CloseFight.h"

#include "PublicManager.h"
#include "Plugin/Utils.h"

#include <string_view>

int CloseFightLastRequest::WeaponMenuHandler(Menu* menu, MenuAction action, int param1, int param2)
{
	if (action == MenuAction_Select)
	{
		int client = param1;
		if (Utils::IsClientValid(client))
		{
			char infoBuf[32];
			menu->GetItem(param2, infoBuf, sizeof(infoBuf));
			std::string_view weaponName(infoBuf);

			// TODO: Add debug macro here for this if
			if (weaponName.empty())
			{
				std::stringstream message;
				message << "[URNA LastRequest] Invalid infoStr (" << __FILE__
					<< ", " << __LINE__ << "), infoStr was: " << infoBuf;
				PM::PrintToServer(message.str().c_str());
				return 0;
			}

			CloseFightLastRequest* lr = reinterpret_cast<CloseFightLastRequest*>(menu->GetParam());
			lr->mWeaponName = weaponName;
		}
	}

	return 0;
}

int CloseFightLastRequest::StartHealthMenuHandler(Menu* menu, MenuAction action, int param1, int param2)
{
	if (action == MenuAction_Select)
	{
		int client = param1;
		if (Utils::IsClientValid(client))
		{
			char infoBuf[4];
			menu->GetItem(param2, infoBuf, sizeof(infoBuf));
			int startHealth = PM::StringToInt(infoBuf);

			// TODO: Add debug macro here for this if too
			if (startHealth == 0)
			{
				std::stringstream message;
				message << "[URNA LastRequest] Invalid infoStr (" << __FILE__
					<< ", " << __LINE__ << "), infoStr was: " << infoBuf;
				PM::PrintToServer(message.str().c_str());
				return 0;
			}

			CloseFightLastRequest* lr = reinterpret_cast<CloseFightLastRequest*>(menu->GetParam());
			lr->mStartHealth = startHealth;
		}
	}

	return 0;
}

CloseFightLastRequest::CloseFightLastRequest(int playerT)
	: mPlayerT(playerT)
{
	// TODO: Translate
	mWeaponMenu = Menu(WeaponMenuHandler);
	mWeaponMenu.SetParam(this);
	mWeaponMenu.AddItem(sKnifeInfoStr, "Knife");
	mWeaponMenu.AddItem(sFistsInfoStr, "Fists");

	mStartHealthMenu = Menu(StartHealthMenuHandler);
	mStartHealthMenu.SetParam(this);
	mStartHealthMenu.AddItem(sHealth1InfoStr, "1 HP");
	mStartHealthMenu.AddItem(sHealth35InfoStr, "35 HP");
	mStartHealthMenu.AddItem(sHealth100InfoStr, "100 HP");
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