#include "minishell.h"
#include <stdio.h>

t_env	*ft_env_add(char *str)
{
	int		len;
	t_env	*newenv;

	newenv = (t_env *)malloc(sizeof(t_env));
	if (!newenv)
		return (NULL);
	len = ft_strlen(ft_strchr(str, '=') + 1);
	newenv->value = ft_substr(str, ft_strlen(str) - len, len);
	len = ft_strlen(str) - len - 1;
	newenv->key = malloc(len + 1);
	newenv->key[len] = '\0';
	while (len-- > 0)
		newenv->key[len] = str[len];
	newenv->next = NULL;
	return (newenv);
}

t_env	*ft_create_envlist(char	**arr)
{
	t_env	*newenv;
	t_env	*start;

	if (*arr == NULL)
		return (NULL);
	start = ft_env_add(*arr);
	arr++;
	newenv = start;
	while(*arr)
	{
		newenv->next = ft_env_add(*arr);
		newenv = newenv->next;
		arr++;
	}
	return (start);
}

int main(int argc, char **argv, char **env)
{
	t_env	*sss;
	char	*d[4];

	ft_cd(argv + 1);
	ft_pwd();
	return (0);
}
