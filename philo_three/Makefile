SRCS		=	main.c\
			ft_atoi.c\
			ft_calloc.c\
			ft_msleep.c\
			get_time.c\
			lifecycle.c\
			check_processes.c\
			print_status.c

OBJS		=	$(SRCS:.c=.o)
				
NAME		=	philo_three
RM		=	rm -f
CC		=	gcc
CFLAGS		=	-Wall -Wextra -Werror

$(NAME) 	:	$(OBJS)
			$(CC) $(CFLAGS) $^ -o $@

all		:	$(NAME)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
