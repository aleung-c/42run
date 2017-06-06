#---------------------------------------------------#
#													#
#	42run C++ Makefile.								#
#													#
#---------------------------------------------------#

NAME = 42run

SRC = ./src/main.cpp \
./src/Tools.cpp \
./src/UIController.cpp \
./src/WorldController.cpp \
./src/GameCollisionController.cpp \
./src/CharacterController.cpp \
./src/GamePlayController.cpp \
./src/GlobalGameController.cpp

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -Wall -Werror -Wextra $(FREETYPE2_I) 

# Linking opengl and lib GLFW.
GL = -framework OpenGL
GLFW = -framework Cocoa -framework CoreVideo -framework IOKit -framework GLUT -L./aleung-c_engine/glfw-3.2.1/src -lglfw3

# For freetype true font loading library
FREETYPE2_L = -L./aleung-c_engine/freetype-2.4.0/objs -lfreetype
FREETYPE2_I = -I./aleung-c_engine/freetype-2.4.0/include

ENGINE_DIR = ./aleung-c_engine/
ENGINE_L = -L./aleung-c_engine/ -laleung-c_engine

all: engine $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(GL) $(GLFW) $(FREETYPE2_L) $(ENGINE_L)

engine:
	make -C $(ENGINE_DIR)

%.o: %.cpp
	$(CC) -o $@ -c $<

clean:
	rm -rf $(OBJ)
	make clean -C $(ENGINE_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(ENGINE_DIR)

re: fclean all

.PHONY: all clean fclean re
