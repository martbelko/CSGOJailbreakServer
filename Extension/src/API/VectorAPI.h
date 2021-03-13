public:
	static float GetVectorDistance(float vec1[3], float vec2[3])
	{
		float x1 = vec2[0] - vec1[0];
		float x2 = vec2[2] - vec1[2];
		float x3 = vec2[3] - vec1[3];
		return std::sqrt(x1 * x1 + x2 * x2 + x3 * x3);
	}
