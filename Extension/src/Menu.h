#pragma once

#include "PublicManager.h"

using MenuFilterFunc = bool(*)(int client);

class Menu
{
public:
	using NewMenuHandler = int(*)(Menu menu, MenuAction action, int param1, int param2);
public:
	Menu() = default;
	Menu(MenuHandler handler, MenuAction actions = MENU_ACTIONS_DEFAULT)
	{
		if (m_Handle != INVALID_HANDLE)
			PM::CloseHandle(m_Handle);
		m_Handle = PM::CreateMenu(handler, actions);
	}

	Menu(const Menu& other)
	{
		m_Handle = other.m_Handle;
		m_Counter = other.m_Counter;
	}

	Menu& operator=(const Menu& other)
	{
		Delete();
		m_Handle = other.m_Handle;
		m_Counter = other.m_Counter;
		return *this;
	}

	void Delete()
	{
		if (m_Handle != INVALID_HANDLE)
		{
			PM::CloseHandle(m_Handle);
			m_Handle = INVALID_HANDLE;
		}
	}

	template<typename ... Args>
	void SetTitle(const char* format, Args ... args) const
	{
		PM::SetMenuTitle(m_Handle, title, args...);
	}

	std::string GetTitle() const
	{
		std::string title;
		title.reserve(32);
		PM::GetMenuTitle(m_Handle, title.data(), title.capacity());
		return title;
	}

	bool AddItem(const char* displayStr, int style = 0) const
	{
		std::string infoStr = GetInfoStr();
		return PM::AddMenuItem(m_Handle, infoStr.c_str(), displayStr, style);
	}

	bool InsertItem(int position, const char* displayStr, int style = 0) const
	{
		std::string infoStr = GetInfoStr();
		return PM::InsertMenuItem(m_Handle, position, infoStr.c_str(), displayStr, style);
	}

	bool RemoveItem(int position) const
	{
		return PM::RemoveMenuItem(m_Handle, position);
	}

	void RemoveAllItems() const
	{
		PM::RemoveAllMenuItems(m_Handle);
	}

	bool GetMenuItem(int position, char* infoBuf, int infoBufLen, int& style = NULL_VALUE, char* dispBuf = "", int dispBufLen = 0, int client = 0) const
	{
		return PM::GetMenuItem(m_Handle, position, infoBuf, infoBufLen, style, dispBuf, dispBufLen, client);
	}

	bool DisplayToClient(int client, int time) const
	{
		if (PM::IsClientInGame(client) && !PM::IsFakeClient(client) && !PM::IsClientSourceTV(client))
			return PM::DisplayMenu(m_Handle, client, time);
		return false;
	}

	void DisplayToAll(int time, MenuFilterFunc filter = [](int) { return true; }) const
	{
		for (int i = 1; i <= PM::GetMaxClients(); ++i)
		{
			if (PM::IsClientInGame(i) && !PM::IsFakeClient(i) && !PM::IsClientSourceTV(i) && filter(i))
				PM::DisplayMenu(m_Handle, i, time);
		}
	}

	MenuHandle GetHandle() const { return m_Handle; }
private:
	std::string GetInfoStr() const
	{
		return std::to_string(m_Counter);
	}

	static int MenuHandlerStatic(MenuHandle handle, MenuAction action, int param1, int param2)
	{
		return Plugin_Continue;
	}
private:
	MenuHandle m_Handle = INVALID_HANDLE;
	uint32_t m_Counter = 0;

	static std::unordered_map<MenuHandle, Menu*> sMenuHandlers;
};
