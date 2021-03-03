SRCS		=	main.c\
				ft_atoi.c\
				ft_calloc.c
				
NAME		=	philo_one
RM			=	rm -f
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -lpthread

$(NAME) :	$(SRCS)
			$(CC) $(CFLAGS) $^ -o $@

all		:	$(NAME)

clean	:	

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re