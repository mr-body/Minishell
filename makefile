NAME = minishell
SRCS = sources/minishell.c\
		sources/parser_redir.c\
		sources/expander.c\
		sources/quote_utils.c\
		sources/syntax_checker.c\
		sources/child_process.c\
		sources/heart.c\
		sources/ft_split_ms.c\
		sources/shell.c\
		sources/redirect.c\
		sources/minishell_sms.c\
		sources/change_env_vars.c\
		sources/execute_command_utils.c\
		sources/util.c\
		sources/util2.c\
		sources/utils_pipe.c\
		sources/utils_redir.c\
		sources/command/echo.c\
		sources/command/cd.c\
		sources/command/pwd.c\
		sources/command/export.c\
		sources/command/export_utils.c\
		sources/command/unset.c\
		sources/command/env.c\

OJBS = ${SRCS:.c=.o}
LIBFT = libft
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: ${NAME}

${NAME}: ${OJBS}
	make -C ${LIBFT}
	${CC} ${CFLAGS} -o ${NAME} ${OJBS} -L${LIBFT} -lft -lreadline

clean:
	${RM} ${OJBS}
	make clean -C ${LIBFT}

fclean: clean
	${RM} ${NAME}
	make fclean -C ${LIBFT}

re: fclean all

.PHONY: all clean fclean re