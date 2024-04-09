CC = cc
NAME= philo
SRC = main.c \
		philo.c \
		init.c \
		init2.c \
		utils.c
OBJ = $(SRC:.c=.o)
DEPS = philo.h
FLAGS = -g -Wall -Wextra

%.o: %.c $(DEPS)
	$(CC) $(FLAGS) -c $< -o $@
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)
re: fclean all

.PHONY: clean fclean re
