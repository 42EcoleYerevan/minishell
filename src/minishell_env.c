#include "../minishell.h"

char	*ft_get_env_value_by_name(t_shell *shell, char *name)
{
	char	*tmp;
	char	*out;

	tmp = ft_substr(name, 0, ft_len_before_quote(name));
	out = ft_get_env_value(shell, tmp);
	free(tmp);
	return (out);
}

char	*ft_get_env_value(t_shell *shell, char *var)
{
	t_env	*tmp;

	tmp = shell->env;
	while (tmp && ft_strncmp(tmp->key, var, ft_strlen(var) + 1) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (ft_strdup(""));
	return (ft_strdup(tmp->value));
}

char	**ft_env_to_arr(t_env *env, int len, int i)
{
	t_env	*start;
	char	**arr;
	char	*tmp;

	start = env;
	while (env && ++len)
		env = env->next;
	arr = malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	arr[len] = NULL;
	while (start && ++i >= 0)
	{
		arr[i] = NULL;
		if (start->value)
			arr[i] = ft_strjoin("=", start->value);
		tmp = arr[i];
		arr[i] = ft_strjoin(start->key, arr[i]);
		free(tmp);
		start = start->next;
	}
	len = 0;
	/* while (arr[len]) */
	/* 	printf("%s\n", arr[len++]); */
	return (arr);
}
