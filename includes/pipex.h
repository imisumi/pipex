/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 21:15:55 by ichiro            #+#    #+#             */
/*   Updated: 2023/03/13 15:47:35 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "../lib/libft/includes/libft.h"

# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO

typedef struct s_pip
{
	int		in;
	int		out;
	int		end[2];
	pid_t	pid_1;
	pid_t	pid_2;
	char	*cmd_path;
	char	**cmd_arg;
	char	**paths;
}	t_pip;

// MAIN
void	free_double(char **array);
void	free_child(char **paths, char **cmd_arg, char *cmd_path);
void	exit_msg(char *msg, char *msg2, int x);
void	exit_error(char *msg, int code);

// PIPEX
void	pipex(char *argv[], char *envp[], t_pip pip);

// PATHS
char	**env_paths(char **envp);

// UTILS
void	check_cmd(char **paths, char **argv, char **envp, int cmd);

#endif