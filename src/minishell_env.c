#include "../minishell.h"

char *ft_get_env_key(char *var)
{
	char **tmp;
	int	len;

	len = ft_strlen(var);
	tmp = ENV;
	while (*tmp)
	{
		if (ft_strncmp(*tmp, var, len)  == 0)
			return (*tmp);
		tmp++;
	}
	return (NULL);
}

/* int ft_check_env_key(char *key) */
/* { */

/* } */

char *ft_get_env_value(char *var)
{
	char *env_var;
	int n;

	env_var = ft_get_env_key(var);
	if (!env_var)
		return (NULL);
	n = 0;
	while (env_var[n] != '=')
		n++;
	n++;
	return (ft_substr(env_var, n, ft_strlen(env_var) - n));
}
