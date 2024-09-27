#include "minishell.h"

static void ctrlC(int signal)
{
    t_minishell g_minishell;

    ft_putstr_fd(VERDE "\n┌──" RESET, 1);
    ft_putstr_fd(AZUL "(Minishell)" RESET, 1); 
    ft_putstr_fd(VERDE "-[" RESET, 1);
    ft_putstr_fd(g_minishell.dir, 1);
    ft_putstr_fd(VERDE "]\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int main(int ac, char **av)
{   
    t_minishell g_minishell;
    
    g_minishell.dir = getcwd(NULL, 0);
    header();
    signal(SIGINT, &ctrlC);
    command(&g_minishell);
    return 0;
}