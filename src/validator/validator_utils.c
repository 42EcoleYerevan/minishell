#include "minishell.h"

int	ft_check_redirect_error(t_mlist *list, int n)
{
	int	error;

	error = 0;
	if (ft_strncmp(list->argv[n], "<", 2) == 0)
		error = ft_check_one_redirect_input_argument(list, n);
	else if (list->argv[n][0] == '>' || \
			ft_strncmp(list->argv[n], "<<", 3) == 0)
		error = ft_check_next_redirect_input_argument(list, n);
	return (error);
}

int	ft_check_pipe_error(t_mlist *list)
{
	if (list->command && !list->bin && !list->argv[0])
	{
		if (list->next && list->next->command)
			return (ft_redirect_unexpected_error(list->command));
		else if (list->next && list->next->argv[0])
			return (ft_redirect_unexpected_error(list->next->argv[0]));
	}
	return (0);
}
