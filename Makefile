NAME = minishell

GREEN		=	\033[1;32m
RED			=	\033[1;31m
DEFAULT		=	\033[0m

GNL_DIR		=	GNL/
PARSING_DIR	=	Srcs/1-Parsing/
BUILTIN_DIR	=	Srcs/4-Exec/builtins/
UTILS_DIR	=	Srcs/Utils/
FREE_DIR	=	Srcs/free/

SRCS		=	main.c	\
				${PARSING_DIR}parsing.c	\
				${UTILS_DIR}utils.c	\
				${GNL_DIR}get_next_line.c		\
				${GNL_DIR}get_next_line_utils.c

OBJS		=	$(SRCS:%.c=%.o)

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
