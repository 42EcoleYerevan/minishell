#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <readline/readline.h>
#include "libft/libft.h"

typedef struct s_mlist
{
	struct s_mlist *next;
	struct s_mlist *prev;
	char **argv;
	char *command;
} t_mlist;

char **ENV;

// len_utils
int		ft_len_spaces(char *str);
int		ft_len_word(char *str);
int		ft_len_quote(char *str, char quote);
int		ft_len_separator(char *str);

// argc argv
int		ft_argc(char **arr);
char	**ft_argv(char **arr);

// command
char	*ft_get_command(char *command);
char	*ft_get_command_path(char *command);
char	*ft_cut_command(char *str);

// env
char	*ft_get_env(char *var);
char	*ft_get_value(char *var);

// len construction
int		ft_len_commands(char *str);
int		ft_len_construction(char *str);

// path
char	*ft_check_path(char *path, char *command, DIR *d);
char	*ft_find_path(char *command);
int		ft_is_valid_path(char *path);
char	*ft_pathjoin(const char *path1, const char *path2);
char	*ft_command_path_join(char *command);

// construction
int		ft_count_construction(char *str);
char	**ft_parse_construction(char *str);

// utils
void	ft_free_2d_array_with_null(char **array);

// list utils
t_mlist	*ft_list_new(char **argv, char *command);
t_mlist	*ft_list_last(t_mlist *list);
void	ft_list_add_front(t_mlist **list, t_mlist *new);
void	ft_list_add_back(t_mlist **list, t_mlist *new);
void	ft_list_clear(t_mlist **list);

// fill list
t_mlist *ft_fill_list(char *str);

#endif
