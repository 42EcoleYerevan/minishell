#include "../minishell.h"

static int ft_len_env(char *str)
{
	int len;
	char *value;

	len = 0;
	while (*str)
	{
		if (*str == '$')
		{
			value = ft_get_env_value_by_name(str + 1);
			len += ft_strlen(value);
			str += ft_len_word(str + 1) + 1;
			free(value);
		}
		else
		{
			len++;
			str++;
		}
	}
	return (len);
}

static void ft_insert_str(char *dst, char *src)
{
	char *value;

	while (*src)
	{
		if (*src == '$')
		{
			value = ft_get_env_value_by_name(src + 1);
			ft_strlcpy(dst, value, ft_strlen(value) + 1);
			dst += ft_strlen(value);
			src += ft_len_word(src + 1) + 1;
			free(value);
		}
		else
		{
			*dst = *src;
			dst++;
			src++;
		}
	}
	*dst = '\0';
}

static char *ft_set_env(char *str)
{
	int len;
	char *out;

	if (!str)
		return (NULL);
	if (ft_strchr(str, '$') == 0)
		out = ft_strdup(str);
	else
	{
		len = ft_len_env(str);
		out = (char *)malloc(sizeof(char) * (len + 1));
		if (!out)
			return (NULL);
		ft_insert_str(out, str);
	}
	free(str);
	return (out);
}

static char **ft_set_commands(char *str, char **out)
{
	int n;

	if (!out)
		return (NULL);
	n = 0;
	str += ft_len_spaces(str);
	while (*str)
	{
		out[n] = ft_cut_command(str);
		if (*str != '\'')
			out[n] = ft_set_env(out[n]);
		out[n] = ft_delete_quotes(out[n]);
		str += ft_len_command(str);
		if (!out[n])
		{
			ft_free_2d_array_with_null(out);
			return (NULL);
		}
		str += ft_len_spaces(str);
		n++;
	}
	out[n] = NULL;
	return (out);
}

char **ft_parse_construction(char *str)
{
	char **out;
	int len;

	len = ft_amount_commands(str) + 1;
	out = (char **)malloc(sizeof(char *) * len);
	out = ft_set_commands(str, out);
	if (!out)
		return (NULL);
	return (out);
}
