/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   pipex.h                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstrasse <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/05/21 14:17:34 by jstrasse       #+#    #+#                */
/*   Updated: 2026/05/21 14:39:39 by jstrasse       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_pipex
{
	int		file1;
	int		file2;
	int		fd[2];
	char	**argv;
	char	**envp;
}	t_pipex;

void	run_pipex(t_pipex *pipex);
void	child_one(t_pipex *pipex);
void	child_two(t_pipex *pipex);
void	execute(char *cmd, char **envp);
char	*get_path_from_envp(char **envp);
char	*resolve_path(char *cmd, char **envp);
void	free_split(char **tab);
void	error_exit(char *msg);

#endif
