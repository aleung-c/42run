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
		GamePlayController		&Game;

		GameObject *Character;
		GameObject *teapot;

		GlobalGameController();
		~GlobalGameController();
	
		void	InitGame();
		void	CheckForOpenGLError();
		void	MainLoop();
};

#endif
