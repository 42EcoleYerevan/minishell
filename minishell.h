#ifndef MINISHELL_H
# define MINISHELL_H

//Libraries
# include <unistd.h>
# include <limits.h>
# include "libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <dirent.h>


//Types
typedef struct s_env
{
    char			*key;
    char			*value;
    struct s_env	*next;
}	t_env;

//minishell_create_envlist
t_env	*ft_env_add(char *str);
t_env	*ft_create_envlist(char	**arr);

//minishell_builtin
int		ft_pwd();
int		ft_echo(char **args, int n);
int		ft_env(t_env *env);
int		ft_exit(char **args);
int 	ft_export(char **args, t_env **env);
int		ft_unset(char **args, t_env **env);
int	    ft_cd(char	**args);

//minishell_builtin_utils
int		ft_num_check(char *arg);
int		ft_export_print(t_env *env);
t_env	*ft_export_add(char *str);
void	ft_node_del(t_env **node);
int		ft_find_env(char *str, t_env *env);
void	ft_export_change(t_env *env, char *str);

#endif
