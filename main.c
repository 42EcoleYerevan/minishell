/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agladkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:14:27 by agladkov          #+#    #+#             */
/*   Updated: 2023/05/22 21:00:49 by agladkov         ###   ########.fr       */
/* ************************************************************************** */

#include "minishell.h"

/* void ft_close_pipe(int fd[2]) */
/* { */
/* 	close(fd[0]); */
/* 	close(fd[1]); */
/* } */

/* void ft_child(char **arr, int fd[2], int n) */
/* { */
/* 	char **arr; */
/* 	char *command; */

/* 	if (n == 0) */
/* 	{ */
/* 		dup2(fd[1], 1); */
/* 		ft_close_fd(fd); */
/* 	} */
/* 	else */
/* 	{ */
/* 		arr++; */
/* 		dup2(fd[0], 0); */
/* 		ft_close_fd(fd); */
/* 	} */ 
/* 	command = ft_command_path_join(*arr); */
/* 	execve(command, arr, ENV); */
/* } */

/* int ft_pipex(char *str) */
/* { */
/* 	int fd[2]; */
/* 	int pid; */
/* 	int n; */
/* 	int len; */

/* 	len = ft_count_construction(str); */
/* 	n = 0; */
/* 	while (n < len) */
/* 	{ */
/* 		if (n % 2 == 0) */
/* 			pipe(fd); */
/* 		pid = fork(); */
/* 		if (pid == -1) */
/* 			return (-1); */
/* 		if (pid == 0) */
/* 		{ */
/* 			construction = ft_substr(str, 0, ft_len_construction(str)); */
/* 			arr = ft_parse_construction(construction); */
/* 			ft_child(arr, fd, n); */
/* 		} */
/* 		str += ft_len_construction(str); */
/* 		n++; */
/* 		if (n % 2 == 0) */
/* 			ft_close_fd(fd); */
/* 	} */
/* 	return (0); */
/* } */

int main(int argc, char **argv, char **env)
{
	(void) argv;
	ENV = env;
	argc = 0;
	(void) argv;

	char *str;

	str = readline("minishel>$ ");
	t_mlist *list = ft_fill_list(str);
	int n = 0;
	while (list)
	{
		puts("");
		n = 0;
		while(list->argv[n])
		{
			printf("%s\n", list->argv[n]);
			n++;
		}
		printf("%s\n", list->command);
		list = list->next;
	}
	return (0);
}
