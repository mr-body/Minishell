#include "minishell.h"

static void ctrlC(int signal)
{
<<<<<<< HEAD
    t_minishell g_minishell;
=======
    t_minishell minishell;
>>>>>>> 34ad2b5e04f5e87a3cc52ef1a3f0f888790bf37d

    ft_putstr_fd(VERDE "\n┌──" RESET, 1);
    ft_putstr_fd(AZUL "(Minishell)" RESET, 1); 
    ft_putstr_fd(VERDE "-[" RESET, 1);
    ft_putstr_fd(minishell.dir, 1);
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
    command(&minishell);
    return 0;
}