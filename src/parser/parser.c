#include "minishell.h"

t_mlist *ft_parser(t_shell *shell, char *str)
{
	char **tokens;
	t_mlist *list;

	tokens = ft_tokenizer(str);
	list = ft_constructor(shell, tokens);
	return (list);
}
