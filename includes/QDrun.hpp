/*
**	Global 42run hpp
*/

#ifndef QDRUN_HPP
# define QDRUN_HPP

// color in text;
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KRESET "\x1B[0m"

// General includes
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <iterator>
# include <cstdlib>
# include <iostream>
# include <fstream>
# include <sstream>
# include <fcntl.h>
# include <list>
# include <vector>
# include <string>
# include <queue> 
# include <regex>
# include <random>
# include <algorithm>
# include <math.h>

// opengl includes
# include "X.h"
# include <ctype.h>
# include <regex.h>
# include <math.h>

// lib GML
# include "../glm/glm/glm.hpp"

// linking GLFW
# include "../glfw-3.2.1/include/GLFW/glfw3.h"

// Linking OpenGL
# if defined(__APPLE__)
#  define __gl_h_
#  define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
#  include <OpenGL/gl3.h>
#  include <OpenGL/gl3ext.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>

# else
#  include <GL/gl3.h>
 // #  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glew.h>
# endif

// Defines

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

/*
**	Global 42run struct
*/

typedef struct		s_GameDatas
{
	
}					t_GameDatas;

class				GameObject;
class				GameEngineController;
class				GlobalGameController;

# include "GameObject.hpp"
# include "GameEngineController.hpp"
# include "GlobalGameController.hpp"



#endif