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
# include <map>

// opengl includes
# include "X.h"
# include <ctype.h>
# include <regex.h>
# include <math.h>

// lib GML
# include "../glm/glm/glm.hpp"
# include "../glm/glm/gtc/matrix_transform.hpp"

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

#include <ft2build.h>
#include FT_FREETYPE_H

// Defines

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

/*
**	
*/


/*
**	Global 42run struct
*/

typedef struct		s_GameDatas
{
	
}					t_GameDatas;

/*
**	BMP helper struct
*/

typedef struct						s_bmp_texture
{
	// Data read from the header of the BMP file
	unsigned char					header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int					data_pos;     // Position in the file where the actual data begins
	unsigned int					width;
	unsigned int					height;
	unsigned int					image_size;   // = width*height*3
	// Actual RGB data
	unsigned char					*data;
}									t_bmp_texture;

/*
**	Freetype character helper struct.
*/

struct Character {
    GLuint			TextureID;  // ID handle of the glyph texture
    glm::ivec2		Size;       // Size of glyph
    glm::ivec2		Bearing;    // Offset from baseline to left/top of glyph
    GLuint			Advance;    // Offset to advance to next glyph
};


class				GameObject;
class				GameTextObject;
class				GameUIObject;
class				GameEngineController;
class				GamePlayController;
class				GlobalGameController;

# include "GameObject.hpp"
# include "GameTextObject.hpp"
# include "GameUIObject.hpp"
# include "GameEngineController.hpp"
# include "GamePlayController.hpp"
# include "GlobalGameController.hpp"



#endif