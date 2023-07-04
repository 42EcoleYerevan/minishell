/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_path_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:35:39 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/04 17:35:40 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_file_in_directory(char *dir_path, char *filename)
{
	DIR				*d;
	struct dirent	*dn;

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

char	*ft_check_file_in_current_directory(t_shell *shell, char *filename)
{
	char	*pwd;
	char	*out;

	pwd = ft_get_env_value(shell, "PWD");
	if (ft_check_file_in_directory(pwd, filename) == 0)
	{
		out = ft_pathjoin(pwd, filename);
		free(pwd);
		return (out);
	}
	free(pwd);
	return (NULL);
}
