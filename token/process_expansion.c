#include "minishell.h"

int calculate_expanded_length(t_shell *shell, char *input, int is_heredoc)
{
    int index = 0;
    int expanded_size = 0;

    shell->tmp.active_quote = 0;

    while (input[index])
    {
        if (input[index] == '$' && input[index + 1] &&
            (shell->values.active_quote != '\'' || is_heredoc))
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


char *process_variable_expansion(t_shell *shell, char *input, int is_heredoc)
{
    char *expanded;
    int expanded_size;

    if (input[0] == '$' && input[1] == '$')
        return input;

    expanded_size = calculate_expanded_length(shell, input, is_heredoc);

    expanded = (char *)malloc(expanded_size + 1);
    if (!expanded)
    {
        ft_free(input, 1);
        return NULL;
    }

    perform_variable_expansion(shell, input, expanded, is_heredoc);
    ft_free(input);

    return expanded;
}
