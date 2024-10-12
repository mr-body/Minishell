#include "minishell.h"

static void ctrlC(int signal)
{
    (void)signal;
    ft_putstr_fd(VERDE "\n┌──" RESET, 1);
    ft_putstr_fd(AZUL "(Minishell)" RESET, 1); 
    ft_putstr_fd(VERDE "-[" RESET, 1);
    ft_putstr_fd(getcwd(NULL, 0), 1);
    ft_putstr_fd(VERDE "]\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

int main(int ac, char **av)
{
    char *prompt;
    int status;
    
    header();
    signal(SIGINT, &ctrlC);
    while(1)
    {
        ft_putstr_fd(VERDE "\n┌──" RESET, 1);
		ft_putstr_fd(AZUL "(Minishell)" RESET, 1);
		ft_putstr_fd(VERDE "-[" RESET, 1);
		ft_putstr_fd(getcwd(NULL, 0), 1);
		ft_putstr_fd(VERDE "]", 1);
		prompt = readline(VERDE "\n└─" RESET AZUL "# " RESET);
        if(!prompt)
            break;
        if(*prompt)
            add_history(prompt);
        if(ft_strncmp(prompt, "exit", 4) == 0)
        {
            free(prompt);
            exit(0);
        }
        else
            execute_command(prompt);
        while (waitpid(-1, &status, 0) > 0);
        free(prompt);
    }
    return 0;
}
