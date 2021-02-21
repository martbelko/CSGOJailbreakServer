#pragma once

#include "PublicManager.h"

#include "Plugin/Abilities/Ability.h"

class Invisibility
{
public:
	static void Enable(int client, float duration)
	{
		PublicManager::SetEntityRenderMode(client, RenderMode::RENDER_NONE);
		s_Ability.Enable(client, duration);
	}

	static void DisableEffect(int client)
	{
		PublicManager::SetEntityRenderMode(client, RenderMode::RENDER_TRANSCOLOR);
	}

	static void Disable(int client)
	{
		PublicManager::SetEntityRenderMode(client, RenderMode::RENDER_TRANSCOLOR);
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

__declspec(selectany) TimedAbility Invisibility::s_Ability;
