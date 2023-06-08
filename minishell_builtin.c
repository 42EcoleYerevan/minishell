#include "minishell.h"

int    ft_pwd()
{
    char    path[PATH_MAX];

    if (getcwd(path, PATH_MAX))
    {
        ft_putstr_fd(path, 1);
        write(1, "\n", 1);
        return (0);
    }
    return (1);
}

int	ft_echo(char **args, int n)
{
	while (*args)
	{
		ft_putstr_fd(*args, 1);
		args++;
		if (*args)
			write (1, " ", 1);
	}
	if (!n)
		write(1, "\n", 1);
    return (0);
}

int     ft_env(t_env *env)
{
    while (env != NULL)
    {
		if (env->value == NULL)
		{
			env = env->next;
			continue ;
		}
        ft_putstr_fd(env->key, 1);
        write(1, "=", 1);
        ft_putstr_fd(env->value, 1);
        write(1, "\n", 1);
        env = env->next;
    }
    return (0);
}

int     ft_num_check(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (i >= 19 || arg[i] < '0' || arg[i] > '9')
            return (1);
        i++;
    }
    return (0);
}

int     ft_exit(char **args)
{
    if (ft_num_check(args[0]))
    {
        ft_putendl_fd("exit", 2);
        ft_putstr_fd("minishell: exit: ", 2);
        ft_putstr_fd(args[0], 2);
        ft_putendl_fd(": numeric argument required", 2);
        exit(1);
    }
    else if (args[1])
    {
        ft_putendl_fd("exit", 2);
        ft_putendl_fd("minishell: exit: too many arguments", 2);
        return (1);
    }
    ft_putendl_fd("exit", 1);
    exit(ft_atoi(args[0]));
    return (0);
}

int	ft_export_print(t_env *env)
{
	while (env)
	{
		if (!ft_strncmp("_", env->key, ft_strlen(env->key)))
		{
	        env = env->next;
			continue;
		}
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		if (env->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
        env = env->next;
	}
	return (0);
}

// Check the multiple "" and '' symbols
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

int ft_export(char **args, t_env **env)
{
	int		res;
	t_env	*last;

	res = 0;
	printf("EXPORT CHECK \n");
    if (args[0] == NULL)
	{
		res = ft_export_print(*env);
		return (res);
	}
	last = *env;
	while (last->next)
		last = last->next;
	while (*args)
	{
		last->next = ft_export_add(*args);
		if (last->next)
			last = last->next;
		if (!last)
			res = 1;
		args++;
	}
	return (res);
}

void ft_node_del(t_env **node)
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

int ft_unset(char **args, t_env **env)
{
	t_env	*tmp;
	t_env	*node;

	if (!(*args))
		return (0);
	node = *env;
	while (*args)
	{
		printf("HERE\n");
		while (node->next)
		{
			if (!ft_strncmp(node->next->key, *args, ft_strlen(*args)))
			{
				printf("FIND\n");
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