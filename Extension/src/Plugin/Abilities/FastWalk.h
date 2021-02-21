#pragma once

#include "PublicManager.h"

#include "Plugin/Abilities/Ability.h"

class FastWalk
{
public:
	static void Enable(int client, float duration, float multiplier)
	{
		PublicManager::SetEntPropFloat(client, Prop_Data, "m_flLaggedMovementValue", multiplier);
		s_Ability.Enable(client, duration);
	}

	static void DisableEffect(int client)
	{
		PublicManager::SetEntPropFloat(client, Prop_Data, "m_flLaggedMovementValue", 1.0f);
	}

	static void Disable(int client)
	{
		PublicManager::SetEntPropFloat(client, Prop_Data, "m_flLaggedMovementValue", 1.0f);
		s_Ability.Disable(client);
	}

	static bool IsActive(int client)
	{
		return s_Ability.IsActive(client);
	}

	static void SetUpdateCallback(TimedAbilityUpdateCallbackFunc callback)
	{
		s_Ability.SetUpdateCallback(callback);
	}

	static void SetOnDisableCallback(TimedAbilityOnDisableCallbackFunc callback)
	{
		s_Ability.SetOnDisableCallback(callback);
	}
private:
	static TimedAbility s_Ability;
};

__declspec(selectany) TimedAbility FastWalk::s_Ability;
