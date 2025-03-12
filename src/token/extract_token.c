#include "minishell.h"

static int is_matching_quote_closed(char *str, int i, int quote)
{
	while (str[++i])
	{
		if (str[i] == quote)
			return (1);
	}
	return (0);
}

static void toggle_quote_state(int *is_single_quoted, int *is_double_quoted,char *input, int *index)
{
	if (input[*index] == '"')
	{
		if (*is_double_quoted == 0)
		{
			if (is_matching_quote_closed(input, *index, '"'))
				*is_double_quoted = 1;
		}
		else
			*is_double_quoted = 0;
	}
	else if (input[*index] == '\'')
	{
		if (*is_single_quoted == 0)
		{
			if (is_matching_quote_closed(input, *index, '\''))
				*is_single_quoted = 1;
		}
		else
			*is_single_quoted = 0;
	}
}

char *extract_token(char *input, int *index_inp, int *has_quotes)
{
	char 	*token;
	int		index_tok;
	int		is_single_quoted;
	int 	is_double_quoted;

	token = (char *)malloc(sizeof(char) * ft_strlen(input) + 1);
	if (!token)
		return (NULL);
	index_tok = 0;
	is_single_quoted = 0;
	is_double_quoted = 0;
	*has_quotes = 0;
	while (input[*index_inp])
	{
		toggle_quote_state(&is_single_quoted, &is_double_quoted, input, index_inp);
		if (is_double_quoted == 1 || is_single_quoted == 1)
			*has_quotes = 1;
		if (is_double_quoted == 0 && is_single_quoted == 0 && ((input[*index_inp] == '|' || input[*index_inp] == '>' || input[*index_inp] == '<') || input[*index_inp] == ' '))
			break ;
		token[index_tok++] = input[(*index_inp)++];
	}
	token[index_tok] = '\0';
	return (token);
}