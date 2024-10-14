NAME = minishell
LIBFT = libft

all: ${NAME}

${NAME}:
	make -C ${LIBFT}
	cc *.c command/*.c -lreadline -g -o ${NAME} ${LIBFT}/libft.a

clean:
	make clean -C ${LIBFT}
	rm -f ${NAME}

re: clean all
