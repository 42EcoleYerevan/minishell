#include "minishell.h"

char *ft_get_absolute_path(char *command)
{
	char *path;
	char *tmp;

	tmp = ft_find_path(command);
	if (!tmp)
		path = ft_check_file_in_current_directory(command);
	else
		path = ft_pathjoin(tmp, command); 
	if (access(path, X_OK) == -1)
	{
		free(tmp);
		free(path);
		return (NULL);
	}
	free(tmp);
	return (path);
}
