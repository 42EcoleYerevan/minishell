/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:32:05 by agladkov          #+#    #+#             */
/*   Updated: 2023/05/19 19:16:02 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void ft_loop(void) */
/* { */
/* 	char *str; */
/* 	char **arr; */
/* 	char **argv; */
/* 	char *tmp_str; */
/* 	char *path; */

/* 	str = readline("minishel>$ "); */
/* 	while (*str) */
/* 	{ */
/* 		tmp_str = ft_substr(str, 0, ft_len_construction(str)); */
/* 		arr = ft_parse_construction(tmp_str); */
/* 		if (arr[0][0] == '|' || \ */
/* 			arr[0][0] == '&' || \ */
/* 			arr[0][0] == '>') */
/* 			arr++; */
/* 		argv = ft_argv(arr); */
/* 		path = ft_command_path_join(*arr); */
/* 		ft_exec(path, argv); */
/* 		str += ft_strlen(tmp_str); */
/* 		free(tmp_str); */
/* 		free(path); */
/* 		ft_free_2d_array_with_null(arr); */
/* 	} */
/* } */

/* int ft_pipe(char *str) */
/* { */
/* 	int pid; */
/* 	int fd[2]; */

/* 	pipe(fd); */
/* 	pid = fork(); */
/* 	if (pid == -1) */
/* 		return (-1); */
/* 	if(pid == 0) */
/* 	{ */
/* 		printf("first leha\n"); */
/* 		ft_child(str, fd, 0); */	
/* 	} */
/* 	else */
/* 	{ */
/* 		printf("second leha\n"); */
/* 		wait(&pid); */
/* 		str += ft_len_construction(str); */
/* 		pid = fork(); */
/* 		if (pid == 0) */
/* 		{ */
/* 			printf("third leha\n"); */
/* 			ft_child(str, fd, 1); */	
/* 		} */
/* 		else */
/* 		{ */
/* 			printf("fourth leha\n"); */
/* 			/1* wait(&pid); *1/ */
/* 		} */
/* 	} */
/* 	return (0); */
/* } */

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
	}
	else
		dup2(fd[1], 1);
	command = ft_command_path_join(*arr);
	if (execve(command, arr, ENV) == -1)
		exit(1);
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
