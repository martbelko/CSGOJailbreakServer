public:
	template<typename ... Args>
	static void ServerCommand(const char* format, Args ... args)
	{
		PushArg(s_ServerCommandFunc, format);
		ServerCommandSub(args...);
	}
private:
	static void ServerCommandSub()
	{
		ExecFunc(s_ServerCommandFunc);
	}

	template<typename T, typename ... Args>
	static void ServerCommandSub(T arg, Args ... args)
	{
		PushArgRef(s_ServerCommandFunc, arg);
		ServerCommandSub(args...);
	}
public:
	template<typename ... Args>
	static void ServerCommandEx(char* buffer, int maxlen, const char* format, Args ... args)
	{
		PushArg(s_ServerCommandExFunc, buffer, maxlen);
		PushArg(s_ServerCommandExFunc, maxlen);
		PushArg(s_ServerCommandExFunc, format);
		ServerCommandExSub(args...);
	}
private:
	static void ServerCommandExSub()
	{
		ExecFunc(s_ServerCommandExFunc);
	}

	template<typename T, typename ... Args>
	static void ServerCommandExSub(T arg, Args ... args)
	{
		PushArgRef(s_ServerCommandExFunc, arg);
		ServerCommandExSub(args...);
	}
public:
	template<typename ... Args>
	static void InsertServerCommand(const char* format, Args ... args)
	{
		PushArg(s_InsertServerCommandFunc, format);
		InsertServerCommandSub(args...);
	}
private:
	static void InsertServerCommandSub()
	{
		ExecFunc(s_InsertServerCommandFunc);
	}

	template<typename T, typename ... Args>
	static void InsertServerCommandSub(T arg, Args ... args)
	{
		PushArgRef(s_InsertServerCommandFunc, arg);
		InsertServerCommandSub(args...);
	}
public:
	static void ServerExecute()
	{
		ExecFunc(s_ServerExecuteFunc);
	}

	template<typename ... Args>
	static void ClientCommand(int client, const char* format, Args ... args)
	{
		PushArg(s_ClientCommandFunc, client);
		PushArg(s_ClientCommandFunc, format);
		ClientCommandSub(args...);
	}
private:
	static void ClientCommandSub()
	{
		ExecFunc(s_ClientCommandFunc);
	}

	template<typename T, typename ... Args>
	static void ClientCommandSub(T arg, Args ... args)
	{
		PushArgRef(s_ClientCommandFunc, arg);
		ClientCommandSub(args...);
	}
public:
	template<typename ... Args>
	static void FakeClientCommand(int client, const char* format, Args ... args)
	{
		PushArg(s_FakeClientCommandFunc, client);
		PushArg(s_FakeClientCommandFunc, format);
		FakeClientCommandSub(args...);
	}
private:
	static void FakeClientCommandSub()
	{
		ExecFunc(s_FakeClientCommandFunc);
	}

	template<typename T, typename ... Args>
	static void FakeClientCommandSub(T arg, Args ... args)
	{
		PushArgRef(s_FakeClientCommandFunc, arg);
		FakeClientCommandSub(args...);
	}
public:
	template<typename ... Args>
	static void FakeClientCommandEx(int client, const char* format, Args ... args)
	{
		PushArg(s_FakeClientCommandExFunc, client);
		PushArg(s_FakeClientCommandExFunc, format);
		FakeClientCommandExSub(args...);
	}
private:
	static void FakeClientCommandExSub()
	{
		ExecFunc(s_FakeClientCommandExFunc);
	}

	template<typename T, typename ... Args>
	static void FakeClientCommandExSub(T arg, Args ... args)
	{
		PushArgRef(s_FakeClientCommandExFunc, arg);
		FakeClientCommandSub(args...);
	}
public:
	static void FakeClientCommandKeyValues(int client, KeyValuesHandle kv)
	{
		ExecFunc(s_FakeClientCommandKeyValuesFunc, client, kv);
	}

	template<typename ... Args>
	static void PrintToServer(const char* format, Args ... args)
	{
		PushArg(s_PrintToServerFunc, format);
		PrintToServerSub(args...);
	}
private:
	static void PrintToServerSub()
	{
		ExecFunc(s_PrintToServerFunc);
	}

	template<typename T, typename ... Args>
	static void PrintToServerSub(T arg, Args ... args)
	{
		PushArgRef(s_PrintToServerFunc, arg);
		PrintToServerSub(args...);
	}
public:
	template<typename ... Args>
	static void PrintToConsole(int client, const char* format, Args ... args)
	{
		PushArg(s_PrintToConsoleFunc, client);
		PushArg(s_PrintToConsoleFunc, format);
		PrintToConsoleSub(args...);
	}
private:
	static void PrintToConsoleSub()
	{
		ExecFunc(s_PrintToConsoleFunc);
	}

	template<typename T, typename ... Args>
	static void PrintToConsoleSub(T arg, Args ... args)
	{
		PushArgRef(s_PrintToConsoleFunc, arg);
		PrintToConsoleSub(args...);
	}
public:
	template<typename ... Args>
	static void PrintToConsoleAll(const char* format, Args ... args)
	{
		char buffer[254];
		for (int i = 1; i <= s_MaxClients; i++)
		{
			if (IsClientInGame(i))
			{
				// SetGlobalTransTarget(i); TODO:
				PrintToConsole(i, "%s", buffer, args...);
			}
		}
	}

	template<typename ... Args>
	static void ReplyToCommand(int client, const char* format, Args ... args)
	{
		PushArg(s_ReplyToCommandFunc, client);
		PushArg(s_ReplyToCommandFunc, format);
		ReplyToCommandSub(args...);
	}
private:
	static void ReplyToCommandSub()
	{
		ExecFunc(s_ReplyToCommandFunc);
	}

	template<typename T, typename ... Args>
	static void ReplyToCommandSub(T arg, Args ... args)
	{
		PushArgRef(s_ReplyToCommandFunc, arg);
		ReplyToCommandSub(args...);
	}
public:
	static ReplySource GetCmdReplySource()
	{
		return static_cast<ReplySource>(ExecFunc(s_GetCmdReplySourceFunc));
	}

	static ReplySource SetCmdReplySource(ReplySource source)
	{
		return static_cast<ReplySource>(ExecFunc(s_SetCmdReplySourceFunc, source));
	}

	static bool IsChatTrigger()
	{
		return ExecFunc(s_IsChatTriggerFunc);
	}

	template<typename ... Args>
	static void ShowActivity2(int client, const char* tag, const char* format, Args ... args)
	{
		PushArg(s_ShowActivity2Func, client);
		PushArg(s_ShowActivity2Func, tag);
		PushArg(s_ShowActivity2Func, format);
		ShowActivity2Sub(args...);
	}
private:
	static void ShowActivity2Sub()
	{
		ExecFunc(s_ShowActivity2Func);
	}

	template<typename T, typename ... Args>
	static void ShowActivity2Sub(T arg, Args ... args)
	{
		PushArgRef(s_ShowActivity2Func, arg);
		ShowActivity2Sub(args...);
	}
public:
	template<typename ... Args>
	static void ShowActivity(int client, const char* format, Args ... args)
	{
		PushArg(s_ShowActivityFunc, client);
		PushArg(s_ShowActivityFunc, format);
		ShowActivitySub(args...);
	}
private:
	static void ShowActivitySub()
	{
		ExecFunc(s_ShowActivityFunc);
	}

	template<typename T, typename ... Args>
	static void ShowActivitySub(T arg, Args ... args)
	{
		PushArgRef(s_ShowActivityFunc, arg);
		ShowActivitySub(args...);
	}
public:
	template<typename ... Args>
	static void ShowActivityEx(int client, const char* tag, const char* format, Args ... args)
	{
		PushArg(s_ShowActivityExFunc, client);
		PushArg(s_ShowActivityExFunc, tag);
		PushArg(s_ShowActivityExFunc, format);
		ShowActivityExSub(args...);
	}
private:
	static void ShowActivityExSub()
	{
		ExecFunc(s_ShowActivityExFunc);
	}

	template<typename T, typename ... Args>
	static void ShowActivityExSub(T arg, Args ... args)
	{
		PushArgRef(s_ShowActivityExFunc, arg);
		ShowActivityExSub(args...);
	}
public:
	static bool FormatActivitySource(int client, int target, const char* namebuf, int maxlength)
	{
		return ExecFunc(s_FormatActivitySourceFunc, client, target, namebuf, maxlength);
	}

	static void RegServerCmd(const char* cmd, const char* description, int flags)
	{
		ExecFunc(s_RegServerCmdFunc, cmd, description, flags);
	}

	static void RegConsoleCmd(const char* command, const char* description, int flags)
	{
		ExecFunc(s_RegConsoleCmdFunc, command, description, flags);
	}

	static void RegAdminCmd(const char* cmd, int adminflags, const char* description, const char* group, int flags)
	{
		ExecFunc(s_RegAdminCmdFunc, cmd, adminflags, description, group, flags);
	}

	static int GetCmdArgs()
	{
		return ExecFunc(s_GetCmdArgsFunc);
	}

	static int GetCmdArg(int argnum, char* buffer, int maxlength)
	{
		return ExecFunc(s_GetCmdArgFunc, argnum, buffer, maxlength);
	}

	static int GetCmdArgInt(int argnum)
	{
		char str[12];
		GetCmdArg(argnum, str, sizeof(str));
		// TODO: Use StringToInt
		char* endPtr = nullptr;
		return std::strtol(str, &endPtr, 0);
	}

	static bool GetCmdArgIntEx(int argnum, int& value)
	{
		char str[12];
		GetCmdArg(argnum, str, sizeof(str));
		// TODO: Use StringToIntEx
		errno = 0;
		char* endPtr = nullptr;
		value = std::strtol(str, &endPtr, 0);
		if (errno == 0 && str && !*endPtr)
			return true;
		return false;
	}

	static int GetCmdArgString(char* buffer, int maxlength)
	{
		return ExecFunc(s_GetCmdArgStringFunc, buffer, maxlength);
	}

	static Handle GetCommandIterator()
	{
		return ExecFunc(s_GetCommandIteratorFunc);
	}

	static bool ReadCommandIterator(Handle iter, char* name, int nameLen, int& eflags, char* desc, int descLen)
	{
		PushArg(s_ReadCommandIteratorFunc, iter);
		PushArg(s_ReadCommandIteratorFunc, name, nameLen);
		PushArg(s_ReadCommandIteratorFunc, nameLen);
		PushArgRef(s_ReadCommandIteratorFunc, eflags);
		PushArg(s_ReadCommandIteratorFunc, desc, descLen);
		PushArg(s_ReadCommandIteratorFunc, descLen);
		return ExecFunc(s_ReadCommandIteratorFunc);
	}

	static bool CheckCommandAccess(int client, const char* command, int flags, bool overrideOnly)
	{
		return ExecFunc(s_CheckCommandAccessFunc, client, command, flags, overrideOnly);
	}

	static bool CheckAccess(AdminId id, const char* command, int flags, bool overrideOnly)
	{
		return ExecFunc(s_CheckAccessFunc, id, command, flags, overrideOnly);
	}

	static int GetCommandFlags(const char* name)
	{
		return ExecFunc(s_GetCommandFlagsFunc, name);
	}

	static bool SetCommandFlags(const char* name, int flags)
	{
		return ExecFunc(s_SetCommandFlagsFunc, name, flags);
	}

	static Handle FindFirstConCommand(char* buffer, int maxSize, bool& isCommand, int& flags, char* description, int descrmaxSize)
	{
		PushArg(s_FindFirstConCommandFunc, buffer, maxSize);
		PushArg(s_FindFirstConCommandFunc, maxSize);
		PushArgRef(s_FindFirstConCommandFunc, reinterpret_cast<int&>(isCommand));
		PushArgRef(s_FindFirstConCommandFunc, flags);
		PushArg(s_FindFirstConCommandFunc, description, descrmaxSize);
		PushArg(s_FindFirstConCommandFunc, descrmaxSize);
		return ExecFunc(s_FindFirstConCommandFunc);
	}

	static bool FindNextConCommand(Handle search, char* buffer, int maxSize, bool& isCommand, int& flags, char* description, int descrmaxSize)
	{
		PushArg(s_FindFirstConCommandFunc, search);
		PushArg(s_FindFirstConCommandFunc, buffer, maxSize);
		PushArg(s_FindFirstConCommandFunc, maxSize);
		PushArgRef(s_FindFirstConCommandFunc, reinterpret_cast<int&>(isCommand));
		PushArgRef(s_FindFirstConCommandFunc, flags);
		PushArg(s_FindFirstConCommandFunc, description, descrmaxSize);
		PushArg(s_FindFirstConCommandFunc, descrmaxSize);
		return ExecFunc(s_FindNextConCommandFunc);
	}

	static void AddServerTag(const char* tag)
	{
		ExecFunc(s_AddServerTagFunc, tag);
	}

	static void RemoveServerTag(const char* tag)
	{
		ExecFunc(s_RemoveServerTagFunc, tag);
	}

	static bool AddCommandListener(const char* command)
	{
		return ExecFunc(s_AddCommandListenerFunc, command);
	}

	static void RemoveCommandListener(const char* command)
	{
		ExecFunc(s_RemoveCommandListenerFunc, command);
	}

	static bool CommandExists(const char* command)
	{
		return GetCommandFlags(command) != INVALID_FCVAR_FLAGS;
	}
