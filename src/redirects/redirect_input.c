#include "minishell.h"

int ft_check_one_redirect_input_argument(t_mlist *list, int n)
{
	int check;
	struct dirent *f;
	DIR *d;

	check = ft_check_next_redirect_input_argument(list, n);
	if (check == 0)
	{
		if (access(list->argv[n + 1], R_OK) == 0)
			return (0);
		d = opendir("./");
		f = readdir(d);
		while (f )
		{
			if (ft_strncmp(list->argv[n + 1],
					   	f->d_name,
					   	ft_strlen(f->d_name) + 1) == 0)
				return (0);
			f = readdir(d);
		}
		printf("minishell: %s: No such file or directory\n", list->argv[n + 1]);
		rl_on_new_line();
		return (1);
	}
	return (check);
}

int ft_one_redirect_input(t_mlist *list, int n)
{
	int check;

	check = ft_check_one_redirect_input_argument(list, n);
	if (check == 0)
		list->heredoc[0] = open(list->argv[n + 1], O_RDONLY);
	return (check);
}

int ft_check_next_redirect_input_argument(t_mlist *list, int n)
{
	if (list->argv[n + 1] && ft_strchr("<>|;&", list->argv[n + 1][0]) == NULL)
		return (0);	
	if (list->argv[n + 1] == NULL)
		ft_redirect_unexpected_error("newline");
	else
		ft_redirect_unexpected_error(list->argv[n + 1]);
	return (1);
}

int ft_two_redirect_input(t_mlist *list, int n)
{
	int check;
	int lenkey;
	char *string;

	check = ft_check_next_redirect_input_argument(list, n);
	if (check == 0)
	{
		lenkey = ft_strlen(list->argv[n + 1]) + 1;
		list->isheredoc = 1;
		pipe(list->heredoc);
		string = readline(">");
		while (ft_strncmp(string, list->argv[n + 1], lenkey) != 0)
		{
			write(list->heredoc[1], string, ft_strlen(string));
			write(list->heredoc[1], "\n", 1); string = readline(">");
		}
	}
	return (check);
}

int ft_redirect_input(t_mlist *list, int n)
{
	int out;

	if (ft_strncmp(list->argv[n], "<", 2) == 0)
		out = ft_one_redirect_input(list, n);
	else
		out = ft_two_redirect_input(list, n);
	ft_remove_redirect(&list->argv, n);
	if (out == 0)
		list->isinput = 1;
	return (out);
}
