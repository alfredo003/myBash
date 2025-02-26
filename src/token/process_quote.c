#include "minishell.h"

int	ft_is_closed(char *str, int i, char quote)
{
	while (str[++i])
	{
		if (str[i] == quote)
			return (1);
	}
	return (0);
}

int	ft_is_unclosed_quote(char *str, int i, char quote, t_shell *shell)
{
	if (shell->tmp.active_quote == quote)
		return (0);
	else if (!shell->tmp.active_quote)
	{
		while (str[++i])
		{
			if (str[i] == quote)
				return (0);
		}
	}
	return (1);
}

void handle_quotes(t_shell *shell, char *input, int *index)
{
    char current_char = input[*index];

    if (current_char == '"' || current_char == '\'')
    {
        if (shell->tmp.active_quote == 0 || shell->tmp.active_quote == current_char)
        {
            if (ft_is_closed(input, *index, current_char))
            {
                if (shell->tmp.active_quote == 0)
                {
                    shell->tmp.active_quote = current_char;
                }
                else
                {
                    shell->tmp.active_quote = 0;
                }
            }
        }
    }
}