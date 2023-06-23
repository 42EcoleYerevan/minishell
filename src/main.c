#include "../minishell.h"
#include <iso646.h>
#include <sys/fcntl.h>

// static void print_list(t_mlist *list)
// {
// 	int n;
// 	int l;

// 	l = 0;
// 	while (list)
// 	{
// 		printf("\033[33mlist #%d\n\033[0m", l++);
// 		printf("bin \t: %s\n", (list->bin));
// 		n = 0;
// 		while (list->argv[n])
// 		{
// 			printf("argv[%d]\t: %s\n", n, (list->argv[n]));
// 			n++;
// 		}
// 		if (list->argv[0] == NULL)
// 			printf("argv[0]\t: %s\n", NULL);
// 		printf("command\t: %s\n", (list->command));
// 		if (list->next)
// 			printf("next\t: %p\n", list->next);
// 		else
// 			printf("next\t: NULL\n");
// 		if (list->prev)
// 			printf("prev\t: %p\n\n", list->prev);
// 		else
// 			printf("prev\t: NULL\n\n");
// 		list = list->next;
// 	}
// }

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

/* void	ft_redirect_to_file(int src_fd, char *filename, int mode) */
/* { */
/* 	int fd; */
/* 	int res; */
/* 	char c; */

/* 	if (mode == 0) */
/* 		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT); */
/* 	else if (mode == 1) */
/* 		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT); */
/* 	res = read(src_fd, &c, 1); */
/* 	while (res > 0 && c != '\0') */
/* 	{ */
/* 		write(fd, &c, 1); */
/* 		res = read(src_fd, &c, 1); */
/* 	} */
/* 	printf(" after while %d\n", res); */
/* 	write(fd, "\n", 1); */
/* 	close(src_fd); */
/* 	close(fd); */
/* 	exit(0); */
/* } */

int	ft_redirect_error(char *command)
{
		printf("syntax error near unexpected token `%s`\n", command); 
		rl_on_new_line();
		return (1);
}

void ft_redirect_output(t_shell *shell, t_mlist *list, int bltin, char **env)
{
	int fd;

	if (list->command)
	{
		if (ft_strncmp(list->command, ">", 2) == 0)
			fd = open(list->next->argv[0], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			fd = open(list->next->argv[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(fd, 1);
	}
	if (bltin)
		exit(builtin_executor(shell, list, bltin));
	execve(list->bin, list->argv, env);
}

void ft_redirect_input(t_shell *shell, t_mlist *list, int bltin, char **env)
{
	int fd;

	if (list->command)
	{
		fd = open(list->next->argv[0], O_RDONLY | O_CREAT);
		dup2(fd, 0);
	}
	if (bltin)
		exit(builtin_executor(shell, list, bltin));
	execve(list->bin, list->argv, env);
}

void ft_redirect_executor(t_shell *shell, t_mlist *list, int bltin, char **env)
{
	if (list->command)
	{
		if (list->command[0] == '>')
			ft_redirect_output(shell, list, bltin, env);
		else if (list->command[0] == '<')
			ft_redirect_input(shell, list, bltin, env);
	}
}

void ft_pipe_executor(t_shell *shell, t_mlist *list, int bltin, char **env)
{
	if (list->prev == NULL && list->next == NULL)
		execve(list->bin, list->argv, env);
	if (list->next &&
		(ft_strncmp(list->command, "|", 2) == 0))
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
		exit(builtin_executor(shell, list, bltin));
	execve(list->bin, list->argv, env);
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
		if (tmp->bin || (tmp->prev && tmp->prev->command))
		{
			pipe(tmp->fd);
			pid = fork();
			if (pid == 0)
			{
				if (tmp->prev == NULL && tmp->next == NULL)
				{
					if (bltin)
						exit(builtin_executor(shell, tmp, bltin));
					else
						execve(
								tmp->bin,
							   	tmp->argv,
							   	ft_env_to_arr(shell->env, 0, -1)
								);
				}
				if ((tmp->command && tmp->command[0] == '>') || 
					(tmp->command && tmp->command[0] == '<'))
					ft_redirect_executor(
							shell,
						   	tmp,
						   	bltin,
						   	ft_env_to_arr(shell->env, 0, -1)
							);
				else if ((tmp->command && tmp->command[0] == '|') || 
						(tmp->prev && tmp->prev->command[0] == '|') ||
						tmp->bin)
					ft_pipe_executor(
							shell,
						   	tmp,
						   	bltin,
						   	ft_env_to_arr(shell->env, 0, -1)
							);
			}
			if (tmp->prev && tmp->prev->command)
				ft_close_pipe(tmp->prev->fd);
		}
		if (tmp->command && (tmp->command[0] == '>' || tmp->command[0] == '<'))
			tmp = tmp->next;
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
		// print_list(list);
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
