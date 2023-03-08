/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imisumi <imisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:54:34 by imisumi           #+#    #+#             */
/*   Updated: 2023/03/08 14:19:58 by imisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
