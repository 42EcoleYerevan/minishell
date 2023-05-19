#include "minishell.h"

char *ft_get_command(char *command)
{
	char *tmp;;

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

	tmp = ft_get_command(command);
	return (ft_substr(command, 0, tmp - command));
}

char *ft_cut_command(char *str)
{
	char *arr;

	if (*str == '\'')
		arr = ft_substr(str, 0, ft_len_quote(str, '\''));
	else if (*str == '\"')
		arr = ft_substr(str, 0, ft_len_quote(str, '\"'));
	else if (*str == '|' || *str == '&' || *str == '>')
		arr = ft_substr(str, 0, ft_len_separator(str));
	else
		arr = ft_substr(str, 0, ft_len_word(str));
	return (arr);
}
