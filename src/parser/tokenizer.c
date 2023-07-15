#include "minishell.h"

char	**ft_tokenizer(char *str)
{
	char	**tokens;
	int		n;

	if (!str || *str == '\0')
		return (NULL);
	n = ft_token_count(str);
	tokens = (char **)malloc(sizeof(char *) * (n + 1));
	if (!tokens)
		return (NULL);
	ft_split_token(tokens, str);
	return (tokens);
}
