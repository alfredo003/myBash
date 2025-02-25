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
}	t_token;

typedef struct s_status_shell
{
    int last_return;
    int no_exec;
    int exit_status;
} t_status_shell;

typedef struct s_tmp_values
{
    int active_quote;
} t_tmp_values;

typedef struct s_env
{
	char			*key;
	int				equal;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
    t_token *tokens;
    t_env *env;
    bool is_parent_process;
    t_status_shell status;
    t_tmp_values tmp;

} t_shell;


void    init_shell();
void	lexical_analysis(t_shell *shell, char *line);
void	ft_free(void *ptr_to_free);
void	process_tokens(t_shell *shell, char *line, t_token *tokens);

int     ft_readline(t_shell *shell, char **line);


char	*ft_getenv(t_env *env, char *var);
char *extract_token(char *input, int *index, int *has_quotes);
char *process_expansion(t_shell *shell, char *input, int is_heredoc);
#endif
