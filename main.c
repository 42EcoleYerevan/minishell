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

void main_loop(void)
{
	char *str;
	char *tmp;
	char *command;

	while (1)
	{
		str = readline("minishel>$ ");
		tmp = str;
		while (*str)
		{
			str += ft_len_spaces(str);
			if (*str == '\'')
				command = ft_substr(str, 0, ft_len_quote(str, '\''));
			else if (*str == '\"')
				command = ft_substr(str, 0, ft_len_quote(str, '\"'));
			else
				command = ft_substr(str, 0, ft_len_word(str));
			str += ft_strlen(command);
			ft_putstr_fd(command, 1);
			ft_putchar_fd('\n', 1);
			free(command);
		}
		free(tmp);
	}
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

char *ft_find_path(char *command)
{
	DIR *d;
	struct dirent *file;
	char **paths;
	char *out;

	paths = ft_split(ft_get_value("PATH"), ':');
	if (!paths)
		return (NULL);
	while (*paths)
	{
		d = opendir(*paths);
		free(*paths);
		file = readdir(d);
		while (file)
		{
			if (ft_strncmp(command, file->d_name, ft_strlen(file->d_name)) == 0)
			{
				out = ft_strdup(*paths);
				ft_free_2d_array_with_null(paths);
				closedir(d);
				return (out);
			}
			file = readdir(d);
		}
		paths++;
	}
	ft_free_2d_array_with_null(paths);
	closedir(d);
	return (NULL);
}

int main(int argc, char **argv, char **env)
{
	argc = 0;
	(void) argv;

	/* char *path; */

	ENV = env;
	/* path = ft_get_env("PATH"); */
	/* puts(path); */
	/* puts(ft_get_value("PATH")); */
	/* path = ft_get_env("SHELL"); */
	/* puts(path); */
	/* puts(ft_get_value("SHELL")); */
	/* path = ft_get_env("LOGNAME"); */
	/* puts(path); */
	/* puts(ft_get_value("LOGNAME")); */

	/* while (*env) */
	/* { */
	/* 	printf("%s\n", *env); */
	/* 	env++; */
	/* } */

	printf("%s\n", ft_find_path("ls"));

	return (0);
}
