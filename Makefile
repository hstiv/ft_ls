NAME	=	ft_ls

SRCS	=	srcs/main.c srcs/var_setters.c \
			srcs/option_reader.c srcs/read_dir.c \
			srcs/sort.c srcs/setters.c srcs/stats.c $(LFT)

HEADER	=	includes/

LFTH	=	libft/

LFT		=	libft/libft.a

FL		=	-Wall -Wextra -Werror

all:		$(NAME)


$(NAME):
			@make -C libft re
			@gcc -o $(NAME) $(SRCS) -I $(HEADER) -I $(LFTH)

clean:
			@rm -rf srcs/*.o
			@make -C libft fclean

fclean:		clean
			@rm -rf $(NAME)

re:			fclean all
