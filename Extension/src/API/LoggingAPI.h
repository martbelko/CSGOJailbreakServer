public:
	/**
	 * @brief Logs a plugin message to the SourceMod logs.  The log message will be
	 * prefixed by the plugin's logtag (filename).
	 *
	 * @param format        String format.
	 * @param args          Format arguments.
	 */
	template<typename ... Args>
	static void LogMessage(const char* format, Args ... args)
	{
		PushArg(s_LogMessageFunc, format);
		LogMessageSub(args...);
	}
private:
	static void LogMessageSub()
	{
		ExecFunc(s_LogMessageFunc);
	}

	template<typename T, typename ... Args>
	static void LogMessageSub(T arg, Args ... args)
	{
		PushArgRef(s_LogMessageFunc, arg);
		LogMessageSub(args...);
	}
public:
	/**
	 * @brief Logs a message to any file.  The log message will be in the normal
	 * SourceMod format, with the plugin logtag prepended.
	 *
	 * @param file          File to write the log message in.
	 * @param format        String format.
	 * @param args          Format arguments.
	 * @error               File could not be opened/written.
	 */
	template<typename ... Args>
	static void LogToFile(const char* file, const char* format, Args ... args)
	{
		PushArg(s_LogToFileFunc, file);
		PushArg(s_LogToFileFunc, format);
		LogToFileSub(args...);
	}
private:
	static void LogToFileSub()
	{
		ExecFunc(s_LogToFileFunc);
	}

	template<typename T, typename ... Args>
	static void LogToFileSub(T arg, Args ... args)
	{
		PushArgRef(s_LogToFileFunc, arg);
		LogToFileSub(args...);
	}
public:
	/**
	 * @brief Same as LogToFile(), except no plugin logtag is prepended.
	 *
	 * @param file          File to write the log message in.
	 * @param format        String format.
	 * @param args          Format arguments.
	 * @error               File could not be opened/written.
	 */
	template<typename ... Args>
	static void LogToFileEx(const char* file, const char* format, Args ... args)
	{
		PushArg(s_LogToFileExFunc, file);
		PushArg(s_LogToFileExFunc, format);
		LogToFileExSub(args...);
	}
private:
	static void LogToFileExSub()
	{
		ExecFunc(s_LogToFileExFunc);
	}

	template<typename T, typename ... Args>
	static void LogToFileExSub(T arg, Args ... args)
	{
		PushArgRef(s_LogToFileExFunc, arg);
		LogToFileExSub(args...);
	}
public:
	/**
	 * @brief Logs an action from a command or event whereby interception and routing may
	 * be important.  This is intended to be a logging version of ShowActivity().
	 *
	 * @param client        Client performing the action, 0 for server, or -1 if not
	 *                      applicable.
	 * @param target        Client being targetted, or -1 if not applicable.
	 * @param message       Message format.
	 * @param args          Message formatting parameters.
	 */
	template<typename ... Args>
	static void LogAction(int client, int target, const char* message, Args ... args)
	{
		PushArg(s_LogActionFunc, client);
		PushArg(s_LogActionFunc, target);
		PushArg(s_LogActionFunc, message);
		LogActionSub(args...);
	}
private:
	static void LogActionSub()
	{
		ExecFunc(s_LogActionFunc);
	}

	template<typename T, typename ... Args>
	static void LogActionSub(T arg, Args ... args)
	{
		PushArgRef(s_LogActionFunc, arg);
		LogActionSub(args...);
	}
public:
	/**
	 * @brief Logs a plugin error message to the SourceMod logs.
	 *
	 * @param format        String format.
	 * @param args          Format arguments.
	 */
	template<typename ... Args>
	static void LogError(const char* format, Args ... args)
	{
		PushArg(s_LogErrorFunc, format);
		LogErrorSub(args...);
	}
private:
	static void LogErrorSub()
	{
		ExecFunc(s_LogErrorFunc);
	}

	template<typename T, typename ... Args>
	static void LogErrorSub(T arg, Args ... args)
	{
		PushArgRef(s_LogErrorFunc, arg);
		LogErrorSub(args...);
	}
public:
	/**
	 * @brief Adds a game log hook.
	 *
	 * @param hook          Hook function.
	 */
	static void AddGameLogHook(GameLogHookFunc hook)
	{
		s_GameLogHookCallback = hook;
		ExecFunc(s_AddGameLogHookFunc);
	}

	/**
	 * @brief Removes a game log hook.
	 */
	static void RemoveGameLogHook()
	{
		ExecFunc(s_RemoveGameLogHookFunc);
	}
