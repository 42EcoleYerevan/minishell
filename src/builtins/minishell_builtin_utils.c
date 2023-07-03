#include "minishell.h"

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
	if (!*arr)
		return (1);
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
