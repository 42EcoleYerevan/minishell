#include "minishell.h"

int	ft_is_valid_linked_list(t_mlist *list)
{
	int	error;

	if (!list)
		return (1);
	while (list)
	{
		error = ft_is_valid_argv(list);
		if (error)
			return (error);
		error = ft_check_pipe_error(list);
		if (error)
			return (error);
		list = list->next;
	}
	return (0);
}
