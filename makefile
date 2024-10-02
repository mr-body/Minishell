NAME = minishell
LIBFT = libft

all: ${NAME}

${NAME}:
	make -C ${LIBFT}
	cc *.c -lreadline -o ${NAME} ${LIBFT}/libft.a

clean:
	make clean -C ${LIBFT}
	rm -f ${NAME}

re: clean all
