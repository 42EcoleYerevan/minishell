/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:32:05 by agladkov          #+#    #+#             */
/*   Updated: 2023/05/20 15:59:55 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_child(char *str, int fd[2], int n)
{
	char **arr;
	char *command;
	char *construction;

	construction = ft_substr(str, 0, ft_len_construction(str));
	arr = ft_parse_construction(construction);
	if (n != 0)
	{
		arr++;
		dup2(fd[0], 0);
		command = ft_command_path_join(*arr);
		execve(command, arr, ENV);
	}
	else
	{
		dup2(fd[1], 1);
		command = ft_command_path_join(*arr);
		execve(command, arr, ENV);
	}
}

int ft_pipex(char *str)
{
	int pid;
	int fd[2];
	int n;
	int len;

	len = ft_count_construction(str);
	n = 0;
	while (n < len)
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
			ft_child(str, fd, n);
		str += ft_len_construction(str);
		n++;
		wait(NULL);
	}
	return (0);
}

int main(int argc, char **argv, char **env)
{
	char *str;
	(void) argv;
	ENV = env;

	if (argc == 1)
	{
		str = readline("minishel>$ ");
		ft_pipex(str);
	}
	return (0);
}
