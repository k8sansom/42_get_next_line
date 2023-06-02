NAME = gnl.a

CFLAGS = -c -Wall -Wextra -Werror

TARGET = a.out

LIB	= ar rcs

RM = rm -f

SRC = get_next_line.c get_next_line_utils.c get_next_line.h

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):	$(OBJ)
	$(LIB) $(NAME) $(OBJ)

bonus:	$(B_OBJ)
	$(LIB) $(NAME) $(B_OBJ)

clean:
	$(RM) $(OBJ) $(B_OBJ)

fclean: clean
	$(RM) $(NAME) $(OBJ) $(B_OBJ)

re: fclean all

.PHONY: all bonus clean fclean re


