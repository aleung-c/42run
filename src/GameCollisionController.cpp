# include "../includes/QDrun.hpp"

GameCollisionController::GameCollisionController()
{

}

GameCollisionController::~GameCollisionController()
{

}

void			GameCollisionController::InitGameCollisions(
				CharacterController *characterController,
				WorldController *worldController)
{
	this->Character = characterController;
	this->World = worldController;
}

GameObject		*GameCollisionController::PlayerCollides()
{
	if (!Character || !World)
	{
		std::cout << "Error: set controller before checking for collision" << std::endl;
		return NULL;
	}

	for (std::vector<GameObject *>::iterator it = World->ObstaclesList.begin();
			it != World->ObstaclesList.end(); it++)
	{
		// Check for player - obstacle collisions
		if (BoxCollisionIntersects(Character->CharacterCollider, (*it)))
		{
			return ((*it));
		}
	}
	return (NULL);

}

bool			GameCollisionController::BoxCollisionIntersects(GameObject *obj1, GameObject *obj2)
{
	if (	// X axis AABB
		(obj1->Transform.Position.x + obj1->BoundingBox.Min.x <= obj2->Transform.Position.x + obj2->BoundingBox.Max.x
		&& obj1->Transform.Position.x + obj1->BoundingBox.Max.x >= obj2->Transform.Position.x + obj2->BoundingBox.Min.x)
			// Y axis
		&& (obj1->Transform.Position.y + obj1->BoundingBox.Min.y <= obj2->Transform.Position.y + obj2->BoundingBox.Max.y
		&& obj1->Transform.Position.y + obj1->BoundingBox.Max.y >= obj2->Transform.Position.y + obj2->BoundingBox.Min.y)
			// Z axis
		&& (obj1->Transform.Position.z + obj1->BoundingBox.Min.z <= obj2->Transform.Position.z + obj2->BoundingBox.Max.z
		&& obj1->Transform.Position.z + obj1->BoundingBox.Max.z >= obj2->Transform.Position.z + obj2->BoundingBox.Min.z)
		// (obj1->BoundingBox.Min.x <= obj2->BoundingBox.Max.x
		// && obj1->BoundingBox.Max.x >= obj2->BoundingBox.Min.x)
		// 	// Y axis
		// && (obj1->BoundingBox.Min.y <= obj2->BoundingBox.Max.y
		// && obj1->BoundingBox.Max.y >= obj2->BoundingBox.Min.y)
		// 	// Z axis
		// && (obj1->BoundingBox.Min.z <= obj2->BoundingBox.Max.z
		// && obj1->BoundingBox.Max.z >= obj2->BoundingBox.Min.z)
		)
		{
			return (true);
		}
		return (false);
}
