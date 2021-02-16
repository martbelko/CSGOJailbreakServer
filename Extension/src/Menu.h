#pragma once

#include "PublicManager.h"

using MenuFilterFunc = bool(*)(int client);

class Menu
{
public:
	Menu() = default;
	Menu(MenuHandler handler, MenuAction actions = MENU_ACTIONS_DEFAULT, Menu* parent = nullptr)
		: m_Parent(parent)
	{
		m_Handle = PublicManager::CreateMenu(handler, actions);
	}

	void SetTitle(const char* title) const
	{
		PublicManager::SetMenuTitle(m_Handle, title);
	}

	std::string GetTitle() const
	{
		std::string title;
		title.reserve(32);
		PublicManager::GetMenuTitle(m_Handle, title.data(), title.capacity());
		return title;
	}

	bool AddItem(const char* displayStr, int style = 0) const
	{
		std::string infoStr = GetInfoStr();
		return PublicManager::AddMenuItem(m_Handle, infoStr.c_str(), displayStr, style);
	}

	bool InsertItem(int position, const char* displayStr, int style = 0) const
	{
		std::string infoStr = GetInfoStr();
		return PublicManager::InsertMenuItem(m_Handle, position, infoStr.c_str(), displayStr, style);
	}

	bool RemoveItem(int position) const
	{
		return PublicManager::RemoveMenuItem(m_Handle, position);
	}

	bool GetMenuItem(int position, char* infoBuf, int infoBufLen, int& style = NULL_VALUE, char* dispBuf = "", int dispBufLen = 0, int client = 0) const
	{
		return PublicManager::GetMenuItem(m_Handle, position, infoBuf, infoBufLen, style, dispBuf, dispBufLen, client);
	}

	bool DisplayToClient(int client, int time) const
	{
		if (PublicManager::IsClientInGame(client) && !PublicManager::IsFakeClient(client)
			&& !PublicManager::IsClientSourceTV(client))
			return PublicManager::DisplayMenu(m_Handle, client, time);
		return false;
	}

	void DisplayToAll(int time, MenuFilterFunc filter = [](int) { return true; }) const
	{
		for (int i = 1; i <= PublicManager::GetMaxClients(); ++i)
		{
			if (PublicManager::IsClientInGame(i) && !PublicManager::IsFakeClient(i) &&
				!PublicManager::IsClientSourceTV(i) && filter(i))
				PublicManager::DisplayMenu(m_Handle, i, time);
		}
	}

	Menu* GetParent() const { return m_Parent; }
	MenuHandle GetHandle() const { return m_Handle; }

	void Delete() const { PublicManager::CloseHandle(m_Handle); }
private:
	std::string GetInfoStr() const
	{
		return std::to_string(m_Counter);
	}
private:
	MenuHandle m_Handle = INVALID_HANDLE;
	Menu* m_Parent = nullptr;
	uint32_t m_Counter = 0;
};
