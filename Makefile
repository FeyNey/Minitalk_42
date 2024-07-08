CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror

NAME_SERVER	=	serveur
NAME_CLIENT	=	client

SRC_SERVEUR	=	server.c\
					utils.c

SRC_CLIENT	=	client.c\
				utils.c

# SRC_BONUS	=	client_bonus.c\
# 				serveur_bonus.c\
# 				utils_bonus.c

OBJ_SERVER	=	$(SRC_SERVEUR:.c=.o)
OBJ_CLIENT	=	$(SRC_CLIENT:.c=.o)

# OBJ_BONUS	=	$(SRC_BONUS:_bonus.c=_bonus.o)

all	:	$(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER)	:	$(OBJ_SERVER)
		$(MAKE) -C ft_printf
		$(CC) $(CFLAGS) $(OBJ_SERVER) ft_printf/libftprintf.a -o $(NAME_SERVER)

$(NAME_CLIENT)	:	$(OBJ_CLIENT)
		$(MAKE) -C ft_printf
		$(CC) $(CFLAGS) $(OBJ_CLIENT) ft_printf/libftprintf.a -o $(NAME_CLIENT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# bonus : $(OBJ_BONUS)
# 		ar rcs $(NAME) $(OBJ_BONUS)

clean	:
		$(MAKE) -C ft_printf clean
		rm -rf $(OBJ_SERVER) $(OBJ_CLIENT)

fclean	:	clean
		$(MAKE) -C ft_printf fclean
		rm -f $(NAME_SERVER) $(NAME_CLIENT)

re	:	fclean all

.PHONY	:	all bonus clean fclean re
