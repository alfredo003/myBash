#include "minishell.h"

int is_valid_character(char *str, int i, t_shell *shell)
{
   char current_char = str[i];

    if (current_char == '"' || current_char == '\'')
    {
        if (ft_is_unclosed_quote(str, i, current_char, shell))
            return (1);
        if (!shell->tmp.active_quote)
            return (0);
        if (shell->tmp.active_quote == current_char)
            return (0);
    }
    return (1);
}

int handle_return_value(t_shell *shell, int *index, int *total_length)
{
    char *return_value_str = ft_itoa(shell->status.last_return);
    if (!return_value_str)
        return 0;
    *total_length += ft_strlen(return_value_str);
    ft_free(return_value_str);
    (*index)++;
    return *total_length;
}

int get_variable_length(t_shell *shell, char *input, int *index)
{
    int i = 0;
    int len_aloc = 0;
    (*index)++;

    if (input[*index] == '?')
        return handle_return_value(shell, index, &len_aloc);
    while (input[*index + i] && (ft_isalnum(input[*index + i]) || input[*index + i] == '_'))
        i++;
    if (i == 0)
        return 0;

    char *env_name = ft_strndup(input + *index, i);
    *index += i;
    char *env_value = ft_getenv(shell->env, env_name);
    ft_free(env_name);

    if (env_value)
    {
        len_aloc += ft_strlen(env_value);
        ft_free(env_value);
    }

    return len_aloc;
}

int calculate_expanded_length(t_shell *shell, char *input, int is_heredoc)
{
    int index = 0;
    int expanded_size = 0;

    shell->tmp.active_quote = 0;

    while (input[index])
    {
        if (input[index] == '$' && input[index + 1] && 
            (shell->tmp.active_quote != '\'' || is_heredoc))
        {
            expanded_size += get_variable_length(shell, input, &index);
        }
        else
        {
            if (is_valid_character(input, index, shell))
                expanded_size++;
            handle_quotes(shell, input, &index);
            index++;
        }
    }
    return expanded_size;
}