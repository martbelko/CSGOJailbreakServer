#include "CloseFight.h"

#include "PublicManager.h"
#include "Plugin/Utils.h"

CloseFightLastRequest::CloseFightLastRequest(int playerT, int playerCT, const char* weaponName, int startHealth, int startArmor, bool helmet)
	: mPlayerT(playerT), mPlayerCT(playerCT)
{
	Utils::DisarmPlayer(playerT);
	Utils::DisarmPlayer(playerCT);
	PM::SetEntityHealth(playerT, startHealth);
	PM::SetEntityHealth(playerCT, startHealth);
	Utils::SetPlayerArmor(playerT, startArmor);
	Utils::SetPlayerArmor(playerCT, startArmor);
	if (helmet)
	{
		Utils::SetPlayerHelmet(playerT, helmet);
		Utils::SetPlayerHelmet(playerCT, helmet);
	}

	PM::GivePlayerItem(playerT, weaponName);
	PM::GivePlayerItem(playerCT, weaponName);

	PM::PrintToChatAll("Starting LR...");

	// TODO: Set beacon or other mark
}

void CloseFightLastRequest::OnEnd(int loser, int winner)
{
	// TODO: Remove beacon etc

	PM::PrintToChatAll("Canceling LR...");
}
