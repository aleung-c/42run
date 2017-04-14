#ifndef GLOBALGAMECONTROLLER
# define GLOBALGAMECONTROLLER

# include "QDrun.hpp"

/*
**	Global controller for the game.
**	Will handle all game states, and ultra high level 
**	variables and stuffs.
*/

class GlobalGameController
{
	public:
		GameEngineController	*GameEngine;

		GlobalGameController();
		~GlobalGameController();
	
		void	InitGame();
		void	MainLoop();
};

#endif
