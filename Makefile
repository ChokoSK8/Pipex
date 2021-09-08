NAME	= pipex.a

SRC		= *.c

OBJ		= $(SRC:.c=.o)

FLAGS	= -Wall -Werror -Wextra

all:	$(NAME)

RM		= rm -rf

INC		= -I includes/

%.o: %.c
			cc $(FLAGS) $(INC) -o $@ -c $?

$(NAME):
		clang $(FLAGS) -c $(SRCS)
		ar rc $(NAME) *.o

clean:
		$(RM) *.o

fclean:		clean
			$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
