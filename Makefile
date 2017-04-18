#---------------------------------------------------#
#													#
#	42run C++ Makefile.								#
#													#
#---------------------------------------------------#

NAME = 42run

SRC = ./src/main.cpp \
./src/GameObject.cpp \
./src/GameObject_Parsing.cpp \
./src/GameEngineController.cpp \
./src/GamePlayController.cpp \
./src/GlobalGameController.cpp

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -Wall -Werror -Wextra

GL = -framework OpenGL
GLFW = -framework Cocoa -framework CoreVideo -framework IOKit -framework GLUT -L./glfw-3.2.1/src -lglfw3

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(GL) $(GLFW)

%.o: %.cpp
	$(CC) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
