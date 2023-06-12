#include "../minishell.h"

/* static void print_list(t_mlist *list) */
/* { */
/* 	int n; */
/* 	int l; */

/* 	l = 0; */
/* 	while (list) */
/* 	{ */
/* 		printf("\033[33mlist #%d\n\033[0m", l++); */
/* 		printf("bin \t: %s\n", (list->bin)); */
/* 		n = 0; */ /* 		while (list->argv[n]) */
/* 		{ */
/* 			printf("argv[%d]\t: %s\n", n, (list->argv[n])); */
/* 			n++; */
/* 		} */
/* 		if (list->argv[0] == NULL) */
/* 			printf("argv[0]\t: %s\n", NULL); */
/* 		printf("command\t: %s\n", (list->command)); */
/* 		if (list->next) */
/* 			printf("next\t: %p\n", list->next); */
/* 		else */
/* 			printf("next\t: NULL\n"); */
/* 		if (list->prev) */
/* 			printf("prev\t: %p\n\n", list->prev); */
/* 		else */
/* 			printf("prev\t: NULL\n\n"); */
/* 		list = list->next; */
/* 	} */
/* } */

static void	ft_close_pipe(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

int builtin_executor(t_shell *shell, t_mlist *list)
{
	char	*key;
	int		out;

	out = 1;
	key = ft_get_command_from_path(list->argv[0]);
	if (!key)
		out = (1);
	else if (list->argv && ft_strncmp(key, "export", 7) == 0)
		out = ft_export(list->argv + 1, &shell->env);
	else if (list->argv && ft_strncmp(key, "exit", 5) == 0)
		out = ft_exit(list->argv + 1);
	else if (ft_strncmp(key, "cd", 3) == 0)
		out = ft_cd(list->argv + 1);
	else if (ft_strncmp(key, "pwd", 4) == 0)
		out = ft_pwd();
	else if (ft_strncmp(key, "echo", 5) == 0)
		out = ft_echo(list->argv + 1, 0);
	else if (ft_strncmp(key, "env", 4) == 0)
		out = ft_env(shell->env);
	else if (ft_strncmp(key, "unset", 6) == 0)
		out = ft_unset(list->argv + 1, &shell->env);
	return (out);
}

/* static void	ft_child(t_mlist *list) */
/* { */
/* 	if (list->command && list->prev == NULL) */
/* 	{ */
/* 		dup2(list->fd[1], 1); */
/* 		close(list->fd[1]); */
/* 	} */
/* 	else if (list->command) */
/* 	{ */
/* 		dup2(list->prev->fd[0], 0); */
/* 		dup2(list->fd[1], 1); */
/* 		ft_close_pipe(list->prev->fd); */
/* 	} */
/* 	else */
/* 	{ */
/* 		dup2(list->prev->fd[0], 0); */
/* 		ft_close_pipe(list->prev->fd); */
/* 	} */
/* 	execve(list->bin, list->argv, NULL); */
/* } */
void ft_child(char **env, t_mlist *list)
{
	if (list->bin)
	{
		if (list->prev == NULL && list->next == NULL)
			execve(list->bin, list->argv, env);
		if (list->next && list->command[0] == '|')
		{
			dup2(list->fd[1], 1);
			close(list->fd[1]);
		}
		if (list->prev && list->prev->command[0] == '|')
		{
			dup2(list->prev->fd[0], 0);
			ft_close_pipe(list->prev->fd);
		}
		execve(list->bin, list->argv, env);
	}
	else
		printf("minishell: %s: command not found\n", list->argv[0]); 
}

void	executor(t_shell *shell)
{
	int		pid;
	int		bltin;
	t_mlist	*tmp;

	tmp = *shell->list;
	while (tmp)
	{
		bltin = builtin_executor(shell, tmp);
		if (bltin == 1)
		{
			pipe(tmp->fd);
			pid = fork();
			if (pid == 0)
				ft_child(ft_env_to_arr(shell->env, 0, -1), tmp);
		}
		if (tmp->prev && tmp->prev->command[0] == '|')
			ft_close_pipe(tmp->prev->fd);
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
		ctrl_d_handler(str);
		list = ft_fill_list(shell, str);
		shell->list = &list;
		add_history(str);
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
		ft_init_action();
		rl_catch_signals = 0;
		using_history();
		ft_event_loop(shell);
	}
	return (0);
}
