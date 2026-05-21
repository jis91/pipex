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

int	run_pipex(t_pipex *pipex)
{
	int		status;

	status = 0;
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		error_exit("fork");
	else if (pipex->pid1 == 0)
		child_one(pipex);
	else
	{
		pipex->pid2 = fork();
		if (pipex->pid2 < 0)
			error_exit("fork");
		else if (pipex->pid2 == 0)
			child_two(pipex);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		close(pipex->file1);
		close(pipex->file2);
		waitpid(pipex->pid1, NULL, 0);
		waitpid(pipex->pid2, &status, 0);
	}
	return (WEXITSTATUS(status));
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
	return (run_pipex(&pipex));
}
