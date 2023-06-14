#include "../minishell.h"

void	ft_free_2d_array_with_null(char **array)
{
	if (!array)
		return ;
	while (*array)
	{
		free(*array);
		array++;
	}
}

void	ft_list_clear(t_mlist **list)
{
	int	n;

	if (!list || !*list)
		return ;
	n = 0;
	while ((*list)->argv[n])
	{
		free((*list)->argv[n]);
		n++;
	}
	free((*list)->argv);
	free((*list)->command);
	free((*list)->bin);
	*list = NULL;
}

void	ft_free_2_linked_list(t_mlist **list)
{
	while (*list)
	{
		if ((*list)->next)
		{
			*list = (*list)->next;
			ft_list_clear(&(*list)->prev);
		}
		else
			ft_list_clear(list);
	}
}