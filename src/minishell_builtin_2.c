/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:26:30 by almeliky          #+#    #+#             */
/*   Updated: 2023/06/14 18:47:51 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(char **args, t_env **env)
{
	t_env	*tmp;
	t_env	*node;

	printf("unset here\n");
	if (!(*args))
		return (0);
	node = *env;
	while (*args)
	{
		while (node->next)
		{
			if (!ft_strncmp(node->next->key, *args, ft_strlen(*args)))
			{
				tmp = node->next;
				node->next = tmp->next;
				ft_node_del(&tmp);
				break ;
			}
			node = node->next;
		}
		args++;
		node = *env;
	}
	return (0);
}

int	ft_cd(char	**args, t_env **env, char *str, char *oldpwd)
{
	int		status;
	DIR		*tmp;
	char	path[PATH_MAX];

	status = 0;
	if (!args || !args[0])
	{
		str = ft_value_by_key("HOME", *env);
		return (ft_cd(&str, env, NULL, NULL));
	}
	if (ft_strncmp(args[0], "-", ft_strlen(args[0])) == 0)
	{
		str = ft_value_by_key("OLDPWD", *env);
		if (str)
			return (ft_cd(&str, env, NULL, NULL));
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return (1);
	}
	if (args[0][0] == '~')
	{
		str = ft_strjoin(ft_value_by_key("HOME", *env), &(args[0][1]));
		return (ft_cd(&str, env, NULL, NULL));
	}
	oldpwd = ft_value_by_key("PWD", *env);
	tmp = opendir(args[0]);
	status = access(args[0], F_OK);
	if (chdir(args[0]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(args[0], 2);
		if (errno == 13)
			ft_putendl_fd(": Permission denied", 2);
		else if (status == -1)
			ft_putendl_fd(": No such file or directory", 2);
		else
			ft_putendl_fd(": Not a directory", 2);
		status = 1;
	}
	if (!status)
	{
		getcwd(path, PATH_MAX);
		ft_export_change(ft_ptr_by_key("OLDPWD", *env), oldpwd);
		ft_export_change(ft_ptr_by_key("PWD", *env), path);
	}
	if (tmp)
		closedir(tmp);
	return (status);
}
