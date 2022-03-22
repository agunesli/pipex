SRC_F	= ft_strdup.c ft_strlen.c ft_split.c ft_strjoin.c ft_substr.c path.c utils.c

SRC_M	= pipex.c

SRC_B	= pipex_bonus.c

SRC_H	= pipex.h

OBJ_M	= $(SRC_M:%.c=%.o)

OBJ_F	= $(SRC_F:%.c=%.o)

OBJ_B	= $(SRC_B:%.c=%.o)

NAME	=	pipex
CC		=	gcc
#FLAGS	=	-g3 -Wall -Wextra -Werror -fsanitize=address
FLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

%.o: %.c
	${CC} ${FLAGS} -c $< -o $@

$(NAME):$(OBJ_M) $(OBJ_F) $(SRC_H)
		$(CC) $(OBJ_M) $(OBJ_F) -o $(NAME)

all:	$(NAME)

bonus:	$(OBJ_F) $(OBJ_B)
		$(CC) $(OBJ_F) $(OBJ_B) -o $(NAME)

clean:
		$(RM) $(OBJ_M) $(OBJ_F) $(OBJ_B)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean bonus re
