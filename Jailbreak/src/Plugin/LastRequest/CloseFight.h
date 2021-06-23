#pragma once

#include "Menu.h"

#include "Plugin/LastRequest/LastRequest.h"

class CloseFightLastRequest : public LastRequest
{
public:
	CloseFightLastRequest(int playerT);
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
	int mPlayerT = 0, mPlayerCT = 0;
	int mStartHealth = 0;
	std::string mWeaponName;
	Menu mWeaponMenu;
	Menu mStartHealthMenu;
private:
	static constexpr const char* sKnifeInfoStr = "weapon_knife";
	static constexpr const char* sFistsInfoStr = "weapon_fists";

	static constexpr const char* sHealth1InfoStr = "1";
	static constexpr const char* sHealth35InfoStr = "35";
	static constexpr const char* sHealth100InfoStr = "100";
};
