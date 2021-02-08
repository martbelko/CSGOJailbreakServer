public:
	/**
	 * @brief Returns the maximum number of networked entities.
	 *
	 * Note: For legacy reasons, this only returns the maximum
	 * networked entities (maximum edicts), rather than total
	 * maximum entities.
	 *
	 * @return              Maximum number of networked entities.
	 */
	static int GetMaxEntities()
	{
		return ExecFunc(s_GetMaxEntitiesFunc);
	}

	/**
	 * @brief Returns the number of networked entities in the server.
	 *
	 * Note: For legacy reasons, this only returns the current count
	 * of networked entities (current edicts), rather than total
	 * count of current entities.
	 *
	 * @return              Number of entities in the server.
	 */
	static int GetEntityCount()
	{
		return ExecFunc(s_GetEntityCountFunc);
	}

	/**
	 * @brief Returns whether or not an entity is valid.  Returns false
	 * if there is no matching CBaseEntity for this entity index.
	 *
	 * @param entity        Index of the entity.
	 * @return              True if valid, false otherwise.
	 */
	static bool IsValidEntity(int entity)
	{
		return ExecFunc(s_IsValidEntityFunc, entity);
	}

	/**
	 * @brief Returns whether or not an edict index is valid.
	 *
	 * @param edict         Index of the edict.
	 * @return              True if valid, false otherwise.
	 */
	static bool IsValidEdict(int edict)
	{
		return ExecFunc(s_IsValidEdictFunc, edict);
	}

	/**
	 * @brief Returns whether or not an entity has a valid networkable edict.
	 *
	 * @param entity        Index of the entity.
	 * @return              True if networkable, false if invalid or not networkable.
	 */
	static bool IsEntNetworkable(int entity)
	{
		return ExecFunc(s_IsEntNetworkableFunc, entity);
	}

	/**
	 * @brief Creates a new edict (the basis of a networkable entity)
	 *
	 * @return              Index of the edict, 0 on failure.
	 */
	static int CreateEdict()
	{
		return ExecFunc(s_CreateEdictFunc);
	}

	/**
	 * @brief Removes an edict from the world.
	 *
	 * @param edict         Index of the edict.
	 * @error               Invalid edict index.
	 */
	static void RemoveEdict(int edict)
	{
		ExecFunc(s_RemoveEdictFunc, edict);
	}

	/**
	 * @brief Marks an entity for deletion.
	 *
	 * @param entity        Index of the entity.
	 * @error               Invalid entity index.
	 */
	static void RemoveEntity(int entity)
	{
		ExecFunc(s_RemoveEntityFunc, entity);
	}

	/**
	 * @brief Returns the flags on an edict.  These are not the same as entity flags.
	 *
	 * @param edict         Index of the entity.
	 * @return              Edict flags.
	 * @error               Invalid edict index.
	 */
	static int GetEdictFlags(int edict)
	{
		return ExecFunc(s_GetEdictFlagsFunc, edict);
	}

	/**
	 * @brief Sets the flags on an edict.  These are not the same as entity flags.
	 *
	 * @param edict         Index of the entity.
	 * @param flags         Flags to set.
	 * @error               Invalid edict index.
	 */
	static void SetEdictFlags(int edict, int flags)
	{
		ExecFunc(s_SetEdictFlagsFunc, edict, flags);
	}

	/**
	 * @brief Retrieves an edict classname.
	 *
	 * @param edict         Index of the entity.
	 * @param className     Buffer to store the classname.
	 * @param maxLength     Maximum length of the buffer.
	 * @return              True on success, false if there is no classname set.
	 */
	static bool GetEdictClassname(int edict, char* className, int maxLength)
	{
		PushArg(s_GetEdictClassnameFunc, edict);
		PushArg(s_GetEdictClassnameFunc, className, maxLength);
		PushArg(s_GetEdictClassnameFunc, maxLength);
		return ExecFunc(s_GetEdictClassnameFunc);
	}

	/**
	 * @brief Retrieves an entity's networkable serverclass name.
	 * This is not the same as the classname and is used for networkable state changes.
	 *
	 * @param edict         Index of the entity.
	 * @param className     Buffer to store the serverclass name.
	 * @param maxLength     Maximum length of the buffer.
	 * @return              True on success, false if the edict is not networkable.
	 * @error               Invalid edict index.
	 */
	static bool GetEntityNetClass(int edict, char* className, int maxLength)
	{
		PushArg(s_GetEntityNetClassFunc, edict);
		PushArg(s_GetEntityNetClassFunc, className, maxLength);
		PushArg(s_GetEntityNetClassFunc, maxLength);
		return ExecFunc(s_GetEntityNetClassFunc);
	}

	/**
	 * @brief Marks an entity as state changed.  This can be useful if you set an offset
	 * and wish for it to be immediately changed over the network.  By default this
	 * is not done for offset setting functions.
	 *
	 * @param edict         Index to the edict.
	 * @param offset        Offset to mark as changed.  If 0,
	 *                      the entire edict is marked as changed.
	 * @error               Invalid entity or offset out of bounds.
	 */
	static void ChangeEdictState(int edict, int offset = 0)
	{
		ExecFunc(s_ChangeEdictStateFunc, edict, offset);
	}

	/**
	 * @brief Peeks into an entity's object data and retrieves the integer value at
	 * the given offset.
	 *
	 * @param entity        Edict index.
	 * @param offset        Offset to use.
	 * @param size          Number of bytes to read (valid values are 1, 2, or 4).
	 * @return              Value at the given memory location.
	 * @error               Invalid entity or offset out of reasonable bounds.
	 */
	static int GetEntData(int entity, int offset, int size = 4)
	{
		return ExecFunc(s_GetEntDataFunc, entity, offset, size);
	}

	/**
	 * @brief Peeks into an entity's object data and sets the integer value at
	 * the given offset.
	 *
	 * @param entity        Edict index.
	 * @param offset        Offset to use.
	 * @param value         Value to set.
	 * @param size          Number of bytes to write (valid values are 1, 2, or 4).
	 * @param changeState   If true, change will be sent over the network.
	 * @error               Invalid entity or offset out of reasonable bounds.
	 */
	template<typename any>
	static void SetEntData(int entity, int offset, any value, int size = 4, bool changeState = false)
	{
		return ExecFunc(s_SetEntDataFunc, entity, offset, value, size, changeState);
	}

	/**
	 * @brief Peeks into an entity's object data and retrieves the float value at
	 * the given offset.
	 *
	 * @param entity        Edict index.
	 * @param offset        Offset to use.
	 * @return              Value at the given memory location.
	 * @error               Invalid entity or offset out of reasonable bounds.
	 */
	static float GetEntDataFloat(int entity, int offset)
	{
		return ExecFunc(s_GetEntDataFunc, entity, offset);
	}

	/**
	 * @brief Peeks into an entity's object data and sets the float value at
	 * the given offset.
	 *
	 * @param entity        Edict index.
	 * @param offset        Offset to use.
	 * @param value         Value to set.
	 * @param changeState   If true, change will be sent over the network.
	 * @error               Invalid entity or offset out of reasonable bounds.
	 */
	static void SetEntDataFloat(int entity, int offset, float value, bool changeState = false)
	{
		ExecFunc(s_SetEntDataFloatFunc, entity, offset, value, changeState);
	}

	/**
	 * @brief Peeks into an entity's object data and retrieves the entity index
	 * at the given offset.
	 *
	 * Note: This will only work on offsets that are stored as "entity
	 * handles" (which usually looks like m_h* in properties).  These
	 * are not SourceMod Handles, but internal Source structures.
	 *
	 * @param entity        Edict index.
	 * @param offset        Offset to use.
	 * @return              Entity index at the given location.  If there is no entity,
	 *                      or the stored entity is invalid, then -1 is returned.
	 * @error               Invalid input entity, or offset out of reasonable bounds.
	 */
	static int GetEntDataEnt2(int entity, int offset)
	{
		return ExecFunc(s_GetEntDataEnt2Func, entity, offset);
	}

	/**
	 * @brief Peeks into an entity's object data and sets the entity index at the
	 * given offset.
	 *
	 * Note: This will only work on offsets that are stored as "entity
	 * handles" (which usually looks like m_h* in properties).  These
	 * are not SourceMod Handles, but internal Source structures.
	 *
	 * @param entity        Edict index.
	 * @param offset        Offset to use.
	 * @param other         Entity index to set, or -1 to clear.
	 * @param changeState   If true, change will be sent over the network.
	 * @error               Invalid input entity, or offset out of reasonable bounds.
	 */
	static void SetEntDataEnt2(int entity, int offset, int other, bool changeState = false)
	{
		ExecFunc(s_SetEntDataEnt2Func, entity, offset, other, changeState);
	}

	/**
	 * @brief Peeks into an entity's object data and retrieves the vector at the
	 * given offset.
	 * @note Both a Vector and a QAngle are three floats.  This is a
	 *       convenience function and will work with both types.
	 *
	 * @param entity        Edict index.
	 * @param offset        Offset to use.
	 * @param vec           Vector buffer to store data in.
	 * @error               Invalid entity or offset out of reasonable bounds.
	 */
	static void GetEntDataVector(int entity, int offset, float vec[3])
	{
		ExecFunc(s_GetEntDataVectorFunc, entity, offset, vec);
	}

	/**
	 * @brief Peeks into an entity's object data and sets the vector at the given
	 * offset.
	 * @note Both a Vector and a QAngle are three floats.  This is a
	 *       convenience function and will work with both types.
	 *
	 * @param entity        Edict index.
	 * @param offset        Offset to use.
	 * @param vec           Vector to set.
	 * @param changeState   If true, change will be sent over the network.
	 * @error               Invalid entity or offset out of reasonable bounds.
	 */
	static void SetEntDataVector(int entity, int offset, const float vec[3], bool changeState = false)
	{
		ExecFunc(s_SetEntDataVectorFunc, entity, offset, vec, changeState);
	}

	/**
	 * @brief Peeks into an entity's object data and retrieves the string at
	 * the given offset.
	 *
	 * @param entity        Edict index.
	 * @param offset        Offset to use.
	 * @param buffer        Destination string buffer.
	 * @param maxLength     Maximum length of output string buffer.
	 * @return              Number of non-null bytes written.
	 * @error               Invalid entity or offset out of reasonable bounds.
	 */
	static int GetEntDataString(int entity, int offset, char* buffer, int maxLength)
	{
		PushArg(s_GetEntDataStringFunc, entity);
		PushArg(s_GetEntDataStringFunc, offset);
		PushArg(s_GetEntDataStringFunc, buffer, maxLength);
		PushArg(s_GetEntDataStringFunc, maxLength);
		return ExecFunc(s_GetEntDataStringFunc);
	}

	/**
	 * @brief Peeks into an entity's object data and sets the string at
	 * the given offset.
	 *
	 * @param entity        Edict index.
	 * @param offset        Offset to use.
	 * @param str           String to set.
	 * @param maxLength     Maximum length of bytes to write.
	 * @param changeState   If true, change will be sent over the network.
	 * @return              Number of non-null bytes written.
	 * @error               Invalid entity or offset out of reasonable bounds.
	 */
	static int SetEntDataString(int entity, int offset, const char* str, int maxLength, bool changeState = false)
	{
		return ExecFunc(s_SetEntDataStringFunc, entity, offset, str, maxLength, changeState);
	}

	/**
	 * @brief Given a ServerClass name, finds a networkable send property offset.
	 * This information is cached for future calls.
	 *
	 * @param className     Classname.
	 * @param propName      Property name.
	 * @param type          Optional parameter to store the type.
	 * @param numBits       Optional parameter to store the number of bits the field
	 *                      uses, if applicable (otherwise 0 is stored).  The number
	 *                      of bits varies for integers and floats, and is always 0
	 *                      for strings.
	 * @param localOffset   Optional parameter to store the local offset, as
	 *                      FindSendPropOffs() would return.
	 * @return              On success, returns an absolutely computed offset.
	 *                      If no offset is available, 0 is returned.
	 *                      If the property is not found, -1 is returned.
	 */
	static int FindSendPropInfo(const char* className, const char* propName, PropFieldType& type = reinterpret_cast<PropFieldType&>(NULL_VALUE), int& numBits = NULL_VALUE, int& localOffset = NULL_VALUE)
	{
		PushArg(s_FindSendPropInfoFunc, className);
		PushArg(s_FindSendPropInfoFunc, propName);
		PushArgRef(s_FindSendPropInfoFunc, reinterpret_cast<int&>(type));
		PushArgRef(s_FindSendPropInfoFunc, numBits);
		PushArgRef(s_FindSendPropInfoFunc, localOffset);
		return ExecFunc(s_FindSendPropInfoFunc);
	}

	/**
	 * @brief Given an entity, finds a nested datamap property offset.
	 * This information is cached for future calls.
	 *
	 * @param entity        Entity index.
	 * @param propName      Property name.
	 * @param type          Optional parameter to store the type.
	 * @param numBits       Optional parameter to store the number of bits the field
	 *                      uses.  The bit count will either be 1 (for boolean) or
	 *                      divisible by 8 (including 0 if unknown).
	 * @param localOffset   Optional parameter to store the local offset, as
	 *                      FindDataMapOffs() would return.
	 * @return              An offset, or -1 on failure.
	 */
	static int FindDataMapInfo(int entity, const char* propName, PropFieldType& type = reinterpret_cast<PropFieldType&>(NULL_VALUE), int& numBits = NULL_VALUE, int& localOffset = NULL_VALUE)
	{
		PushArg(s_FindDataMapInfoFunc, entity);
		PushArg(s_FindDataMapInfoFunc, propName);
		PushArgRef(s_FindDataMapInfoFunc, reinterpret_cast<int&>(type));
		PushArgRef(s_FindDataMapInfoFunc, numBits);
		PushArgRef(s_FindDataMapInfoFunc, localOffset);
		return ExecFunc(s_FindDataMapInfoFunc);
	}

	/**
	 * @brief Wrapper function for finding a send property for a particular entity.
	 *
	 * @param entity        Entity index.
	 * @param propName      Property name.
	 * @param actual        Defaults to false for backwards compatibility.
	 *                      If true, the newer FindSendPropInfo() function
	 *                      is used instead.
	 * @return              An offset, or -1 on failure.
	 */
	static int GetEntSendPropOffs(int entity, const char* propName, bool actual = false)
	{
		char cls[64];
		if (!GetEntityNetClass(entity, cls, sizeof(cls)))
		{
			return -1;
		}

		int local = -1;
		int offset = FindSendPropInfo(cls, propName, reinterpret_cast<PropFieldType&>(NULL_VALUE), NULL_VALUE, local);
		if (actual)
			return offset;
		return local;
	}

	/**
	 * @brief Checks if an entity property exists on an entity.
	 *
	 * @param entity        Entity/edict index.
	 * @param type          Property type.
	 * @param propName      Property name.
	 * @return              Whether the property exists on the entity.
	 * @error               Invalid entity.
	 */
	static bool HasEntProp(int entity, PropType type, const char* propName)
	{
		if (type == Prop_Data)
			return (FindDataMapInfo(entity, propName) != -1);

		if (type != Prop_Send)
			return false;

		char className[64];
		if (!GetEntityNetClass(entity, className, sizeof(className)))
			return false;

		return (FindSendPropInfo(className, propName) != -1);
	}

	/**
	 * @brief Retrieves an integer value from an entity's property.
	 *
	 * This function is considered safer and more robust over GetEntData,
	 * because it performs strict offset checking and typing rules.
	 *
	 * @param entity        Entity/edict index.
	 * @param type          Property type.
	 * @param propName      Property name.
	 * @param size          Number of bytes to write (valid values are 1, 2, or 4).
	 *                      This value is auto-detected, and the size parameter is
	 *                      only used as a fallback in case detection fails.
	 * @param element       Element # (starting from 0) if property is an array.
	 * @return              Value at the given property offset.
	 * @error               Invalid entity or property not found.
	 */
	static int GetEntProp(int entity, PropType type, const char* propName, int size = 4, int element = 0)
	{
		return ExecFunc(s_GetEntPropFunc, entity, type, propName, size, element);
	}

	/**
	 * @brief Sets an integer value in an entity's property.
	 *
	 * This function is considered safer and more robust over SetEntData,
	 * because it performs strict offset checking and typing rules.
	 *
	 * @param entity        Entity/edict index.
	 * @param type          Property type.
	 * @param propName      Property name.
	 * @param value         Value to set.
	 * @param size          Number of bytes to write (valid values are 1, 2, or 4).
	 *                      This value is auto-detected, and the size parameter is
	 *                      only used as a fallback in case detection fails.
	 * @param element       Element # (starting from 0) if property is an array.
	 * @error               Invalid entity or offset out of reasonable bounds.
	 */
	template<typename any>
	static void SetEntProp(int entity, PropType type, const char* propName, any value, int size = 4, int element = 0)
	{
		ExecFunc(s_SetEntPropFunc, entity, type, propName, value, size, element);
	}

	/**
	 * @brief Retrieves a float value from an entity's property.
	 *
	 * This function is considered safer and more robust over GetEntDataFloat,
	 * because it performs strict offset checking and typing rules.
	 *
	 * @param entity        Entity/edict index.
	 * @param type          Property type.
	 * @param propName      Property name.
	 * @param element       Element # (starting from 0) if property is an array.
	 * @return              Value at the given property offset.
	 * @error               Invalid entity or offset out of reasonable bounds.
	 */
	static float GetEntPropFloat(int entity, PropType type, const char* propName, int element = 0)
	{
		return ExecFunc(s_GetEntPropFloatFunc, entity, type, propName, element);
	}

	/**
	 * @brief Sets a float value in an entity's property.
	 *
	 * This function is considered safer and more robust over SetEntDataFloat,
	 * because it performs strict offset checking and typing rules.
	 *
	 * @param entity        Entity/edict index.
	 * @param type          Property type.
	 * @param propName      Property name.
	 * @param value         Value to set.
	 * @param element       Element # (starting from 0) if property is an array.
	 * @error               Invalid entity or offset out of reasonable bounds.
	 */
	static void SetEntPropFloat(int entity, PropType type, const char* propName, float value, int element = 0)
	{
		ExecFunc(s_SetEntPropFloatFunc, entity, type, propName, value, element);
	}

	/**
	 * @brief Retrieves an entity index from an entity's property.
	 *
	 * This function is considered safer and more robust over GetEntDataEnt*,
	 * because it performs strict offset checking and typing rules.
	 *
	 * @param entity        Entity/edict index.
	 * @param type          Property type.
	 * @param propName      Property name.
	 * @param element       Element # (starting from 0) if property is an array.
	 * @return              Entity index at the given property.
	 *                      If there is no entity, or the entity is not valid,
	 *                      then -1 is returned.
	 * @error               Invalid entity or offset out of reasonable bounds.
	 */
	static int GetEntPropEnt(int entity, PropType type, const char* propName, int element = 0)
	{
		return ExecFunc(s_GetEntPropEntFunc, entity, type, propName, element);
	}

	/**
	 * @brief Sets an entity index in an entity's property.
	 *
	 * This function is considered safer and more robust over SetEntDataEnt*,
	 * because it performs strict offset checking and typing rules.
	 *
	 * @param entity        Entity/edict index.
	 * @param type          Property type.
	 * @param propName      Property name.
	 * @param other         Entity index to set, or -1 to unset.
	 * @param element       Element # (starting from 0) if property is an array.
	 * @error               Invalid entity or offset out of reasonable bounds.
	 */
	static void SetEntPropEnt(int entity, PropType type, const char* propName, int other, int element = 0)
	{
		ExecFunc(s_SetEntPropEntFunc, entity, type, propName, other, element);
	}

	/**
	 * @brief Retrieves a vector of floats from an entity, given a named network property.
	 *
	 * This function is considered safer and more robust over GetEntDataVector,
	 * because it performs strict offset checking and typing rules.
	 *
	 * @param entity        Entity/edict index.
	 * @param type          Property type.
	 * @param propName      Property name.
	 * @param vec           Vector buffer to store data in.
	 * @param element       Element # (starting from 0) if property is an array.
	 * @error               Invalid entity, property not found, or property not
	 *                      actually a vector data type.
	 */
	static void GetEntPropVector(int entity, PropType type, const char* propName, float vec[3], int element = 0)
	{
		ExecFunc(s_GetEntPropVectorFunc, entity, type, propName, vec, element);
	}

	/**
	 * @brief Sets a vector of floats in an entity, given a named network property.
	 *
	 * This function is considered safer and more robust over SetEntDataVector,
	 * because it performs strict offset checking and typing rules.
	 *
	 * @param entity        Entity/edict index.
	 * @param type          Property type.
	 * @param propName      Property name.
	 * @param vec           Vector to set.
	 * @param element       Element # (starting from 0) if property is an array.
	 * @error               Invalid entity, property not found, or property not
	 *                      actually a vector data type.
	 */
	static void SetEntPropVector(int entity, PropType type, const char* propName, const float vec[3], int element = 0)
	{
		ExecFunc(s_SetEntPropVectorFunc, entity, type, propName, vec, element);
	}

	/**
	 * @brief Gets a network property as a string.
	 *
	 * @param entity        Edict index.
	 * @param type          Property type.
	 * @param propName      Property to use.
	 * @param buffer        Destination string buffer.
	 * @param maxLength     Maximum length of output string buffer.
	 * @param element       Element # (starting from 0) if property is an array.
	 * @return              Number of non-null bytes written.
	 * @error               Invalid entity, offset out of reasonable bounds, or property is not a valid string.
	 */
	static int GetEntPropString(int entity, PropType type, const char* propName, char* buffer, int maxLength, int element = 0)
	{
		PushArg(s_GetEntPropStringFunc, entity);
		PushArg(s_GetEntPropStringFunc, type);
		PushArg(s_GetEntPropStringFunc, propName);
		PushArg(s_GetEntPropStringFunc, buffer, maxLength);
		PushArg(s_GetEntPropStringFunc, maxLength);
		PushArg(s_GetEntPropStringFunc, element);
		return ExecFunc(s_GetEntPropStringFunc);
	}

	/**
	 * @brief Sets a network property as a string.
	 *
	 * @param entity        Edict index.
	 * @param type          Property type.
	 * @param propName      Property to use.
	 * @param str           String to set.
	 * @param element       Element # (starting from 0) if property is an array.
	 * @return              Number of non-null bytes written.
	 * @error               Invalid entity, offset out of reasonable bounds, or property is not a valid string.
	 */
	static int SetEntPropString(int entity, PropType type, const char* propName, const char* str, int element = 0)
	{
		return ExecFunc(s_SetEntPropStringFunc, entity, type, propName, str, element);
	}

	/**
	 * @brief Retrieves the count of values that an entity property's array can store.
	 *
	 * @param entity        Entity/edict index.
	 * @param type          Property type.
	 * @param propName      Property name.
	 * @return              Size of array (in elements) or 1 if property is not an array.
	 * @error               Invalid entity or property not found.
	 */
	static int GetEntPropArraySize(int entity, PropType type, const char* propName)
	{
		return ExecFunc(s_GetEntPropArraySizeFunc, entity, type, propName);
	}

	/**
	 * @brief Copies an array of cells from an entity at a given offset.
	 *
	 * @param entity        Entity index.
	 * @param offset        Offset to use.
	 * @param array         Array to read into.
	 * @param arraySize     Number of values to read.
	 * @param dataSize      Size of each value in bytes (1, 2, or 4).
	 * @error               Invalid entity or offset out of reasonable bounds.
	 */
	template<typename any>
	static void GetEntDataArray(int entity, int offset, any arr[], int arraySize, int dataSize = 4)
	{
		for (int i = 0; i < arraySize; i++)
		{
			array[i] = GetEntData(entity, offset + i * dataSize, dataSize);
		}
	}

	/**
	 * @brief Copies an array of cells to an entity at a given offset.
	 *
	 * @param entity        Entity index.
	 * @param offset        Offset to use.
	 * @param array         Array of values to copy.
	 * @param arraySize     Number of values to copy.
	 * @param dataSize      Size of each value in bytes (1, 2, or 4).
	 * @param changeState   True to set the network state as changed; false otherwise.
	 * @error               Invalid entity or offset out of reasonable bounds.
	 */
	template<typename any>
	static void SetEntDataArray(int entity, int offset, const any arr[], int arraySize, int dataSize = 4, bool changeState = false)
	{
		for (int i = 0; i < arraySize; i++)
		{
			SetEntData(entity, offset + i * dataSize, array[i], dataSize, changeState);
		}
	}

	/**
	 * @brief Gets the memory address of an entity.
	 *
	 * @param entity        Entity index.
	 * @return              Address of the entity.
	 * @error               Invalid entity.
	 */
	static Address GetEntityAddress(int entity)
	{
		return ExecFunc(s_GetEntityAddressFunc, entity);
	}

	/**
	 * @brief Retrieves the classname of an entity.
	 * This is like GetEdictClassname(), except it works for ALL
	 * entities, not just edicts.
	 *
	 * @param entity        Index of the entity.
	 * @param className     Buffer to store the classname.
	 * @param maxlength     Maximum length of the buffer.
	 * @return              True on success, false if there is no classname set.
	 */
	static bool GetEntityClassname(int entity, char* className, int maxlength)
	{
		return !!GetEntPropString(entity, Prop_Data, "m_iClassname", className, maxlength);
	}
