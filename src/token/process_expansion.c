#include "minishell.h"

char *process_expansion(t_shell *shell, char *input, int is_heredoc)
{
    char *expanded;
    int expanded_size;

    if (input[0] == '$' && input[1] == '$')
        return input;

    expanded_size = calculate_expanded_length(shell, input, is_heredoc);
    expanded = (char *)malloc(expanded_size + 1);
    if (!expanded)
    {
        ft_free(input);
        return NULL;
    }
    perform_variable_expansion(shell, input, expanded, is_heredoc);
    ft_free(input);

    return expanded;
}
