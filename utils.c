/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   utils.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: jstrasse <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/05/21 14:16:00 by jstrasse       #+#    #+#                */
/*   Updated: 2026/05/21 14:17:12 by jstrasse       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	error_exit(char *msg)
{
	perror(msg);
	exit(1);
}
