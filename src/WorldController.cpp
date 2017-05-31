#include "../includes/QDrun.hpp"

WorldController::WorldController()
:
WorldSpeed(DEFAULT_WORLD_SPEED),
GameSpaceMax_X(DEFAULT_GAMESPACE_MAX_X),
GameSpaceMin_X(DEFAULT_GAMESPACE_MIN_X),
WorldGenDepth(DEFAULT_WORLD_GEN_DEPTH)
{
	GameSpaceMax_X = 11.0;
	GameSpaceMin_X = -8.0;
	WorldGenDepth = 6;
	AppearStrength = 0.1;
}

WorldController::~WorldController()
{

}

/*
**	At first, we want to spawn a base of world before making a continuous
**	world generation.
*/

void	WorldController::SpawnInitialWorld()
{
	float z_pos = 0;

	// walls generation. one wall has a depth of 16.0
	for (int i = 0; i != WorldGenDepth; i++)
	{
		WorldObjects.push_back(new GameObject("WallRight", "./ressources/models/basic_wall_1.obj"));
		WorldObjects.back()->Transform.Rotation.y += 90;
		WorldObjects.back()->Transform.Position.x = GameSpaceMin_X;
		WorldObjects.back()->Transform.Position.z = z_pos;
		WorldObjects.push_back(new GameObject("WallLeft", "./ressources/models/basic_wall_1.obj"));
		WorldObjects.back()->Transform.Rotation.y += 90;
		WorldObjects.back()->Transform.Position.x = GameSpaceMax_X;
		WorldObjects.back()->Transform.Position.z = z_pos;
		z_pos += 16.0;
	}
	// ceiling and ground generation.
	z_pos = 0;
	for (int i = 0; i != WorldGenDepth / 2; i++)
	{
		WorldObjects.push_back(new GameObject("GroundBlock", "./ressources/models/ground_block_1.obj"));
		WorldObjects.back()->Transform.Rotation.y += 90;
		WorldObjects.back()->Transform.Position.x = GameSpaceMin_X;
		WorldObjects.back()->Transform.Position.z = z_pos;
		WorldObjects.push_back(new GameObject("CeilingBlock", "./ressources/models/ceiling_1.obj"));
		WorldObjects.back()->Transform.Rotation.y += 90;
		WorldObjects.back()->Transform.Position.x = GameSpaceMax_X;
		WorldObjects.back()->Transform.Position.z = z_pos;
		z_pos += 100.0;
	}
	new_wall_text = (t_bmp_texture *)malloc(sizeof(t_bmp_texture));
	GameEngineController::LoadTextureFile(new_wall_text, "./ressources/BasicWall.bmp");
}

void	WorldController::UpdateWorld()
{
	for (std::vector<GameObject *>::iterator it = WorldObjects.begin(); it != WorldObjects.end(); it++)
	{
		// soft scale transition for respawned elements clipping.
		(*it)->Transform.Position.z -= WorldSpeed;
		if ((*it)->Transform.Scale.x < 1.0)
		{
			(*it)->Transform.Scale.x += AppearStrength;
			(*it)->Transform.Scale.y += AppearStrength;
			(*it)->Transform.Scale.z += AppearStrength;
		}
		// check wall going out of screen.
		if ((*it)->Name == "WallRight" || (*it)->Name == "WallLeft")
		{
			if ((*it)->Transform.Position.z < -10.0)
			{
				(*it)->Texture.Swap(new_wall_text);
				(*it)->Transform.Position.z += 16.0 * WorldGenDepth;
				(*it)->Transform.Scale = glm::vec3(0.0, 0.0, 0.0);
			}
		}
	}
}
