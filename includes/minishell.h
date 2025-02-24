#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "../libs/libft/libft.h"

typedef struct s_token
{
	char	*str;
	char	type;
    size_t  len; 
}	t_token;

typedef struct s_status_shell
{
    int last_return;
    int no_exec;
    int exit_status;
} t_status_shell;

typedef struct s_shell
{
    t_token *tokens;
    bool is_parent_process;
    t_status_shell status;

} t_shell;


void    init_shell();
int     ft_readline(t_shell *shell, char **line);
void	lexical_analysis(t_shell *shell, char *line);
void	ft_free(void **ptr_to_free);
#endif
