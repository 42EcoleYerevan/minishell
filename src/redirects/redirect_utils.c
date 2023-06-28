#include "minishell.h"

void ft_remove_redirect(char ***argv, int n)
{
	int	len;
	int step;

	if ((*argv)[n + 1])
		step = 2;
	else
		step = 1;
	len = ft_len_nullable_2d_array(*argv);
	while (n < len)
	{
		if (n + step < len && (*argv)[n + step])
			(*argv)[n] = (*argv)[n + step];
		else 
			(*argv)[n] = NULL;
		n++;
	}
}
