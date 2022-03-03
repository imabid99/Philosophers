
NAME	= philo_bonus
CC		= gcc
FLAGS	= -Wall -Wextra -Werror

SRCS	= check_arg_bonus.c  \
		main_bonus.c \
		philo_utils_bonus.c \
		philo_utils2_bonus.c \
		philo_utils3_bonus.c

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