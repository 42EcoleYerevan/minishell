#include "minishell.h"

char **ft_parse_construction(char *str)
{
	char **out;
	int n;
	int len;

	len = ft_len_commands(str) + 1;
	out = (char **)malloc(sizeof(char *) * len);
	if (!out)
		return (NULL);
	n = 0;
	str += ft_len_spaces(str);
	while (*str)
	{
		out[n] = ft_cut_command(str);
		if (!out[n])
		{
			ft_free_2d_array_with_null(out);
			return (NULL);
		}
		str += ft_strlen(out[n]);
		str += ft_len_spaces(str);
		n++;
	}
	out[n] = NULL;
	return (out);
}

int ft_count_construction(char *str)
{
	int n;

	n = 0;
	while (*str)
	{
		n++;
		str += ft_len_construction(str);
	}
	return (n);
}
