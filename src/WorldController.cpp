#include "../includes/QDrun.hpp"

WorldController::WorldController()
:
WorldSpeed(0.01)
{

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

	GameObject	*Desk = new GameObject("Desk", "./ressources/models/table_desk_1.obj");
	Desk->Rotation.y += 90;
	WorldObjects.push_back(Ground);
	WorldObjects.push_back(Desk);
}

void	WorldController::UpdateWorld()
{
	WorldObjects[1]->Rotation.y -= 1.0;

}