#include "minishell.h"

void	ft_free(void **ptr_to_free)
{
	if (!ptr_to_free || !*ptr_to_free)
		return ;
	free(*ptr_to_free);
	*ptr_to_free = NULL;
}