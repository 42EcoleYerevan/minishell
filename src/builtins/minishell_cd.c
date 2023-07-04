/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:42:30 by almeliky          #+#    #+#             */
/*   Updated: 2023/07/01 17:10:38 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_change(char *arg, t_env **env)
{
	t_env	*last;

	last = *env;
	if (ft_find_env(arg, *env))
		return ;
	while (last->next)
		last = last->next;
	ft_export_add(arg, &last);
}

int	ft_cd_key(char	**args, t_env **env, char *str)
{
	if (!args || !args[0])
	{
		str = ft_value_by_key("HOME", *env);
		return (ft_cd(&str, env, NULL, 0));
	}
	if (ft_strncmp(args[0], "-", ft_strlen(args[0])) == 0)
	{
		str = ft_value_by_key("OLDPWD", *env);
		if (str)
		{
			ft_cd(&str, env, NULL, 0);
			return (ft_pwd());
		}
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return (1);
	}
	if (args[0][0] == '~')
	{
		str = ft_strjoin(ft_value_by_key("HOME", *env), *args + 1);
		return (ft_cd(&str, env, NULL, 0));
	}
	return (0);
}

void	ft_cd_err(char **args, int *status)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(args[0], 2);
	if (errno == 13)
		ft_putendl_fd(": Permission denied", 2);
	else if (*status == -1)
		ft_putendl_fd(": No such file or directory", 2);
	else
		ft_putendl_fd(": Not a directory", 2);
	*status = 1;
}

int	ft_cd(char	**args, t_env **env, char *str, int status)
{
	DIR		*tmp;
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	if (!args || !args[0] || ft_strncmp(args[0], "-", 2) == 0
		|| args[0][0] == '~')
		return (ft_cd_key(args, env, str));
	tmp = opendir(args[0]);
	status = access(args[0], F_OK);
	if (chdir(args[0]) == -1)
		ft_cd_err(args, &status);
	if (!status)
	{
		ft_cd_change(ft_strjoin("OLDPWD=", path), env);
		getcwd(path, PATH_MAX);
		ft_cd_change(ft_strjoin("PWD=", path), env);
	}
	if (tmp)
		closedir(tmp);
	return (status);
}
