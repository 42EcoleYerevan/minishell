#include "minishell.h"

int ft_len_commands(char *str)
{
	int n;

	n = 0;
	str += ft_len_spaces(str);
	while (*str)
	{
		n++;
		if (*str == '\'')
			str += ft_len_quote(str, '\'');
		else if (*str == '\"')
			str += ft_len_quote(str, '\"');
		else if (*str == '|' || *str == '&' || *str == '>')
			str += ft_len_separator(str);
		else if (*str == '$')
			str += ft_len_word(str + 1) + 1;
		else
			str += ft_len_word(str);
		str += ft_len_spaces(str);
	}
	return (n);
}


int ft_len_construction(char *str)
{
	int n;

	n = 0;
	while (*str && *str != '|' && *str != '&' && *str != '>')
	{
		n++;
		str++;
	}
	n += ft_len_separator(str);
	str += ft_len_separator(str);
	n += ft_len_spaces(str);
	return (n);
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
