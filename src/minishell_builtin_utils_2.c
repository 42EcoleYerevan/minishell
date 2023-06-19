/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_utils_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 21:29:30 by almeliky          #+#    #+#             */
/*   Updated: 2023/06/19 17:17:32 by almeliky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_export_add(char *str)
{
	int		len;
	t_env	*newenv;

	newenv = (t_env *)malloc(sizeof(t_env));
	if (!newenv)
		return (NULL);
	len = ft_strlen(str);
	if (ft_strchr(str, '='))
	{
		len = ft_strlen(ft_strchr(str, '=') + 1);
		newenv->value = ft_substr(str, ft_strlen(str) - len, len);
		len = ft_strlen(str) - len - 1;
	}
	else
		newenv->value = NULL;
	newenv->key = malloc(len + 1);
	newenv->key[len] = '\0';
	while (len-- > 0)
		newenv->key[len] = str[len];
	newenv->next = NULL;
	return (newenv);
}

void	ft_export_errprint(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	while (*arg)
		write(2, arg++, 1);
	ft_putendl_fd("': not a valid identifier", 2);
}

int	ft_export_valid(char *arg, int *res)
{
	int	status;
	int	i;
	
	i = 0;
	if (!arg)
		return (0);
	status = 0;
	if (ft_isdigit(arg[0]) || arg[0] == '=')
		status = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			status = 1;
			break ;
		}
		i++;
	}
	*res = status;
	if (status)
		ft_export_errprint(arg);
	return (status);
}

void	ft_node_del(t_env **node)
{
	if (!(*node))
		return ;
	if ((*node)->key)
		free((*node)->key);
	(*node)->key = NULL;
	if ((*node)->value)
		free((*node)->value);
	(*node)->value = NULL;
	free(*node);
	node = NULL;
}

int	ft_num_check(char *arg)
{
	int					i;
	unsigned long long	max;
	unsigned long long	check;

	max = 9223372036854775807;
	i = 0;
	if (*arg == '-' || *arg == '+')
		arg++;
	if (ft_strlen(arg) > 19)
		return (1);
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	check = 0;
	i = 0;
	while (arg[i])
	{
		check *= 10;
		check += arg[i] - '0';
		i++;
	}
	return (check > max);
}