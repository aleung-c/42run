/*
**	Global 42run hpp
*/

#ifndef QDRUN_HPP
# define QDRUN_HPP


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

// linking GLFW
# include "../glfw-3.2.1/include/GLFW/glfw3.h"

class GlobalGameController;

# include "GlobalGameController.hpp"

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

#endif