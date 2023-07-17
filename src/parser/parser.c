#include "minishell.h"

t_mlist *ft_parser(t_shell *shell, char *str)
{
	char **tokens;
	t_mlist *list;

	tokens = ft_tokenizer(str);
	list = ft_constructor(shell, tokens);
	ft_free_2d_array_with_null(tokens);
	free(tokens);
	return (list);
}
