public:
	/**
	 * @brief Tests whether a string is found inside another string
	 * Note: Case-sensitive
	 *
	 * @param str           String to search in.
	 * @param substr        Substring to find inside the original string.
	 * @param caseSensitive If true (default), search is case sensitive.
	 * @return              -1 on failure (no match found). Any other value
	 *                      indicates a position in the string where the match starts.
	 */
	static int StrContainsCaseSensitive(const char* str, const char* substr)
	{
		const char* firstMatchPtr = std::strstr(str, substr);
		if (firstMatchPtr == nullptr)
			return -1;
		return str - firstMatchPtr;
	}

	/**
	 * @brief Tests whether a string is found inside another string
	 * Note: Case-INsensitive
	 *
	 * @param str           String to search in.
	 * @param substr        Substring to find inside the original string.
	 * @param caseSensitive If true (default), search is case sensitive.
	 * @return              -1 on failure (no match found). Any other value
	 *                      indicates a position in the string where the match starts.
	 */
	static int StrContainsCaseInsensitive(const char* str, const char* substr)
	{
		auto stristr = [](const char* str1, const char* str2) -> const char*
		{
			const char* p1 = str1;
			const char* p2 = str2;
			const char* r = *p2 == 0 ? str1 : 0;

			while (*p1 != 0 && *p2 != 0)
			{
				if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2))
				{
					if (r == 0)
						r = p1;
					p2++;
				}
				else
				{
					p2 = str2;
					if (r != 0)
						p1 = r + 1;

					if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2))
					{
						r = p1;
						p2++;
					}
					else
					{
						r = 0;
					}
				}

				p1++;
			}

			return *p2 == 0 ? (const char*)r : nullptr;
		};

		const char* firstMatchPtr = stristr(str, substr);
		if (firstMatchPtr == nullptr)
			return -1;
		return str - firstMatchPtr;
	}

	/**
	 * @brief Returns whether two strings are equal (case-sensitive)
	 *
	 * @param str1          First string (left).
	 * @param str2          Second string (right).
	 * @return              True if equal, false otherwise.
	 */
	static bool StrEqualCaseSensitive(const char* str1, const char* str2)
	{
		return (std::strcmp(str1, str2) == 0);
	}

	/**
	 * @brief Returns whether two strings are equal (case-INsensitive)
	 *
	 * @param str1          First string (left).
	 * @param str2          Second string (right).
	 * @return              True if equal, false otherwise.
	 */
	static bool StrEqualCaseInsensitive(const char* str1, const char* str2)
	{
		return (stricmp(str1, str2) == 0);
	}

	/**
	 * @brief Formats a string according to the SourceMod format rules (see documentation).
	 * @note None of the input buffers can overlap the same memory as the output buffer
	 *       Since this security check is removed, it is slightly faster.
	 *
	 * @param buffer        Destination string buffer.
	 * @param maxlength     Maximum length of output string buffer.
	 * @param format        Formatting rules.
	 * @param args          Variable number of format parameters.
	 * @return              Number of cells written.
	 */
	template<typename ... Args>
	static int Format(char* buffer, int maxlength, const char* format, Args ... args)
	{
		PushArg(s_FormatFunc, buffer, maxlength);
		PushArg(s_FormatFunc, maxlength);
		PushArg(s_FormatFunc, format);
		return FormatSub(args...);
	}
private:
	static int FormatSub()
	{
		return ExecFunc(s_FormatFunc);
	}

	template<typename T, typename ... Args>
	static int FormatSub(T arg, Args ... args)
	{
		PushArgRef(s_FormatFunc, arg);
		return FormatSub(args...);
	}
public:
	/**
	 * @brief Converts a string to an integer.
	 *
	 * @param str           String to convert.
	 * @param nBase         Numerical base to use. 10 is default, 0 for auto detection
	 * @return              Integer conversion of string, or 0 on failure.
	 */
	static int StringToInt(const char* str, int nBase = 10)
	{
		return std::stoi(str, nullptr, nBase);
	}

	/**
	 * @brief Converts a string to an integer with some more options.
	 *
	 * @param str           String to convert.
	 * @param result        Variable to store the result in.
	 * @param nBase         Numerical base to use.  10 is default.
	 * @return              Number of characters consumed.
	 */
	static int StringToIntEx(const char* str, int& result, int nBase = 10)
	{
		char* endPtr = nullptr;
		errno = 0;
		result = std::stoi(str, reinterpret_cast<size_t*>(&endPtr), nBase);
		return endPtr - str;
	}

	/**
	 * @brief Converts an integer to a string.
	 *
	 * @param num           Integer to convert.
	 * @param str           Buffer to store string in.
	 * @param maxlength     Maximum length of string buffer.
	 * @return              Number of cells written to buffer.
	 */
	static int IntToString(int num, char* str, int maxlength)
	{
		std::string numStr = std::to_string(num);
		int count = min(maxlength, static_cast<int>(numStr.size()));
		std::strncpy(str, numStr.c_str(), count);
		return count;
	}

	/**
	 * @brief Converts a string to a floating point number.
	 *
	 * @param str           String to convert to a float.
	 * @return              Floating point result, or 0.0 on error.
	 */
	static float StringToFloat(const char* str)
	{
		return std::stof(str);
	}

	/**
	 * @brief Converts a string to a floating point number with some more options.
	 *
	 * @param str           String to convert to a float.
	 * @param result        Variable to store result in.
	 * @return              Number of characters consumed.
	 */
	static int StringToFloatEx(const char* str, float& result)
	{
		char* endPtr = nullptr;
		errno = 0;
		result = std::stof(str, reinterpret_cast<size_t*>(endPtr));
		return endPtr - str;
	}

	/**
	 * @brief Converts a floating point number to a string.
	 *
	 * @param num           Floating point number to convert.
	 * @param str           Buffer to store string in.
	 * @param maxlength     Maximum length of string buffer.
	 * @return              Number of cells written to buffer.
	 */
	static int FloatToString(float num, char* str, int maxlength)
	{
		std::string numStr = std::to_string(num);
		int count = min(maxlength, static_cast<int>(numStr.size()));
		std::strncpy(str, numStr.c_str(), count);
		return count;
	}
