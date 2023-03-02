/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:38:38 by imisumi           #+#    #+#             */
/*   Updated: 2023/03/02 15:53:42 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_double(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	if (array)
		free(array);
}

void	free_child(char **paths, char **cmd_arg, char *cmd_path)
{
	if (paths)
		free_double(paths);
	if (cmd_arg)
		free_double(cmd_arg);
	if (cmd_path)
		free(cmd_path);
}

char	*get_env(char **envp)
{
	char	*env;
	int		i;

	i = 0;
	while (envp[i])
	{
		env = ft_strnstr(envp[i], "PATH", 4);
		if (env != NULL)
			break ;
		i++;
	}
	env = env + 5;
	return (env);
}

char	**env_paths(char **envp, t_pip pip)
{
	char	*env;
	char	**paths;
	char	*temp;
	int		i;

	env = get_env(envp);
	paths = ft_split(env, ':');
	if (paths == NULL)
		exit_msg("Malloc in ft_split has failed", NULL, 1);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (temp == NULL)
		{
			free_double(paths);
			exit_msg("Malloc in ft_strjoin has failed", NULL, 1);
		}
		free(paths[i]);
		paths[i] = temp;
		i++;
	}
	return (paths);
}

void	run_cmd(char **paths, char **argv, char **envp, int cmd)
{
	char	**cmd_arg;
	char	*cmd_path;
	int		i;

	cmd_arg = ft_split(argv[cmd], ' ');
	if (cmd_arg == NULL)
		free(paths);
	if (cmd_arg == NULL)
		exit_msg("Malloc in ft_split has failed", NULL, 1);
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
			execve(cmd_path, cmd_arg, 0);
		i++;
		free(cmd_path);
	}
	free_child(paths, cmd_arg, NULL);
	exit_msg("Command not found: ", argv[cmd], 127);
}
