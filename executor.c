/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   executor.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstrasse <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/05/21 14:01:51 by jstrasse       #+#    #+#                */
/*   Updated: 2026/05/21 14:42:40 by jstrasse       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_one(t_pipex *pipex)
{
	if (pipex->file1 < 0)
	{
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		exit(1);
	}
	if (dup2(pipex->file1, STDIN_FILENO) < 0)
		error_exit("dup2");
	if (dup2(pipex->fd[1], STDOUT_FILENO) < 0)
		error_exit("dup2");
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	close(pipex->file1);
	execute(pipex->argv[2], pipex->envp);
}

void	child_two(t_pipex *pipex)
{
	if (dup2(pipex->file2, STDOUT_FILENO) < 0)
		error_exit("dup2");
	if (dup2(pipex->fd[0], STDIN_FILENO) < 0)
		error_exit("dup2");
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	close(pipex->file2);
	execute(pipex->argv[3], pipex->envp);
}

void	execute(char *cmd, char **envp)
{
	char	**argv_exec;
	char	*path;

	argv_exec = ft_split(cmd, ' ');
	path = resolve_path(argv_exec[0], envp);
	if (path == NULL)
	{
		perror(argv_exec[0]);
		free_split(argv_exec);
		exit(127);
	}
	execve(path, argv_exec, envp);
	free_split(argv_exec);
	free(path);
	error_exit(cmd);
}
