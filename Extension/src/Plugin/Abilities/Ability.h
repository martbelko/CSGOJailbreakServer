#pragma once

#include "PublicManager.h"

#include <vector>

class Effect
{
public:
	virtual ~Effect() = default;

	virtual void Start() = 0;
	virtual void End() = 0;

	virtual int GetClient() const = 0;
	virtual bool IsActive() const = 0;
};

class Ability
{
public:
	virtual ~Ability() = default;

	virtual void Enable() = 0;
	virtual void Disable() = 0;

	virtual bool IsEnabled() const = 0;
	virtual const std::vector<Effect*>& GetEffects() const = 0;
};

class BEffect : public Effect
{
public:
	virtual void Start() override
	{
		mActive = true;
	}

	virtual void End() override
	{
		mActive = false;
	}

	virtual int GetClient() const { return mClient; }
	virtual bool IsActive() const { return mActive; }
private:
	int mClient;
	bool mActive = false;
};

class BAbility : public Ability
{
public:
	BAbility(const int players[], int playersCount)
	{
		for (int i = 0; i < playersCount; ++i)
		{

		}
	}

	virtual void Enable(float duration)
	{
		mEnabled = true;
	}

	virtual void Disable() override
	{
		mEnabled = false;
	}

	virtual bool IsEnabled() const override
	{
		return mEnabled;
	}

	virtual const std::vector<Effect*>& GetEffects() const override
	{
		return reinterpret_cast<std::vector<Effect*>>(mEffects);
	}
private:
	std::vector<BEffect> mEffects;
	bool mEnabled = false;
};

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
