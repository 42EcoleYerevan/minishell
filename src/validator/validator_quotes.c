#include "minishell.h"

static int ft_len_next_quote(char *str)
{
	char	current_quote;
	int		n;

	n = 1;
	current_quote = str[0];
	while (str[n] && str[n] != current_quote)
		n++;
	return (n);
}

int ft_check_quotes_in_string(char *str)
{
	int i;
	/* int	len; */

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			i += ft_len_next_quote(str + i);
			if (str[i] == '\0' )
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_unclosed_quotes_in_argv(char **argv)
{
	int	n;

	n = 0;
	while (argv[n])
	{
		if (ft_check_quotes_in_string(argv[n]))
			return (1);
		n++;
	}
	return (0);
}

int	ft_is_valid_argv(t_mlist *list)
{
	int	error;
	int	n;

	n = 0;
	while (list->argv[n])
	{
		error = ft_check_unclosed_quotes_in_argv(list->argv);
		if (error)
			return (error);
		error = ft_check_redirect_error(list, n);
		if (error)
			return (error);
		n++;
	}
	return (0);
}
