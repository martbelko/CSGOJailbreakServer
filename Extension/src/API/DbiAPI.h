public:
	/**
	 * @brief Creates an SQL connection from a named configuration.
	 *
	 * @param confname      Named configuration.
	 * @param persistent    True to re-use a previous persistent connection if
	 *                      possible, false otherwise.
	 * @param error         Error buffer.
	 * @param maxlength     Maximum length of the error buffer.
	 * @return              A database connection Handle, or INVALID_HANDLE on failure.
	 */
	static database_t SQL_Connect(const char* confname, bool persistent, char* error, int maxlength) { return ExecFunc(s_SQL_ConnectFunc, confname, persistent, error, maxlength); }

	/**
	 * @brief Connects to a database using key value pairs containing the database info.
	 * The key/value pairs should match what would be in databases.cfg.
	 *
	 * I.e. "driver" should be "default" or a driver name (or omitted for
	 * the default).  For SQLite, only the "database" parameter is needed in addition.
	 * For drivers which require external connections, more of the parameters may be
	 * needed.
	 *
	 * In general it is discouraged to use this function.  Connections should go through
	 * databases.cfg for greatest flexibility on behalf of users.
	 *
	 * @param keyvalues     Key/value pairs from a KeyValues handle, describing the connection.
	 * @param error         Error buffer.
	 * @param maxlength     Maximum length of the error buffer.
	 * @param persistent    True to re-use a previous persistent connection if
	 *                      possible, false otherwise.
	 * @return              A database connection Handle, or INVALID_HANDLE on failure.
	 *                      On failure the error buffer will be filled with a message.
	 * @error               Invalid KeyValues handle.
	 */
	static database_t SQL_ConnectCustom(Handle keyvalues, char* error, int maxlength, bool persistent) { return ExecFunc(s_SQL_ConnectCustomFunc, keyvalues, error, maxlength, persistent); }

	/**
	 * @brief Returns if a named configuration is present in databases.cfg.
	 *
	 * @param name          Configuration name.
	 * @return              True if it exists, false otherwise.
	 */
	static bool SQL_CheckConfig(const char* name) { return ExecFunc(s_SQL_CheckConfigFunc, name); }

	/**
	 * @brief Returns a driver Handle from a name string.
	 *
	 * If the driver is not found, SourceMod will attempt
	 * to load an extension named dbi.<name>.ext.[dll|so].
	 *
	 * @param name          Driver identification string, or an empty
	 *                      string to return the default driver.
	 * @return              Driver Handle, or INVALID_HANDLE on failure.
	 */
	static DBDriver SQL_GetDriver(const char* name) { return ExecFunc(s_SQL_GetDriverFunc, name); }

	/**
	 * @brief Reads the driver of an opened database.
	 *
	 * @param database      Database Handle.
	 * @param ident         Option buffer to store the identification string.
	 * @param ident_length  Maximum length of the buffer.
	 * @return              Driver Handle.
	 */
	static DBDriver SQL_ReadDriver(Handle database, char* ident, int ident_length) { return ExecFunc(s_SQL_ReadDriverFunc, database, ident, ident_length); }

	/**
	 * @brief Retrieves a driver's identification string.
	 *
	 * Example: "mysql", "sqlite"
	 *
	 * @param driver        Driver Handle, or INVALID_HANDLE for the default driver.
	 * @param ident         Identification string buffer.
	 * @param maxlength     Maximum length of the buffer.
	 * @error               Invalid Handle other than INVALID_HANDLE.
	 */
	static void SQL_GetDriverIdent(Handle driver, char* ident, int maxlength) { ExecFunc(s_SQL_GetDriverIdentFunc, driver, ident, maxlength); }

	/**
	 * @brief Retrieves a driver's product string.
	 *
	 * Example: "MySQL", "SQLite"
	 *
	 * @param driver        Driver Handle, or INVALID_HANDLE for the default driver.
	 * @param product       Product string buffer.
	 * @param maxlength     Maximum length of the buffer.
	 * @error               Invalid Handle other than INVALID_HANDLE.
	 */
	static void SQL_GetDriverProduct(Handle driver, char* product, int maxlength) { ExecFunc(s_SQL_GetDriverProductFunc, driver, product, maxlength); }

	/**
	 * @brief Sets the character set of the current connection.
	 * Like SET NAMES .. in mysql, but stays after connection problems.
	 *
	 * Example: "utf8", "latin1"
	 *
	 * @param database      Database Handle.
	 * @param charset       The character set string to change to.
	 * @return              True, if character set was changed, false otherwise.
	 */
	static bool SQL_SetCharset(Handle database, const char* charset) { return ExecFunc(s_SQL_SetCharsetFunc, database, charset); }

	/**
	 * @brief Returns the number of affected rows from the last query.
	 *
	 * @param hndl          A database OR statement Handle.
	 * @return              Number of rows affected by the last query.
	 * @error               Invalid database or statement Handle.
	 */
	static int SQL_GetAffectedRows(Handle hndl) { return ExecFunc(s_SQL_GetAffectedRowsFunc, hndl); }

	/**
	 * @brief Returns the last query's insertion id.
	 *
	 * @param hndl          A database, query, OR statement Handle.
	 * @return              Last query's insertion id.
	 * @error               Invalid database, query, or statement Handle.
	 */
	static int SQL_GetInsertId(Handle hndl) { return ExecFunc(s_SQL_GetInsertIdFunc, hndl); }

	/**
	 * @brief Returns the error reported by the last query.
	 *
	 * @param hndl          A database, query, OR statement Handle.
	 * @param error         Error buffer.
	 * @param maxlength     Maximum length of the buffer.
	 * @return              True if there was an error, false otherwise.
	 * @error               Invalid database, query, or statement Handle.
	 */
	static bool SQL_GetError(Handle hndl, char* error, int maxlength) { return ExecFunc(s_SQL_GetErrorFunc, hndl, error, maxlength); }

	/**
	 * @brief Escapes a database string for literal insertion.  This is not needed
	 * for binding strings in prepared statements.
	 *
	 * Generally, database strings are inserted into queries enclosed in
	 * single quotes (').  If user input has a single quote in it, the
	 * quote needs to be escaped.  This function ensures that any unsafe
	 * characters are safely escaped according to the database engine and
	 * the database's character set.
	 *
	 * NOTE: SourceMod only guarantees properly escaped strings when the query
	 * encloses the string in ''. While drivers tend to allow " instead, the string
	 * may be not be escaped (for example, on SQLite)!
	 *
	 * @param database      A database Handle.
	 * @param string        String to quote.
	 * @param buffer        Buffer to store quoted string in.
	 * @param maxlength     Maximum length of the buffer.
	 * @param written       Optionally returns the number of bytes written.
	 * @return              True on success, false if buffer is not big enough.
	 *                      The buffer must be at least 2*strlen(string)+1.
	 * @error               Invalid database or statement Handle.
	 */
	static bool SQL_EscapeString(Handle database, const char* string, char* buffer, int maxlength, int& written)
	{
		PushArg(s_SQL_EscapeStringFunc, database); PushArg(s_SQL_EscapeStringFunc, string);
		PushArg(s_SQL_EscapeStringFunc, buffer); PushArg(s_SQL_EscapeStringFunc, maxlength);
		PushArgRef(s_SQL_EscapeStringFunc, written);
		return ExecAndReturn(s_SQL_EscapeStringFunc);
	}

	/**
	 * @brief Formats a string according to the SourceMod format rules (see documentation).
	 * All format specifiers are escaped (see SQL_EscapeString) unless the '!' flag is used.
	 *
	 * @param database      A database Handle.
	 * @param buffer        Destination string buffer.
	 * @param maxlength     Maximum length of output string buffer.
	 * @param format        Formatting rules.
	 * @return              Number of cells written.
	 */
	static int SQL_FormatQuery(Handle database, const char* buffer, int maxlength, const char* format)
	{
		return ExecFunc(s_SQL_FormatQueryFunc, database, buffer, maxlength, format);
	}

	/**
	* @brief Formats a string according to the SourceMod format rules (see documentation).
	* All format specifiers are escaped (see SQL_EscapeString) unless the '!' flag is used.
	*
	* @param database      A database Handle.
	* @param buffer        Destination string buffer.
	* @param maxlength     Maximum length of output string buffer.
	* @param format        Formatting rules.
	* @param ...           Variable number of format parameters.
	* @return              Number of cells written.
	*/
	template<typename ... Args>
	static int SQL_FormatQuery(Handle database, const char* buffer, int maxlength, const char* format, Args ... args)
	{
		PushArg(s_SQL_FormatQueryFunc, database);
		PushArg(s_SQL_FormatQueryFunc, buffer);
		PushArg(s_SQL_FormatQueryFunc, maxlength);
		PushArg(s_SQL_FormatQueryFunc, format);
		return SQL_FormatQuerySub(args...);
	}
private:
	template<typename T>
	static int SQL_FormatQuerySub(T arg)
	{
		PushArg(s_SQL_FormatQueryFunc, arg);
		return ExecAndReturn(s_SQL_FormatQueryFunc);
	}

	template<typename T, typename ... Args>
	static int SQL_FormatQuerySub(T arg, Args ... args)
	{
		PushArg(s_SQL_FormatQueryFunc, arg);
		return SQL_FormatQuerySub(args...);
	}
public:
	/**
	 * @brief Executes a query and ignores the result set.
	 *
	 * @param database      A database Handle.
	 * @param query         Query string.
	 * @param len           Optional parameter to specify the query length, in
	 *                      bytes.  This can be used to send binary queries that
	 *                      have a premature terminator.
	 * @return              True if query succeeded, false otherwise.  Use
	 *                      SQL_GetError to find the last error.
	 * @error               Invalid database Handle.
	 */
	static bool SQL_FastQuery(Handle database, const char* query, int len) { return ExecFunc(s_SQL_FastQueryFunc, database, query, len); }

	/**
	 * @brief Executes a simple query and returns a new query Handle for
	 * receiving the results.
	 *
	 * @param database      A database Handle.
	 * @param query         Query string.
	 * @param len           Optional parameter to specify the query length, in
	 *                      bytes.  This can be used to send binary queries that
	 *                      have a premature terminator.
	 * @return              A new Query Handle on success, INVALID_HANDLE
	 *                      otherwise.  The Handle must be freed with CloseHandle().
	 * @error               Invalid database Handle.
	 */
	static DBResultSet SQL_Query(Handle database, const char* query, int len) { return ExecFunc(s_SQL_QueryFunc, database, query, len); }

	/**
	 * @brief Creates a new prepared statement query.  Prepared statements can
	 * be executed any number of times.  They can also have placeholder
	 * parameters, similar to variables, which can be bound safely and
	 * securely (for example, you do not need to quote bound strings).
	 *
	 * Statement handles will work in any function that accepts a Query handle.
	 *
	 * @param database      A database Handle.
	 * @param query         Query string.
	 * @param error         Error buffer.
	 * @param maxlength     Maximum size of the error buffer.
	 * @return              A new statement Handle on success, INVALID_HANDLE
	 *                      otherwise.  The Handle must be freed with CloseHandle().
	 * @error               Invalid database Handle.
	 */
	static DBStatement SQL_PrepareQuery(Handle database, const char* query, char* error, int maxlength) { return ExecFunc(s_SQL_PrepareQueryFunc, database, query, error, maxlength); }

	/**
	 * @brief Advances to the next set of results.
	 *
	 * In some SQL implementations, multiple result sets can exist on one query.
	 * This is possible in MySQL with simple queries when executing a CALL
	 * query.  If this is the case, all result sets must be processed before
	 * another query is made.
	 *
	 * @param query         A query Handle.
	 * @return              True if there was another result set, false otherwise.
	 * @error               Invalid query Handle.
	 */
	static bool SQL_FetchMoreResults(Handle query) { return ExecFunc(s_SQL_FetchMoreResultsFunc, query); }

	/**
	 * @brief Returns whether or not a result set exists.  This will
	 * return true even if 0 results were returned, but false
	 * on queries like UPDATE, INSERT, or DELETE.
	 *
	 * @param query         A query (or statement) Handle.
	 * @return              True if there is a result set, false otherwise.
	 * @error               Invalid query Handle.
	 */
	static bool SQL_HasResultSet(Handle query) { return ExecFunc(s_SQL_HasResultSetFunc, query); }

	/**
	 * @brief Retrieves the number of rows in the last result set.
	 *
	 * @param query         A query (or statement) Handle.
	 * @return              Number of rows in the current result set.
	 * @error               Invalid query Handle.
	 */
	static int SQL_GetRowCount(Handle query) { return ExecFunc(s_SQL_GetRowCountFunc, query); }

	/**
	 * @brief Retrieves the number of fields in the last result set.
	 *
	 * @param query         A query (or statement) Handle.
	 * @return              Number of fields in the current result set.
	 * @error               Invalid query Handle.
	 */
	static int SQL_GetFieldCount(Handle query) { return ExecFunc(s_SQL_GetFieldCountFunc, query); }

	/**
	 * @brief Retrieves the name of a field by index.
	 *
	 * @param query         A query (or statement) Handle.
	 * @param field         Field number (starting from 0).
	 * @param name          Name buffer.
	 * @param maxlength     Maximum length of the name buffer.
	 * @error               Invalid query Handle, invalid field index, or
	 *                      no current result set.
	 */
	static void SQL_FieldNumToName(Handle query, int field, char* name, int maxlength) { ExecFunc(s_SQL_FieldNumToNameFunc, query, field, name, maxlength); }

	/**
	 * @brief Retrieves a field index by name.
	 *
	 * @param query         A query (or statement) Handle.
	 * @param name          Name of the field (case sensitive).
	 * @param field         Variable to store field index in.
	 * @return              True if found, false if not found.
	 * @error               Invalid query Handle or no current result set.
	 */
	static bool SQL_FieldNameToNum(Handle query, const char* name, int& field)
	{
		PushArg(s_SQL_FieldNameToNumFunc, query); PushArg(s_SQL_FieldNameToNumFunc, name); PushArgRef(s_SQL_FieldNameToNumFunc, field);
		return ExecAndReturn(s_SQL_FieldNameToNumFunc);
	}

	/**
	 * @brief Fetches a row from the current result set.  This must be
	 * successfully called before any results are fetched.
	 *
	 * If this function fails, SQL_MoreRows() can be used to
	 * tell if there was an error or the result set is finished.
	 *
	 * @param query         A query (or statement) Handle.
	 * @return              True if a row was fetched, false otherwise.
	 * @error               Invalid query Handle.
	 */
	static bool SQL_FetchRow(Handle query) { return ExecFunc(s_SQL_FetchRowFunc, query); }

	/**
	 * @brief Returns if there are more rows.
	 *
	 * @param query         A query (or statement) Handle.
	 * @return              True if there are more rows, false otherwise.
	 * @error               Invalid query Handle.
	 */
	static bool SQL_MoreRows(Handle query) { return ExecFunc(s_SQL_MoreRowsFunc, query); }

	/**
	 * @brief Rewinds a result set back to the first result.
	 *
	 * @param query         A query (or statement) Handle.
	 * @return              True on success, false otherwise.
	 * @error               Invalid query Handle or no current result set.
	 */
	static bool SQL_Rewind(Handle query) { return ExecFunc(s_SQL_RewindFunc, query); }

	/**
	 * @brief Fetches a string from a field in the current row of a result set.
	 * If the result is NULL, an empty string will be returned.  A NULL
	 * check can be done with the result parameter, or SQL_IsFieldNull().
	 *
	 * @param query         A query (or statement) Handle.
	 * @param field         The field index (starting from 0).
	 * @param buffer        String buffer.
	 * @param maxlength     Maximum size of the string buffer.
	 * @param result        Optional variable to store the status of the return value.
	 * @return              Number of bytes written.
	 * @error               Invalid query Handle or field index, invalid
	 *                      type conversion requested from the database,
	 *                      or no current result set.
	 */
	static int SQL_FetchString(Handle query, int field, char* buffer, int maxlength, DBResult& result)
	{
		PushArg(s_SQL_FetchStringFunc, query); PushArg(s_SQL_FetchStringFunc, field); PushArg(s_SQL_FetchStringFunc, buffer);
		PushArg(s_SQL_FetchStringFunc, maxlength); PushArgRef(s_SQL_FetchStringFunc, reinterpret_cast<int&>(result));
		return ExecFunc(s_SQL_FetchStringFunc, query, field, buffer, maxlength, result);
	}

	/**
	 * @brief Fetches a float from a field in the current row of a result set.
	 * If the result is NULL, a value of 0.0 will be returned.  A NULL
	 * check can be done with the result parameter, or SQL_IsFieldNull().
	 *
	 * @param query         A query (or statement) Handle.
	 * @param field         The field index (starting from 0).
	 * @param result        Optional variable to store the status of the return value.
	 * @return              A float value.
	 * @error               Invalid query Handle or field index, invalid
	 *                      type conversion requested from the database,
	 *                      or no current result set.
	 */
	static float SQL_FetchFloat(Handle query, int field, DBResult& result)
	{
		PushArg(s_SQL_FetchFloatFunc, query); PushArg(s_SQL_FetchFloatFunc, field); PushArgRef(s_SQL_FetchFloatFunc, reinterpret_cast<int&>(result));
		return ExecAndReturn(s_SQL_FetchFloatFunc);
	}

	/**
	 * @brief Fetches an integer from a field in the current row of a result set.
	 * If the result is NULL, a value of 0 will be returned.  A NULL
	 * check can be done with the result parameter, or SQL_IsFieldNull().
	 *
	 * @param query         A query (or statement) Handle.
	 * @param field         The field index (starting from 0).
	 * @param result        Optional variable to store the status of the return value.
	 * @return              An integer value.
	 * @error               Invalid query Handle or field index, invalid
	 *                      type conversion requested from the database,
	 *                      or no current result set.
	 */
	static int SQL_FetchInt(Handle query, int field, DBResult& result)
	{
		PushArg(s_SQL_FetchIntFunc, query); PushArg(s_SQL_FetchIntFunc, field); PushArgRef(s_SQL_FetchIntFunc, reinterpret_cast<int&>(result));
		return ExecAndReturn(s_SQL_FetchIntFunc);
	}

	/**
	 * @brief Returns whether a field's data in the current row of a result set is
	 * NULL or not.  NULL is an SQL type which means "no data."
	 *
	 * @param query         A query (or statement) Handle.
	 * @param field         The field index (starting from 0).
	 * @return              True if data is NULL, false otherwise.
	 * @error               Invalid query Handle or field index, or no
	 *                      current result set.
	 */
	static bool SQL_IsFieldNull(Handle query, int field) { return ExecFunc(s_SQL_IsFieldNullFunc, query, field); }

	/**
	 * @brief Returns the length of a field's data in the current row of a result
	 * set.  This only needs to be called for strings to determine how many
	 * bytes to use.  Note that the return value does not include the null
	 * terminator.
	 *
	 * @param query         A query (or statement) Handle.
	 * @param field         The field index (starting from 0).
	 * @return              Number of bytes for the field's data size.
	 * @error               Invalid query Handle or field index or no
	 *                      current result set.
	 */
	static int SQL_FetchSize(Handle query, int field) { return ExecFunc(s_SQL_FetchSizeFunc, query, field); }

	/**
	 * @brief Binds a parameter in a prepared statement to a given integer value.
	 *
	 * @param statement     A statement (prepared query) Handle.
	 * @param param         The parameter index (starting from 0).
	 * @param number        The number to bind.
	 * @param signed        True to bind the number as signed, false to
	 *                      bind it as unsigned.
	 * @error               Invalid statement Handle or parameter index, or
	 *                      SQL error.
	 */
	static void SQL_BindParamInt(Handle statement, int param, int number, bool isSigned) { ExecFunc(s_SQL_BindParamStringFunc, statement, param, number, isSigned); }

	/**
	 * @brief Binds a parameter in a prepared statement to a given float value.
	 *
	 * @param statement     A statement (prepared query) Handle.
	 * @param param         The parameter index (starting from 0).
	 * @param value         The float number to bind.
	 * @error               Invalid statement Handle or parameter index, or
	 *                      SQL error.
	 */
	static void SQL_BindParamFloat(Handle statement, int param, float value) { ExecFunc(s_SQL_BindParamFloatFunc, statement, param, value); }

	/**
	 * @brief Binds a parameter in a prepared statement to a given string value.
	 *
	 * @param statement     A statement (prepared query) Handle.
	 * @param param         The parameter index (starting from 0).
	 * @param value         The string to bind.
	 * @param copy          Whether or not SourceMod should copy the value
	 *                      locally if necessary.  If the string contents
	 *                      won't change before calling SQL_Execute(), this
	 *                      can be set to false for optimization.
	 * @error               Invalid statement Handle or parameter index, or
	 *                      SQL error.
	 */
	static void SQL_BindParamString(Handle statement, int param, const char* value, bool copy) { ExecFunc(s_SQL_BindParamStringFunc, statement, param, value, copy); }

	/**
	 * @brief Executes a prepared statement.  All parameters must be bound beforehand.
	 *
	 * @param statement     A statement (prepared query) Handle.
	 * @return              True on success, false on failure.
	 * @error               Invalid statement Handle.
	 */
	static bool SQL_Execute(Handle statement) { return ExecFunc(s_SQL_ExecuteFunc, statement); }

	/**
	 * @brief Locks a database so threading operations will not interrupt.
	 *
	 * If you are using a database Handle for both threading and non-threading,
	 * this MUST be called before doing any set of non-threading DB operations.
	 * Otherwise you risk corrupting the database driver's memory or network
	 * connection.
	 *
	 * Leaving a lock on a database and then executing a threaded query results
	 * in a dead lock! Make sure to call SQL_UnlockDatabase()!
	 *
	 * If the lock cannot be acquired, the main thread will pause until the
	 * threaded operation has concluded.
	 *
	 * @param database      A database Handle.
	 * @error               Invalid database Handle.
	 */
	static void SQL_LockDatabase(Handle database) { ExecFunc(s_SQL_LockDatabaseFunc, database); }

	/**
	 * @brief Unlocks a database so threading operations may continue.
	 *
	 * @param database      A database Handle.
	 * @error               Invalid database Handle.
	 */
	static void SQL_UnlockDatabase(Handle database) { ExecFunc(s_SQL_UnlockDatabaseFunc, database); }

	/**
	 * @brief Tells whether two database handles both point to the same database
	 * connection.
	 *
	 * @param hndl1         First database Handle.
	 * @param hndl2         Second database Handle.
	 * @return              True if the Handles point to the same
	 *                      connection, false otherwise.
	 * @error               Invalid Handle.
	 */
	static bool SQL_IsSameConnection(Handle hndl1, Handle hndl2) { return ExecFunc(s_SQL_IsSameConnectionFunc, hndl1, hndl2); }

	/**
	 * @brief Connects to a database via a thread.  This can be used instead of
	 * SQL_Connect() if you wish for non-blocking functionality.
	 *
	 * It is not necessary to use this to use threaded queries.  However, if you
	 * don't (or you mix threaded/non-threaded queries), you should see
	 * SQL_LockDatabase().
	 *
	 * @param callback      Callback; new Handle will be in hndl, owner is the driver.
	 *                      If no driver was found, the owner is INVALID_HANDLE.
	 * @param name          Database name.
	 * @param data          Extra data value to pass to the callback.
	 */
	static void SQL_TConnect(SQLTCallbackFunc callback, const char* name, int data)
	{
		static int index = 0;
		s_SQLTConnectCallbacksData[index] = data;
		s_SQLTConnectCallbacks[index] = callback;
		ExecFunc(s_SQL_TConnectFunc, name, index);
		++index;
	}

	/**
	 * @brief Executes a simple query via a thread.  The query Handle is passed through
	 * the callback.
	 *
	 * The database Handle returned through the callback is always a new Handle,
	 * and if necessary, SQL_IsSameConnection() should be used to test against
	 * other connections.
	 *
	 * The query Handle returned through the callback is temporary and destroyed
	 * at the end of the callback.  If you need to hold onto it, use CloneHandle().
	 *
	 * @param database      A database Handle.
	 * @param callback      Callback; database is in "owner" and the query Handle
	 *                      is passed in "hndl".
	 * @param query         Query string.
	 * @param data          Extra data value to pass to the callback.
	 * @param prio          Priority queue to use.
	 * @error               Invalid database Handle.
	 */
	static void SQL_TQuery(Handle database, SQLTCallbackFunc callback, const char* query, int data, DBPriority prio)
	{
		static int index = 0;
		s_SQLTQueryCallbacksData[index] = data;
		s_SQLTQueryCallbacks[index] = callback;
		ExecFunc(s_SQL_TQueryFunc, database, query, data, prio);
		++index;
	}

	/**
	 * @brief Creates a new transaction object. A transaction object is a list of queries
	 * that can be sent to the database thread and executed as a single transaction.
	 *
	 * @return              A transaction handle.
	 */
	static transaction_t SQL_CreateTransaction() { return ExecFunc(s_SQL_CreateTransactionFunc); }

	/**
	 * @brief Adds a query to a transaction object.
	 *
	 * @param txn           A transaction handle.
	 * @param query         Query string.
	 * @param data          Extra data value to pass to the final callback.
	 * @return              The index of the query in the transaction's query list.
	 * @error               Invalid transaction handle.
	 */
	static int SQL_AddQuery(transaction_t txn, const char* query, int data) { return ExecFunc(s_SQL_AddQueryFunc, txn, query, data); }

	// TODO: Callbacks
	/**
	 * @brief Sends a transaction to the database thread. The transaction handle is
	 * automatically closed. When the transaction completes, the optional
	 * callback is invoked.
	 *
	 * @param db            A database handle.
	 * @param txn           A transaction handle.
	 * @param onSuccess     An optional callback to receive a successful transaction.
	 * @param onError       An optional callback to receive an error message.
	 * @param data          An optional value to pass to callbacks.
	 * @param prio          Priority queue to use.
	 * @error               An invalid handle.
	 */
	static void SQL_ExecuteTransaction(Handle db, transaction_t txn, int data, DBPriority priority) { ExecFunc(s_SQL_ExecuteTransactionFunc, db, txn, data, priority); }
