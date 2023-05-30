#include "minishell.h"

char *ft_get_env(char *var)
{
	char **tmp;

	tmp = ENV;
	while (*tmp)
	{
		if (ft_strncmp(*tmp, var, ft_strlen(var)) == 0)
			return (*tmp);
		tmp++;
	}
	return ("");
}

char *ft_get_env_value(char *var)
{
	char *env_var;
	int n;

	env_var = ft_get_env(var);
	n = 0;
	while (env_var[n] != '=')
		n++;
	n++;
	return (ft_substr(env_var, n, ft_strlen(env_var) - n));
}
