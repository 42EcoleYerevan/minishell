#include "minishell.h"
#include <stdlib.h>

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
	int		n_command;

	n_command = 0;
	command = ft_get_command_from_path(path);
	if (!command)
		n_command = 0;
	else if (ft_strncmp(command, "export", 7) == 0)
		n_command = 1;
	else if (ft_strncmp(command, "exit", 5) == 0)
		n_command = 2;
	else if (ft_strncmp(command, "cd", 3) == 0)
		n_command = 3;
	else if (ft_strncmp(command, "pwd", 4) == 0)
		n_command = 4;
	else if (ft_strncmp(command, "echo", 5) == 0)
		n_command = 5;
	else if (ft_strncmp(command, "env", 4) == 0)
		n_command = 6;
	else if (ft_strncmp(command, "unset", 6) == 0)
		n_command = 7;
	return (n_command);
}

int ft_check_n_flag(char **arr)
{
	char	*tmp;
	if (!*arr)
		return (0);
	arr++;
	tmp = ft_strchr(*arr, '-');
	if (tmp == NULL)
		return (1);
	else if (*(tmp + 1) == 'n')
		return 0;
	return (1);
}

int ft_builtin_bin(t_shell *shell, t_mlist *list, int command)
{
	int out;

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

void ft_dup_pipe(t_mlist *list)
{
	if (list->next)
	{
		dup2(list->fd[1], 1);
		close(list->fd[1]);
	}
	if (list->prev)
	{
		dup2(list->prev->fd[0], 0);
		close(list->prev->fd[0]);
	}
}

void ft_close_fd(t_mlist *list)
{
	if (list->next)
		close(list->fd[1]);
	if (list->prev)
		close(list->prev->fd[0]);
}

int	ft_builtin_executor(t_shell *shell, t_mlist *list, int command)
{
	int status;

	status = ft_handle_redirect(list);
	if (list->isinput || list->isoutput)
	{
		if (fork() == 0)
		{
			ft_dup_pipe(list);
			ft_dup_redirect(list);
			ft_close_fd(list);
			if (list->isheredoc || list->isinput || list->isoutput)
				ft_close_pipe(list->heredoc);
			exit(ft_builtin_bin(shell, list, command));
		}
	}
	else
	{
		ft_dup_pipe(list);
		ft_dup_redirect(list);
		ft_close_fd(list);
		status = ft_builtin_bin(shell, list, command);
	}
	if (list->isheredoc || list->isinput || list->isoutput)
		ft_close_pipe(list->heredoc);
	return (status);
}

int ft_builtin_handler(t_shell *shell, t_mlist *list)
{
	int status;

	status = 1;
	if (ft_isbuiltin(list->bin) || ft_isbuiltin(list->argv[0]))
	{
		if (ft_isbuiltin(list->bin))
			status = ft_builtin_executor(
					shell,
				   	list,
				   	ft_isbuiltin(list->bin)
					);
		else
			status = ft_builtin_executor(
					shell,
				   	list,
				   	ft_isbuiltin(list->argv[0])
					);
	}
	return (status);
}

int ft_executor(t_shell *shell, t_mlist *list)
{
	char **env;
	int status;

	env = ft_env_to_arr(shell->env, 0, -1);
	status = ft_handle_redirect(list);
	if (status != 0)
		return (status);
	if (fork() == 0)
	{
		ft_dup_pipe(list);
		ft_close_fd(list);
		ft_dup_redirect(list);
		if (list->isheredoc || list->isinput || list->isoutput)
			ft_close_pipe(list->heredoc);
		return execve(list->bin, list->argv, env);
	}
	if (list->isheredoc || list->isinput || list->isoutput)
		ft_close_pipe(list->heredoc);
	ft_close_fd(list);
	return (0);
}

void	executor(t_shell *shell)
{
	int		pid;
	t_mlist	*tmp;

	pid = 1;
	tmp = *shell->list;
	while (tmp)
	{
		if (tmp->bin || ft_isbuiltin(tmp->argv[0]))
		{
			if (tmp->next)
				pipe(tmp->fd);
			if (ft_isbuiltin(tmp->bin) || ft_isbuiltin(tmp->argv[0]))
				exit_status = ft_builtin_handler(shell, tmp);
			else
				exit_status = ft_executor(shell, tmp);
			if (exit_status != 0)
				break ;
		}
		else 
			printf("minishell: %s: command not found\n", tmp->argv[0]);
		tmp = tmp->next;
	}
	/* while(wait(NULL) != -1); */
	while(waitpid(-1, &exit_status, 0) != -1);
	exit_status = exit_status / 256;
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
		/* print_list(list); */
		executor(shell);
		free(str);
		ft_free_2_linked_list(shell->list);
	}
}

int exit_status;

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
	return (exit_status);
}
