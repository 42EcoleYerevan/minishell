#include "../minishell.h"

void print_list(t_mlist *list)
{
	int n;
	int l;

	l = 0;
	while (list)
	{
		printf("\033[33mlist #%d\n\033[0m", l++);
		printf("bin \t: %s\n", (list->bin));
		n = 0;
		while (list->argv[n])
		{
			printf("argv[%d]\t: %s\n", n, (list->argv[n]));
			n++;
		}
		if (list->argv[0] == NULL)
			printf("argv[0]\t: (null)\n");
		printf("command\t: %s\n", (list->command));
		if (list->next)
			printf("next\t: %p\n", list->next);
		else
			printf("next\t: NULL\n");
		if (list->prev)
			printf("prev\t: %p\n\n", list->prev);
		else
			printf("prev\t: NULL\n\n");
		list = list->next;
	}
}

static void	ft_close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

int ft_isbuiltin(char *path)
{
	char	*command;
	int		out;

	out = 0;
	command = ft_get_command_from_path(path);
	if (!command)
		out = 0;
	else if (ft_strncmp(command, "export", 7) == 0)
		out = 1;
	else if (ft_strncmp(command, "exit", 5) == 0)
		out = 2;
	else if (ft_strncmp(command, "cd", 3) == 0)
		out = 3;
	else if (ft_strncmp(command, "pwd", 4) == 0)
		out = 4;
	else if (ft_strncmp(command, "echo", 5) == 0)
		out = 5;
	else if (ft_strncmp(command, "env", 4) == 0)
		out = 6;
	else if (ft_strncmp(command, "unset", 6) == 0)
		out = 7;
	return (out);
}

int ft_check_n_flag(char **arr)
{
	if (!*arr)
		return (0);
	arr++;
	if (ft_strchr(*arr, 'n') == 0)
		return (1);
	return (0);
}

int	builtin_executor(t_shell *shell, t_mlist *list, int command)
{
	int out;

	printf("BUILTINS\n");
	out = 1;
	if (command == 1)
		out = ft_export(list->argv + 1, &shell->env);
	else if (command == 2)
		out = ft_exit(list->argv + 1);
	else if (command == 3)
		out = ft_cd(list->argv + 1, &shell->env, NULL, 0);
	else if (command == 4)
		out = ft_pwd();
	else if (command == 5)
	{
		if (ft_check_n_flag(list->argv))
			out = ft_echo(list->argv + 1, 0);
		else
			out = ft_echo(list->argv + 2, 1);
	}
	else if (command == 6)
		out = ft_env(shell->env);
	else if (command == 7)
		out = ft_unset(list->argv + 1, &shell->env, 0);
	return (out);
}

int ft_clear_file(char *filename)
{
	int	fd;

	if (!filename)
	{
		printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT);
	close(fd);
	return (0);
}

int	ft_redirect_error(char *command)
{
		printf("syntax error near unexpected token `%s`\n", command); 
		rl_on_new_line();
		return (1);
}

// echo leha > file.txt
/* void ft_redirect_output(t_shell *shell, t_mlist *list, int bltin, char **env) */
/* { */
/* 	int fd; */

/* 	fd = 0; */
/* 	if (list->command && list->next && list->next->argv[0]) */
/* 	{ */
/* 		if (ft_strncmp(list->command, ">", 2) == 0) */
/* 			fd = open(list->next->argv[0], O_WRONLY | O_TRUNC | O_CREAT, 0644); */
/* 		else if (ft_strncmp(list->command, ">>", 3) == 0) */
/* 			fd = open(list->next->argv[0], O_WRONLY | O_APPEND | O_CREAT, 0644); */
/* 		dup2(fd, 1); */
/* 	} */
/* 	else */ 
/* 		ft_redirect_error(list->next->command); */
/* 	if (bltin) */
/* 		exit(builtin_executor(shell, list, bltin)); */
/* 	execve(list->bin, list->argv, env); */
/* } */

/* void ft_heredoc(char *tgkey) */
/* { */
/* 	char *line; */
/* 	int tglen; */
/* 	int pipefd[2]; */
	   
/* 	pipe(pipefd); */
/* 	tglen = ft_strlen(tgkey); */
/* 	line = readline(">"); */
/* 	while (ft_strncmp(line, tgkey, tglen) != 0) */
/* 	{ */
/* 		write(pipefd[0], line, ft_strlen(line)); */
/* 		line = readline(">"); */
/* 	} */
/* } */

/* void ft_redirect_input(t_shell *shell, t_mlist *list, int bltin, char **env) */
/* { */
/* 	int fd; */

/* 	if (list->command) */
/* 	{ */
/* 		if (ft_strncmp(list->command, "<", 2) == 0) */
/* 			fd = open(list->next->argv[0], O_RDONLY | O_CREAT); */
/* 		else if (ft_strncmp(list->command, "<<", 3) == 0) */
/* 			ft_heredoc(list->next->argv[0]); */

/* 		dup2(fd, 0); */
/* 	} */
/* 	if (bltin) */
/* 		exit(builtin_executor(shell, list, bltin)); */
/* 	execve(list->bin, list->argv, env); */
/* } */

/* void ft_redirect_executor(t_shell *shell, t_mlist *list, int bltin, char **env) */
/* { */
/* 	if (list->command) */
/* 	{ */
/* 		if (list->command[0] == '>') */
/* 			ft_redirect_output(shell, list, bltin, env); */
/* 		/1* else if (list->command[0] == '<') *1/ */
/* 		/1* 	ft_redirect_input(shell, list, bltin, env); *1/ */
/* 	} */
/* } */

/* void ft_pipe_executor(t_shell *shell, t_mlist *list, int bltin, char **env) */
/* { */
/* 	if (list->prev == NULL && list->next == NULL) */
/* 		execve(list->bin, list->argv, env); */
/* 	if (list->next && */
/* 		(ft_strncmp(list->command, "|", 2) == 0)) */
/* 	{ */
/* 		dup2(list->fd[1], 1); */
/* 		close(list->fd[1]); */
/* 	} */
/* 	if (list->prev && ft_strncmp(list->prev->command, "|", 2) == 0) */
/* 	{ */
/* 		dup2(list->prev->fd[0], 0); */
/* 		ft_close_pipe(list->prev->fd); */
/* 	} */
/* 	if (bltin) */
/* 		exit(builtin_executor(shell, list, bltin)); */
/* 	execve(list->bin, list->argv, env); */
/* } */
void ft_remove_redirect(char ***argv, int n)
{
	int	len;
	int step;

	if ((*argv)[n + 1])
		step = 2;
	else
		step = 1;
	len = ft_len_nullable_2d_array(*argv);
	while (n < len)
	{
		if (n + step < len && (*argv)[n + step])
			(*argv)[n] = (*argv)[n + step];
		else 
			(*argv)[n] = NULL;
		n++;
	}
}

void ft_redirect_error_argument(t_mlist *list, int n)
{
	if (list->argv[n + 1])
		ft_redirect_error(list->argv[n + 1]);
	else
		ft_redirect_error("newline");
}

int ft_one_redirect_input(t_mlist *list, int n)
{
	int fd;
	int out;

	fd = 0;
	out = 1;
	if (list->argv[n + 1])
	{
		fd = open(list->argv[n + 1], O_RDONLY | O_TRUNC | O_CREAT);
		dup2(fd, 0);
		close(fd);
		out = 0;
	}
	else 
		ft_redirect_error_argument(list, n);
	return (out);
}

int ft_two_redirect_input(t_mlist *list, int n)
{
	int fd;
	int out;
	int lenkey;
	char *string;

	fd = 0;
	out = 1;
	lenkey = ft_strlen(list->argv[n + 1]) + 1;
	if (list->argv[n + 1])
	{
		pipe(list->fd);
		string = readline(">");
		while (ft_strncmp(string, list->argv[n + 1], lenkey) != 0)
		{
			write(list->fd[1], string, ft_strlen(string));
			write(list->fd[1], "\n", 1); string = readline(">");
		}
		out = 0;
	}
	else 
		ft_redirect_error_argument(list, n);
	return (out);
}

int ft_check_redirect_argument(t_mlist *list, int n)
{
	if (list->argv[n + 1] && ft_strchr("<>|;&", list->argv[n + 1][0]) == NULL)
		return (0);	
	if (list->argv[n + 1] == NULL)
		ft_redirect_error("newline");
	else
		ft_redirect_error(list->argv[n + 1]);
	return (1);
}

int ft_redirect_input(t_mlist *list, int n)
{
	int out;

	out = ft_check_redirect_argument(list, n);
	if (out == 0)
	{
		if (ft_strncmp(list->argv[n], "<", 2) == 0)
			out = ft_one_redirect_input(list, n);
		else
			out = ft_two_redirect_input(list, n);
	}
	ft_remove_redirect(&list->argv, n);
	return (out);
}

int ft_handle_redirect(t_mlist *list)
{
	int n;
	int out;

	n = 0;
	out = 1;
	while (list->argv[n])
	{
		if (list->argv[n][0] == '<')
			out = ft_redirect_input(list, n);
		else
			n++;
	}
	return (out);
}

void	executor(t_shell *shell)
{
	int		pid;
	int		red;
	t_mlist	*tmp;

	tmp = *shell->list;
	while (tmp)
	{
		red = ft_handle_redirect(tmp);
		if (red == 1)
			break;
		if (tmp->bin)
		{
			pid = fork();
			if (pid == 0)
			{
				dup2(tmp->fd[0], 0);
				if (red)
					ft_close_pipe(tmp->fd);
				execve(tmp->bin, tmp->argv, NULL);
			}
			ft_close_pipe(tmp->fd);
		}
		tmp = tmp->next;
	}
	while (wait(NULL) != -1)
		;
}

void ft_event_loop(t_shell *shell)
{
	char	*str;
	t_mlist	*list;
	while (1)
	{
		str = readline("minishell>$ ");
		add_history(str);
		ctrl_d_handler(str);
		list = ft_fill_list(shell, str);
		shell->list = &list;
		print_list(list);
		executor(shell);
		free(str);
		ft_free_2_linked_list(shell->list);
	}
}

int	main(int argc, char **argv, char **menv)
{
	t_shell	*shell;

	(void) argv;
	if (argc == 1)
	{
		shell = (t_shell *)malloc(sizeof(t_shell));
		shell->env = ft_create_envlist(menv);
		/* ft_init_action(); */
		rl_catch_signals = 0;
		using_history();
		ft_event_loop(shell);
	}
	return (0);
}
