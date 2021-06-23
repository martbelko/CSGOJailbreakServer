public:
	/**
	 * @brief Loads a translation file for the plugin calling this native.
	 * If no extension is specified, .txt is assumed.
	 *
	 * @param file          Translation file.
	 */
	static void LoadTranslations(const char* file)
	{
		ExecFunc(s_LoadTranslationsFunc, file);
	}

	/**
	 * @brief Sets the global language target.  This is useful for creating functions
	 * that will be compatible with the %t format specifier.  Note that invalid
	 * indexes can be specified but the error will occur during translation,
	 * not during this function call.
	 *
	 * @param client        Client index or LANG_SERVER.
	 */
	static void SetGlobalTransTarget(int client)
	{
		ExecFunc(s_SetGlobalTransTargetFunc, client);
	}

	/**
	 * @brief Retrieves the language number of a client.
	 *
	 * @param client        Client index.
	 * @return              Language number client is using.
	 * @error               Invalid client index or client not connected.
	 */
	static int GetClientLanguage(int client)
	{
		return ExecFunc(s_GetClientLanguageFunc, client);
	}

	/**
	 * @brief Retrieves the server's language.
	 *
	 * @return              Language number server is using.
	 */
	static int GetServerLanguage()
	{
		return ExecFunc(s_GetServerLanguageFunc);
	}

	/**
	 * @brief Returns the number of languages known in languages.cfg.
	 *
	 * @return              Language count.
	 */
	static int GetLanguageCount()
	{
		return ExecFunc(s_GetLanguageCountFunc);
	}

	/**
	 * @brief Retrieves info about a given language number.
	 *
	 * @param language      Language number.
	 * @param code          Language code buffer (2-3 characters usually).
	 * @param codeLen       Maximum length of the language code buffer.
	 * @param name          Language name buffer.
	 * @param nameLen       Maximum length of the language name buffer.
	 * @error               Invalid language number.
	 */
	static void GetLanguageInfo(int language, char* code = const_cast<char*>(""), int codeLen = 0, char* name = const_cast<char*>(""), int nameLen = 0)
	{
		PushArg(s_GetLanguageInfoFunc, language);
		PushArg(s_GetLanguageInfoFunc, code, codeLen);
		PushArg(s_GetLanguageInfoFunc, codeLen);
		PushArg(s_GetLanguageInfoFunc, name, nameLen);
		PushArg(s_GetLanguageInfoFunc, nameLen);
		ExecFunc(s_GetLanguageInfoFunc);
	}

	/**
	 * @brief Sets the language number of a client.
	 *
	 * @param client        Client index.
	 * @param language      Language number.
	 * @error               Invalid client index or client not connected.
	 */
	static void SetClientLanguage(int client, int language)
	{
		ExecFunc(s_SetClientLanguageFunc, client, language);
	}

	/**
	 * @brief Retrieves the language number from a language code.
	 *
	 * @param code          Language code (2-3 characters usually).
	 * @return              Language number. -1 if not found.
	 */
	static int GetLanguageByCode(const char* code)
	{
		return ExecFunc(s_GetLanguageByCodeFunc, code);
	}

	/**
	 * @brief Retrieves the language number from a language name.
	 *
	 * @param name          Language name (case insensitive).
	 * @return              Language number. -1 if not found.
	 */
	static int GetLanguageByName(const char* name)
	{
		return ExecFunc(s_GetLanguageByNameFunc, name);
	}

	/**
	 * @brief Determines if the specified phrase exists within the plugin's
	 * translation cache.
	 *
	 * @param phrase        Phrase to look for.
	 * @return              True if phrase exists.
	 */
	static bool TranslationPhraseExists(const char* phrase)
	{
		return ExecFunc(s_TranslationPhraseExistsFunc, phrase);
	}

	/**
	 * @brief Determines if there is a translation for the specified language.
	 *
	 * @param phrase        Phrase to check.
	 * @param language      Language number.
	 * @return              True if translation exists.
	 */
	static bool IsTranslatedForLanguage(const char* phrase, int language)
	{
		return ExecFunc(s_IsTranslatedForLanguageFunc, phrase, language);
	}
