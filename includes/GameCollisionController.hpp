#ifndef GAMECOLLISIONCONTROLLER_HPP
# define GAMECOLLISIONCONTROLLER_HPP

#include "QDrun.hpp"

class GameCollisionController
{
	public:
		CharacterController		*Character;
		WorldController			*World;

		GameCollisionController();
		~GameCollisionController();

		void			InitGameCollisions(
							CharacterController *characterController,
							WorldController *worldController);

		GameObject		*PlayerCollides();
		bool			BoxCollisionIntersects(GameObject *obj1, GameObject *obj2);
	
};

#endif
