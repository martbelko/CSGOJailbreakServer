#pragma once

#include "PublicManager.h"
#include "Menu.h"

#include "Plugin/VIP.h"
#include "Plugin/Shop/ShopItem.h"

#include <array>
#include <vector>
#include <string>
#include <unordered_map>

class Shop
{
public:
	Shop() = default;
	Shop(const char* title, std::vector<ShopItem>& shopItems)
	{
		m_Items = std::move(shopItems);
		for (Menu& menu : m_Menus)
		{
			menu = Menu(ShopMenuHandler, MENU_ACTIONS_ALL);
			s_ShopHashmap[menu.GetHandle()] = this;
		}
	}

	Shop& operator=(Shop& shop)
	{
		m_Items = std::move(shop.m_Items);
		m_Menus = std::move(shop.m_Menus);
		for (Menu& menu : m_Menus)
			s_ShopHashmap[menu.GetHandle()] = this;

		return *this;
	}

	void RefreshMenusForClient(const char* title, int client)
	{
		Menu& menu = m_Menus[client - 1];
		menu.SetTitle(title);
		menu.RemoveAllItems();
		for (const ShopItem& item : m_Items)
			menu.AddItem(item.GetName(client).c_str());
	}

	void Delete() const
	{
		for (const Menu& menu : m_Menus)
			menu.Delete();
	}

	bool DisplayToClient(int client, int time) const { return m_Menus[client - 1].DisplayToClient(client, time); }

	void DisplayToAll(int time, MenuFilterFunc func = [](int) { return true; }) const
	{
		for (int i = 1; i <= PublicManager::GetMaxClients(); ++i)
		{
			if (PublicManager::IsClientInGame(i) && !PublicManager::IsFakeClient(i)
				&& !PublicManager::IsClientSourceTV(i) && func(i))
				m_Menus[i - 1].DisplayToClient(i, time);
		}
	}

	bool IsEnabled() const { return m_Enabled; }
	void SetEnable(bool enable) { m_Enabled = enable; }
public:
	static int GetPlayerPoints(int client) { return s_PlayerPoints[client - 1]; }
	static void SetPlayerPoints(int client, int value) { s_PlayerPoints[client - 1] = value; }
private:
	static int ShopMenuHandler(MenuHandle menuHandle, MenuAction action, int param1, int param2)
	{
		if (action == MenuAction::MenuAction_Select)
		{
			int client = param1;
			int itemIndex = param2;
			Shop* shop = s_ShopHashmap[menuHandle];
			if (!shop->m_Enabled)
			{
				PublicManager::PrintCenterText(client, "[URNA SHOP] Sorry, shop is disabled!");
			}
			else
			{
				ShopItem& item = shop->m_Items[itemIndex];
				item.CallCallback(client);
			}
		}
		else if (action == MenuAction::MenuAction_DrawItem)
		{
			int client = param1;
			int itemIndex = param2;
			Shop* shop = s_ShopHashmap[menuHandle];
			ShopItem& item = shop->m_Items[itemIndex];
			return item.CanBeUsedByClient(client) ? ITEMDRAW_DEFAULT : ITEMDRAW_DISABLED;
		}

		return 0;
	}
private:
	static std::unordered_map<MenuHandle, Shop*> s_ShopHashmap;
	static std::array<int, MAXPLAYERS> s_PlayerPoints;
private:
	std::vector<ShopItem> m_Items;
	std::array<Menu, MAXPLAYERS> m_Menus;
	bool m_Enabled = true;
};
