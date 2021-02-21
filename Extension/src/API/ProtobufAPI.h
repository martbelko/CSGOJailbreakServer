public:
	/**
	 * @brief Reads an int32, uint32, sint32, fixed32, sfixed32, or enum value from a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param index         Index into repeated field.
	 * @return              Integer value read.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static int PbReadInt(Handle pb, const char* field, int index = PB_FIELD_NOT_REPEATED)
	{
		return ExecFunc(s_PbReadIntFunc, pb, field, index);
	}

	/**
	 * @brief Reads a float or downcasted double from a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param index         Index into repeated field.
	 * @return              Float value read.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static float PbReadFloat(Handle pb, const char* field, int index = PB_FIELD_NOT_REPEATED)
	{
		return ExecFunc(s_PbReadFloatFunc, pb, field, index);
	}

	/**
	 * @brief Reads a bool from a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param index         Index into repeated field.
	 * @return              Boolean value read.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static bool PbReadBool(Handle pb, const char* field, int index = PB_FIELD_NOT_REPEATED)
	{
		return ExecFunc(s_PbReadBoolFunc, pb, field, index);
	}

	/**
	 * @brief Reads a string from a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param buffer        Destination string buffer.
	 * @param maxlength     Maximum length of output string buffer.
	 * @param index         Index into repeated field.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbReadString(Handle pb, const char* field, char* buffer, int maxlength, int index = PB_FIELD_NOT_REPEATED)
	{
		PushArg(s_PbReadStringFunc, pb);
		PushArg(s_PbReadStringFunc, field);
		PushArg(s_PbReadStringFunc, buffer, maxlength);
		PushArg(s_PbReadStringFunc, maxlength);
		PushArg(s_PbReadStringFunc, index);
		ExecFunc(s_PbReadStringFunc);
	}

	/**
	 * @brief Reads an RGBA color value from a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param buffer        Destination color buffer.
	 * @param index         Index into repeated field.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbReadColor(Handle pb, const char* field, int buffer[4], int index = PB_FIELD_NOT_REPEATED)
	{
		PushArg(s_PbReadColorFunc, pb);
		PushArg(s_PbReadColorFunc, field);
		PushArg(s_PbReadColorFunc, buffer, 4);
		PushArg(s_PbReadColorFunc, index);
		ExecFunc(s_PbReadColorFunc);
	}

	/**
	 * @brief Reads an XYZ angle value from a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param buffer        Destination angle buffer.
	 * @param index         Index into repeated field.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbReadAngle(Handle pb, const char* field, float buffer[3], int index = PB_FIELD_NOT_REPEATED)
	{
		PushArg(s_PbReadAngleFunc, pb);
		PushArg(s_PbReadAngleFunc, field);
		PushArg(s_PbReadAngleFunc, buffer, 3);
		PushArg(s_PbReadAngleFunc, index);
		ExecFunc(s_PbReadAngleFunc);
	}

	/**
	 * @brief Reads an XYZ vector value from a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param buffer        Destination vector buffer.
	 * @param index         Index into repeated field.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbReadVector(Handle pb, const char* field, float buffer[3], int index = PB_FIELD_NOT_REPEATED)
	{
		PushArg(s_PbReadVectorFunc, pb);
		PushArg(s_PbReadVectorFunc, field);
		PushArg(s_PbReadVectorFunc, buffer, 3);
		PushArg(s_PbReadVectorFunc, index);
		ExecFunc(s_PbReadVectorFunc);
	}

	/**
	 * @brief Reads an XY vector value from a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param buffer        Destination vector buffer.
	 * @param index         Index into repeated field.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbReadVector2D(Handle pb, const char* field, float buffer[2], int index = PB_FIELD_NOT_REPEATED)
	{
		PushArg(s_PbReadVector2DFunc, pb);
		PushArg(s_PbReadVector2DFunc, field);
		PushArg(s_PbReadVector2DFunc, buffer, 2);
		PushArg(s_PbReadVector2DFunc, index);
		ExecFunc(s_PbReadVector2DFunc);
	}

	/**
	 * @brief Gets the number of elements in a repeated field of a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @return              Number of elements in the field.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static int PbGetRepeatedFieldCount(Handle pb, const char* field)
	{
		return ExecFunc(s_PbGetRepeatedFieldCountFunc, pb, field);
	}

	/**
	 * @brief Sets an int32, uint32, sint32, fixed32, sfixed32, or enum value on a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param value         Integer value to set.
	 * @param index         Index into repeated field.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbSetInt(Handle pb, const char* field, int value, int index = PB_FIELD_NOT_REPEATED)
	{
		ExecFunc(s_PbSetIntFunc, pb, field, value, index);
	}

	/**
	 * @brief Sets a float or double on a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param value         Float value to set.
	 * @param index         Index into repeated field.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbSetFloat(Handle pb, const char* field, float value, int index = PB_FIELD_NOT_REPEATED)
	{
		ExecFunc(s_PbSetFloatFunc, pb, field, value, index);
	}

	/**
	 * @brief Sets a bool on a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param value         Boolean value to set.
	 * @param index         Index into repeated field.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbSetBool(Handle pb, const char* field, bool value, int index = PB_FIELD_NOT_REPEATED)
	{
		ExecFunc(s_PbSetBoolFunc, pb, field, value, index);
	}

	/**
	 * @brief Sets a string on a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param value         String value to set.
	 * @param index         Index into repeated field.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbSetString(Handle pb, const char* field, const char* value, int index = PB_FIELD_NOT_REPEATED)
	{
		ExecFunc(s_PbSetStringFunc, pb, field, value, index);
	}

	/**
	 * @brief Sets an RGBA color on a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param color         Color value to set.
	 * @param index         Index into repeated field.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbSetColor(Handle pb, const char* field, const int color[4], int index = PB_FIELD_NOT_REPEATED)
	{
		PushArg(s_PbSetColorFunc, pb);
		PushArg(s_PbSetColorFunc, field);
		PushArg(s_PbSetColorFunc, color, 4);
		PushArg(s_PbSetColorFunc, index);
		ExecFunc(s_PbSetColorFunc);
	}

	/**
	 * @brief Sets an XYZ angle on a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param angle         Angle value to set.
	 * @param index         Index into repeated field.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbSetAngle(Handle pb, const char* field, const float angle[3], int index = PB_FIELD_NOT_REPEATED)
	{
		PushArg(s_PbSetAngleFunc, pb);
		PushArg(s_PbSetAngleFunc, field);
		PushArg(s_PbSetAngleFunc, angle, 3);
		PushArg(s_PbSetAngleFunc, index);
		ExecFunc(s_PbSetAngleFunc);
	}

	/**
	 * @brief Sets an XYZ vector on a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param vec           Vector value to set.
	 * @param index         Index into repeated field.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbSetVector(Handle pb, const char* field, const float vec[3], int index = PB_FIELD_NOT_REPEATED)
	{
		PushArg(s_PbSetVectorFunc, pb);
		PushArg(s_PbSetVectorFunc, field);
		PushArg(s_PbSetVectorFunc, vec, 3);
		PushArg(s_PbSetVectorFunc, index);
		ExecFunc(s_PbSetVectorFunc);
	}

	/**
	 * @brief Sets an XY vector on a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param vec           Vector value to set.
	 * @param index         Index into repeated field.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbSetVector2D(Handle pb, const char* field, const float vec[2], int index = PB_FIELD_NOT_REPEATED)
	{
		PushArg(s_PbSetVector2DFunc, pb);
		PushArg(s_PbSetVector2DFunc, field);
		PushArg(s_PbSetVector2DFunc, vec, 2);
		PushArg(s_PbSetVector2DFunc, index);
		ExecFunc(s_PbSetVector2DFunc);
	}

	/**
	 * @brief Add an int32, uint32, sint32, fixed32, sfixed32, or enum value to a protobuf message repeated field.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param value         Integer value to add.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbAddInt(Handle pb, const char* field, int value)
	{
		ExecFunc(s_PbAddIntFunc, pb, field, value);
	}

	/**
	 * @brief Add a float or double to a protobuf message repeated field.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param value         Float value to add.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbAddFloat(Handle pb, const char* field, float value)
	{
		ExecFunc(s_PbAddFloatFunc, pb, field, value);
	}

	/**
	 * @brief Add a bool to a protobuf message repeated field.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param value         Boolean value to add.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbAddBool(Handle pb, const char* field, bool value)
	{
		ExecFunc(s_PbAddBoolFunc, pb, field, value);
	}

	/**
	 * @brief Add a string to a protobuf message repeated field.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param value         String value to add.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbAddString(Handle pb, const char* field, const char* value)
	{
		ExecFunc(s_PbAddStringFunc, pb, field, value);
	}

	/**
	 * @brief Add an RGBA color to a protobuf message repeated field.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param color         Color value to add.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbAddColor(Handle pb, const char* field, const int color[4])
	{
		PushArg(s_PbAddColorFunc, pb);
		PushArg(s_PbAddColorFunc, field);
		PushArg(s_PbAddColorFunc, color, 4);
		ExecFunc(s_PbAddColorFunc);
	}

	/**
	 * @brief Add an XYZ angle to a protobuf message repeated field.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param angle         Angle value to add.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbAddAngle(Handle pb, const char* field, const float angle[3])
	{
		PushArg(s_PbAddAngleFunc, pb);
		PushArg(s_PbAddAngleFunc, field);
		PushArg(s_PbAddAngleFunc, angle, 3);
		ExecFunc(s_PbAddAngleFunc);
	}

	/**
	 * @brief Add an XYZ vector to a protobuf message repeated field.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param vec           Vector value to add.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbAddVector(Handle pb, const char* field, const float vec[3])
	{
		PushArg(s_PbAddVectorFunc, pb);
		PushArg(s_PbAddVectorFunc, field);
		PushArg(s_PbAddVectorFunc, vec, 3);
		ExecFunc(s_PbAddVectorFunc);
	}

	/**
	 * @brief Add an XY vector to a protobuf message repeated field.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param vec           Vector value to add.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbAddVector2D(Handle pb, const char* field, const float vec[2])
	{
		PushArg(s_PbAddVector2DFunc, pb);
		PushArg(s_PbAddVector2DFunc, field);
		PushArg(s_PbAddVector2DFunc, vec, 2);
		ExecFunc(s_PbAddVector2DFunc);
	}

	/**
	 * @brief Removes a value by index from a protobuf message repeated field.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param index         Index into repeated field.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static void PbRemoveRepeatedFieldValue(Handle pb, const char* field, int index)
	{
		ExecFunc(s_PbRemoveRepeatedFieldValueFunc, pb, field, index);
	}

	/**
	 * @brief Retrieve a handle to an embedded protobuf message in a protobuf message.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @return              protobuf handle to embedded message.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static Handle PbReadMessage(Handle pb, const char* field)
	{
		return ExecFunc(s_PbReadMessageFunc, pb, field);
	}

	/**
	 * @brief Retrieve a handle to an embedded protobuf message in a protobuf message repeated field.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @param index         Index in the repeated field.
	 * @return              protobuf handle to embedded message.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static Handle PbReadRepeatedMessage(Handle pb, const char* field, int index)
	{
		return ExecFunc(s_PbReadRepeatedMessageFunc, pb, field, index);
	}

	/**
	 * @brief Adds an embedded protobuf message to a protobuf message repeated field.
	 *
	 * @param pb            protobuf handle.
	 * @param field         Field name.
	 * @return              protobuf handle to added, embedded message.
	 * @error               Invalid or incorrect Handle, non-existent field, or incorrect field type.
	 */
	static Handle PbAddMessage(Handle pb, const char* field)
	{
		return ExecFunc(s_PbAddMessageFunc, pb, field);
	}
