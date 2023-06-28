#include "minishell.h"

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

void	ft_close_pipe(int fd[2])
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

/* int ft_clear_file(char *filename) */
/* { */
/* 	int	fd; */

/* 	if (!filename) */
/* 	{ */
/* 		printf("syntax error near unexpected token `newline'\n"); */
/* 		return (1); */
/* 	} */
/* 	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT); */
/* 	close(fd); */
/* 	return (0); */
/* } */

int ft_handle_redirect(t_mlist *list)
{
	int n;
	int out;

	n = 0;
	out = 0;
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
				if (tmp->ispipe == 1)
				{
					dup2(tmp->fd[0], 0);
					ft_close_pipe(tmp->fd);
				}
				execve(tmp->bin, tmp->argv, NULL);
			}
			if (tmp->ispipe == 1)
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
		executor(shell);
		/* print_list(list); */
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
