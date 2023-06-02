#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_mlist
{
	struct s_mlist *next;
	struct s_mlist *prev;
	int	fd[2];
	char *bin;
	char **argv;
	char *command;
} t_mlist;

char **ENV;

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
char	*ft_cut_command(char *str);

// env
char	*ft_get_env_string(char *var);
char	*ft_get_env_value(char *var);

// len construction
int		ft_amount_constructions(char *str);
int		ft_len_construction(char *str);

// path
char	*ft_get_absolute_path(char *command);

// path utils
char	*ft_pathjoin(const char *path1, const char *path2);
char	*ft_find_path(char *command);
int		ft_check_file_in_directory(char *dir_path, char *filename);
int		ft_check_file_in_directory(char *dir_path, char *filename);
char	*ft_check_file_in_current_directory(char *filename);

// construction
int		ft_count_construction(char *str);
char	**ft_parse_construction(char *str);

// utils
void	ft_free_2d_array_with_null(char **array);
char	*ft_get_env_value_by_name(char *str);

// list utils
t_mlist	*ft_list_new(char **argv, char *command);
t_mlist	*ft_list_last(t_mlist *list);
void	ft_list_add_front(t_mlist **list, t_mlist *new);
void	ft_list_add_back(t_mlist **list, t_mlist *new);
void	ft_list_clear(t_mlist **list);

// fill list
t_mlist *ft_fill_list(char *str);

// pipex
void ft_pipex(t_mlist *list);

#endif
