# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

int	main(void)
{
	// char	*cmd[] = {"/bin/ls", NULL};

	// // cmd = {"/bin/ls", "-l", NULL};
	// execve(cmd[0], cmd, 0);

	if (access("lsf", F_OK) != 0)
		write(1, "no such file or directory", 25);
	if (access("lsf", X_OK) == 0)
		write(1, "OK", 2);
}
