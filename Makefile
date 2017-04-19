#---------------------------------------------------#
#													#
#	42run C++ Makefile.								#
#													#
#---------------------------------------------------#

NAME = 42run

SRC = ./src/main.cpp \
./src/GameObject.cpp \
./src/GameObject_Parsing.cpp \
./src/GameTextObject.cpp \
./src/GameEngineController.cpp \
./src/GamePlayController.cpp \
./src/GlobalGameController.cpp

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -Wall -Werror -Wextra $(FREETYPE2_I)

# Linking opengl and lib GLFW.
GL = -framework OpenGL
GLFW = -framework Cocoa -framework CoreVideo -framework IOKit -framework GLUT -L./glfw-3.2.1/src -lglfw3

# For freetype true font loading library
FREETYPE2_L = -L./freetype-2.4.0/objs -lfreetype
FREETYPE2_I = -I./freetype-2.4.0/include

all: freetype $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(GL) $(GLFW) $(FREETYPE2_L)

%.o: %.cpp
	$(CC) -o $@ -c $<

freetype :
	make -C ./freetype-2.4.0/

clean:
	rm -rf $(OBJ)
	make clean -C ./freetype-2.4.0/

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
