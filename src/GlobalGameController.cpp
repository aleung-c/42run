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
	GameEngine->LoadShaders();
	GameObject *Character = new GameObject("Character", "./ressources/teapot.obj");
	if (Character)
	{
		std::cout << "hello char" << std::endl;
	}
}

void	GlobalGameController::MainLoop()
{

	// -------------------------------------------------------------------------- //
	//	Error checking															  //
	// -------------------------------------------------------------------------- //
	// check if shader is compiled and linked;
	GLint isLinked = 0;
	glGetProgramiv(GameEngine->MainShaderProgramme, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
		printf(KRED "Error: Shader programme NOT linked%s\n", KRESET);
	else
		printf(KGRN "Shader programme linked%s\n", KRESET);

	// check for opengl errors.
	GLenum err = GL_NO_ERROR;
	while((err = glGetError()) != GL_NO_ERROR)
	{
		printf(KRED "OpenGL Error: %u%s\n", err, KRESET);
	}
	// -------------------------------------------------------------------------- //
	//	Error checking	--- END													  //
	// -------------------------------------------------------------------------- //

	// -------------------------------------------------------------------------- //
	//	drawing																	  //
	// -------------------------------------------------------------------------- //

	while (!glfwWindowShouldClose(GameEngine->Window))
	{
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(GameEngine->MainShaderProgramme);
		// event_process(sc);
		GameEngine->DrawObjects();

		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(GameEngine->Window);
	}
}
