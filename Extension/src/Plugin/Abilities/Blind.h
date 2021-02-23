#pragma once

#include "Plugin/Abilities/Ability.h"

#include "Plugin/Utils.h"

class BlindAbilityCallback
{
public:
	virtual void OnStart(float remainingBlindTime) = 0;
	virtual void OnUpdate(float remainingBlindTime) = 0;
	virtual void OnEnd(int client) = 0;
};

class BlindAbility
{
public:
	static void Enable(int players[], int playerCount, float blindTime)
	{
		for (int i = 0; i < playerCount; ++i)
			sBlinded[players[i] - 1] = true;

		Utils::FadeUserMessage(players, playerCount, sBlackColor, FADE_IN | FADE_PURGE);
		sRemainingBlindTime += blindTime;
		sCallbackClass->OnStart(sRemainingBlindTime);
		if (sTimer == INVALID_HANDLE)
		{
			sTimer = PublicManager::CreateTimer(sTimerInterval, [](Handle, void*)
			{
				sRemainingBlindTime -= sTimerInterval;
				if (sRemainingBlindTime <= 0.0f)
				{
					for (int i = 1; i < PublicManager::GetMaxClients(); ++i)
					{
						if (sBlinded[i - 1] && PublicManager::IsClientInGame(i))
						{
							Utils::FadeUserMessage(&i, 1, sNormalColor, FADE_IN | FADE_STAYOUT | FADE_PURGE);
							sBlinded[i - 1] = false;
							sCallbackClass->OnEnd(i);
						}
					}

					sRemainingBlindTime = 0.0f;
					sTimer = INVALID_HANDLE;
					return Plugin_Stop;
				}

				sRemainingBlindTime -= sTimerInterval;
				sCallbackClass->OnUpdate(sRemainingBlindTime);
				return Plugin_Continue;
			},
			nullptr, TIMER_REPEAT); // We want this timer to carry over mapchanges in order to set sTimer to INVALID_HANDLE
		}
	}

	static void Disable(int client)
	{
		sBlinded[client - 1] = false;
		Utils::FadeUserMessage(&client, 1, sNormalColor, FADE_IN | FADE_STAYOUT | FADE_PURGE);
		sCallbackClass->OnEnd(client);
	}

	static void SetCallbackClass(BlindAbilityCallback* callbackClass) { sCallbackClass = callbackClass; }
private:
	static constexpr int sBlackColor[4] = { 0, 0, 0, 255 };
	static constexpr int sNormalColor[4] = { 0, 0, 0, 0 };
	static constexpr float sTimerInterval = 0.1f;

	static BlindAbilityCallback* sCallbackClass;

	static bool sBlinded[MAXPLAYERS];
	static float sRemainingBlindTime;
	static Handle sTimer;
};
