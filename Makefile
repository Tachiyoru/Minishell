NAME = minishell

GREEN		=	\033[1;32m
RED			=	\033[1;31m
DEFAULT		=	\033[0m

OBJ_DIR		=	objs
INC_DIR		=	include
SRC_DIR		=	$(shell find srcs -type d)

vpath %.c $(foreach dir, $(SRC_DIR), $(dir):)

RM			= /usr/bin/rm

SRCS		=	main.c	\
				ft_env.c	\
				ft_env_utils.c	\
				utils3.c	\
				parsing_token.c	\
				parsing_rec.c	\
				parsing_rec_utils.c	\
				utils.c	\
				free.c	\
				utils2.c	\
				expand_quote.c \
				expand_utils.c \
				expand_quote_parsing_utils.c \
				expand_var.c \
				expand_spaces.c \
				ft_itoa.c		\
				exec.c		\
				pre_exec_utils.c	\
				redir_fct.c		\
				redir_utils.c		\
				exec_utils.c		\
				cmd_utils.c			\
				pwd.c				\
				echo.c				\
				cd.c


OBJS		=	$(SRCS:%.c=${OBJ_DIR}/%.o)

CC			=	clang
CFLAGS		=	-Werror -Wall -Wextra -g3

all:	${NAME}

$(NAME):	${OBJS} $(INC_DIR)/minishell.h
		${CC} ${CFLAGS} -lreadline ${OBJS} -I ${INC_DIR} -o ${NAME}
	@echo "$(GREEN)##### Minishell compiling finished! #####$(DEFAULT)"

$(OBJ_DIR)/%.o: %.c $(INC_DIR)/minishell.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

$(OBJ_DIR) :
	mkdir -p $@

clean:
		${RM} -r $(OBJ_DIR)

fclean:		clean
		${RM} ${NAME}

re:			fclean
		$(MAKE) all -j

.PHONY:		all clean fclean re
