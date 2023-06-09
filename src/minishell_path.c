#include "../minishell.h"

char *ft_get_absolute_path(t_shell *shell, char *command)
{
	char *path;
	char *tmp;

	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	tmp = ft_find_path(shell, command);
	if (!tmp)
		path = ft_check_file_in_current_directory(shell, command);
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
