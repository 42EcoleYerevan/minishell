#include "minishell.h"

void ft_free_2d_array_with_null(char **array)
{
	if (!array)
		return ;
	while (*array)
	{
		free(*array);
		array++;
	}
}

char *ft_get_env_value_by_name(char *str)
{
	char *tmp;
	char *out;

	tmp = ft_substr(str,  0, ft_len_word(str));
	out = ft_get_env_value(tmp);
	free(tmp);
	return (out);
}

