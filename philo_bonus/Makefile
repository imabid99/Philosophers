
NAME	= philo
CC		= gcc
FLAGS	= -Wall -Wextra -Werror

SRCS	= check_arg.c  \
		main.c \
		philo_utils.c \
		philo_utils2.c

OBJS	= $(SRCS:.c=.o)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

all:
	@$(MAKE) $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean:  clean
	rm -rf $(NAME)

re: fclean all