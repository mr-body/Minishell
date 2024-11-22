NAME = minishell
SRCS = sources/minishell.c\
		sources/parser_redir.c\
		sources/expander.c\
		sources/expander_utils.c\
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
		sources/ft_big_split.c\
		sources/utils1.c\
		sources/utils2.c\
		sources/utils3.c\
		sources/utils_pipe.c\
		sources/utils_redir.c\
		sources/command/echo.c\
		sources/command/cd.c\
		sources/command/pwd.c\
		sources/command/export.c\
		sources/command/export_utils.c\
		sources/command/unset.c\
		sources/command/env.c\
		sources/command/exit.c\
		sources/redirect_case_one.c\
		sources/redirect_aux.c\
		sources/new_redirect.c\


#LDFLAGS = -fsanitize=address
OJBS = ${SRCS:.c=.o}
LIBFT = libft
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
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
