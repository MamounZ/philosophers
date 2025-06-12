CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = philo
SRCS = main.c clean_exit.c input_validation.c main_utils.c monitor.c routine.c utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
