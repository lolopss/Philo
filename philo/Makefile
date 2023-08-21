NAME = philo

CC = gcc -Werror -Wall -Wextra -g3 -pthread -fsanitize=thread

RM = rm -rf

SRC = main.c check_args.c init.c philo_start.c threads.c one_philo.c exit.c check.c routine.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
