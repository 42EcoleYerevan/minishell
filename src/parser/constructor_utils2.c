#include "minishell.h"

int ft_len_between_quotes(char *str);

void	ft_change_element_with_free(t_shell *shell, char **out, int n)
{
	char	*tmp;

	tmp = ft_set_env(shell, out[n]);
	free(out[n]);
	out[n] = tmp;
}

int	ft_len_without_quotes(char *str)
{
	int	n;
	int	len;

	n = 0;
	while (*str)
	{
		len = 0;
		if (*str == '\'' || *str == '\"')
		{
			n += ft_len_between_quotes(str);
			str += ft_len_quote(str, *str);
		}
		else
		{
			n++;
			str++;
		}
	}
	return (n);
}

int ft_len_between_quotes(char *str)
{
	int	n;

	if (*str != '\'' && *str != '\"')
		return (0);
	n = ft_len_quote(str, *str);
	return (n - 2);
}

void	ft_copy_between_quotes(char *dst, char *src)
{
	char quote;

	if (*src != '\'' && *src != '\"')
		return ;
	quote = *src++;
	while (*src && *src != quote)
		*dst++ = *src++;
}

char	*ft_delete_quotes(char *str)
{
	char	*out;
	int		indx;
	int		len;

	len = ft_len_without_quotes(str);
	printf("%d\n", len);
	out = (char *)malloc(sizeof(char) * (len + 1));
	if (!out)
	{
		free (str);
		return (NULL);
	}
	indx = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			ft_copy_between_quotes(out + indx, str);
			indx += ft_len_between_quotes(str);
			str += ft_len_quote(str, *str);
		}
		else
		{
			out[indx] = *str;
			str++;
			indx++;
		}
	}
	out[len] = '\0';
	return (out);
}
