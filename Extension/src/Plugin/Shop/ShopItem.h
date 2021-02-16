#pragma once

#include "Plugin/VIP.h"

#include <string>
#include <sstream>

class ShopItem
{
	using ShopItemSelectedFunc = void(*)(int client);
public:
	ShopItem() = default;
	ShopItem(const std::string& name, int price, ShopItemSelectedFunc callback, VipMode vipMode = VipMode::NONE, float duration = 0.0f)
		: m_Name(name), m_Price(price), m_VipMode(vipMode), m_Duration(duration), m_Callback(callback)
	{
		constexpr char vipStr[] = " [ VIP ]";
		constexpr char extraVipStr[] = " [ ExtraVIP ]";

		m_Name += " (";
		m_Name += std::to_string(price);
		m_Name += ')';
		if (duration != 0.0f)
		{
			std::stringstream ss;
			ss.precision(2);
			ss << duration;
			m_Name += " {";
			m_Name += ss.str().c_str();
			m_Name += '}';
		}
		if (vipMode != VipMode::NONE)
		{
			if (vipMode == VipMode::VIP)
				m_Name += vipStr;
			else
				m_Name += extraVipStr;
		}
	}

	bool CanBeUsedByClient(int client)
	{
		return static_cast<int>(m_VipMode) <= static_cast<int>(VIPManager::GetClientVipMode(client));
	}

	void CallCallback(int client) { m_Callback(client); }

	const char* GetName() const { return m_Name.c_str(); }
private:
	std::string m_Name;
	int m_Price;
	VipMode m_VipMode;
	float m_Duration;
	ShopItemSelectedFunc m_Callback;
};
