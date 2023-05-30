#include "minishell.h"

int ft_len_spaces(char *str)
{
	char *tmp;

	tmp = str;
	while (*str && *str == ' ')
		str++;
	return (str - tmp);
}

int ft_len_word(char *str)
{
	char *tmp;

	tmp = str;
	while (*str != ' ' &&
		   	*str &&
		   	*str != '|' &&
		   	*str != '&' &&
		   	*str != '>' &&
			*str != '<' &&
			*str != '$')
		str++;
	return (str - tmp);
}

int ft_len_quote(char *str, char quote)
{
	char *tmp;

	tmp = str;
	str++;
	while (*str && *str != quote)
		str++;
	str++;
	return (str - tmp);
}

int ft_len_separator(char *str)
{
	int n;

	n = 0;
	while (str[n] == '|' || str[n] == '&' || str[n] == '>')
		n++;
	return (n);
}
