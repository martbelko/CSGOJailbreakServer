#pragma once

#include "PublicManager.h"

using MenuFilterFunc = bool(*)(int client);

class Menu
{
public:
	using NewMenuHandler = int(*)(Menu* menu, MenuAction action, int param1, int param2);
public:
	Menu() = default;
	Menu(NewMenuHandler handler, MenuAction actions = MENU_ACTIONS_DEFAULT)
		: mHandler(handler)
	{
		m_Handle = PM::CreateMenu(MenuHandlerStatic, actions);
		sMenus[m_Handle] = this;
	}

	Menu(const Menu&) = delete;
	Menu(Menu&& other) noexcept
		:
		m_Handle(std::move(other.m_Handle)),
		m_Counter(std::move(other.m_Counter)),
		mHandler(std::move(other.mHandler))
	{
		sMenus[m_Handle] = this;
		other.m_Handle = INVALID_HANDLE;
	}

	Menu& operator=(const Menu&) = delete;
	Menu& operator=(Menu&& other) noexcept
	{
		if (this != &other)
		{
			Destroy();

			m_Handle = std::move(other.m_Handle);
			m_Counter = std::move(other.m_Counter);
			mHandler = std::move(other.mHandler);
			sMenus[m_Handle] = this;

			other.m_Handle = INVALID_HANDLE;
		}

		return *this;
	}

	~Menu()
	{
		Destroy();
	}

	void SetParam(void* param) { mParam = param; }
	void* GetParam() const { return mParam; }

	template<typename ... Args>
	void SetTitle(const char* format, Args ... args) const
	{
		PM::SetMenuTitle(m_Handle, format, args...);
	}

	std::string GetTitle() const
	{
		char title[32];
		PM::GetMenuTitle(m_Handle, title, sizeof(title));
		return title;
	}

	bool GetItem(int position, char* infoBuf, int infoBufLen, int& style = NULL_VALUE, char* dispBuf = const_cast<char*>(""), int dispBufLen = 0) const
	{
		return PM::GetMenuItem(m_Handle, position, infoBuf, infoBufLen, style, dispBuf, dispBufLen);
	}

	bool AddItem(const char* displayStr, int style = 0)
	{
		std::string infoStr = GetInfoStr();
		bool result = PM::AddMenuItem(m_Handle, infoStr.c_str(), displayStr, style);
		if (result)
			++m_Counter;
		return result;
	}

	bool AddItem(const char* infoStr, const char* displayStr, int style = 0) const
	{
		return PM::AddMenuItem(m_Handle, infoStr, displayStr, style);
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

	bool DisplayToClient(int client, int time = 20) const
	{
		if (PM::IsClientInGame(client) && !PM::IsFakeClient(client) && !PM::IsClientSourceTV(client))
			return PM::DisplayMenu(m_Handle, client, time);
		return false;
	}

	void DisplayToAll(int time = 20, MenuFilterFunc filter = [](int) { return true; }) const
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

	void Move(Menu&& other)
	{
		m_Handle = other.m_Handle;
		m_Counter = other.m_Counter;
		mHandler = other.mHandler;
		sMenus[m_Handle] = this;

		other.m_Handle = INVALID_HANDLE;
	}

	void Destroy()
	{
		if (m_Handle != INVALID_HANDLE)
		{
			PM::CloseHandle(m_Handle);
			m_Handle = INVALID_HANDLE;
		}
	}
private:
	static int MenuHandlerStatic(MenuHandle handle, MenuAction action, int param1, int param2)
	{
		Menu* menu = sMenus[handle];
		return menu->mHandler(menu, action, param1, param2);
	}
private:
	MenuHandle m_Handle = INVALID_HANDLE;
	uint32_t m_Counter = 0;
	NewMenuHandler mHandler = nullptr;
	void* mParam;

	static std::unordered_map<MenuHandle, Menu*> sMenus;
};
