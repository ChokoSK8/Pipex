NAME	= pipex

SRCS	= check_error.c init_newargv.c init_newargv_utils.c utils.c pipex.c ft_close.c ft_cmd.c init_paths.c get_next_line.c get_next_line_utils.c

SRCS_B	= check_error_bonus.c init_newargv_bonus.c init_newargv_2_bonus.c pipex_bonus.c ft_close_bonus.c ft_cmd_bonus.c make_cmd_bonus.c make_heredoc_cmd_bonus.c utils_bonus.c get_next_line.c get_next_line_utils.c

OBJS	= $(SRCS:.c=.o)

OBJS_B	= $(SRCS_B:.c=.o)

FLAGS	= -Wall -Werror -Wextra

%.o: %.c
			cc $(FLAGS) $(INC) -o $@ -c $?

all:	$(NAME)

bonus:		lib $(OBJS_B)
		gcc $(FLAGS) $(OBJS_B) -o $(NAME) Libft/libft.a

RM		= rm -rf

INC		= -I includes/

lib:	
	make -C Libft

$(NAME):	lib $(OBJS)
		gcc $(FLAGS) $(OBJS) -o $(NAME) Libft/libft.a

clean:
		$(RM) *.o

fclean:		clean
			$(RM) $(NAME)
			make fclean -C Libft

re:		fclean all

.PHONY:		all clean fclean re
