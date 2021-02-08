public:
	/**
	 * Given a partial team name, attempts to find a matching team.
	 *
	 * The search is performed case insensitively and only against the
	 * first N characters of the team names, where N is the number of
	 * characters in the search pattern.
	 *
	 * @param name          Partial or full team name.
	 * @return              A valid team index on success.
	 *                      -1 if no team matched.
	 *                      -2 if more than one team matched.
	 */
	static int FindTeamByName(const char* name)
	{
		int nameLen = strlen(name);
		int numTeams = GetTeamCount();
		char teamName[32];
		int foundTeam = -1;
		for (int i = 0; i < numTeams; ++i)
		{
			GetTeamName(i, teamName, sizeof(teamName));
			if (strnicmp(teamName, name, nameLen) == 0)
			{
				if (foundTeam >= 0)
					return -2;
				else
					foundTeam = i;
			}
		}

		return foundTeam;
	}
