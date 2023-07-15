#include "minishell.h"

t_mlist *ft_create_list(t_shell *shell, char **tokens)
{
	int	n;
	int len;
	char **argv;
	t_mlist *new;
	t_mlist	*list;

	n = 0;
	list = NULL;
	while (tokens[n])
	{
		len = ft_token_count_in_construction(tokens + n);
		argv = ft_slice_arr(tokens, n, n + len);
		new = ft_list_new(shell, argv, ft_find_token(tokens + n, "|"));
		ft_list_add_back(&list, new);
		if (!tokens[n + len])
			break ;
		n += len + 1;
	}
	return (list);
}

char **ft_slice_arr(char **arr, int start, int end)
{
	char	**out;
	int		n;

	out = (char **)malloc(sizeof(char *) * (end - start + 1));
	n = 0;
	while (start < end)
	{
		out[n] = ft_substr(arr[start], 0, ft_strlen(arr[start]));
		start++;
		n++;
	}
	out[n] = NULL;
	return (out);
}

char *ft_find_token(char **tokens, char *token)
{
	int	n;

	n = 0;
	while (tokens[n] && \
			ft_strncmp(tokens[n], token, ft_strlen(token) + 1) != 0)
		n++;
	return (tokens[n]);
}

int		ft_token_count_in_construction(char **tokens)
{
	int	n;

	n = 0;
	while (tokens[n])
	{
		if (tokens[n][0] == '|') 
			return (n);
		n++;
	}
	return (n);
}

void	ft_set_env_token(t_shell *shell, char **tokens)
{
	int	n;

	n = 0;
	while (tokens[n])
	{
		ft_change_element_with_free(shell, tokens, n);
		n++;
	}
}
