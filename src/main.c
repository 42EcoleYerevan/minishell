/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:13:56 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/04 16:16:18 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_shell *shell)
{
	t_mlist	*tmp;

	tmp = *shell->list;
	while (tmp)
	{
		if (tmp->bin || ft_isbuiltin(tmp->argv[0]) || \
				tmp->argv[0][0] == '<' || tmp->argv[0][0] == '>')
		{
			if (tmp->next)
				pipe(tmp->fd);
			if (ft_isbuiltin(tmp->bin) || ft_isbuiltin(tmp->argv[0]))
				exit_status = ft_builtin_handler(shell, tmp);
			else
				exit_status = ft_executor(shell, tmp);
			if (exit_status != 0)
				return ;
		}
		else
			printf("minishell: %s: command not found\n", tmp->argv[0]);
		tmp = tmp->next;
	}
	while (waitpid(-1, &exit_status, 0) != -1)
		;
	exit_status = exit_status / 256;
}

void	ft_event_loop(t_shell *shell)
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
	return (exit_status);
}
