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
		float				GameSpaceMax_X;
		float				GameSpaceMin_X;

		int					WorldGenDepth; // number of world steps to be generated ahead.
		float				AppearStrength;

		t_bmp_texture		*new_wall_text;


		std::vector<GameObject *>	WorldObjects;

		GameObject			*BackgroundPlane;

		WorldController();
		~WorldController();

		void	SpawnInitialWorld();
		void	UpdateWorld();
		void	RepushObjectsAtFront(GameObject *obj);
	
};

#endif