#pragma once

#include "Plugin/Abilities/Ability.h"

class AbilityManager
{
public:
	static Ability& GetActiveAbility(int client) { return *sAbilities[client]; }
private:
	static Ability* sAbilities[MAXPLAYERS];
};
