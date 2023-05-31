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

char *ft_pathjoin(const char *path1, const char *path2)
{
	char *out;
	char *tmp;

	if (!path1 || !path2)
		return (NULL);
	tmp = ft_strjoin(path1, "/");
	out = ft_strjoin(tmp, path2);
	free(tmp);
	return (out);
}

int	ft_check_file_in_directory(char *dir_path, char *filename)
{
	DIR *d;
	struct dirent *dn;

	d = opendir(dir_path);
	if (!d)
		return (1);
	dn = readdir(d);
	while (dn)
	{
		if (ft_strncmp(dn->d_name, filename, ft_strlen(filename) + 1) == 0)
		{
			closedir(d);
			return (0);
		}
		dn = readdir(d);
	}
	closedir(d);
	return (1);
}

char *ft_check_file_in_current_directory(char *filename)
{
	char *pwd;
	char *out;

	pwd = ft_get_env_value("PWD");
	if (ft_check_file_in_directory(pwd, filename) == 0)
	{
		out = ft_pathjoin(pwd, filename);
		free(pwd);
		return (out);
	}
	return (NULL);
}
