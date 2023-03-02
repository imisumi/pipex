/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:29:41 by imisumi           #+#    #+#             */
/*   Updated: 2023/03/01 16:43:51 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_one(char **argv, char **envp, t_pip pip)
{
	pip.in = open(argv[1], O_RDONLY);
	if (pip.in == -1)
	{
		// system("leaks pipex");
		exit_error(argv[1], 1);
	}
	dup2(pip.in, STDIN);
	close(pip.in);
	close(pip.end[0]);
	dup2(pip.end[1], STDOUT);
	run_cmd(pip.paths, argv, envp, 2);
}

void	child_two(char **argv, char **envp, t_pip pip)
{
	pip.out = open(argv[4], O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (pip.out == -1)
		exit_error(argv[4], 1);
	dup2(pip.end[0], STDIN);
	close(pip.end[1]);
	dup2(pip.out, STDOUT);
	close(pip.out);
	run_cmd(pip.paths, argv, envp, 3);
}

void	parent_process(t_pip pip)
{
	int	status;
	int	code;

	status = 0;
	close(pip.end[0]);
	close(pip.end[1]);
	waitpid(pip.pid_1, NULL, 0);
	waitpid(pip.pid_2, &status, 0);
	if (status)
	{
		code = WEXITSTATUS(status);
		exit(code);
	}
}

void	pipex(char *argv[], char *envp[], t_pip pip)
{
	pip.paths = env_paths(envp, pip);
	if (pipe(pip.end) == -1)
		exit_msg("Failed to create pipe", NULL, 1);
	pip.pid_1 = fork();
	if (pip.pid_1 == -1)
		exit_msg("Failed to create fork", NULL, 1);
	else if (pip.pid_1 == 0)
		child_one(argv, envp, pip);
	pip.pid_2 = fork();
	if (pip.pid_2 == -1)
		exit_msg("Failed to create fork", NULL, 1);
	else if (pip.pid_2 == 0)
	{
		waitpid(pip.pid_2, NULL, 0);
		child_two(argv, envp, pip);
	}
	parent_process(pip);
}
