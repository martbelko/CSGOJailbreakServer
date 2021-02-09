public:
	// TODO: Add another stock

	/**
	 * @brief Wraps ProcessTargetString() and handles producing error messages for
	 * bad targets.
	 *
	 * Note that you should use LoadTranslations("common.phrases") in OnPluginStart().
	 * "common.phrases" contains all of the translatable phrases that FindTarget() will
	 * reply with in the event a target is not found (error).
	 *
	 * @param client        Client who issued command
	 * @param target        Client's target argument
	 * @param nobots        Optional. Set to true if bots should NOT be targetted
	 * @param immunity      Optional. Set to false to ignore target immunity.
	 * @return              Index of target client, or -1 on error.
	 */
	static int FindTarget(int client, const char* target, bool nobots = false, bool immunity = true)
	{
		char targetName[MAX_TARGET_LENGTH];
		int targetList[1], targetCount;
		bool tnIsMl;

		int flags = COMMAND_FILTER_NO_MULTI;
		if (nobots)
		{
			flags |= COMMAND_FILTER_NO_BOTS;
		}

		if (!immunity)
		{
			flags |= COMMAND_FILTER_NO_IMMUNITY;
		}

		if ((targetCount = ProcessTargetString(
			target,
			client,
			targetList,
			1,
			flags,
			targetName,
			sizeof(targetName),
			tnIsMl)) > 0)
		{
			return targetList[0];
		}

		ReplyToTargetError(client, targetCount);
		return -1;
	}
