#include "../includes/QDrun.hpp"

WorldController::WorldController()
:
WorldSpeed(0.01)
{
	GameSpaceMax_X = 10.0;
	GameSpaceMin_X = -7.0;
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
	GameObject	*Ground = new GameObject("GroundBlock", "./ressources/models/ground_block_1.obj");
	Ground->Position.z = 0.0;
	Ground->Position.x += 0.0;

	GameObject	*Ceiling = new GameObject("GroundBlock", "./ressources/models/ceiling_1.obj");

	GameObject	*WallRight = new GameObject("GroundBlock", "./ressources/models/basic_wall_1.obj");
	WallRight->Rotation.y += 90;
	WallRight->Position.x = GameSpaceMin_X;
	GameObject	*WallLeft = new GameObject("GroundBlock", "./ressources/models/basic_wall_1.obj");
	WallLeft->Rotation.y += 90;
	WallLeft->Position.x = GameSpaceMax_X;

	GameObject	*Desk = new GameObject("Desk", "./ressources/models/table_desk_1.obj");
	Desk->Rotation.y += 90;

	GameObject	*Chair = new GameObject("Chair", "./ressources/models/chair_1.obj");

	WorldObjects.push_back(Ground);
	WorldObjects.push_back(Ceiling);
	WorldObjects.push_back(Desk);
	WorldObjects.push_back(WallRight);
	WorldObjects.push_back(WallLeft);
	WorldObjects.push_back(Chair);

}

void	WorldController::UpdateWorld()
{

}