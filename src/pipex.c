/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:29:41 by imisumi           #+#    #+#             */
/*   Updated: 2023/03/13 16:01:25 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_one(char **argv, char **envp, t_pip pip)
{
	pip.in = open(argv[1], O_RDONLY);
	if (pip.in == -1)
		exit_error(argv[1], 1);
	if (argv[2][0] == '\0' || argv[3][0] == '\0')
	{
		if (argv[2][0] == '\0')
			exit_msg("Command not found:", NULL, 127);
		else
			exit(0);
	}
	dup2(pip.in, STDIN);
	close(pip.in);
	close(pip.end[0]);
	dup2(pip.end[1], STDOUT);
	check_cmd(pip.paths, argv, envp, 2);
}

void	parent_process(char **argv, char **envp, t_pip pip)
{
	pip.out = open(argv[4], O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (pip.out == -1)
		exit_error(argv[4], 1);
	if (access(argv[1], F_OK | R_OK) != 0)
		exit(1);
	if (argv[3][0] == '\0')
	{
		if (argv[3][0] == '\0')
			exit_msg("Command not found:", NULL, 127);
		else
			exit(0);
	}
	dup2(pip.end[0], STDIN);
	close(pip.end[1]);
	dup2(pip.out, STDOUT);
	close(pip.out);
	check_cmd(pip.paths, argv, envp, 3);
	free_double(pip.paths);
	exit(0);
}

void	pipex(char *argv[], char *envp[], t_pip pip)
{
	pip.paths = env_paths(envp);
	if (pipe(pip.end) == -1)
		exit_msg("Failed to create pipe", NULL, 1);
	pip.pid_1 = fork();
	if (pip.pid_1 == -1)
		exit_msg("Failed to create fork", NULL, 1);
	else if (pip.pid_1 == 0)
		child_one(argv, envp, pip);
	waitpid(pip.pid_1, NULL, WNOHANG);
	parent_process(argv, envp, pip);
}
