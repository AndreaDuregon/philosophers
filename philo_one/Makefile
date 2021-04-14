NAME	=	philo_one

SRCS	=	philo_one.c \
			utils.c \
			utils2.c \
			exit.c \
			time.c \
			init.c \
			display.c \
			philo_life.c \
			philo_turn.c

OBJS	=	$(SRCS:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			@gcc -lpthread -pthread -Wall -Wextra -Werror -O3 -o $(NAME) $(OBJS)

clean	:	
			rm -f $(OBJS)

fclean	:	clean
			rm -f $(NAME)

re		:	fclean all

.PHONY	:	all	clean fclean re