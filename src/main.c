/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:13:56 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/07 20:31:14 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_error(t_mlist *list)
{
	if (list->argv[0] || list->bin)
		printf("minishell: %s: command not found\n", list->argv[0]);
}

void	executor(t_shell *shell)
{
	t_mlist	*tmp;

	tmp = *shell->list;
	while (tmp)
	{
		if (tmp->bin || ft_isbuiltin(tmp->argv[0]) || \
		(tmp->argv[0] && (tmp->argv[0][0] == '<' || tmp->argv[0][0] == '>')))
		{
			if (tmp->next)
				pipe(tmp->fd);
			if (ft_isbuiltin(tmp->bin) || ft_isbuiltin(tmp->argv[0]))
				exit_status = ft_builtin_handler(shell, tmp);
			else
				exit_status = ft_executor(shell, tmp);
		}
		else
			ft_print_error(tmp);
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
		ft_init_action();
		str = readline("minishell>$ ");
		if (str && *str == '\0')
		{
			free(str);
			continue ;
		}
		ctrl_d_handler(str);
		add_history(str);
		list = ft_fill_list(shell, str);
		shell->list = &list;
		if (!list->argv[0] && !list->bin && list->command)
			ft_redirect_unexpected_error(list->command);
		else
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
		rl_catch_signals = 0;
		using_history();
		ft_event_loop(shell);
	}
	return (exit_status);
}
