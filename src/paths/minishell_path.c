/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:54:18 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/19 17:23:50 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path(t_shell *shell, char *command)
{
	char	*tmp_path;
	char	*path;

	tmp_path = ft_find_path(shell, command);
	if (!tmp_path)
		path = ft_check_file_in_current_directory(shell, command);
	else
		path = ft_pathjoin(tmp_path, command);
	if (tmp_path)
		free(tmp_path);
	return (path);
}

int	ft_is_dir(char *path)
{
	DIR	*d;

	d = opendir(path);
	if (d)
	{
		closedir(d);
		return (1);
	}
	return (0);
}

int	ft_is_executable(char *path)
{
	if (access(path, X_OK) == 0)
		return (1);
	return (0);
}

char	*ft_get_absolute_path(t_shell *shell, char *command)
{
	char	*path;

	if (!command)
		return (NULL);
	if (ft_is_dir(command))
		return (NULL);
	if (ft_is_executable(command))
		return (ft_strdup(command));
	path = ft_get_path(shell, command);
	return (path);
}
