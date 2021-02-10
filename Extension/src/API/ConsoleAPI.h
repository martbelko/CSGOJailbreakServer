public:
	/**
	 * @brief Executes a server command as if it were on the server console (or RCON)
	 *
	 * @param format        Formatting rules.
	 * @param args          Variable number of format parameters.
	 */
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
	/**
	 * @brief Executes a server command as if it were on the server console (or RCON)
	 * and stores the printed text into buffer.
	 *
	 * Warning: This calls ServerExecute internally and may have issues if
	 * certain commands are in the buffer, only use when you really need
	 * the response.
	 * Also, on L4D2 this will not print the command output to the server console.
	 *
	 * @param buffer        String to store command result into.
	 * @param maxlen        Length of buffer.
	 * @param format        Formatting rules.
	 * @param args          Variable number of format parameters.
	 */
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
	/**
	 * @brief Inserts a server command at the beginning of the server command buffer.
	 *
	 * @param format        Formatting rules.
	 * @param args          Variable number of format parameters.
	 */
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
	/**
	 * @brief Executes every command in the server's command buffer, rather than once per frame.
	 */
	static void ServerExecute()
	{
		ExecFunc(s_ServerExecuteFunc);
	}

	/**
	 * @brief Executes a client command.  Note that this will not work on clients unless
	 * they have cl_restrict_server_commands set to 0.
	 *
	 * @param client        Index of the client.
	 * @param format        Format of the client command.
	 * @param args          Format parameters
	 * @error               Invalid client index, or client not connected.
	 */
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
	/**
	 * @brief Executes a client command on the server without being networked.
	 *
	 * FakeClientCommand() overwrites the command tokenization buffer.  This can
	 * cause undesired effects because future calls to GetCmdArg* will return
	 * data from the FakeClientCommand(), not the parent command.  If you are in
	 * a hook where this matters (for example, a "say" hook), you should use
	 * FakeClientCommandEx() instead.
	 *
	 * @param client        Index of the client.
	 * @param fmt           Format of the client command.
	 * @param args          Format parameters
	 * @error               Invalid client index, or client not connected.
	 */
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
	/**
	 * @brief Executes a client command on the server without being networked.  The
	 * execution of the client command is delayed by one frame to prevent any
	 * re-entrancy issues that might surface with FakeClientCommand().
	 *
	 * @param client        Index of the client.
	 * @param format        Format of the client command.
	 * @param args          Format parameters
	 * @error               Invalid client index, or client not connected.
	 */
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
	/**
	 * @brief Executes a KeyValues client command on the server without being networked.
	 *
	 * @param client        Index of the client.
	 * @param kv            KeyValues data to be sent.
	 * @error               Invalid client index, client not connected,
	 *                      or unsupported on current game.
	 */
	static void FakeClientCommandKeyValues(int client, KeyValuesHandle kv)
	{
		ExecFunc(s_FakeClientCommandKeyValuesFunc, client, kv);
	}

	/**
	 * @brief Sends a message to the server console.
	 *
	 * @param format        Formatting rules.
	 * @param args          Variable number of format parameters.
	 */
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
	/**
	 * @brief Sends a message to a client's console.
	 *
	 * @param client        Client index.
	 * @param format        Formatting rules.
	 * @param args          Variable number of format parameters.
	 * @error               If the client is not connected an error will be thrown.
	 */
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
	/**
	 * @brief Sends a message to every client's console.
	 *
	 * @param format        Formatting rules.
	 * @param args          Variable number of format parameters.
	 */
	template<typename ... Args>
	static void PrintToConsoleAll(const char* format, Args ... args)
	{
		for (int i = 1; i <= s_MaxClients; i++)
		{
			if (IsClientInGame(i))
			{
				SetGlobalTransTarget(i);
				PrintToConsole(i, format, args...);
			}
		}
	}

	/**
	 * @brief Replies to a message in a command.
	 *
	 * A client index of 0 will use PrintToServer().
	 * If the command was from the console, PrintToConsole() is used.
	 * If the command was from chat, PrintToChat() is used.
	 *
	 * @param client        Client index, or 0 for server.
	 * @param format        Formatting rules.
	 * @param args          Variable number of format parameters.
	 * @error               If the client is not connected or invalid.
	 */
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
	/**
	 * @brief Returns the current reply source of a command.
	 *
	 * @return              ReplySource value.
	 */
	static ReplySource GetCmdReplySource()
	{
		return static_cast<ReplySource>(ExecFunc(s_GetCmdReplySourceFunc));
	}

	/**
	 * @brief Sets the current reply source of a command.
	 *
	 * Only use this if you know what you are doing.  You should save the old value
	 * and restore it once you are done.
	 *
	 * @param source        New ReplySource value.
	 * @return              Old ReplySource value.
	 */
	static ReplySource SetCmdReplySource(ReplySource source)
	{
		return static_cast<ReplySource>(ExecFunc(s_SetCmdReplySourceFunc, source));
	}

	/**
	 * @brief Returns whether the current say hook is a chat trigger.
	 *
	 * This function is only meaningful inside say or say_team hooks.
	 *
	 * @return              True if a chat trigger, false otherwise.
	 */
	static bool IsChatTrigger()
	{
		return ExecFunc(s_IsChatTriggerFunc);
	}

	/**
	 * @brief Displays usage of an admin command to users depending on the
	 * setting of the sm_show_activity cvar.  All users receive a message
	 * in their chat text, except for the originating client, who receives
	 * the message based on the current ReplySource.
	 *
	 * @param client        Client index doing the action, or 0 for server.
	 * @param tag           Tag to prepend to the message.
	 * @param format        Formatting rules.
	 * @param ...           Variable number of format parameters.
	 * @error
	 */
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
	/**
	 * @brief Displays usage of an admin command to users depending on the
	 * setting of the sm_show_activity cvar.
	 *
	 * This version does not display a message to the originating client
	 * if used from chat triggers or menus.  If manual replies are used
	 * for these cases, then this function will suffice.  Otherwise,
	 * ShowActivity2() is slightly more useful.
	 *
	 * @param client        Client index doing the action, or 0 for server.
	 * @param format        Formatting rules.
	 * @param ...           Variable number of format parameters.
	 * @error
	 */
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
	/**
	 * @brief Same as ShowActivity(), except the tag parameter is used instead of
	 * "[SM] " (note that you must supply any spacing).
	 *
	 * @param client        Client index doing the action, or 0 for server.
	 * @param tag           Tag to display with.
	 * @param format        Formatting rules.
	 * @param ...           Variable number of format parameters.
	 * @error
	 */
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
	/**
	 * @brief Given an originating client and a target client, returns the string
	 * that describes the originating client according to the sm_show_activity cvar.
	 *
	 * For example, "ADMIN", "PLAYER", or a player's name could be placed in this buffer.
	 *
	 * @param client        Originating client; may be 0 for server console.
	 * @param target        Targeted client.
	 * @param namebuf       Name buffer.
	 * @param maxlength     Maximum size of the name buffer.
	 * @return              True if activity should be shown.  False otherwise.  In either
	 *                      case, the name buffer is filled.  The return value can be used
	 *                      to broadcast a "safe" name to all players regardless of the
	 *                      sm_show_activity filters.
	 * @error               Invalid client index or client not connected.
	 */
	static bool FormatActivitySource(int client, int target, const char* namebuf, int maxlength)
	{
		return ExecFunc(s_FormatActivitySourceFunc, client, target, namebuf, maxlength);
	}

	/**
	 * @brief Creates a server-only console command, or hooks an already existing one.
	 *
	 * Server commands are case sensitive.
	 *
	 * @param command       Name of the command to hook or create.
	 * @param callback      A function to use as a callback for when the command is invoked.
	 * @param description   Optional description to use for command creation.
	 * @param flags         Optional flags to use for command creation.
	 * @error               Command name is the same as an existing convar.
	 */
	static void RegServerCmd(const char* command, SrvCmdFunc callback, const char* description = "", int flags = 0)
	{
		std::string commandStr(command);
		s_SrvCmdCallbacks[commandStr] = callback;
		ExecFunc(s_RegServerCmdFunc, command, description, flags);
	}

	/**
	 * @brief Creates a console command, or hooks an already existing one.
	 *
	 * Console commands are case sensitive.  However, if the command already exists in the game,
	 * a client may enter the command in any case.  SourceMod corrects for this automatically,
	 * and you should only hook the "real" version of the command.
	 *
	 * @param cmd           Name of the command to hook or create.
	 * @param callback      A function to use as a callback for when the command is invoked.
	 * @param description   Optional description to use for command creation.
	 * @param flags         Optional flags to use for command creation.
	 * @error               Command name is the same as an existing convar.
	 */
	static void RegConsoleCmd(const char* command, ConCmdFunc callback, const char* description = "", int flags = 0)
	{
		std::string commandStr(command);
		s_ConCmdCallbacks[commandStr] = callback;
		ExecFunc(s_RegConsoleCmdFunc, command, description, flags);
	}

	/**
	 * @brief Creates a console command as an administrative command.  If the command does not exist,
	 * it is created.  When this command is invoked, the access rights of the player are
	 * automatically checked before allowing it to continue.
	 *
	 * Admin commands are case sensitive from both the client and server.
	 *
	 * @param cmd           String containing command to register.
	 * @param callback      A function to use as a callback for when the command is invoked.
	 * @param adminflags    Administrative flags (bitstring) to use for permissions.
	 * @param description   Optional description to use for help.
	 * @param group         String containing the command group to use.  If empty,
	 *                      the plugin's filename will be used instead.
	 * @param flags         Optional console flags.
	 * @error               Command name is the same as an existing convar.
	 */
	static void RegAdminCmd(const char* command, ConCmdFunc callback, int adminflags, const char* description = "", const char* group = "", int flags = 0)
	{
		std::string commandStr(command);
		s_ConCmdCallbacks[commandStr] = callback;
		ExecFunc(s_RegAdminCmdFunc, command, adminflags, description, group, flags);
	}

	/**
	 * @brief Returns the number of arguments from the current console or server command.
	 * @note Unlike the HL2 engine call, this does not include the command itself.
	 *
	 * @return              Number of arguments to the current command.
	 */
	static int GetCmdArgs()
	{
		return ExecFunc(s_GetCmdArgsFunc);
	}

	/**
	 * @brief Retrieves a command argument given its index, from the current console or
	 * server command.
	 * @note Argument indexes start at 1; 0 retrieves the command name.
	 *
	 * @param argnum        Argument number to retrieve.
	 * @param buffer        Buffer to use for storing the string.
	 * @param maxlength     Maximum length of the buffer.
	 * @return              Length of string written to buffer.
	 */
	static int GetCmdArg(int argnum, char* buffer, int maxlength)
	{
		PushArg(s_GetCmdArgFunc, argnum);
		PushArg(s_GetCmdArgFunc, buffer, maxlength);
		PushArg(s_GetCmdArgFunc, maxlength);
		return ExecFunc(s_GetCmdArgFunc);
	}

	/**
	 * @brief Retrieves a numeric command argument given its index, from the current
	 * console or server command. Will return 0 if the argument can not be
	 * parsed as a number. Use GetCmdArgIntEx to handle that explicitly.
	 *
	 * @param argnum Argument number to retrieve.
	 * @return       Value of the command argument.
	 */
	static int GetCmdArgInt(int argnum)
	{
		char str[12];
		GetCmdArg(argnum, str, sizeof(str));
		return StringToInt(str);
	}

	/**
	 * @brief Retrieves a numeric command argument given its index, from the current
	 * console or server command. Returns false if the argument can not be
	 * completely parsed as an integer.
	 *
	 * @param argnum Argument number to retrieve.
	 * @param value  Populated with the value of the command argument.
	 * @return       Whether the argument was entirely a numeric value.
	 */
	static bool GetCmdArgIntEx(int argnum, int& value)
	{
		char str[12];
		int len = GetCmdArg(argnum, str, sizeof(str));
		return StringToIntEx(str, value) == len && len > 0;
	}

	/**
	 * @brief Retrieves the entire command argument string in one lump from the current
	 * console or server command.
	 *
	 * @param buffer        Buffer to use for storing the string.
	 * @param maxlength     Maximum length of the buffer.
	 * @return              Length of string written to buffer.
	 */
	static int GetCmdArgString(char* buffer, int maxlength)
	{
		return ExecFunc(s_GetCmdArgStringFunc, buffer, maxlength);
	}

	/**
	 * @brief Gets a command iterator.  Must be freed with CloseHandle().
	 *
	 * @return              A new command iterator.
	 */
	static Handle GetCommandIterator()
	{
		return ExecFunc(s_GetCommandIteratorFunc);
	}

	/**
	 * @brief Reads a command iterator, then advances to the next command if any.
	 * Only SourceMod specific commands are returned.
	 *
	 * @param iter          Command iterator Handle.
	 * @param name          Name buffer.
	 * @param nameLen       Name buffer size.
	 * @param eflags        Effective default flags of a command.
	 * @param desc          Command description buffer.
	 * @param descLen       Command description buffer size.
	 * @return              True on success, false if there are no more commands.
	 */
	static bool ReadCommandIterator(Handle iter, char* name, int nameLen, int& eflags = NULL_VALUE, char* desc = "", int descLen = 0)
	{
		PushArg(s_ReadCommandIteratorFunc, iter);
		PushArg(s_ReadCommandIteratorFunc, name, nameLen);
		PushArg(s_ReadCommandIteratorFunc, nameLen);
		PushArgRef(s_ReadCommandIteratorFunc, eflags);
		PushArg(s_ReadCommandIteratorFunc, desc, descLen);
		PushArg(s_ReadCommandIteratorFunc, descLen);
		return ExecFunc(s_ReadCommandIteratorFunc);
	}

	/**
	 * @brief Returns whether a client has access to a given command string.  The string
	 * can be any override string, as overrides can be independent of
	 * commands.  This feature essentially allows you to create custom
	 * flags using the override system.
	 *
	 * @param client        Client index.
	 * @param command       Command name.  If the command is not found, the default
	 *                      flags are used.
	 * @param flags         Flag string to use as a default, if the command or override
	 *                      is not found.
	 * @param overrideOnly  If true, SourceMod will not attempt to find a matching
	 *                      command, and it will only use the default flags specified.
	 *                      Otherwise, SourceMod will ignore the default flags if
	 *                      there is a matching admin command.
	 * @return              True if the client has access, false otherwise.
	 */
	static bool CheckCommandAccess(int client, const char* command, int flags, bool overrideOnly = false)
	{
		return ExecFunc(s_CheckCommandAccessFunc, client, command, flags, overrideOnly);
	}

	/**
	 * @brief Returns whether an admin has access to a given command string.  The string
	 * can be any override string, as overrides can be independent of
	 * commands.  This feature essentially allows you to create custom flags
	 * using the override system.
	 *
	 * @param id            AdminId of the admin.
	 * @param command       Command name.  If the command is not found, the default
	 *                      flags are used.
	 * @param flags         Flag string to use as a default, if the command or override
	 *                      is not found.
	 * @param overrideOnly  If true, SourceMod will not attempt to find a matching
	 *                      command, and it will only use the default flags specified.
	 *                      Otherwise, SourceMod will ignore the default flags if
	 *                      there is a matching admin command.
	 * @return              True if the admin has access, false otherwise.
	 */
	static bool CheckAccess(AdminId id, const char* command, int flags, bool overrideOnly = false)
	{
		return ExecFunc(s_CheckAccessFunc, id, command, flags, overrideOnly);
	}

	/**
	 * @brief Returns the bitstring of flags of a command.
	 *
	 * @param name          Name of the command.
	 * @return              A bitstring containing the FCVAR_* flags that are enabled
	 *                      or INVALID_FCVAR_FLAGS if command not found.
	 */
	static int GetCommandFlags(const char* name)
	{
		return ExecFunc(s_GetCommandFlagsFunc, name);
	}

	/**
	 * @brief Sets the bitstring of flags of a command.
	 *
	 * @param name          Name of the command.
	 * @param flags         A bitstring containing the FCVAR_* flags to enable.
	 * @return              True on success, otherwise false.
	 */
	static bool SetCommandFlags(const char* name, int flags)
	{
		return ExecFunc(s_SetCommandFlagsFunc, name, flags);
	}

	/**
	 * @brief Starts a ConCommandBase search, traversing the list of ConVars and
	 * ConCommands.  If a Handle is returned, the next entry must be read
	 * via FindNextConCommand().  The order of the list is undefined.
	 *
	 * @param buffer        Buffer to store entry name.
	 * @param max_size      Maximum size of the buffer.
	 * @param isCommand     Variable to store whether the entry is a command.
	 *                      If it is not a command, it is a ConVar.
	 * @param flags         Variable to store entry flags.
	 * @param description   Buffer to store the description, empty if no description present.
	 * @param descrmaxSize  Maximum size of the description buffer.
	 * @return              On success, a ConCmdIter Handle is returned, which
							can be read via FindNextConCommand(), and must be
							closed via CloseHandle().  Additionally, the output
							parameters will be filled with information of the
							first ConCommandBase entry.
							On failure, INVALID_HANDLE is returned, and the
							contents of outputs is undefined.
	 */
	static Handle FindFirstConCommand(char* buffer, int maxSize, bool& isCommand, int& flags = NULL_VALUE, char* description = "", int descrmaxSize = 0)
	{
		PushArg(s_FindFirstConCommandFunc, buffer, maxSize);
		PushArg(s_FindFirstConCommandFunc, maxSize);
		PushArgRef(s_FindFirstConCommandFunc, reinterpret_cast<int&>(isCommand));
		PushArgRef(s_FindFirstConCommandFunc, flags);
		PushArg(s_FindFirstConCommandFunc, description, descrmaxSize);
		PushArg(s_FindFirstConCommandFunc, descrmaxSize);
		return ExecFunc(s_FindFirstConCommandFunc);
	}

	/**
	 * @brief Reads the next entry in a ConCommandBase iterator.
	 *
	 * @param search        ConCmdIter Handle to search.
	 * @param buffer        Buffer to store entry name.
	 * @param max_size      Maximum size of the buffer.
	 * @param isCommand     Variable to store whether the entry is a command.
							If it is not a command, it is a ConVar.
	 * @param flags         Variable to store entry flags.
	 * @param description   Buffer to store the description, empty if no description present.
	 * @param descrmaxSize  Maximum size of the description buffer.
	 * @return              On success, the outputs are filled, the iterator is
							advanced to the next entry, and true is returned.
							If no more entries exist, false is returned, and the
							contents of outputs is undefined.
	 */
	static bool FindNextConCommand(Handle search, char* buffer, int maxSize, bool& isCommand, int& flags = NULL_VALUE, char* description = "", int descrmaxSize = 0)
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

	/**
	 * @brief Adds an informational string to the server's public "tags".
	 * This string should be a short, unique identifier.
	 *
	 * Note: Tags are automatically removed when a plugin unloads.
	 * Note: Currently, this function does nothing because of bugs in the Valve master.
	 *
	 * @param tag           Tag string to append.
	 */
	static void AddServerTag(const char* tag)
	{
		ExecFunc(s_AddServerTagFunc, tag);
	}

	/**
	 * @brief Removes a tag previously added by the calling plugin.
	 *
	 * @param tag           Tag string to remove.
	 */
	static void RemoveServerTag(const char* tag)
	{
		ExecFunc(s_RemoveServerTagFunc, tag);
	}

	/**
	 * @brief Adds a callback that will fire when a command is sent to the server.
	 *
	 * Registering commands is designed to create a new command as part of the UI,
	 * whereas this is a lightweight hook on a command string, existing or not.
	 * Using Reg*Cmd to intercept is in poor practice, as it physically creates a
	 * new command and can slow down dispatch in general.
	 *
	 * To see if this feature is available, use FeatureType_Capability and
	 * FEATURECAP_COMMANDLISTENER.
	 *
	 * @param callback      Callback.
	 * @param command       Command, or if not specified, a global listener.
	 *                      The command is case insensitive.
	 * @return              True if this feature is available on the current game,
	 *                      false otherwise.
	 */
	static bool AddCommandListener(CommandListenerFunc callback, const char* command = "")
	{
		std::string commnadStr(command);
		s_CommandListenerCallbacks[commnadStr] = callback;
		return ExecFunc(s_AddCommandListenerFunc, command);
	}

	/**
	 * @brief Removes a previously added command listener, in reverse order of being added.
	 *
	 * @param callback      Callback.
	 * @param command       Command, or if not specified, a global listener.
	 *                      The command is case insensitive.
	 * @error               Callback has no active listeners.
	 */
	static void RemoveCommandListener(const char* command = "")
	{
		ExecFunc(s_RemoveCommandListenerFunc, command);
	}

	/**
	 * @brief Returns true if the supplied command exists.
	 *
	 * @param command       Command to find.
	 * @return              True if command is found, false otherwise.
	 */
	static bool CommandExists(const char* command)
	{
		return GetCommandFlags(command) != INVALID_FCVAR_FLAGS;
	}
