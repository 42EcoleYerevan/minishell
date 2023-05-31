#include "minishell.h"

static char *ft_check_path(char *path, char *command, DIR *d)
{
	struct dirent *file;

	file = readdir(d);
	while (file)
	{
		if (ft_strncmp(command, file->d_name, ft_strlen(file->d_name) + 1) == 0)
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

	paths = ft_split(ft_get_env_value("PATH"), ':');
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

static int ft_is_valid_path(char *path)
{
	DIR *d;

	d = opendir(path);
	if (!d)
		return (0);
	closedir(d);
	return (1);
}

static char *ft_pathjoin(const char *path1, const char *path2)
{
	char *out;
	char *tmp;

	tmp = ft_strjoin(path1, "/");
	out = ft_strjoin(tmp, path2);
	free(tmp);
	return (out);
}

char *ft_get_absolute_path(char *command)
{
	char *path;
	char *tmp;

	tmp = ft_find_path(command);
	path = ft_pathjoin(tmp, command); 
	if (access(path, X_OK) == -1)
	{
		free(tmp);
		free(path);
		return (NULL);
	}
	if (ft_is_valid_path(tmp) == 0)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (path);
}
