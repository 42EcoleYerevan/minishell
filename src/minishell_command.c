#include "../minishell.h"

int ft_amount_commands(char *str)
{
	int n;

	n = 0;
	str += ft_len_spaces(str);
	while (*str)
	{
		n++;
		if (*str == '|' ||
			   	*str == '&' ||
			   	*str == '>' ||
			   	*str == '<' ||
			   	*str == ';')
			str += ft_len_separator(str);
		else if (*str == '$')
			str += ft_len_word(str + 1) + 1;
		else
			str += ft_len_word(str);
		str += ft_len_spaces(str);
	}
	return (n);
}

char *ft_get_command_from_path(char *command)
{
	char *tmp;;

	if (!command)
		return (NULL);
	tmp = command;
	while (*command)
		command++;
	while (command != tmp && *command != '/')
		command--;
	if (*command == '/')
		return (++command);
	return (command);
}

char *ft_get_command_path(char *command)
{
	char *tmp;

	tmp = ft_get_command_from_path(command);
	return (ft_substr(command, 0, tmp - command));
}
