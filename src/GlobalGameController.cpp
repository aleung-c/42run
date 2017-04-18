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
	int error = 0;

	// check if shader is compiled and linked;
	GLint isLinked = 0;
	glGetProgramiv(GameEngine->MainShaderProgramme, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		printf(KRED "Error: Main Shader programme NOT linked%s\n", KRESET);
		error = -1;
	}
	else
	{
		printf(KGRN "Main Shader programme linked%s\n", KRESET);
	}

	// check if shader is compiled and linked;
	isLinked = 0;
	glGetProgramiv(GameEngine->TextShaderProgramme, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		printf(KRED "Error: Text Shader programme NOT linked%s\n", KRESET);
		error = -1;
	}
	else
	{
		printf(KGRN "Text Shader programme linked%s\n", KRESET);
	}
	if (error == 0)
	{
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
