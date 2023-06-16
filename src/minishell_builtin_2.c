/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:26:30 by almeliky          #+#    #+#             */
/*   Updated: 2023/06/11 21:26:34 by almeliky         ###   ########.fr       */
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

int	ft_cd(char	**args)
{
	int		status;
	char	path[PATH_MAX];
	DIR		*tmp;

	if (!args || args[0] == NULL)
		return (0);
	getcwd(path, PATH_MAX);
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
	if (tmp)
		closedir(tmp);
	return (status);
}
