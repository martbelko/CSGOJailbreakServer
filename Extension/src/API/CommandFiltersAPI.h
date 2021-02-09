public:
	/**
	 * @brief Processes a generic command target string, and resolves it to a list
	 * of clients or one client, based on filtering rules and a pattern.
	 *
	 * Note that you should use LoadTranslations("common.phrases") in OnPluginStart(),
	 * as that file is guaranteed to contain all of the translatable phrases that
	 * ProcessTargetString() will return.
	 *
	 * @param pattern       Pattern to find clients against.
	 * @param admin         Admin performing the action, or 0 if the server.
	 * @param targets       Array to hold targets.
	 * @param maxTargets    Maximum size of the targets array.
	 * @param filterFlags   Filter flags.
	 * @param targetName    Buffer to store the target name.
	 * @param tnMaxLength   Maximum length of the target name buffer.
	 * @param tnIsMl       OUTPUT: Will be true if the target name buffer is an ML phrase,
	 *                      false if it is a normal string.
	 * @return              If a multi-target pattern was used, the number of clients found
	 *                      is returned.  If a single-target pattern was used, 1 is returned
	 *                      if one valid client is found.  Otherwise, a COMMAND_TARGET reason
	 *                      for failure is returned.
	 */
	static int ProcessTargetString(const char* pattern, int admin, int targets[], int maxTargets, int filterFlags,
		char* targetName, int tnMaxLength, bool& tnIsMl)
	{
		PushArg(s_ProcessTargetStringFunc, pattern);
		PushArg(s_ProcessTargetStringFunc, admin);
		PushArg(s_ProcessTargetStringFunc, targets, maxTargets);
		PushArg(s_ProcessTargetStringFunc, maxTargets);
		PushArg(s_ProcessTargetStringFunc, filterFlags);
		PushArg(s_ProcessTargetStringFunc, targetName, tnMaxLength);
		PushArg(s_ProcessTargetStringFunc, tnMaxLength);
		int tnIsMlInt;
		PushArgRef(s_ProcessTargetStringFunc, tnIsMlInt);
		int ret = ExecFunc(s_ProcessTargetStringFunc);
		tnIsMl = static_cast<bool>(tnIsMlInt);
		return ret;
	}

	/**
	 * @brief Replies to a client with a given message describing a targetting
	 * failure reason.
	 *
	 * Note: The translation phrases are found in common.phrases.txt.
	 *
	 * @param client        Client index, or 0 for server.
	 * @param reason        COMMAND_TARGET reason.
	 */
	static void ReplyToTargetError(int client, int reason)
	{
		switch (reason)
		{
		case COMMAND_TARGET_NONE:
		{
			ReplyToCommand(client, "[SM] %t", "No matching client");
		}
		case COMMAND_TARGET_NOT_ALIVE:
		{
			ReplyToCommand(client, "[SM] %t", "Target must be alive");
		}
		case COMMAND_TARGET_NOT_DEAD:
		{
			ReplyToCommand(client, "[SM] %t", "Target must be dead");
		}
		case COMMAND_TARGET_NOT_IN_GAME:
		{
			ReplyToCommand(client, "[SM] %t", "Target is not in game");
		}
		case COMMAND_TARGET_IMMUNE:
		{
			ReplyToCommand(client, "[SM] %t", "Unable to target");
		}
		case COMMAND_TARGET_EMPTY_FILTER:
		{
			ReplyToCommand(client, "[SM] %t", "No matching clients");
		}
		case COMMAND_TARGET_NOT_HUMAN:
		{
			ReplyToCommand(client, "[SM] %t", "Cannot target bot");
		}
		case COMMAND_TARGET_AMBIGUOUS:
		{
			ReplyToCommand(client, "[SM] %t", "More than one client matched");
		}
		}
	}

	/**
	* @brief Adds a multi-target filter function for ProcessTargetString().
	*
	* @param pattern       Pattern to match (case sensitive).
	* @param filter        Filter function.
	* @param phrase        Descriptive phrase to display on successful match.
	* @param phraseIsML    True if phrase is multi-lingual, false otherwise.
	*/
	static void AddMultiTargetFilter(const char* pattern, MultiTargetFilterFunc filter, const char* phrase, bool phraseIsML)
	{
		std::string patternStr(pattern);
		s_MultiTargetFilterCallbacks[patternStr] = filter;
		ExecFunc(s_AddMultiTargetFilterFunc, pattern, phrase, phraseIsML);
	}

	/**
	 * @brief Removes a multi-target filter function from ProcessTargetString().
	 *
	 * @param pattern       Pattern to match (case sensitive).
	 * @param filter        Filter function.
	 */
	static void RemoveMultiTargetFilter(const char* pattern)
	{
		ExecFunc(s_RemoveMultiTargetFilterFunc, pattern);
	}
