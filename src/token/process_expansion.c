#include "minishell.h"

void	perform_variable_expansion(t_shell *shell, char *input,
	char *expanded, int in_heredoc)
{
	int	n;
	int	j;

	n = 0;
	j = 0;
	shell->tmp.active_quote = 0;
	if (!expanded)
		return ;
	while (input[n])
	{
		if (input[n] == '$' && input[n + 1]
			&& (shell->tmp.active_quote != 39 || in_heredoc))
		{
			shell->tmp.active_quote = input;
			handle_variable_expansion(shell, expanded, &n, &j);
		}
		else
		{
			if (ft_can_be_add(input, n, shell))
				expanded[j++] = input[n];
			handle_quotes(shell, input, &n);
			n++;
		}
	}
	expanded[j] = '\0';
}

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
