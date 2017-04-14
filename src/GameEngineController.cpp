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
	LoadShaders();
	LoadMatrices();
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
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

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
	VertexShader_1 = GetFileContent("./shaders/vshader_1.vs");
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
//	This creates the usual MODEL - VIEW - PROJECTION					//
//	matrice.															//
//																		//
// --------------------------------------------------------------------	//

/*
**	This method initialize the VIEW and PROJECTION matrices.
**	The MODEL matrice will be set for each object at runtime.
**	Same goes for the merge into the MVP matrice.
*/

void	GameEngineController::LoadMatrices()
{
	// View matrices init;
	MainCamera = new GameObject("MainCamera");
	MainCamera->Position = glm::vec3(0.0, 2.0, 10.0);
	MatView = glm::lookAt(
		MainCamera->Position,
		glm::vec3(0.0, 0.0, 0.0), // regarde l'origine
		glm::vec3(0.0, 2.0, 0.0)  // La tête est vers le haut (utilisez 0,-1,0 pour regarder à l'envers) 
	);

	// Project matrices init;
	CameraNear = 0.1;
	CameraFar = 100.0;
	CameraFov = 90.0;
	CameraAspect = 1.77; // 4/3, 16/9, etc 1 = 4/4
	MatPerspectiveProjection = glm::perspective(CameraFov, CameraAspect, CameraNear, CameraFar);
}

/*
**	For one object of our scene, 
*/

void GameEngineController::ApplyMatricesToObject(GameObject *Object)
{
	// generate model matrice for each GameObject.
	// Identity matrice -> base for our calculations.
	MatModelIdentity = glm::mat4();
	// Translation
	MatModelTranslation = glm::translate(MatModelIdentity, Object->Position);
	// Rotation : x > y > z
	MatModelRotation = glm::rotate(MatModelIdentity, (glm::mediump_float)Object->Rotation.x, glm::vec3(1.0, 0.0, 0.0));
	MatModelRotation = glm::rotate(MatModelRotation, (glm::mediump_float)Object->Rotation.y, glm::vec3(0.0, 1.0, 0.0));
	MatModelRotation = glm::rotate(MatModelRotation, (glm::mediump_float)Object->Rotation.z, glm::vec3(0.0, 0.0, 1.0));
	// Scaling
	MatModelScaling = glm::scale(MatModelIdentity, Object->Scale);

	// Merge MODEL matrice.
	MatModel = MatModelTranslation * MatModelRotation * MatModelScaling;

	// Merge MVP matrice.
	MatMVP = MatPerspectiveProjection * MatView * MatModel;

	// Send it to shader.
	GLint uniform_mat = glGetUniformLocation(MainShaderProgramme, "mvp_matrix");
	if (uniform_mat != -1)
	{
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &MatMVP[0][0]);
	}
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
	glUseProgram(MainShaderProgramme);
	// wipe the drawing surface clear
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// run through each object to set their matrices and draw them on screen.
	for (std::vector<GameObject *>::iterator it = GameObjectList.begin();
		it != GameObjectList.end();
		it++)
	{
		if ((*it)->HasModel == true)
		{
			ApplyMatricesToObject(*it);
			(*it)->DrawObject();
		}
	}
}