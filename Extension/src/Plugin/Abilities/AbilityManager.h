#pragma once

#include "PublicManager.h"

#include <vector>

class Ability;

class AbilityManager
{
public:
	static void RegisterAbility(int client, Ability* ability) { sAbilities[client - 1].push_back(ability); }
	static void RemoveAbility(int client, Ability* ability)
	{
		std::vector<Ability*>& abilities = sAbilities[client - 1];
		abilities.erase(std::find(abilities.begin(), abilities.end(), ability));
	}

	static std::vector<Ability*>& GetActiveAbilitiesForClient(int client) { return sAbilities[client]; }
private:
	static std::vector<Ability*> sAbilities[MAXPLAYERS];
};
