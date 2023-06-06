#ifndef MINISHELL_H
# define MINISHELL_H

//Libraries
# include <unistd.h>
# include <limits.h>
# include "libft/libft.h"

//Types
typedef struct s_env
{
    char			*key;
    char			*value;
    struct s_env	*next;
}	t_env;

//minishell_create_envlist
t_env	*ft_add_env(char *str);
t_env	*ft_create_envlist(char	**arr);

//minishell_builtin
void    ft_putstr_fd(char *s, int fd);
int     ft_pwd();
int     ft_echo(char **args, int n);
int     ft_env(t_env *env);

#endif