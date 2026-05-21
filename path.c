/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   path.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstrasse <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/05/21 14:11:39 by jstrasse       #+#    #+#                */
/*   Updated: 2026/05/21 14:44:50 by jstrasse       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*try_path(char *dir, char *cmd)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(dir, "/");
	path = ft_strjoin(temp, cmd);
	free(temp);
	return (path);
}

static void	handle_permission(char **directories)
{
	free_split(directories);
	write(2, "Permission denied\n", 19);
	exit(126);
}

static char	*check_access(char *path, char **directories)
{
	if (access(path, X_OK) == 0)
	{
		free_split(directories);
		return (path);
	}
	if (access(path, F_OK) == 0)
	{
		free(path);
		handle_permission(directories);
	}
	free(path);
	return (NULL);
}

char	*get_path_from_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_strchr(envp[i], '=') + 1);
		i++;
	}
	return (NULL);
}

char	*resolve_path(char *cmd, char **envp)
{
	char	**directories;
	char	*path;
	char	*raw_path;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	raw_path = get_path_from_envp(envp);
	if (raw_path == NULL)
		return (NULL);
	i = 0;
	directories = ft_split(raw_path, ':');
	while (directories[i])
	{
		path = try_path(directories[i], cmd);
		path = check_access(path, directories);
		if (path)
			return (path);
		i++;
	}
	free_split(directories);
	return (NULL);
}
