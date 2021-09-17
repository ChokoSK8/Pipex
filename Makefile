NAME	= pipex

SRCS	= *.c

OBJS	= $(SRC:.c=.o)

FLAGS	= -Wall -Werror -Wextra

all:	$(NAME)

RM		= rm -rf

INC		= -I includes/

%.o: %.c
			cc $(FLAGS) $(INC) -o $@ -c $?

lib:	
	make re -C Libft

$(NAME):	lib
		ranlib Libft/libft.a
		gcc $(FLAGS) $(SRCS) -o $(NAME) Libft/libft.a

clean:
		$(RM) *.o

fclean:		clean
			$(RM) $(NAME)
			make fclean -C Libft

re:		fclean all

.PHONY:		all clean fclean re
