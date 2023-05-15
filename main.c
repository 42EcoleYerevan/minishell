/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:32:05 by agladkov          #+#    #+#             */
/*   Updated: 2023/05/15 15:36:04 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

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
	while (*str != ' ' && *str)
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

char *ft_get_env(char *env)
{
	char **tmp;
	char *out;

	out = "";
	tmp = ENV;
	while (*tmp)
	{
		if (ft_strncmp(*tmp, env, ft_strlen(env)) == 0)
			return (*tmp);
		tmp++;
	}
	return (out);
}

char *ft_get_value(char *env)
{
	char *env_var;
	int n;

	env_var = ft_get_env(env);
	n = 0;
	while (env_var[n] != '=')
		n++;
	n++;
	return (ft_substr(env_var, n, ft_strlen(env_var) - n));
}

void ft_free_2d_array_with_null(char **array)
{
	if (!array)
		return ;
	while (*array)
	{
		free(*array);
		array++;
	}
	/* free(array); */
}

char *ft_check_path(char *path, char *command, DIR *d)
{
	struct dirent *file;

	file = readdir(d);
	while (file)
	{
		if (ft_strncmp(command, file->d_name, ft_strlen(file->d_name)) == 0)
			return (ft_strdup(path));
		file = readdir(d);
	}
	return (NULL);
}

char *ft_find_path(char *command)
{
	DIR *d;
	char **paths;
	char *out;

	paths = ft_split(ft_get_value("PATH"), ':');
	if (!paths)
		return (NULL);
	while (*paths)
	{
		d = opendir(*paths);
		out = ft_check_path(*paths, command, d);
		if (out)
		{
			ft_free_2d_array_with_null(paths);
			closedir(d);
			return (out);
		}
		free(*paths);
		paths++;
	}
	ft_free_2d_array_with_null(paths);
	closedir(d);
	return (NULL);
}

int ft_is_valid_path(char *path)
{
	DIR *d;

	d = opendir(path);
	if (!d)
		return (0);
	closedir(d);
	return (1);
}

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

int ft_len_commands(char *str)
{
	int n;

	n = 0;
	str += ft_len_spaces(str);
	while (*str)
	{
		n++;
		str += ft_len_spaces(str);
		if (*str == '\'')
			str += ft_len_quote(str, '\'');
		else if (*str == '\"')
			str += ft_len_quote(str, '\"');
		else
			str += ft_len_word(str);
	}
	return (n);
}

char **ft_parse_commands(char *str)
{
	char **out;
	char **tmp;

	out = (char **)malloc(sizeof(char *) * (ft_len_commands(str) + 1));
	tmp = out;
	if (!out)
		return (NULL);
	while (*str)
	{
		str += ft_len_spaces(str);
		if (*str == '\'')
			*out = ft_substr(str, 0, ft_len_quote(str, '\''));
		else if (*str == '\"')
			*out = ft_substr(str, 0, ft_len_quote(str, '\"'));
		else
			*out = ft_substr(str, 0, ft_len_word(str));
		if (!*out)
		{
			ft_free_2d_array_with_null(out);
			return (NULL);
		}
		str += ft_strlen(*out);
		out++;
	}
	*out = NULL;
	return (tmp);
}

int main(int argc, char **argv, char **env)
{
	argc = 0;
	(void) argv;

	ENV = env;


	char *str;

	str = readline("minishel>$ ");
	char **out = ft_parse_commands(str);
	while (*out)
	{
		printf("%s\n", *out);
		out++;
	}
	return (0);
}
