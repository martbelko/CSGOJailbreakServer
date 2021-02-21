public:
	/**
	 * @brief Sets up a sparks effect.
	 *
	 * @param pos           Position of the sparks.
	 * @param dir           Direction of the sparks.
	 * @param Magnitude     Sparks size.
	 * @param TrailLength   Trail lenght of the sparks.
	 */
	static void TE_SetupSparks(const float pos[3], const float dir[3], int Magnitude, int TrailLength)
	{
		TE_Start("Sparks");
		TE_WriteVector("m_vecOrigin[0]", pos);
		TE_WriteVector("m_vecDir", dir);
		TE_WriteNum("m_nMagnitude", Magnitude);
		TE_WriteNum("m_nTrailLength", TrailLength);
	}

	/**
	 * @brief Sets up a smoke effect.
	 *
	 * @param pos           Position of the smoke.
	 * @param Model         Precached model index.
	 * @param Scale         Scale of the smoke.
	 * @param FrameRate     Frame rate of the smoke.
	 */
	static void TE_SetupSmoke(const float pos[3], int Model, float Scale, int FrameRate)
	{
		TE_Start("Smoke");
		TE_WriteVector("m_vecOrigin", pos);
		TE_WriteNum("m_nModelIndex", Model);
		TE_WriteFloat("m_fScale", Scale);
		TE_WriteNum("m_nFrameRate", FrameRate);
	}

	/**
	 * @brief Sets up a dust cloud effect.
	 *
	 * @param pos           Position of the dust.
	 * @param dir           Direction of the dust.
	 * @param Size          Dust cloud size.
	 * @param Speed         Dust cloud speed.
	 */
	static void TE_SetupDust(const float pos[3], const float dir[3], float Size, float Speed)
	{
		TE_Start("Dust");
		TE_WriteVector("m_vecOrigin[0]", pos);
		TE_WriteVector("m_vecDirection", dir);
		TE_WriteFloat("m_flSize", Size);
		TE_WriteFloat("m_flSpeed", Speed);
	}

	/**
	 * @brief Sets up a muzzle flash effect.
	 *
	 * @param pos           Position of the muzzle flash.
	 * @param angles        Rotation angles of the muzzle flash.
	 * @param Scale         Scale of the muzzle flash.
	 * @param Type          Muzzle flash type to render (Mod specific).
	 */
	static void TE_SetupMuzzleFlash(const float pos[3], const float angles[3], float Scale, int Type)
	{
		TE_Start("MuzzleFlash");
		TE_WriteVector("m_vecOrigin", pos);
		TE_WriteVector("m_vecAngles", angles);
		TE_WriteFloat("m_flScale", Scale);
		TE_WriteNum("m_nType", Type);
	}

	/**
	 * @brief Sets up a metal sparks effect.
	 *
	 * @param pos           Position of the metal sparks.
	 * @param dir           Direction of the metal sparks.
	 */
	static void TE_SetupMetalSparks(const float pos[3], const float dir[3])
	{
		TE_Start("Metal Sparks");
		TE_WriteVector("m_vecPos", pos);
		TE_WriteVector("m_vecDir", dir);
	}

	/**
	 * @brief Sets up an energy splash effect.
	 *
	 * @param pos           Position of the energy splash.
	 * @param dir           Direction of the energy splash.
	 * @param Explosive     Makes the effect explosive.
	 */
	static void TE_SetupEnergySplash(const float pos[3], const float dir[3], bool Explosive)
	{
		TE_Start("Energy Splash");
		TE_WriteVector("m_vecPos", pos);
		TE_WriteVector("m_vecDir", dir);
		TE_WriteNum("m_bExplosive", Explosive);
	}

	/**
	 * @brief Sets up an armor ricochet effect.
	 *
	 * @param pos           Position of the armor ricochet.
	 * @param dir           Direction of the armor ricochet.
	 */
	static void TE_SetupArmorRicochet(const float pos[3], const float dir[3])
	{
		TE_Start("Armor Ricochet");
		TE_WriteVector("m_vecPos", pos);
		TE_WriteVector("m_vecDir", dir);
	}

	/**
	 * @brief Sets up a glowing sprite effect.
	 *
	 * @param pos           Position of the sprite.
	 * @param Model         Precached model index.
	 * @param Life          Time duration of the sprite.
	 * @param Size          Sprite size.
	 * @param Brightness    Sprite brightness.
	 */
	static void TE_SetupGlowSprite(const float pos[3], int Model, float Life, float Size, int Brightness)
	{
		TE_Start("GlowSprite");
		TE_WriteVector("m_vecOrigin", pos);
		TE_WriteNum("m_nModelIndex", Model);
		TE_WriteFloat("m_fScale", Size);
		TE_WriteFloat("m_fLife", Life);
		TE_WriteNum("m_nBrightness", Brightness);
	}

	/**
	 * @brief Sets up a explosion effect.
	 *
	 * @param pos           Explosion position.
	 * @param Model         Precached model index.
	 * @param Scale         Explosion scale.
	 * @param Framerate     Explosion frame rate.
	 * @param Flags         Explosion flags.
	 * @param Radius        Explosion radius.
	 * @param Magnitude     Explosion size.
	 * @param normal        Normal vector to the explosion.
	 * @param MaterialType  Exploded material type.
	 */
	static void TE_SetupExplosion(const float pos[3], int Model, float Scale, int Framerate, int Flags, int Radius, int Magnitude, const float normal[3] = nullptr, int MaterialType = 'C')
	{
		TE_Start("Explosion");
		TE_WriteVector("m_vecOrigin[0]", pos);
		if (normal)
			TE_WriteVector("m_vecNormal", normal);
		else
			TE_WriteNum("m_vecNormal", NULL_VECTOR);

		TE_WriteNum("m_nModelIndex", Model);
		TE_WriteFloat("m_fScale", Scale);
		TE_WriteNum("m_nFrameRate", Framerate);
		TE_WriteNum("m_nFlags", Flags);
		TE_WriteNum("m_nRadius", Radius);
		TE_WriteNum("m_nMagnitude", Magnitude);
		TE_WriteNum("m_chMaterialType", MaterialType);
	}

	/**
	 * @brief Sets up a blood sprite effect.
	 *
	 * @param pos             Position of the sprite.
	 * @param dir             Sprite direction.
	 * @param color           Color array (r, g, b, a).
	 * @param Size            Sprite size.
	 * @param SprayModel      Precached model index.
	 * @param BloodDropModel  Precached model index.
	 */
	static void TE_SetupBloodSprite(const float pos[3], const float dir[3], const int color[4], int Size, int SprayModel, int BloodDropModel)
	{
		TE_Start("Blood Sprite");
		TE_WriteVector("m_vecOrigin", pos);
		TE_WriteVector("m_vecDirection", dir);
		TE_WriteNum("r", color[0]);
		TE_WriteNum("g", color[1]);
		TE_WriteNum("b", color[2]);
		TE_WriteNum("a", color[3]);
		TE_WriteNum("m_nSize", Size);
		TE_WriteNum("m_nSprayModel", SprayModel);
		TE_WriteNum("m_nDropModel", BloodDropModel);
	}

	/**
	 * @brief Sets up a beam ring point effect.
	 *
	 * @param center        Center position of the ring.
	 * @param Start_Radius  Initial ring radius.
	 * @param End_Radius    Final ring radius.
	 * @param ModelIndex    Precached model index.
	 * @param HaloIndex     Precached model index.
	 * @param StartFrame    Initial frame to render.
	 * @param FrameRate     Ring frame rate.
	 * @param Life          Time duration of the ring.
	 * @param Width         Beam width.
	 * @param Amplitude     Beam amplitude.
	 * @param Color         Color array (r, g, b, a).
	 * @param Speed         Speed of the beam.
	 * @param Flags         Beam flags.
	 */
	static void TE_SetupBeamRingPoint(const float center[3], float Start_Radius, float End_Radius, int ModelIndex, int HaloIndex, int StartFrame,
		int FrameRate, float Life, float Width, float Amplitude, const int Color[4], int Speed, int Flags)
	{
		TE_Start("BeamRingPoint");
		TE_WriteVector("m_vecCenter", center);
		TE_WriteFloat("m_flStartRadius", Start_Radius);
		TE_WriteFloat("m_flEndRadius", End_Radius);
		TE_WriteNum("m_nModelIndex", ModelIndex);
		TE_WriteNum("m_nHaloIndex", HaloIndex);
		TE_WriteNum("m_nStartFrame", StartFrame);
		TE_WriteNum("m_nFrameRate", FrameRate);
		TE_WriteFloat("m_fLife", Life);
		TE_WriteFloat("m_fWidth", Width);
		TE_WriteFloat("m_fEndWidth", Width);
		TE_WriteFloat("m_fAmplitude", Amplitude);
		TE_WriteNum("r", Color[0]);
		TE_WriteNum("g", Color[1]);
		TE_WriteNum("b", Color[2]);
		TE_WriteNum("a", Color[3]);
		TE_WriteNum("m_nSpeed", Speed);
		TE_WriteNum("m_nFlags", Flags);
		TE_WriteNum("m_nFadeLength", 0);
	}

	/**
	 * @brief Sets up a point to point beam effect.
	 *
	 * @param start         Start position of the beam.
	 * @param end           End position of the beam.
	 * @param ModelIndex    Precached model index.
	 * @param HaloIndex     Precached model index.
	 * @param StartFrame    Initial frame to render.
	 * @param FrameRate     Beam frame rate.
	 * @param Life          Time duration of the beam.
	 * @param Width         Initial beam width.
	 * @param EndWidth      Final beam width.
	 * @param FadeLength    Beam fade time duration.
	 * @param Amplitude     Beam amplitude.
	 * @param Color         Color array (r, g, b, a).
	 * @param Speed         Speed of the beam.
	 */
	static void TE_SetupBeamPoints(const float start[3], const float end[3], int ModelIndex, int HaloIndex, int StartFrame, int FrameRate, float Life,
		float Width, float EndWidth, int FadeLength, float Amplitude, const int Color[4], int Speed)
	{
		TE_Start("BeamPoints");
		TE_WriteVector("m_vecStartPoint", start);
		TE_WriteVector("m_vecEndPoint", end);
		TE_WriteNum("m_nModelIndex", ModelIndex);
		TE_WriteNum("m_nHaloIndex", HaloIndex);
		TE_WriteNum("m_nStartFrame", StartFrame);
		TE_WriteNum("m_nFrameRate", FrameRate);
		TE_WriteFloat("m_fLife", Life);
		TE_WriteFloat("m_fWidth", Width);
		TE_WriteFloat("m_fEndWidth", EndWidth);
		TE_WriteFloat("m_fAmplitude", Amplitude);
		TE_WriteNum("r", Color[0]);
		TE_WriteNum("g", Color[1]);
		TE_WriteNum("b", Color[2]);
		TE_WriteNum("a", Color[3]);
		TE_WriteNum("m_nSpeed", Speed);
		TE_WriteNum("m_nFadeLength", FadeLength);
	}

	/**
	 * @brief Sets up an entity to entity laser effect.
	 *
	 * @param StartEntity   Entity index from where the beam starts.
	 * @param EndEntity     Entity index from where the beam ends.
	 * @param ModelIndex    Precached model index.
	 * @param HaloIndex     Precached model index.
	 * @param StartFrame    Initial frame to render.
	 * @param FrameRate     Beam frame rate.
	 * @param Life          Time duration of the beam.
	 * @param Width         Initial beam width.
	 * @param EndWidth      Final beam width.
	 * @param FadeLength    Beam fade time duration.
	 * @param Amplitude     Beam amplitude.
	 * @param Color         Color array (r, g, b, a).
	 * @param Speed         Speed of the beam.
	 */
	static void TE_SetupBeamLaser(int StartEntity, int EndEntity, int ModelIndex, int HaloIndex, int StartFrame, int FrameRate, float Life,
		float Width, float EndWidth, int FadeLength, float Amplitude, const int Color[4], int Speed)
	{
		TE_Start("BeamLaser");
		TE_WriteEncodedEnt("m_nStartEntity", StartEntity);
		TE_WriteEncodedEnt("m_nEndEntity", EndEntity);
		TE_WriteNum("m_nModelIndex", ModelIndex);
		TE_WriteNum("m_nHaloIndex", HaloIndex);
		TE_WriteNum("m_nStartFrame", StartFrame);
		TE_WriteNum("m_nFrameRate", FrameRate);
		TE_WriteFloat("m_fLife", Life);
		TE_WriteFloat("m_fWidth", Width);
		TE_WriteFloat("m_fEndWidth", EndWidth);
		TE_WriteFloat("m_fAmplitude", Amplitude);
		TE_WriteNum("r", Color[0]);
		TE_WriteNum("g", Color[1]);
		TE_WriteNum("b", Color[2]);
		TE_WriteNum("a", Color[3]);
		TE_WriteNum("m_nSpeed", Speed);
		TE_WriteNum("m_nFadeLength", FadeLength);
	}

	/**
	 * @brief Sets up a beam ring effect.
	 *
	 * @param StartEntity   Entity index from where the ring starts.
	 * @param EndEntity     Entity index from where the ring ends.
	 * @param ModelIndex    Precached model index.
	 * @param HaloIndex     Precached model index.
	 * @param StartFrame    Initial frame to render.
	 * @param FrameRate     Ring frame rate.
	 * @param Life          Time duration of the ring.
	 * @param Width         Beam width.
	 * @param Amplitude     Beam amplitude.
	 * @param Color         Color array (r, g, b, a).
	 * @param Speed         Speed of the beam.
	 * @param Flags         Beam flags.
	 */
	static void TE_SetupBeamRing(int StartEntity, int EndEntity, int ModelIndex, int HaloIndex, int StartFrame, int FrameRate, float Life, float Width, float Amplitude, const int Color[4], int Speed, int Flags)
	{
		TE_Start("BeamRing");
		TE_WriteEncodedEnt("m_nStartEntity", StartEntity);
		TE_WriteEncodedEnt("m_nEndEntity", EndEntity);
		TE_WriteNum("m_nModelIndex", ModelIndex);
		TE_WriteNum("m_nHaloIndex", HaloIndex);
		TE_WriteNum("m_nStartFrame", StartFrame);
		TE_WriteNum("m_nFrameRate", FrameRate);
		TE_WriteFloat("m_fLife", Life);
		TE_WriteFloat("m_fWidth", Width);
		TE_WriteFloat("m_fEndWidth", Width);
		TE_WriteFloat("m_fAmplitude", Amplitude);
		TE_WriteNum("r", Color[0]);
		TE_WriteNum("g", Color[1]);
		TE_WriteNum("b", Color[2]);
		TE_WriteNum("a", Color[3]);
		TE_WriteNum("m_nSpeed", Speed);
		TE_WriteNum("m_nFadeLength", 0);
		TE_WriteNum("m_nFlags", Flags);
	}

	/**
	 * @brief Sets up a follow beam effect.
	 *
	 * @param EntIndex      Entity index from where the beam starts.
	 * @param ModelIndex    Precached model index.
	 * @param HaloIndex     Precached model index.
	 * @param Life          Time duration of the beam.
	 * @param Width         Initial beam width.
	 * @param EndWidth      Final beam width.
	 * @param FadeLength    Beam fade time duration.
	 * @param Color         Color array (r, g, b, a).
	 */
	static void TE_SetupBeamFollow(int EntIndex, int ModelIndex, int HaloIndex, float Life, float Width, float EndWidth, int FadeLength, const int Color[4])
	{
		TE_Start("BeamFollow");
		TE_WriteEncodedEnt("m_iEntIndex", EntIndex);
		TE_WriteNum("m_nModelIndex", ModelIndex);
		TE_WriteNum("m_nHaloIndex", HaloIndex);
		TE_WriteNum("m_nStartFrame", 0);
		TE_WriteNum("m_nFrameRate", 0);
		TE_WriteFloat("m_fLife", Life);
		TE_WriteFloat("m_fWidth", Width);
		TE_WriteFloat("m_fEndWidth", EndWidth);
		TE_WriteNum("m_nFadeLength", FadeLength);
		TE_WriteNum("r", Color[0]);
		TE_WriteNum("g", Color[1]);
		TE_WriteNum("b", Color[2]);
		TE_WriteNum("a", Color[3]);
	}
