#pragma once

#include "PublicManager.h"

#include "Plugin/Abilities/AbilityManager.h"

#include <vector>

class Effect
{
public:
	virtual ~Effect() = default;

	virtual void Start() = 0;
	virtual void End() = 0;

	virtual const std::vector<int>& GetClients() const = 0;
	virtual bool IsActive() const = 0;
};

class Ability
{
public:
	Ability(int client)
		: mClient(client)
	{
		AbilityManager::RegisterAbility(client, this);
	}

	Ability(const Ability& other) = delete;
	Ability& operator=(const Ability& ability) = delete;

	virtual ~Ability() = default;

	void Enable() { GetEffect()->Start(); }
	void Disable() { GetEffect()->End(); }
	bool IsEnabled() const { return GetEffect()->IsActive(); };
	int GetClient() const { return mClient; };

	virtual Effect* GetEffect() = 0;
protected:
	const Effect* GetEffect() const { return GetEffect(); }
protected:
	int mClient;
};

class BEffect : public Effect
{
public:
	BEffect(const int players[], int count)
		: mClients(players, players + count * sizeof(int))
	{
	}

	virtual void Start() override
	{
		mActive = true;
		for (int client : mClients)
		{
			// HERE GOES BLIND EFFECT
		}
	}

	virtual void End() override
	{
		mActive = false;
		for (int client : mClients)
		{
			// HERE GOES UNBLIND EFFECT
		}
	}

	virtual const std::vector<int>& GetClients() const override { return mClients; }
	virtual bool IsActive() const override { return mActive; }
private:
	std::vector<int> mClients;
	bool mActive = false;
};

class BAbility : public Ability
{
public:
	BAbility(int client, const int players[], int playersCount)
		: Ability(client), mEffect(new BEffect(players, playersCount))
	{
	}

	virtual ~BAbility() override
	{
		delete mEffect;
		AbilityManager::RemoveAbility(mClient, this);
	}

	virtual Effect* GetEffect() override { return mEffect; }
private:
	BEffect* mEffect;
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
