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
// # include "X.h"
# include <ctype.h>
# include <regex.h>

#include "../aleung-c_engine/includes/aleung-c_engine.hpp"

// // lib GML
// # include "../glm/glm/glm.hpp"
// # include "../glm/glm/gtc/matrix_transform.hpp"

// // linking GLFW
// # include "../glfw-3.2.1/include/GLFW/glfw3.h"

// Linking OpenGL
// # if defined(__APPLE__)
// #  define __gl_h_
// #  define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED
// #  include <OpenGL/gl3.h>
// #  include <OpenGL/gl3ext.h>
// #  include <OpenGL/glu.h>
// #  include <GLUT/glut.h>

// # else
// #  include <GL/gl3.h>
//  // #  include <GL/gl.h>
// #  include <GL/glu.h>
// #  include <GL/glew.h>
// // # endif

// #include <ft2build.h>
// #include FT_FREETYPE_H

// Default Defines

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define WINDOW_NAME "aleung-c's 42run"

// GamePlay variables

# define DEFAULT_WORLD_SPEED 0.2
# define DEFAULT_CHAR_ANIM_SPEED 0.2

# define DEFAULT_GAMESPACE_MAX_X 9.0
# define DEFAULT_GAMESPACE_MIN_X -9.0
# define DEFAULT_WORLD_GEN_DEPTH 6

# define DEFAULT_INVINCIBILITY_TIME 2 // in seconds
# define DEFAULT_GRAVITY_FORCE 0.34
# define DEFAULT_JUMP_FORCE 0.4
# define DEFAULT_MOVE_SPEED 0.2
# define DEFAULT_JUMP_MAX_HEIGHT 4.0
# define DEFAULT_PLAYER_WALLS_OFFSET 2.0

// Gameplay difficulty defines

# define DEFAULT_NB_SPAWN 1
# define DEFAULT_SEC_UNTIL_OBSTACLE 6
# define DEFAULT_SEC_UNTIL_COIN 5

typedef enum		e_GameScene
{
	MAIN_MENU,
	IN_GAME
}					t_GameScene;

typedef struct		s_GameDatas
{
	int				PlayerLife;
	int				PlayerCoins;
	double			Distance;
	int				Score;
	double			CurDistanceStep;
	double			DifficultyStep;

}					t_GameDatas;

class				Tools;
class				UIController;
class				WorldController;
class				CharacterController;
class				GameCollisionController;
class				GamePlayController;
class				GlobalGameController;

# include "Tools.hpp"
# include "UIController.hpp"
# include "WorldController.hpp"
# include "CharacterController.hpp"
# include "GameCollisionController.hpp"
# include "GamePlayController.hpp"
# include "GlobalGameController.hpp"



#endif