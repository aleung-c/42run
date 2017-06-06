#include "../includes/QDrun.hpp"

WorldController::WorldController()
:
	WorldSpeed(DEFAULT_WORLD_SPEED),
	GameSpaceMax_X(DEFAULT_GAMESPACE_MAX_X),
	GameSpaceMin_X(DEFAULT_GAMESPACE_MIN_X),
	WorldGenDepth(DEFAULT_WORLD_GEN_DEPTH),
	SpawnTimerStarted(false),
	TimeUntilSpawn(DEFAULT_SEC_UNTIL_OBSTACLE),
	CoinTimeUntilSpawn(DEFAULT_SEC_UNTIL_COIN)
{
	// GameSpaceMax_X = 11.0;
	// GameSpaceMin_X = -8.0;
	// WorldGenDepth = 6;
	AppearStrength = 0.1;
}

WorldController::~WorldController()
{

}

/*
**	Before using them, we will load the obstacles in memory.
*/

void	WorldController::InitObstacles()
{
	// fallen chair
	ObstaclesList.push_back(new GameObject("Obstacle_chair_1", "./ressources/models/chair_1.obj"));
	ObstaclesList.back()->Transform.Position.y = 1.0;
	// grillage obstacle pillar
	ObstaclesList.push_back(new GameObject("Obstacle_wall_1", "./ressources/models/obstacle_wall_1.obj"));
	// grillage obstacle pillar
	ObstaclesList.push_back(new GameObject("Obstacle_wall_1", "./ressources/models/obstacle_wall_1.obj"));
	// WoodPillar obstacle
	ObstaclesList.push_back(new GameObject("Obstacle_wall_2", "./ressources/models/obstacle_wall_2.obj"));
	// desk 1
	ObstaclesList.push_back(new GameObject("Obstacle_table_desk_1", "./ressources/models/table_desk_1.obj"));
	ObstaclesList.back()->Transform.Position.y = 2.0;
	// desk 1 - second
	ObstaclesList.push_back(new GameObject("Obstacle_table_desk_1", "./ressources/models/table_desk_1.obj"));
	ObstaclesList.back()->Transform.Position.y = 2.0;
	// desk 1 reversed.
	ObstaclesList.push_back(new GameObject("Obstacle_table_desk_1b", "./ressources/models/table_desk_1.obj"));
	ObstaclesList.back()->Transform.Position.y = 2.0;
	ObstaclesList.back()->Transform.Rotation.y = 180.0;
	// long step
	ObstaclesList.push_back(new GameObject("Obstacle_step_1", "./ressources/models/obstacle_step_1.obj"));
		// long step
	ObstaclesList.push_back(new GameObject("Obstacle_step_1", "./ressources/models/obstacle_step_1.obj"));

	for (std::vector<GameObject *>::iterator it = ObstaclesList.begin();
		it != ObstaclesList.end(); it++)
	{
		(*it)->Visible = false;
		(*it)->Transform.Position.z = -15.0;
		(*it)->Transform.Scale = glm::vec3(0.0, 0.0, 0.0);
	}
}

/*
**	Bonus : coins to pick up.
*/

void	WorldController::InitCoins()
{
	CoinList.push_back(new GameObject("Coin", "./ressources/models/coin.obj"));
	CoinList.push_back(new GameObject("Coin", "./ressources/models/coin.obj"));
	for (std::vector<GameObject *>::iterator it = CoinList.begin();
		it != CoinList.end(); it++)
	{
		(*it)->Visible = false;
		(*it)->Transform.Position.z = -15.0;
		(*it)->Transform.Position.y = 2.0;
		(*it)->Transform.Scale = glm::vec3(0.0, 0.0, 0.0);
	}
}

void		WorldController::InitTextureVariations()
{
	// init different wall textures
	tmp_texture = (t_bmp_texture *)malloc(sizeof(t_bmp_texture));
	GameEngineController::LoadTextureFile(tmp_texture, "./ressources/models/basic_wall_1.bmp");
	WallTexturesVariations.push_back(tmp_texture);

	tmp_texture = (t_bmp_texture *)malloc(sizeof(t_bmp_texture));
	GameEngineController::LoadTextureFile(tmp_texture, "./ressources/models/basic_wall_2.bmp");
	WallTexturesVariations.push_back(tmp_texture);

	tmp_texture = (t_bmp_texture *)malloc(sizeof(t_bmp_texture));
	GameEngineController::LoadTextureFile(tmp_texture, "./ressources/models/basic_wall_3.bmp");
	WallTexturesVariations.push_back(tmp_texture);

	tmp_texture = (t_bmp_texture *)malloc(sizeof(t_bmp_texture));
	GameEngineController::LoadTextureFile(tmp_texture, "./ressources/models/basic_wall_4.bmp");
	WallTexturesVariations.push_back(tmp_texture);

	tmp_texture = (t_bmp_texture *)malloc(sizeof(t_bmp_texture));
	GameEngineController::LoadTextureFile(tmp_texture, "./ressources/models/basic_wall_5.bmp");
	WallTexturesVariations.push_back(tmp_texture);
}

/*
**	At first, we want to spawn a base of world before making a continuous
**	world generation.
*/

void	WorldController::SpawnInitialWorld()
{
	float z_pos = 0;

	BackgroundPlane = new GameObject("BG_PLANE", "./ressources/models/background_plane.obj");
	BackgroundPlane->Transform.Position.y = 8.0;
	BackgroundPlane->Transform.Position.z = 90.0;
	BackgroundPlane->Transform.Rotation.y = 90.0;

	// walls generation. one wall has a depth of 16.0
	for (int i = 0; i != WorldGenDepth; i++)
	{
		WorldObjects.push_back(new GameObject("WallRight", "./ressources/models/basic_wall_1.obj"));
		WorldObjects.back()->Transform.Position.x = GameSpaceMin_X;
		WorldObjects.back()->Transform.Position.y = 5;
		WorldObjects.back()->Transform.Position.z = z_pos;
		WorldObjects.push_back(new GameObject("WallLeft", "./ressources/models/basic_wall_1.obj"));
		WorldObjects.back()->Transform.Position.x = GameSpaceMax_X;
		WorldObjects.back()->Transform.Position.y = 5;
		WorldObjects.back()->Transform.Position.z = z_pos;
		z_pos += 16.0;
	}
	// ceiling and ground generation.
	z_pos = 0;
	for (int i = 0; i != (WorldGenDepth / 2); i++)
	{
		WorldObjects.push_back(new GameObject("GroundBlock", "./ressources/models/ground_block_1.obj"));
		WorldObjects.back()->Transform.Position.x = GameSpaceMin_X;
		WorldObjects.back()->Transform.Position.y = -0.25;
		WorldObjects.back()->Transform.Position.z = z_pos;
		WorldObjects.push_back(new GameObject("CeilingBlock", "./ressources/models/ceiling_1.obj"));
		WorldObjects.back()->Transform.Position.x = GameSpaceMax_X;
		WorldObjects.back()->Transform.Position.y = 14;
		WorldObjects.back()->Transform.Position.z = z_pos;
		z_pos += 50.0;
	}
}

/*
**	For this method, ill make a randomized timer that will spawn obstacles at interval.
*/

void	WorldController::ObstacleSpawn()
{
	// set random timer start or reset counter;
	if (SpawnTimerStarted == false)
	{
		SpawnTimerStarted = true;
		Start = std::chrono::system_clock::now();
	}
	if (SpawnTimerStarted)
	{
		// look for timer time's up.
		End = std::chrono::system_clock::now();

		ElapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>
			(End - Start).count();

		if (ElapsedSeconds >= TimeUntilSpawn)
		{
			// spawn new obstacle
			SpawnedObject = ObstaclesList[rand() % (ObstaclesList.size())];
			if (SpawnedObject->Transform.Position.z < -10.0)
			{
				SpawnedObject->Visible = true;
				SpawnedObject->Transform.Position.z = 50.0;
				SpawnedObject->Transform.Position.x = Tools::GetRandomDouble(GameSpaceMin_X, GameSpaceMax_X);

				SpawnedObject->Transform.Scale.x = 0.0;
				SpawnedObject->Transform.Scale.y = 0.0;
				SpawnedObject->Transform.Scale.z = 0.0;
			}
			// reset timer
			SpawnTimerStarted = false;
		}
	}
}

void	WorldController::CoinSpawn()
{
	// set random timer start or reset counter;
	if (CoinSpawnTimerStarted == false)
	{
		CoinSpawnTimerStarted = true;
		CoinStart = std::chrono::system_clock::now();
	}
	if (CoinSpawnTimerStarted)
	{
		// look for timer time's up.
		CoinEnd = std::chrono::system_clock::now();

		CoinElapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>
			(CoinEnd - CoinStart).count();

		if (CoinElapsedSeconds >= CoinTimeUntilSpawn)
		{
			// spawn new obstacle
			SpawnedObject = CoinList[rand() % (CoinList.size())];
			if (SpawnedObject->Transform.Position.z < -10.0)
			{
				SpawnedObject->Visible = true;
				SpawnedObject->Transform.Position.z = 50.0;
				SpawnedObject->Transform.Position.x = Tools::GetRandomDouble(GameSpaceMin_X, GameSpaceMax_X);

				SpawnedObject->Transform.Scale.x = 0.0;
				SpawnedObject->Transform.Scale.y = 0.0;
				SpawnedObject->Transform.Scale.z = 0.0;
			}
			// reset timer
			CoinSpawnTimerStarted = false;
		}
	}
}


void	WorldController::UpdateWorld()
{
	if (IsMoving)
	{
		// spawn obstacles on the field
		ObstacleSpawn();
		CoinSpawn();
		// obstacle move toward player
		for (std::vector<GameObject *>::iterator it = ObstaclesList.begin();
				it != ObstaclesList.end(); it++)
		{
			// soft scale transition for respawned elements clipping.
			if ((*it)->Transform.Scale.x < 1.0)
			{
				(*it)->Transform.Scale.x += AppearStrength;
				(*it)->Transform.Scale.y += AppearStrength;
				(*it)->Transform.Scale.z += AppearStrength;
			}
			(*it)->Transform.Position.z -= WorldSpeed;
		}

		// coin move toward player
		for (std::vector<GameObject *>::iterator it = CoinList.begin();
				it != CoinList.end(); it++)
		{
			// soft scale transition for respawned elements clipping.
			if ((*it)->Transform.Scale.x < 1.0)
			{
				(*it)->Transform.Scale.x += AppearStrength;
				(*it)->Transform.Scale.y += AppearStrength;
				(*it)->Transform.Scale.z += AppearStrength;
			}
			(*it)->Transform.Position.z -= WorldSpeed;
			(*it)->Transform.Rotation.y += 3.0;
		}

		// Operations on every spawned objects.
		for (std::vector<GameObject *>::iterator it = WorldObjects.begin();
				it != WorldObjects.end(); it++)
		{
			// every world object in the list moves toward the player.
			(*it)->Transform.Position.z -= WorldSpeed;

			// soft scale transition for respawned elements clipping.
			if ((*it)->Transform.Scale.x < 1.0)
			{
				(*it)->Transform.Scale.x += AppearStrength;
				(*it)->Transform.Scale.y += AppearStrength;
				(*it)->Transform.Scale.z += AppearStrength;
			}
			RepushObjectsAtFront((*it));
		}
	}
}

/*
**	Stop the world from moving and spawning items.
*/

void	WorldController::Stop()
{
	IsMoving = false;
}

/*
**	Put the world back in motion.
*/

void	WorldController::Move()
{
	IsMoving = true;
}

void	WorldController::RepushObjectsAtFront(GameObject *obj)
{
	// check wall going out of screen.
	if (obj->Name == "WallRight" || obj->Name == "WallLeft")
	{
		if (obj->Transform.Position.z < -16.0)
		{
			obj->Texture.Swap(WallTexturesVariations[rand() % WallTexturesVariations.size()]);
			obj->Transform.Position.z += 16.0 * WorldGenDepth;
			obj->Transform.Scale = glm::vec3(0.0, 0.0, 0.0);
		}
	}

	// check floor-ceiling going out of screen.
	if (obj->Name == "GroundBlock" || obj->Name == "CeilingBlock")
	{
		if (obj->Transform.Position.z < -50.0)
		{
			obj->Transform.Position.z += 50.0 * (WorldGenDepth / 2);
			obj->Transform.Scale = glm::vec3(0.0, 0.0, 0.0);
		}
	}
}
