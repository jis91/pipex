#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"

void    run_pipex(int fd[2], int file1, int file2, char **argv, char **envp);
void    child_one(int fd[2], int file1, char **argv, char **envp);
void    child_two(int fd[2], int file2, char **argv, char **envp);
void    execute(char *cmd, char **envp);
char    *get_path_from_envp(char **envp);
char    *resolve_path(char *cmd, char **envp);
void    free_split(char **tab);
void    error_exit(char *msg);

#endif