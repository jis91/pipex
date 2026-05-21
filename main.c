/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   main.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstrasse <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/05/21 14:07:23 by jstrasse       #+#    #+#                */
/*   Updated: 2026/05/21 14:40:53 by jstrasse       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_pipex(t_pipex *pipex)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 < 0)
		error_exit("fork");
	else if (pid1 == 0)
		child_one(pipex);
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			error_exit("fork");
		else if (pid2 == 0)
			child_two(pipex);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		close(pipex->file1);
		close(pipex->file2);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
		return (1);
	}
	pipex.file1 = open(argv[1], O_RDONLY);
	if (pipex.file1 < 0)
	{
		perror(argv[1]);
	}
	pipex.file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.file2 < 0)
		error_exit(argv[4]);
	pipex.argv = argv;
	pipex.envp = envp;
	if (pipe(pipex.fd) < 0)
		error_exit("pipe");
	run_pipex(&pipex);
	return (0);
}
