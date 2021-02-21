#pragma once

#include "PublicManager.h"

using TimedAbilityUpdateCallbackFunc = bool(*)(int client, float timeRemains);
using TimedAbilityOnDisableCallbackFunc = void(*)(int client);

class TimedAbility
{
public:
	void Enable(int client, float duration)
	{
		if (m_Timers[client - 1] != INVALID_HANDLE)
		{
			PublicManager::KillTimer(m_Timers[client - 1], false);
			m_Timers[client - 1] = INVALID_HANDLE;
		}

		m_Structs[client - 1].ability = this;
		m_Structs[client - 1].time = duration - 1.0f;
		m_Structs[client - 1].client = client;

		m_Timers[client - 1] = PublicManager::CreateTimer(1.0f, [](Handle, void* data)
		{
			TimedAbilityStruct* abStruct = reinterpret_cast<TimedAbilityStruct*>(data);
			TimedAbility* ability = abStruct->ability;
			int client = abStruct->client;
			bool res = ability->m_UpdateCallback(client, ability->m_Structs[client - 1].time);
			if (res)
			{
				abStruct->time -= 1.0f;
				return Plugin_Continue;
			}
			else
			{
				ability->m_Timers[client - 1] = INVALID_HANDLE;
				return Plugin_Stop;
			}
		},
		&m_Structs[client - 1], TIMER_REPEAT);
	}

	void Disable(int client)
	{
		if (m_Timers[client - 1] != INVALID_HANDLE)
		{
			PublicManager::KillTimer(m_Timers[client - 1]);
			m_Timers[client - 1] = INVALID_HANDLE;
			m_OnDisableCallback(client);
		}
	}

	bool IsActive(int client)
	{
		return m_Timers[client - 1] != INVALID_HANDLE;
	}

	void SetUpdateCallback(TimedAbilityUpdateCallbackFunc callback)
	{
		m_UpdateCallback = callback;
	}

	void SetOnDisableCallback(TimedAbilityOnDisableCallbackFunc callback)
	{
		m_OnDisableCallback = callback;
	}
private:
	struct TimedAbilityStruct
	{
		TimedAbility* ability;
		int client;
		float time;
	};

	Handle m_Timers[MAXPLAYERS];
	TimedAbilityStruct m_Structs[MAXPLAYERS];
	TimedAbilityUpdateCallbackFunc m_UpdateCallback;
	TimedAbilityOnDisableCallbackFunc m_OnDisableCallback;
};
