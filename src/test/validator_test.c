/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:40:18 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/19 17:41:05 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_validator_test(t_shell *shell, char *str, int answer);
void	ft_quores_test(t_shell *shell);
void	ft_redirect_test(t_shell *shell);
void	ft_pipe_test(t_shell *shell);

void	ft_validator_test_run(t_shell *shell)
{
	fprintf(stderr, "\n\033[31mVALIDATOR TESTING\033[0m\n");
	ft_quores_test(shell);
	ft_redirect_test(shell);
	ft_pipe_test(shell);
}

void	ft_quores_test(t_shell *shell)
{
	fprintf(stderr, "\nquotes testing ...\n");
	ft_validator_test(shell, "\"", 1);
	ft_validator_test(shell, "\"\"", 0);
	ft_validator_test(shell, "\"a\"", 0);
	ft_validator_test(shell, "\'\'", 0);
	ft_validator_test(shell, "\'a\'", 0);
	ft_validator_test(shell, "\'\"", 1);
	ft_validator_test(shell, "\"\'", 1);
	ft_validator_test(shell, "\"\"\'\'", 0);
	ft_validator_test(shell, "echo leha \"", 1);
	ft_validator_test(shell, "echo leha \"\"", 0);
	ft_validator_test(shell, "echo leha \"asdf\"", 0);
	ft_validator_test(shell, "echo leha \"$PATH\"", 0);
	ft_validator_test(shell, "echo leha \'$PATH\'", 0);
	ft_validator_test(shell, "'echo leha \'$PATH\'leha'", 0);
	ft_validator_test(shell, "'echo leha \'$PATH\'leha|'", 0);
}

void	ft_redirect_test(t_shell *shell)
{
	fprintf(stderr, "\nedirect testing ...\n");
	ft_validator_test(shell, "echo <", 258);
	ft_validator_test(shell, "echo < test", 1);
	ft_validator_test(shell, "echo < minishell.h", 0);
	ft_validator_test(shell, "< minishell.h", 0);
	ft_validator_test(shell, "<\">\"", 1);
}

void	ft_pipe_test(t_shell *shell)
{
	fprintf(stderr, "\npipes testing ...\n");
	ft_validator_test(shell, "|", 258);
	ft_validator_test(shell, "| echo", 258);
	ft_validator_test(shell, "echo |", 258);
	ft_validator_test(shell, "    |          ", 258);
	ft_validator_test(shell, "leha | <", 258);
	ft_validator_test(shell, "cat < file.txt | <", 258);
	ft_validator_test(shell, "echo | echo", 0);
}

void	ft_validator_test(t_shell *shell, char *str, int answer)
{
	t_mlist	*list;

	if (fork() == 0)
	{
		close(1);
		list = ft_parser(shell, str);
		g_exit_status = ft_is_valid_linked_list(list);
		if (answer == g_exit_status)
			fprintf(stderr, "\033[32mOK %d\033[0m\n", g_exit_status);
		else
			fprintf(stderr, "\033[31mKO %d\033[0m\n", g_exit_status);
		exit(g_exit_status);
	}
	waitpid(-1, NULL, 0);
}
