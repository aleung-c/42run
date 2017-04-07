#---------------------------------------------------#
#													#
#	42run C++ Makefile.								#
#													#
#---------------------------------------------------#

NAME = 42run

SRC = ./src/main.cpp \
./src/GlobalGameController.cpp

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.cpp
	$(CC) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
