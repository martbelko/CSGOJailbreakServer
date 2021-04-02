#pragma once

#include "Plugin/LastRequest/LastRequest.h"

#include <string_view>

class CloseFightLastRequest : public LastRequest
{
public:
	CloseFightLastRequest(int playerT, int playerCT, const char* weaponName = "weapon_knife", int startHealth = 100, int startArmor = 0, bool helmet = false);

	virtual void OnEnd(int loser, int winner) override;

	virtual int GetPlayerT() const override { return mPlayerT; }
	virtual int GetPlayerCT() const override { return mPlayerCT; }
	virtual const char* GetName() const override { return "CloseFight"; };
private:
private:
	int mPlayerT, mPlayerCT;
};
