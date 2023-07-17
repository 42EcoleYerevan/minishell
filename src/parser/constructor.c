#include "minishell.h"

t_mlist	*ft_constructor(t_shell *shell, char **tokens)
{
	t_mlist *list;

	list = ft_create_list(shell, tokens);
	return (list);
}
