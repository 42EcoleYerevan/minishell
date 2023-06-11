#include "../minishell.h"

int	ft_len_spaces(char *str)
{
	char	*tmp;

	tmp = str;
	while (*str && *str == ' ')
		str++;
	return (str - tmp);
}

int	ft_len_word(char *str)
{
	char	*tmp;

	tmp = str;
	while (*str
		&& *str != ' '
		&& *str != '|'
		&& *str != '&'
		&& *str != '>'
		&& *str != '<'
		&& *str != ';')
	{
		if (*str == '\"' || *str == '\'')
			str += ft_len_quote(str, *str);
		else
			str++;
	}
	return (str - tmp);
}

int	ft_len_quote(char *str, char quote)
{
	char	*tmp;

	tmp = str;
	str++;
	while (*str && *str != quote)
		str++;
	if (*str == '\0')
	{
		printf("Error\n");
		exit(1);
	}
	str++;
	return (str - tmp);
}

int	ft_len_separator(char *str)
{
	int		n;
	char	sep;

	n = 0;
	sep = 0;
	if (str[n] == '|'
		|| str[n] == '&'
		|| str[n] == '>'
		|| str[n] == '<'
		|| str[n] == ';')
		sep = str[n];
	while (str[n] && str[n] == sep)
		n++;
	return (n);
}

int	ft_len_command(char *str)
{
	if (*str == '|'
		|| *str == '&'
		|| *str == '>'
		|| *str == '<'
		|| *str == ';')
		return (ft_len_separator(str));
	else if (*str == '$')
		return (ft_len_word(str + 1) + 1);
	else
		return (ft_len_word(str));
}
