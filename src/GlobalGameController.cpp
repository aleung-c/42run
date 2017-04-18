#include "../includes/QDrun.hpp"

GlobalGameController::GlobalGameController()
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
	GameEngine->InitEngine();
	Game.InitGame();
}

void	GlobalGameController::CheckForOpenGLError()
{
	// check if shader is compiled and linked;
	GLint isLinked = 0;
	glGetProgramiv(GameEngine->MainShaderProgramme, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
		printf(KRED "Error: Shader programme NOT linked%s\n", KRESET);
	else
	{
		printf(KGRN "Shader programme linked%s\n", KRESET);
		return ;
	}

	// check for opengl errors.
	GLenum err = GL_NO_ERROR;
	while((err = glGetError()) != GL_NO_ERROR)
	{
		printf(KRED "OpenGL Error: %u%s\n", err, KRESET);
	}
	exit (-1);
}

void	GlobalGameController::MainLoop()
{	
	CheckForOpenGLError();
	while (!glfwWindowShouldClose(GameEngine->Window))
	{
		glfwPollEvents();
		// catch events
		Game.Update();
		GameEngine->Draw();
		Game.LateUpdate();
	}
}
