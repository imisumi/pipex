/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:57:59 by imisumi           #+#    #+#             */
/*   Updated: 2023/03/13 14:59:32 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_env_path(char **envp)
{
	int		i;
	char	*env;

	i = 0;
	while (envp[i])
	{
		env = ft_strnstr(envp[i], "PATH", 4);
		if (env != NULL)
		{
			env = env + 5;
			return (env);
		}
		i++;
	}
	return (NULL);
}

char	**env_paths(char **envp)
{
	int		i;
	char	*env;
	char	*temp;
	char	**paths;

	env = get_env_path(envp);
	if (env == NULL)
		return (NULL);
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
