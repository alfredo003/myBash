#include "minishell.h"

static void skip_whitespace(char *line, int *i)
{
    while (line[*i] == ' ' || line[*i] == '\t')
        (*i)++;
}

void	process_tokens(t_shell *shell, char *line, t_token *tokens)
{
	int		i;
	int		token_index;
	int		in_quotes;
	char	*current_str;

	i = 0;
	token_index = 0;
	while (line[i])
	{
		skip_whitespace(line, &i);
		current_str = extract_token(line, &i, &in_quotes);
		current_str = process_expansion(shell, current_str, 0);
		printf("%s\n", current_str);
		//tokens[token_index].str = ft_strdup(current_str);
        //tokens[token_index].type = type_str(current_str, in_quotes);
        //token_index++;
		//skip_whitespace(line, &i);
		//process_separator(line, &i, tokens, &token_index);
		//free_str_and_set_null(&current_str);
	}
	tokens[token_index].str = NULL;
}