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
		// ----- Basic World generation variables
		float							WorldSpeed;
		float							GameSpaceMax_X;
		float							GameSpaceMin_X;

		bool							IsMoving;

		int								WorldGenDepth; // number of world steps to be generated ahead.
		float							AppearStrength;

		std::vector<t_bmp_texture *>	WallTexturesVariations;

		GameObject						*BackgroundPlane;

		std::vector<GameObject *>		WorldObjects;

		// ------ Obstacle spawning
		std::vector<GameObject *>		ObstaclesList;
		std::vector<GameObject *>		CoinList;
		bool							SpawnTimerStarted;

		// time points
		int								NbSpawn;
		int								TimeUntilSpawn;
		int								ElapsedSeconds;
		std::chrono::time_point<std::chrono::system_clock>	Start;
		std::chrono::time_point<std::chrono::system_clock>	End;

		GameObject						*SpawnedObject;

		// ------ Coin spawning
		bool							CoinSpawnTimerStarted;

		// time points
		int								CoinTimeUntilSpawn;
		int								CoinElapsedSeconds;
		std::chrono::time_point<std::chrono::system_clock>	CoinStart;
		std::chrono::time_point<std::chrono::system_clock>	CoinEnd;


		WorldController();
		~WorldController();

		void	InitTextureVariations();
		void	InitObstacles();
		void	InitCoins();

		void	SpawnInitialWorld();

		void	ObstacleSpawn();
		void	CoinSpawn();

		void	UpdateWorld();

		void	RepushObjectsAtFront(GameObject *obj);

		void	ResetWorld();

		void	Stop();
		void	Move();


	private:
		t_bmp_texture					*_tmp_texture;
		int								_spawn_i;
	
};

#endif
