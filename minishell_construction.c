#include "minishell.h"

/* static void ft_str_insert(char *dst, char *str, char *value) */
/* { */
/* 	while (*str) */
/* 	{ */
/* 		if (*str == '$') */
/* 		{ */
/* 			ft_strlcpy(dst, value, ft_strlen(value) + 1); */
/* 			dst += ft_strlen(value); */
/* 			str += ft_len_word(str); */
/* 		} */
/* 		else */
/* 		{ */
/* 			*dst = *str; */
/* 			str++; */
/* 			dst++; */
/* 		} */
/* 	} */
/* 	*dst = '\0'; */
/* } */

/* static char *ft_get_env_value(char *str) */
/* { */
/* 	char *tmp; */
/* 	char *out; */

/* 	tmp = ft_substr(str,  0, ft_len_word(str)); */
/* 	out = ft_get_value(tmp); */
/* 	free(tmp); */
/* 	return (out); */
/* } */

/* static int ft_env_len(char *str) */
/* { */
/* 	int len; */
/* 	char *tmp; */

/* 	len = 0; */
/* 	while (*str) */
/* 	{ */
/* 		if (*str == '$') */
/* 		{ */
/* 			if (tmp) */
/* 				free(tmp); */
/* 			tmp = ft_substr(*str, */ 
/* 		} */
/* 		len++; */
/* 	} */
/* } */

/* char *ft_set_env(char *str) */
/* { */
/* 	int n; */
/* 	int len; */
/* 	char *value; */
/* 	char *out; */

/* 	n = 0; */
/* 	out = str; */
/* 	len = 0; */
/* 	while (str[n]) */
/* 	{ */
/* 		if (str[n] == '$') */
/* 		{ */
/* 			len += ft_strlen(str); */
/* 			len -= ft_len_word(&str[n]); */
/* 			value = ft_get_env_value(&str[n + 1]); */
/* 			len += ft_strlen(value); */
/* 			out = (char *)malloc(sizeof(char) * len); */
/* 			ft_str_insert(out, str, value); */
/* 		} */
/* 		n++; */
/* 	} */
/* 	return (out); */
/* } */

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
		str += ft_strlen(out[n]);
		/* out[n] = ft_set_env(out[n]); */
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
