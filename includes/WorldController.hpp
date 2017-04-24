#ifndef WORLDCONTROLLER_HPP
# define WORLDCONTROLLER_HPP

# include "QDrun.hpp"

/*
**	This is the class that will spawn world elements, and make them move
**	at each loop turn;
**	It will maintain a list of world elements, as well as a list of
**	world obstacles that must be jumped or dodged.
*/

class WorldController
{
	public:
		float				WorldSpeed;

		std::vector<GameObject *>	WorldObjects;

		WorldController();
		~WorldController();

		void	SpawnInitialWorld();
		void	UpdateWorld();
	
};

#endif