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

void    error_exit(char *msg)
{
    perror(msg);
    exit(1);
}

