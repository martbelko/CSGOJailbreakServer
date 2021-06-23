#pragma once

class LastRequest
{
	friend class LastRequestManager;
public:
	enum class Type
	{
		None = 0,
		CloseFight,
		Shot4Shot,
		GunToss,
		ChickenFight,
		Noscope,
		HotPotato,
		DodgeBall,
		Rebel,
	};
public:
	virtual void StartWithMenu(int client) = 0;
	virtual void OnEnd(int loser, int winner) = 0;

	virtual int GetPlayerT() const = 0;
	virtual int GetPlayerCT() const = 0;
	virtual const char* GetName() const = 0;
	virtual Type GetType() const = 0;
protected:
	virtual ~LastRequest() = default;
};
