NAME	= libft.a

SRCS	= *.c

OBJS	= $(SRCS:.c=.o)

CC		= cc

AR		= ar rc

RM		= rm -rf

INC		= -I includes/

CFLAGS	= -Wall -Werror -Wextra 

%.o: %.c
			$(CC) $(CFLAGS) $(INC) -o $@ -c $?

$(NAME):
			clang $(CFLAGS) -c $(SRCS)
			ar rc $(NAME) *.o

all:		$(NAME)

clean:
			$(RM) *.o *.a

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
