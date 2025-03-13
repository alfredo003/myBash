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
    char    *str;
} t_tmp_values;

typedef struct s_env
{
	char			*key;
	bool				equal;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
    t_token *tokens;
    t_env *env;
    //t_env *env_copy;
    bool is_parent_process;
    t_status_shell status;
    t_tmp_values tmp;

} t_shell;

void    duplicate_env(t_shell *shell, char **env);
//static t_env *add_env(char *env_var);
void	free_matrix(char **matrix);
void    init_shell(t_shell *shell,char **env);
int     ft_readline(t_shell *shell, char **line);
void	lexical_analysis(t_shell *shell, char *line);
void	ft_free(void *ptr_to_free);
void	process_tokens(t_shell *shell, char *line, t_token *tokens);
char    *extract_token(char *input, int *index_inp, int *has_quotes);
char    *process_expansion(t_shell *shell, char *input, int is_heredoc);
int     calculate_expanded_length(t_shell *shell, char *input, int is_heredoc);
int     get_variable_length(t_shell *shell, char *input, int *index);
int     handle_return_value(t_shell *shell, int *index, int *total_length);
char	*ft_getenv(t_env *env, char *var);
bool     is_valid_token(char *str, int i, t_shell *shell);
bool     is_quote_unclosed(char *str, int i, char quote, t_shell *shell);
void    handle_quotes(t_shell *shell, char *input, int *index);
void	ft_free_tokens(t_token *tokens);
void	perform_variable_expansion(t_shell *shell, char *input, char *expanded, int in_heredoc);
void    handle_variable_expansion(t_shell *shell, char *expanded, int *index_inp, int *index_exp);
char	*get_env_value(t_shell *shell, char *input, int *index_inp);

#endif
