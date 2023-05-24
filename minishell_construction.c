#include "minishell.h"

void ft_str_copy(char *dst, char *str, char *value)
{
	while (*str)
	{
		if (*str == '$')
		{
			while (*value)
			{
				*dst = *value;
				dst++;
				value++;
			}
			str += ft_len_word(str);
		}
		else
		{
			*dst = *str;
			str++;
			dst++;
		}
	}
}

void ft_swap_env(char *str)
{
	int n;
	int len;
	char *value;
	char *out;

	n = 0;
	while (str[n])
	{
		if (str[n] == '$')
		{
			len = ft_strlen(str);
			len -= ft_len_word(&str[n]);
			value = ft_substr(str,  n + 1, ft_len_word(&str[n + 1]));
			len += ft_strlen(value) + 1;
			out = (char *)malloc(sizeof(char) * len);
			value = ft_get_value(value);
			ft_str_copy(out, str, value);
			puts(out);
		}
		n++;
	}
}

char **ft_parse_construction(char *str)
{
	char **out;
	int n;
	int len;

	len = ft_len_commands(str) + 1;
	out = (char **)malloc(sizeof(char *) * len);
	if (!out)
		return (NULL);
	n = 0;
	str += ft_len_spaces(str);
	while (*str)
	{
		out[n] = ft_cut_command(str);
		if (!out[n])
		{
			ft_free_2d_array_with_null(out);
			return (NULL);
		}
		ft_swap_env(out[n]);
		str += ft_strlen(out[n]);
		str += ft_len_spaces(str);
		n++;
	}
	out[n] = NULL;
	return (out);
}

int ft_count_construction(char *str)
{
	int n;

	n = 0;
	while (*str)
	{
		n++;
		str += ft_len_construction(str);
	}
	return (n);
}
