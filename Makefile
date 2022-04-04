SRC_F	= ft_split.c ft_substr.c ft_strncmp.c path.c utils.c \
		  get_next_line.c get_next_line_utils.c \

SRC_M	= pipex.c

SRC_B	= pipex_bonus.c pipex_bonus2.c here_doc.c 

SRC_H	= pipex.h

OBJ_M	= $(SRC_M:%.c=%.o)

OBJ_F	= $(SRC_F:%.c=%.o)

OBJ_B	= $(SRC_B:%.c=%.o)

NAME	=	pipex
NAME_B	=	pipex_bonus
CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

%.o: %.c
	${CC} ${FLAGS} -c $< -o $@

$(NAME):$(OBJ_M) $(OBJ_F) $(SRC_H)
		$(CC) $(OBJ_M) $(OBJ_F) -o $(NAME)

all:	$(NAME)

$(NAME_B)	: $(OBJ_F) $(OBJ_B) $(SRC_H)
		$(CC) $(OBJ_F) $(OBJ_B) -o $(NAME_B)

bonus:	$(NAME_B)
clean:
		$(RM) $(OBJ_M) $(OBJ_F) $(OBJ_B)

fclean:	clean
		$(RM) $(NAME)
		$(RM) $(NAME_B)

re:		fclean all

.PHONY:		all clean fclean bonus re
