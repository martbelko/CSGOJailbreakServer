#pragma once

#include "Plugin/VIP.h"

#include <string>
#include <sstream>

class ShopItem
{
	using ShopItemSelectedFunc = void(*)(int client, const ShopItem* item, void* param);
public:
	ShopItem() = default;
	ShopItem(const std::string& name, int price, ShopItemSelectedFunc callback, VipMode vipMode = VipMode::NONE, float duration = 0.0f)
		: m_Name(name), m_Price(price), m_VipMode(vipMode), m_Duration(duration), m_Callback(callback)
	{
	}

	bool CanBeUsedByClient(int client)
	{
		return mEnabled && static_cast<int>(m_VipMode) <= static_cast<int>(VIPManager::GetClientVipMode(client));
	}

	void CallCallback(int client, void* param = nullptr) { m_Callback(client, this, param); }

	int GetPrice() const { return m_Price; }
	float GetDuration() const { return m_Duration; }
	VipMode GetVipMode() const { return m_VipMode; }

	void Disable() { mEnabled = false; }
	void Enable() { mEnabled = true; }
	bool IsEnabled() const { return mEnabled; }

	std::string GetName(int client) const
	{
		constexpr char vipStr[] = " [ VIP ]";
		constexpr char extraVipStr[] = " [ ExtraVIP ]";

		char translated[40];
		PM::Format(translated, sizeof(translated), "%T", m_Name.c_str(), client);

		std::string name(translated);
		name += " (";
		name += std::to_string(m_Price);
		name += ')';
		if (m_Duration != 0.0f)
		{
			std::stringstream ss;
			ss.precision(2);
			ss << m_Duration;
			name += " {";
			name += ss.str().c_str();
			name += '}';
		}
		if (m_VipMode != VipMode::NONE)
		{
			if (m_VipMode == VipMode::VIP)
				name += vipStr;
			else
				name += extraVipStr;
		}

		return name;
	}

	const std::string& GetRawName() const { return m_Name; }
private:
	std::string m_Name;
	int m_Price;
	VipMode m_VipMode;
	float m_Duration;
	ShopItemSelectedFunc m_Callback;
	bool mEnabled = true;
};
