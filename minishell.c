#include "minishell.h"

t_minishell g_minishell;

static void ctrlC(int signal)
{
    ft_putstr(VERDE "\n┌──" RESET);
    ft_putstr(AZUL "(Minishell)" RESET); 
    ft_putstr(VERDE "-[" RESET);
    ft_putstr(g_minishell.dir);
    ft_putstr(VERDE "]\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int main(int ac, char **av)
{   
    g_minishell.dir = getcwd(NULL, 0);

    header();
    signal(SIGINT, &ctrlC);
    command(&g_minishell);
    return 0;
}