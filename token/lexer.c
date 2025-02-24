#include "minishell.h"


void gettokens(t_token *tokens, t_shell *shell, char *input_line)
{
	tokens = (t_token *)malloc(sizeof(t_token) * 10000);
	ft_memset(tokens, 0, sizeof(t_token) * 10000);
	if (!tokens)
			tokens = NULL;
	process_tokens(shell, input_line, tokens);

	organize_tokens(&tokens);
}


void	lexical_analysis(t_shell *shell, char *input_line)
{
	t_token	*tokens;

	input_line = ft_strtrim(input_line, " ");
	if (!input_line || !input_line[0])
	{
		ft_free(input_line);
		return ;
	}
	gettokens(&tokens,shell, input_line);
	if (!tokens)
	{
		ft_free(input_line);
		shell->status.last_return = 1;
		return ;
	}
	/*process_and_validate_line(shell, &tokens);
	if (shell->status.last_return == 258)
	{
		ft_free(input_line);
		return ;
	}
	shell->charge = 1;
	redir_and_exec(shell, 0, 0);
	ft_free_tokens(tokens);
	ft_free(input_line);*/
}