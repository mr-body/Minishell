NAME = minishell

${NAME}:
	cc *.c -lreadline -o ${NAME}

clean:
	rm -f ${NAME}

re: clean
	cc *.c -lreadline -o ${NAME}
