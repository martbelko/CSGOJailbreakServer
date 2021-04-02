#include "LastRequest.h"

#include "PublicManager.h"

LastRequest* LastRequestManager::sActiveLastRequest = nullptr;

void LastRequestManager::Unset(int loser, int winner)
{
	delete sActiveLastRequest;
	sActiveLastRequest = nullptr;
}

void LastRequestManager::OnPlayerDeath(int victim)
{
	bool tPlayerVictim = sActiveLastRequest->GetPlayerT() == victim;
	if (tPlayerVictim || sActiveLastRequest->GetPlayerCT() == victim)
	{
		int winner = tPlayerVictim ? sActiveLastRequest->GetPlayerCT() : sActiveLastRequest->GetPlayerT();
		sActiveLastRequest->OnEnd(victim, winner);
		LastRequestManager::Unset();
	}
}
