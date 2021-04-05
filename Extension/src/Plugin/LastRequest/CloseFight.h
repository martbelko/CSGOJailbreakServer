#pragma once

#include "Menu.h"

#include "Plugin/LastRequest/LastRequest.h"

#include <string_view>

class CloseFightLastRequest : public LastRequest
{
public:
	CloseFightLastRequest(int client);
	CloseFightLastRequest(int playerT, int playerCT, const char* weaponName = "weapon_knife", int startHealth = 100);

	virtual ~CloseFightLastRequest() override;

	virtual void StartWithMenu(int client) override;
	virtual void OnEnd(int loser, int winner) override;

	virtual int GetPlayerT() const override { return mPlayerT; }
	virtual int GetPlayerCT() const override { return mPlayerCT; }
	virtual const char* GetName() const override { return "CloseFight"; };
	virtual Type GetType() const override { return Type::CloseFight; };
private:
	static int WeaponMenuHandler(Menu* menu, MenuAction action, int param1, int param2);
	static int StartHealthMenuHandler(Menu* menu, MenuAction action, int param1, int param2);
private:
	int mPlayerT, mPlayerCT;
	int mStartHealth;
	std::string mWeaponName;
	Menu mWeaponMenu;
	Menu mStartHealthMenu;
};
