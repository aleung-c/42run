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
	if (InitGLFW() == -1
		|| InitOpenGL() == -1
		|| InitFreeType() == -1)
	{
		std::cout << "Initialization error. Exiting..." << std::endl;
		exit (-1);
	}
	
	LoadShaders();
	LoadMatrices();
}


// --------------------------------------------------------------------	//
//																		//
//	Library inits														//
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

	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	glewInit();
#endif
	return (0);
}

int		GameEngineController::InitFreeType()
{
	if (FT_Init_FreeType(&FT_Lib))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return (-1);
	}
	// Get one font
	int error = FT_New_Face(FT_Lib,
				"./ressources/fonts/Roboto_Condensed/RobotoCondensed-Regular.ttf", 0, &Face);
	if (error == FT_Err_Unknown_File_Format)
	{
		std::cout << KRED "FreeType init: Font format not supported" KRESET << std::endl;
		return (-1);
	}
	else if (error)
	{
		std::cout << KRED "FreeType init: Cant open or read font file." KRESET << std::endl;
		return (-1);
	}
	FT_Set_Pixel_Sizes(Face, 0, 48);
	LoadFreeTypesCharacters();
	return (0);
}

/*
**	In here, we stock asciis first 128 characters from truetype font into a map
**	that we will use to draw our letters.
*/

void	GameEngineController::LoadFreeTypesCharacters()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(Face, c, FT_LOAD_RENDER))
		{
		std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint	texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
			Face->glyph->bitmap.width,
			Face->glyph->bitmap.rows,
			0, GL_RED, GL_UNSIGNED_BYTE, Face->glyph->bitmap.buffer);

		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		 // Now store character for later use
		Character character = {
			texture, 
			glm::ivec2(Face->glyph->bitmap.width, Face->glyph->bitmap.rows),
			glm::ivec2(Face->glyph->bitmap_left, Face->glyph->bitmap_top),
			Face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}
	FT_Done_Face(Face);
	FT_Done_FreeType(FT_Lib);
}

// --------------------------------------------------------------------	//
//																		//
//	Shaders inits														//
//																		//
// --------------------------------------------------------------------	//

void GameEngineController::LoadShaders()
{
	// -------------------------------------------------------------------------- //
	//	3d model Shaders -> main shader											  //
	// -------------------------------------------------------------------------- //
	// Go get Position shader
	VertexShader_1 = GetFileContent("./shaders/vshader_1.vs");
	FragmentShader_1 = GetFileContent("./shaders/fshader_1.fs");

	// Create shader programme
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, (const char * const *)&VertexShader_1, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, (const char * const *)&FragmentShader_1, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram ();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram (shader_programme);
	MainShaderProgramme = shader_programme;

	// -------------------------------------------------------------------------- //
	//	Text Shaders															  //
	// -------------------------------------------------------------------------- //
	TextVShader = GetFileContent("./shaders/text_vshader_1.vs");
	TextFShader = GetFileContent("./shaders/text_fshader_1.fs");

	// Create shader programme
	GLuint vs2 = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs2, 1, (const char * const *)&TextVShader, NULL);
	glCompileShader(vs2);
	GLuint fs2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs2, 1, (const char * const *)&TextFShader, NULL);
	glCompileShader(fs2);

	GLuint shader_programme2 = glCreateProgram ();
	glAttachShader(shader_programme2, fs2);
	glAttachShader(shader_programme2, vs2);
	glLinkProgram (shader_programme2);
	TextShaderProgramme = shader_programme2;
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

	MatOrthographicProjection = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT);
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
//	Textures															//
//	Handle the per object texturing										//
//																		//
// --------------------------------------------------------------------	//
/*
**	We will say that each object only has one texture...
*/

void	GameEngineController::LoadObjectTexture(GameObject *Object)
{
	GLuint			uniform_mat;

	// we will only activate the number 0 texture. it may go up to 32 on newest graphic cards.
	// mobile devices usually have only 2.
	glActiveTexture(GL_TEXTURE0);

	// "Bind" the object's texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, Object->GetTextureID());

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Object->GetTexture().width, Object->GetTexture().height, 0,
		GL_BGR, GL_UNSIGNED_BYTE, Object->GetTexture().data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// bind texture to fragment shader uniform sampler2D
	uniform_mat = glGetUniformLocation(MainShaderProgramme, "texture_0");
	glUniform1i(uniform_mat, 0);

	// set fshader bool to true -> there is a texture loaded.
	glUniform1i(glGetUniformLocation(MainShaderProgramme, "has_texture"), GL_TRUE);
}

// --------------------------------------------------------------------	//
//																		//
//	Text																//
//	Handle displaying of GameTextObjects								//
//																		//
// --------------------------------------------------------------------	//

void	GameEngineController::RenderText(GameTextObject *obj)
{
	GLint uniform_mat = glGetUniformLocation(TextShaderProgramme, "projection_matrix");
	if (uniform_mat != -1)
	{
		glUniformMatrix4fv(uniform_mat, 1, GL_FALSE, &MatOrthographicProjection[0][0]);
	}
	
	glUniform3f(glGetUniformLocation(TextShaderProgramme, "textColor"),
		obj->Color.x, obj->Color.y, obj->Color.z);
	// glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(obj->GetVao());

	int tmp_x = obj->Position.x;
	int tmp_y = obj->Position.y;

	// Iterate through all characters
	std::string::const_iterator c;
	for (c = obj->Text.begin(); c != obj->Text.end(); c++)
	{
		Character ch = Characters[*c]; // take the struct in the map.

		GLfloat xpos = tmp_x + ch.Bearing.x * obj->Scale;
		GLfloat ypos = tmp_y - (ch.Size.y - ch.Bearing.y) * obj->Scale;

		GLfloat w = ch.Size.x * obj->Scale;
		GLfloat h = ch.Size.y * obj->Scale;
		// Update VBO for each character
		// That is two triangles forming a quad.
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// (void)vertices;
		glActiveTexture(GL_TEXTURE0);
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// GLuint uniform_mat = glGetUniformLocation(TextShaderProgramme, "text");
		// glUniform1i(uniform_mat, 0);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, obj->GetVbo());
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		// glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, &vertices[0][0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
		// glBindBuffer(GL_ARRAY_BUFFER, 0);
	// 	// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
	// 	// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		tmp_x += (ch.Advance >> 6) * obj->Scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	// glBindVertexArray(0);
	// glBindTexture(GL_TEXTURE_2D, 0);
	glDisableVertexAttribArray(0);
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

void	GameEngineController::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawTextObjects();
	Draw3DModels();

	// display on screen.
	glfwSwapBuffers(Window);
}

/*
** Run through and display each GameTextObject and render the text.
*/

void	GameEngineController::DrawTextObjects()
{
	glUseProgram(TextShaderProgramme);
	for (std::vector<GameTextObject *>::iterator it = GameTextObjectList.begin();
		it != GameTextObjectList.end();
		it++)
	{
		RenderText(*it);
	}
}

/*
** Run through and display each GameObject that has a model/texture.
*/

void	GameEngineController::Draw3DModels()
{
	glUseProgram(MainShaderProgramme);
	// draw 3d objects
	// run through each object to set their matrices and textures and draw them on screen.
	for (std::vector<GameObject *>::iterator it = GameObjectList.begin();
		it != GameObjectList.end();
		it++)
	{
		// texture loading.
		if ((*it)->HasTexture == true)
			LoadObjectTexture(*it);
		else
			glUniform1i(glGetUniformLocation(MainShaderProgramme, "has_texture"), GL_FALSE);
		// opengl buffer loading.
		if ((*it)->HasModel == true)
		{
			ApplyMatricesToObject(*it);
			(*it)->DrawObject();
		}
	}
}
