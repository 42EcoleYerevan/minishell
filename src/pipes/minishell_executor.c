#include "minishell.h"

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
		return execve(list->bin, list->argv, env);
	}
	ft_close_fd(list);
	ft_free_2d_array_with_null(env);
	free(env);
	return (0);
}

