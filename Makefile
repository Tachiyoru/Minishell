NAME = Minishell

GREEN		=	\033[1;32m
RED			=	\033[1;31m
DEFAULT		=	\033[0m

BUILTIN_DIR	=	builtins/
FREE_DIR	=	free/
PARSING_DIR	=	parsing/
UTIS_DIR	=	utils/

SRCS		=

OBJS		=	${SRCS:.c=.o}

CC			=	clang
CFLAGS		=	-Werror -Wall -Wextra -g3

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}
@echo "$(GREEN)##### Minishell compiling finished! #####$(DEFAULT)"

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}

re:			fclean
		$(MAKE) all -j

.PHONY:		all clean fclean re
