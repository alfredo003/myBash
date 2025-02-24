#include "minishell.h"

int main(int argc,char **argv, char **env)
{
    t_shell shell;
    (void)argc;
    (void)argv;
    (void)env;
    
    init_shell(&shell);
    return(shell.status.last_return);
}