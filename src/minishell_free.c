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
	while ((*list)->argv && (*list)->argv[n])
	{
		free((*list)->argv[n]);
		n++;
	}
	if ((*list)->argv)
		free((*list)->argv);
	if ((*list)->command)
		free((*list)->command);
	if ((*list)->bin)
		free((*list)->bin);
	free(*list);
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
	*list = NULL;
}
