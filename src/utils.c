/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:38:38 by imisumi           #+#    #+#             */
/*   Updated: 2023/03/13 16:01:28 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	check_absolute_path(char *cmd, char **envp)
{
	char	**cmd_arg;

	if (cmd[0] == '/')
	{
		cmd_arg = ft_split(cmd, ' ');
		if (cmd_arg == NULL)
			exit_msg("Malloc in ft_split has failed", NULL, 1);
		execve(cmd_arg[0], cmd_arg, envp);
		exit_msg("Command not found: ", cmd, 1);
	}
	else
		return ;
}

void	check_local_path(char *cmd, char **envp)
{
	char	**cmd_arg;

	cmd_arg = ft_split(cmd, ' ');
	if (cmd_arg == NULL)
		exit_msg("Malloc in ft_split has failed", NULL, 1);
	if (access(cmd_arg[0], F_OK) != 0)
		exit_error(cmd_arg[0], 1);
	if (access(cmd_arg[0], X_OK) != 0)
		exit_error(cmd_arg[0], 1);
	execve(cmd_arg[0], cmd_arg, envp);
	exit (0);
}

void	run_command(char **paths, char *cmd_path, char **cmd_arg)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd_arg[0]);
		if (cmd_path == NULL)
		{
			free_child(paths, cmd_arg, cmd_path);
			exit_msg("Command not found: ", NULL, 127);
		}
		if (access(cmd_path, F_OK) == 0)
		{
			execve(cmd_path, cmd_arg, 0);
			exit (0);
		}
		i++;
		free(cmd_path);
	}
	return ;
}

void	check_cmd(char **paths, char **argv, char **envp, int cmd)
{
	char	**cmd_arg;
	char	*cmd_path;

	check_absolute_path(argv[cmd], envp);
	if (paths == NULL)
		check_local_path(argv[cmd], envp);
	cmd_arg = ft_split(argv[cmd], ' ');
	if (cmd_arg == NULL)
	{
		free(paths);
		exit_msg("Malloc in ft_split has failed", NULL, 1);
	}
	run_command(paths, cmd_path, cmd_arg);
	free_child(paths, cmd_arg, NULL);
	exit_msg("Command not found: ", argv[cmd], 127);
}
