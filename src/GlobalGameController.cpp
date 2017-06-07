#include "../includes/QDrun.hpp"

/*
**	The main Controller for the 42run.
**	Can also be seen as "minimum code for the aleung-c engine".
*/

GlobalGameController::GlobalGameController() : Game(GamePlayController::Instance())
{

}

GlobalGameController::~GlobalGameController()
{

}

/*
**	This method will init all required variables and classes
**	for the control of the game.
*/

void	GlobalGameController::InitGame()
{
	GameEngine->InitEngine(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	glfwSetKeyCallback(GameEngine->Window, &GamePlayController::KeyCallback);
	Game.InitGame();
}

/*
**	The main loop for our game, linking our gameplay
**	and the visual engine.
*/

void	GlobalGameController::MainLoop()
{	
	GameEngine->CheckForOpenGLErrors();
	while (!glfwWindowShouldClose(GameEngine->Window))
	{
		glfwPollEvents();
		// catch events
		Game.Update();
		GameEngine->Draw();
		Game.LateUpdate();
	}
}
