#pragma once

#include <vector>

#include "PublicManager.h"

class DoorManager
{
public:
	static void OpenCellDoors()
	{
		for (int door : sDoors)
			PM::AcceptEntityInput(door, "Open");
	}

	static void CloseCellDoors()
	{
		for (int door : sDoors)
			PM::AcceptEntityInput(door, "Close");
	}

	static void OnMapStart()
	{
		int ent = -1;
		int door = -1;

		while ((ent = PM::FindEntityByClassname(ent, "info_player_terrorist")) != -1)
		{
			float prisoner_pos[3];
			PM::GetEntPropVector(ent, Prop_Data, "m_vecOrigin", prisoner_pos);

			while ((door = PM::FindEntityByClassname(door, "func_door")) != -1)
			{
				float door_pos[3];
				PM::GetEntPropVector(door, Prop_Data, "m_vecOrigin", door_pos);

				if (PM::GetVectorDistance(door_pos, prisoner_pos) <= sMin)
				{
					sMin = PM::GetVectorDistance(door_pos, prisoner_pos);
				}
			}

			while ((door = PM::FindEntityByClassname(door, "func_door_rotating")) != -1)
			{
				float door_pos[3];
				PM::GetEntPropVector(door, Prop_Data, "m_vecOrigin", door_pos);

				if (PM::GetVectorDistance(door_pos, prisoner_pos) <= sMin)
				{
					sMin = PM::GetVectorDistance(door_pos, prisoner_pos);
				}
			}

			while ((door = PM::FindEntityByClassname(door, "func_movelinear")) != -1)
			{
				float door_pos[3];
				PM::GetEntPropVector(door, Prop_Data, "m_vecOrigin", door_pos);

				if (PM::GetVectorDistance(door_pos, prisoner_pos) <= sMin)
				{
					sMin = PM::GetVectorDistance(door_pos, prisoner_pos);
				}
			}

			while ((door = PM::FindEntityByClassname(door, "prop_door_rotating")) != -1)
			{
				float door_pos[3];
				PM::GetEntPropVector(door, Prop_Data, "m_vecOrigin", door_pos);

				if (PM::GetVectorDistance(door_pos, prisoner_pos) <= sMin)
				{
					sMin = PM::GetVectorDistance(door_pos, prisoner_pos);
				}
			}
		}

		sMin += 100.0f;

		while ((ent = PM::FindEntityByClassname(ent, "info_player_terrorist")) != -1)
		{
			float prisoner_pos[3];
			PM::GetEntPropVector(ent, Prop_Data, "m_vecOrigin", prisoner_pos);

			while ((door = PM::FindEntityByClassname(door, "func_door")) != -1)
			{
				float door_pos[3];
				PM::GetEntPropVector(door, Prop_Data, "m_vecOrigin", door_pos);

				if (PM::GetVectorDistance(door_pos, prisoner_pos) <= sMin)
				{
					sDoors.push_back(door);
				}
			}

			while ((door = PM::FindEntityByClassname(door, "func_door_rotating")) != -1)
			{
				float door_pos[3];
				PM::GetEntPropVector(door, Prop_Data, "m_vecOrigin", door_pos);

				if (PM::GetVectorDistance(door_pos, prisoner_pos) <= sMin)
				{
					sDoors.push_back(door);
				}
			}

			while ((door = PM::FindEntityByClassname(door, "func_movelinear")) != -1)
			{
				float door_pos[3];
				PM::GetEntPropVector(door, Prop_Data, "m_vecOrigin", door_pos);

				if (PM::GetVectorDistance(door_pos, prisoner_pos) <= sMin)
				{
					sDoors.push_back(door);
				}
			}

			while ((door = PM::FindEntityByClassname(door, "prop_door_rotating")) != -1)
			{
				float door_pos[3];
				PM::GetEntPropVector(door, Prop_Data, "m_vecOrigin", door_pos);

				if (PM::GetVectorDistance(door_pos, prisoner_pos) <= sMin)
				{
					sDoors.push_back(door);
				}
			}
		}
	}

	static void OnMapEnd()
	{
		sDoors.clear();
	}
private:
	static std::vector<int> sDoors;
	static float sMin;
};
