/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 20:54:18 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/10 16:54:16 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_absolute_path(t_shell *shell, char *command)
{
	char	*path;
	char	*tmp;
	DIR		*d;

	d = opendir(command);
	if (d)
	{
		closedir(d);
		return (NULL);
	}
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
