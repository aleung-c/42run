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
	GameEngine.InitEngine();
}

void	GlobalGameController::MainLoop()
{
	const char* vertex_shader =
		"#version 400\n"
		"in vec4 vp;"
		"void main() {"
		"  gl_Position = vec4(vp);"
		"}";

	const char* fragment_shader =
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main() {"
		"  frag_colour = vec4(1.0, 1.0, 1.0, 1.0);"
		"}";

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	// -------------------------------------------------------------------------- //
	//	Error checking															  //
	// -------------------------------------------------------------------------- //
	// check if shader is compiled and linked;
	GLint isLinked = 0;
	glGetProgramiv(shader_programme, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		printf("Error: Shader programme NOT linked\n");
	}
	else
	{
		printf("Shader programme linked\n");
	}

	// check for opengl errors.
	GLenum err = GL_NO_ERROR;
	while((err = glGetError()) != GL_NO_ERROR)
	{
		printf("OpenGL Error: %u\n", err);
	}
	// -------------------------------------------------------------------------- //
	//	Error checking	--- END													  //
	// -------------------------------------------------------------------------- //

	// -------------------------------------------------------------------------- //
	//	drawing																	  //
	// -------------------------------------------------------------------------- //
	while (!glfwWindowShouldClose(GameEngine.Window))
	{
		// wipe the drawing surface clear
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		// event_process(sc);
		GameEngine.DrawObjects();

		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(GameEngine.Window);
	}
}
