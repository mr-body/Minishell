#include "minishell.h"

void command(void)
{
    String command;
    String pwd = getcwd(NULL, 0);

    while(1)
    {
        ft_putstr(VERDE "\n┌──" RESET);
        ft_putstr(AZUL "(Minishell)" RESET); 
        ft_putstr(VERDE "-[" RESET);
        ft_putstr(pwd);
        ft_putstr(VERDE "]\n└─" RESET);
        ft_putstr(AZUL "# " RESET);

        command = readline("");
        if(!command)
            break;

        if(command)
            add_history(command);

        if(!strcmp(command, "clear"))
        {
            clear_history();
            ft_putstr(CLEAR);
        }

        ft_putstr(command);

        rl_on_new_line();
        rl_redisplay();

        free(command);
    }
}