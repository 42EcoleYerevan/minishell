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
        ft_putstr_fd(env->key, 1);
        write(1, "=", 1);
        ft_putstr_fd(env->value, 1);
        write(1, "\n", 1);
        env = env->next;
    }
    return (0);
}

int     ft_exit(t_env *env, char **args)
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
    }
    ft_putendl_fd("exit", 2);
    exit(ft_atoi(args[0]));
}