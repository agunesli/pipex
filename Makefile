SRC_F	= ft_strdup.c ft_strlen.c ft_split.c ft_strjoin.c ft_substr.c 

SRC_M	= pipex.c path.c utils.c

SRC_H	= pipex.h

OBJ_M	= $(SRC_M:%.c=%.o)

OBJ_F	= $(SRC_F:%.c=%.o)

NAME	=	pipex
CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

%.o: %.c
	${CC} ${FLAGS} -c $< -o $@

$(NAME):$(OBJ_M) $(OBJ_F)
		$(CC) $(OBJ_M) $(OBJ_F) -o $(NAME)

all:	$(NAME)

bonus:	$(OBJ_F) $(OBJ_B)
		$(CC) $(OBJ_F) $(OBJ_B) -o $(NAME)

clean:
		$(RM) $(OBJ_M) $(OBJ_F)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean bonus re
