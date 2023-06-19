#include "../minishell.h"
#include <sys/fcntl.h>

static void print_list(t_mlist *list)
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
			printf("argv[0]\t: %s\n", NULL);
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

	out = 1;
	if (command == 1)
		out = ft_export(list->argv + 1, &shell->env);
	else if (command == 2)
		out = ft_exit(list->argv + 1);
	else if (command == 3)
		out = ft_cd(list->argv + 1, &shell->env, NULL, NULL);
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
		out = ft_unset(list->argv + 1, &shell->env);
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

void	ft_redirect_to_file(int src_fd, char *filename, int mode)
{
	int fd;
	int res;
	char c;

	if (mode == 0)
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT);
	else if (mode == 1)
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT);
	res = read(src_fd, &c, 1);
	while (res > 0 && c != '\n')
	{
		write(fd, &c, 1);
		res = read(src_fd, &c, 1);
	}
	write(fd, "\n", 1);
	close(src_fd);
	close(fd);
	exit(0);
}

int	ft_redirect_error(char *command)
{
		printf("syntax error near unexpected token `%s`\n", command); 
		rl_on_new_line();
		return (1);
}

void ft_redirect_handler(t_mlist *list)
{
	if (list->argv[0])
	{
		if (list->prev && ft_strncmp(list->prev->command, ">", 2) == 0)
			ft_redirect_to_file(list->prev->fd[0], list->argv[0], 0);
		else if (list->prev && ft_strncmp(list->prev->command, ">>", 3) == 0)
			ft_redirect_to_file(list->prev->fd[0], list->argv[0], 1);
	}
	else 
		exit(ft_redirect_error(list->prev->command));
}

void ft_pipe_executor(t_shell *shell, t_mlist *list, int bltin, char **env)
{
	if (list->prev == NULL && list->next == NULL)
		execve(list->bin, list->argv, env);
	if (list->next &&
		(ft_strncmp(list->command, "|", 2) == 0 ||
		ft_strncmp(list->command, ">", 2) == 0 ||
		ft_strncmp(list->command, ">>", 2) == 0))
	{
		dup2(list->fd[1], 1);
		close(list->fd[1]);
	}
	if (list->prev && ft_strncmp(list->prev->command, "|", 2) == 0)
	{
		dup2(list->prev->fd[0], 0);
		ft_close_pipe(list->prev->fd);
	}
	if (bltin)
		builtin_executor(shell, list, bltin);
	execve(list->bin, list->argv, env);
}

void ft_child(t_shell *shell, t_mlist *list, int bltin)
{
	char **env;

	env = ft_env_to_arr(shell->env, 0, -1);
	if (list->prev && list->prev->command[0] == '>')
		ft_redirect_handler(list);
	if (list->bin || bltin)
		ft_pipe_executor(shell, list, bltin, env);
	else if (list->command && list->next && 
			(ft_strncmp(list->command, ">", 2) == 0 ||
			ft_strncmp(list->command, ">>", 3) == 0))
		exit(ft_clear_file(list->next->argv[0]));
	printf("minishell: %s: command not found\n", list->argv[0]); 
	exit(1);
}

void	executor(t_shell *shell)
{
	int		pid;
	int		bltin;
	t_mlist	*tmp;

	tmp = *shell->list;
	while (tmp)
	{
		bltin = ft_isbuiltin(tmp->argv[0]);
		if (bltin && tmp->next == NULL)
			builtin_executor(shell, tmp, bltin);
		else
		{
			pipe(tmp->fd);
			pid = fork();
			if (pid == 0)
				ft_child(shell, tmp, bltin);
			if (tmp->prev && tmp->prev->command)
				ft_close_pipe(tmp->prev->fd);
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
