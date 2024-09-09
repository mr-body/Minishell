#include "minishell.h"


void execute(char *command)
{
    char **args = ft_split(command);

    if (args[0] == NULL) // Se o comando estiver vazio
    {
        free(args);
        return;
    }

    pid_t pid = fork();
    if (pid == 0) // Processo filho
    {
        if (execvp(args[0], args) == -1) // Executa o comando
        {
            perror("Erro ao executar o comando");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0) // Processo pai
    {
        waitpid(pid, NULL, 0); // Espera o filho terminar
    }
    else
    {
        perror("Erro ao criar o processo filho");
    }

    free(args);
}

void command(void)
{
    String command;
    String pwd = getcwd(NULL, 0);

    while (1)
    {
        ft_putstr(VERDE "\n┌──" RESET);
        ft_putstr(AZUL "(Minishell)" RESET);
        ft_putstr(VERDE "-[" RESET);
        ft_putstr(pwd);
        ft_putstr(VERDE "]\n└─" RESET);

        // Ajuste o prompt, removendo o '#' se não for necessário
        command = readline(AZUL "$ " RESET); // Altere o prompt para '>' ou outro símbolo de sua escolha
        if (!command)
            break;

        if (command)
            add_history(command);

        if (!strcmp(command, "clear"))
        {
            clear_history();
            ft_putstr(CLEAR);
        }
        execute(command);
        

        rl_on_new_line();

        free(command);
    }
}
