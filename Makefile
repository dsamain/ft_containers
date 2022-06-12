NAME = ft_containers 
SRC = main.cpp

.cpp.o:
	$(CC) $(FLAGS) -c $(SRC)

OBJ = $(SRC:.cpp=.o)

FLAGS = -Wall -Wextra -Werror -std=c++98

CC = clang++ 



all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(FLAGS) $(OBJ) 

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: clean all

run: all
	./$(NAME)