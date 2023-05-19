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
	while (*str == '|' || *str == '&' || *str == '>')
	{
		n++;
		str++;
	}
	while (*str && *str != '|' && *str != '&' && *str != '>')
	{
		n++;
		str++;
	}
	return (n);
}

