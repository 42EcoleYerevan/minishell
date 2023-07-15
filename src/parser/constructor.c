#include "minishell.h"

t_mlist	*ft_constructor(t_shell *shell, char **tokens)
{
	t_mlist *list;

	ft_set_env_token(shell, tokens);
	list = ft_create_list(shell, tokens);
	return (list);
}
