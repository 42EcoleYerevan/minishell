#include "../minishell.h"
#include <unistd.h>

/* static void print_list(t_mlist *list) */
/* { */
/* 	int n; */
/* 	int l; */

/* 	l = 0; */
/* 	while (list) */
/* 	{ */
/* 		printf("\033[33mlist #%d\n\033[0m", l++); */
/* 		printf("bin \t: %s\n", (list->bin)); */
/* 		n = 0; */
/* 		while (list->argv[n]) */
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

/* static char *ft_lowercase(char *str) */
/* { */
/* 	char *out; */
/* 	int n; */

/* 	if (!str) */
/* 		return (str); */
/* 	out = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1)); */
/* 	n = 0; */
/* 	while (str[n]) */
/* 	{ */
/* 		out[n] = str[n]; */
/* 		n++; */
/* 	} */
/* 	return (out); */
/* } */

void interesnaya_funkciya(t_shell *shell)
{
	int pid;
	char *key;

	t_mlist *tmp = *shell->list;
	while (tmp)
	{
		if (tmp->argv && ft_strncmp(tmp->argv[0], "export", 7) == 0)
		{
			ft_export(tmp->argv + 1, &shell->env);
			return;
		}

		key = ft_get_command_from_path(tmp->bin);
		if (!key)
			return ;
		if (ft_strncmp(key, "cd", 3) == 0)
			ft_cd(tmp->argv + 1);
		else if (ft_strncmp(key, "pwd", 4) == 0)
			ft_pwd();
		else if (ft_strncmp(key, "echo", 5) == 0)
			ft_echo(tmp->argv + 1, 0);
		else if (ft_strncmp(key, "env", 4) == 0)
			ft_env(shell->env);
		else if (ft_strncmp(key, "exit", 5) == 0)
			ft_exit(tmp->argv + 1);
		else if (ft_strncmp(key, "unset", 6) == 0)
			ft_unset(tmp->argv + 1, &shell->env);

		else if (tmp->bin)
		{
			pid = fork();
			if (pid == 0)
				execve(tmp->bin, tmp->argv, NULL);
		}

		ft_close_pipe(tmp->fd);
		tmp = tmp->next;
	}
	while (wait(NULL) != -1)
		;
}

char	**ft_env_to_arr(t_env *env, int len, int i)
{
	t_env	*start;
	char	**arr;
	char	*tmp;

	start = env;
	while (env && ++len)
		env = env->next;
	arr = malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	arr[len] = NULL;
	while (start && ++i >= 0)
	{
		arr[i] = NULL;
		if (start->value)
			arr[i] = ft_strjoin("=", start->value);
		tmp = arr[i];
		arr[i] = ft_strjoin(start->key, arr[i]);
		free(tmp);
		start = start->next;
	}
	len = 0;
	while (arr[len])
		printf("%s\n", arr[len++]);
	return (arr);
}

int main(int argc, char **argv, char **menv)
{
	t_shell *shell;
	t_mlist *list;

	(void) argv;
	argc = 0;

	shell = (t_shell *)malloc(sizeof(t_shell));
	shell->env = ft_create_envlist(menv);
	//ft_env_to_arr(shell->env, 0, -1);

	char *str;

	signal(SIGINT, ft_action);
	signal(SIGQUIT, ft_quit);
	rl_catch_signals = 0;
	using_history();
	while (1)
	{
		str = readline("minishell>$ ");
		if (!str)
		{
			printf("\033[1A\033[12Cexit\n");
			return (1);
		}
		list = ft_fill_list(shell, str);
		shell->list = &list;
		add_history(str);
		free(str);
		interesnaya_funkciya(shell);
		ft_free_2_linked_list(shell->list);
	}
	return (0);
}