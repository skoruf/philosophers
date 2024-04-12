CC = cc
NAME= philo
SRC = main.c \
		philo.c \
		philo_routine.c \
		init.c \
		init2.c \
		threads.c \
		utils.c \
		utils2.c
OBJ = $(SRC:.c=.o)
DEPS = philo.h
FLAGS = -g -Wall -Wextra -Werror

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
