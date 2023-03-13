/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:54:34 by imisumi           #+#    #+#             */
/*   Updated: 2023/03/13 15:40:40 by imisumi          ###   ########.fr       */
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

void	exit_msg(char *msg, char *msg2, int x)
{
	write(STDERR, msg, ft_strlen(msg));
	if (msg2)
		write(STDERR, msg2, ft_strlen(msg2));
	write(STDERR, "\n", 1);
	exit(x);
}

void	exit_error(char *msg, int code)
{
	perror(msg);
	exit(code);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pip	pip;

	if (argc == 5)
		pipex(argv, envp, pip);
	else
	{
		write(STDERR, "Invalid number of arguments\n", 28);
		return (1);
	}
}
