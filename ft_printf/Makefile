CC	=	cc

CFLAGS	=	-Wall	-Wextra	-Werror

NAME	=	libftprintf.a

SRCS	=	ft_print.c \
			ft_printf.c

OBJS	=	$(SRCS:.c=.o)

all	:	$(NAME)

%.o	:	%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME)	:	$(OBJS)
		ar rcs $(NAME) $(OBJS)

clean	:
		rm -rf $(OBJS)

fclean	:	clean
			rm -f $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
