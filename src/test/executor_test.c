/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:36:15 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/20 12:42:13 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_test_reader(int fd);
void	ft_executor_test(t_shell *shell, char *str, char *expected);
void	ft_executor_env_test(t_shell *shell);
void	ft_executor_pipe_test(t_shell *shell);

void	ft_executor_test_run(t_shell *shell)
{
	fprintf(stderr, "\n\033[31mEXECUTOR TESTING\033[0m\n\n");
	ft_executor_test(shell, "echo leha", "leha");
	ft_executor_test(shell, "echo \"\"", "");
	ft_executor_test(shell, "echo \"leha\"", "leha");
	ft_executor_test(shell, "echo \"hello(leha)\"", "hello(leha)");
	ft_executor_test(shell, "echo \"hello''\"", "hello''");
	ft_executor_pipe_test(shell);
	ft_executor_env_test(shell);
}

void	ft_executor_pipe_test(t_shell *shell)
{
	ft_executor_test(shell, "yes | head", "y\ny\ny\ny\ny\ny\ny\ny\ny\ny");
	ft_executor_test(shell, "echo leha | cat", "leha");
	ft_executor_test(shell, "echo leha > file.txt | cat < file.txt", "leha");
	ft_executor_test(shell, "< file.txt cat | grep leha", "leha");
}

void	ft_executor_env_test(t_shell *shell)
{
	ft_executor_test(shell, "echo hello'$PATH'", "hello$PATH");
	ft_executor_test(shell, "echo $PATH", \
			"/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki");
	ft_executor_test(shell, "echo \"$PATH\"'$PATH'", \
	"/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki$PATH");
	ft_executor_test(shell, "echo \"$PATH\"", \
	"/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki");
	ft_executor_test(shell, "echo '$PATH'", "$PATH");
	ft_executor_test(shell, "echo '$PATH\"\"'", "$PATH\"\"");
	ft_executor_test(shell, "echo \'$PATH$USER\'", "$PATH$USER");
	ft_executor_test(shell, "echo \'\'", "");
	ft_executor_test(shell, "echo \"$PATH.leha\"", \
	"/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki.leha");
	ft_executor_test(shell, "echo leha\"$PATH\"", \
	"leha/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki");
}

void	ft_executor_test(t_shell *shell, char *str, char *expected)
{
	char	*out;
	int		fd[2];
	t_mlist	*list;

	list = ft_parser(shell, str);
	shell->list = &list;
	pipe(fd);
	if (fork() == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		executor(shell);
		exit(0);
	}
	close(fd[1]);
	out = ft_test_reader(fd[0]);
	close(fd[0]);
	wait(NULL);
	if (ft_strncmp(out, expected, ft_strlen(expected) + 1) == 0)
		fprintf(stderr, "\033[32mOK\033[0m\n");
	else
		fprintf(stderr, "\033[31mKO\n\tout: %s\n\texpected: \
				%s\033[0m\n", out, expected);
	return ;
}

char	*ft_test_reader(int fd)
{
	char	*out;
	char	c;
	int		n;

	n = 0;
	out = (char *)malloc(sizeof(char) * 1000);
	while (read(fd, &c, 1) > 0)
		out[n++] = c;
	out[n] = 0;
	out = ft_strtrim(out, "\n");
	return (out);
}
