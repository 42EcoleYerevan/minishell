/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:32:05 by agladkov          #+#    #+#             */
/*   Updated: 2023/05/17 17:01:34 by agladkov         ###   ########.fr       */
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
	while (*str != ' ' && *str && *str != '|' && *str != '&' && *str != '>')
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

int ft_argc(char **arr)
{
	int n;

	n = 0;
	if (*arr[0] == '|' || *arr[0] == '&' || *arr[0] == '>')
		arr++;
	while (*arr && *arr[0] != '|' && *arr[0] != '&' && *arr[0] != '>') 
	{
		n++;
		arr++;
	}
	return (n);
}

char **ft_argv(char **arr)
{
	char **argv;
	char **tmp;

	argv = (char **)malloc(sizeof(char *) * ft_argc(arr) + 1);
	tmp = argv;
	if (!argv)
		return (NULL);
	if (*arr[0] == '|' || *arr[0] == '&' || *arr[0] == '>')
		arr++;
	while (*arr && *arr[0] != '|' && *arr[0] != '&' && *arr[0] != '>') 
	{
		*argv = *arr;
		argv++;
		arr++;
	}
	*argv = NULL;
	return (tmp);
}

char *ft_pathjoin(const char *path1, const char *path2)
{
	char *out;
	char *tmp;

	tmp = ft_strjoin(path1, "/");
	out = ft_strjoin(tmp, path2);
	free(tmp);
	return (out);
}

char *ft_command_path_join(char *command)
{
	char *path;
	char *tmp;

	tmp = ft_find_path(command);
	path = ft_pathjoin(tmp, command); 
	free(tmp);
	return (path);
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

void ft_exec(char *command_path, char **argv)
{
	int pid;

	pid = fork();
	if (pid == 0)
		execve(command_path, argv, ENV);
	else
		wait(&pid);
}

void ft_loop(void)
{
	char *str;
	char **arr;
	char **argv;
	char *tmp_str;
	char *path;

	str = readline("minishel>$ ");
	while (*str)
	{
		tmp_str = ft_substr(str, 0, ft_len_construction(str));
		arr = ft_parse_construction(tmp_str);
		if (arr[0][0] == '|' || \
			arr[0][0] == '&' || \
			arr[0][0] == '>')
			arr++;
		argv = ft_argv(arr);
		path = ft_command_path_join(*arr);
		ft_exec(path, argv);
		str += ft_strlen(tmp_str);
		free(tmp_str);
		free(path);
		ft_free_2d_array_with_null(arr);
	}
}

int main(int argc, char **argv, char **env)
{
	(void) argv;
	ENV = env;
	if (argc == 1)
		ft_loop();
	return (0);
}
