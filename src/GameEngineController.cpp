#include "../includes/QDrun.hpp"

GameEngineController& GameEngineController::Instance()
{
    return m_instance;
}

GameEngineController::GameEngineController()
{

}

GameEngineController::~GameEngineController()
{

}

void		GameEngineController::InitEngine()
{
	if (InitGLFW() == -1 || InitOpenGL() == -1)
	{
		std::cout << "Initialization error. Exiting..." << std::endl;
		exit (-1);
	}
	//LoadGameObjects();
}


// --------------------------------------------------------------------	//
//																		//
//	GLFW and OPENGL inits												//
//																		//
// --------------------------------------------------------------------	//

int		GameEngineController::InitGLFW()
{
	// start GL context and O/S window using the GLFW helper library
	if (!glfwInit ())
	{
		std::cout << "ERROR: could not start GLFW3" << std::endl;
		return 1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "aleung-c's 42 run", NULL, NULL);
	if (!Window)
	{
		std::cout << "ERROR: could not open window with GLFW3" << std::endl;
		glfwTerminate();
		return (-1);
	}
	// Create context
	glfwMakeContextCurrent (Window);
	return (0);
}


int		GameEngineController::InitOpenGL()
{
	// get version info
	const GLubyte* renderer = glGetString (GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString (GL_VERSION); // version as a string
	std::cout << "Renderer: " << renderer << std::endl;
	std::cout << "OpenGL version supported " << version << std::endl;

	//glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	//glEnable(GL_CULL_FACE);

#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	glewInit();
#endif
	return (0);
}

// --------------------------------------------------------------------	//
//																		//
//	Shaders inits														//
//																		//
// --------------------------------------------------------------------	//

void GameEngineController::LoadShaders()
{
	// -------------------------------------------------------------------------- //
	//	Shaders																	  //
	// -------------------------------------------------------------------------- //
	// Go get Position shader
	VertexShader_1 = GetFileContent("./shaders/easy_vshader_1.vs");
	FragmentShader_1 = GetFileContent("./shaders/easy_fshader_1.fs");

	// Create shader programme
	GLuint vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vs, 1, (const char * const *)&VertexShader_1, NULL);
	glCompileShader (vs);
	GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
	glShaderSource (fs, 1, (const char * const *)&FragmentShader_1, NULL);
	glCompileShader (fs);

	GLuint shader_programme = glCreateProgram ();
	glAttachShader (shader_programme, fs);
	glAttachShader (shader_programme, vs);
	glLinkProgram (shader_programme);
	glUseProgram(shader_programme);
	MainShaderProgramme = shader_programme;
}

char		*GameEngineController::GetFileContent(std::string file_path)
{
	FILE *fp;
	long lsize;
	char *buffer;

	fp = fopen(file_path.c_str(), "rb" );
	if (!fp)
	{
		printf("Error opening file\n");
		exit(-1);
	}

	fseek(fp, 0L, SEEK_END);
	lsize = ftell(fp);
	rewind(fp);

	buffer = (char *)malloc(sizeof(char) * lsize);
	if (!buffer)
	{
		printf("Error allocating vertex shader memory\n");
		exit(-1);
	}

	if (fread(buffer, lsize, 1, fp) != 1)
	{
		fclose(fp);
		free(buffer);
		printf("entire read fails\n");
		exit(1);
	}
	buffer[lsize] = '\0';
	fclose(fp);
	return (buffer);
}

// --------------------------------------------------------------------	//
//																		//
//	Matrices															//
//																		//
// --------------------------------------------------------------------	//

void	GameEngineController::LoadMatrices()
{
	MatModelIdentity = glm::mat4();
}

// --------------------------------------------------------------------	//
//																		//
//	Engine side drawing													//
//																		//
// --------------------------------------------------------------------	//
/*
**	When a GameObject is created, it goes into the GameObjectList, 
**	and the engine will draw it if it has a model.
*/

void	GameEngineController::DrawObjects()
{
	for (std::vector<GameObject *>::iterator it = GameObjectList.begin();
		it != GameObjectList.end();
		it++)
	{
		(*it)->DrawObject();
	}
}