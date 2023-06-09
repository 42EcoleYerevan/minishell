#ifndef MINISHELL_H
# define MINISHELL_H


//Libraries
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

//Types
typedef struct s_mlist
{
	struct s_mlist *next;
	struct s_mlist *prev;
	int	fd[2];
	char *bin;
	char **argv;
	char *command;
} t_mlist;

typedef struct s_env
{
    char			*key;
    char			*value;
    struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	struct s_mlist	**list;
	struct s_env	*env;
	int 			err_status;
} t_shell;

// len_utils
int		ft_len_spaces(char *str);
int		ft_len_word(char *str);
int		ft_len_quote(char *str, char quote);
int		ft_len_separator(char *str);
int		ft_len_command(char *str);

// argc argv
int		ft_argc(char **arr);
char	**ft_argv(char **arr);

// command
int		ft_amount_commands(char *str);
char	*ft_get_command_from_path(char *command);
char	*ft_get_command_path(char *command);

// env
char	*ft_get_env_value(t_shell *shell, char *var);
char	*ft_get_env_value_by_name(t_shell *shell, char *str);

// len construction
int		ft_amount_constructions(char *str);
int		ft_len_construction(char *str);

// path
char	*ft_get_absolute_path(t_shell *shell, char *command);

// path utils
char	*ft_pathjoin(const char *path1, const char *path2);
char	*ft_find_path(t_shell *shell, char *command);
char	*ft_check_file_in_current_directory(t_shell *shell, char *filename);

// construction
int		ft_count_construction(char *str);
char	**ft_parse_construction(t_shell *shell, char *str);
char	*ft_set_env(t_shell *shell, char *str);

// construction utils
int		ft_num_quotes(char *str);
char	*ft_delete_quotes(char *str);

// parse utils
int		ft_len_before_quote(char *str);
char	*ft_parse_quotes(t_shell *shell, char *str);

// utils
void	ft_free_2d_array_with_null(char **array);
void	ft_list_clear(t_mlist **list);
void	ft_free_2_linked_list(t_mlist **list);

// list utils
t_mlist *ft_list_new(t_shell *shell, char **argv, char *command);
t_mlist	*ft_list_last(t_mlist *list);
void	ft_list_add_front(t_mlist **list, t_mlist *new);
void	ft_list_add_back(t_mlist **list, t_mlist *new);
void	ft_list_clear(t_mlist **list);

// fill list
t_mlist *ft_fill_list(t_shell *shell, char *str);
	
// pipex
void	ft_pipex(t_mlist *list);

// action
void	ft_action(int sig);
void	ft_quit(int sig);


//minishell_create_envlist
t_env	*ft_add_env(char *str);
t_env	*ft_create_envlist(char	**arr);

//minishell_builtin
void    ft_putstr_fd(char *s, int fd);
int     ft_pwd();
int     ft_echo(char **args, int n);
int     ft_env(t_env *env);

#endif
