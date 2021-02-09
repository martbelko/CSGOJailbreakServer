public:
	/**
	 * @brief Gets the two character country code from an IP address. (US, CA, etc)
	 *
	 * @param ip            Ip to determine the country code.
	 * @param ccode         Destination string buffer to store the code.
	 * @return              True on success, false if no country found.
	 */
	static bool GeoipCode2(const char* ip, char ccode[3])
	{
		PushArg(s_GeoipCode2Func, ip);
		PushArg(s_GeoipCode2Func, ccode, 3);
		return ExecFunc(s_GeoipCode2Func);
	}

	/**
	 * @brief Gets the three character country code from an IP address. (USA, CAN, etc)
	 *
	 * @param ip            Ip to determine the country code.
	 * @param ccode         Destination string buffer to store the code.
	 * @return              True on success, false if no country found.
	 */
	static bool GeoipCode3(const char* ip, char ccode[4])
	{
		PushArg(s_GeoipCode3Func, ip);
		PushArg(s_GeoipCode3Func, ccode, 4);
		return ExecFunc(s_GeoipCode3Func);
	}

	/**
	 * @brief Gets the full country name. (max length of output string is 45)
	 *
	 * @param ip            Ip to determine the country code.
	 * @param name          Destination string buffer to store the country name.
	 * @param maxlength     Maximum length of output string buffer.
	 * @return              True on success, false if no country found.
	 */
	static bool GeoipCountry(const char* ip, char* name, int maxlength)
	{
		PushArg(s_GeoipCountryFunc, ip);
		PushArg(s_GeoipCountryFunc, name, maxlength);
		PushArg(s_GeoipCountryFunc, maxlength);
		return ExecFunc(s_GeoipCountryFunc);
	}
