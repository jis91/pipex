#include "pipex.h"

void    child_one(int fd[2], int file1, char **argv, char **envp)
{
    if (dup2(file1, STDIN_FILENO) < 0)
        error_exit("dup2");
    if (dup2(fd[1], STDOUT_FILENO) < 0)
        error_exit("dup2");
    close(fd[0]);
    close(fd[1]);
    close(file1);
    execute(argv[2], envp);

}

void child_two(int fd[2], int file2, char **argv, char **envp)
{
    if (dup2(file2, STDOUT_FILENO) < 0)
        error_exit("dup2");
    if (dup2(fd[0], STDIN_FILENO) < 0)
        error_exit("dup2");
    close(fd[0]);
    close(fd[1]);
    close(file2);
    execute(argv[3], envp);
}

void execute(char *cmd, char **envp)
{
    char **argv_exec;
    char *path;

    argv_exec = ft_split(cmd, ' ');
    path = resolve_path(argv_exec[0], envp);
    if (path == NULL)
    {
        write(2, argv_exec[0], ft_strlen(argv_exec[0]));
        write(2, ": command not found\n", 20);
        free_split(argv_exec);
        exit(127); // 127 is standard cmd error in bash
    }
    execve(path, argv_exec, envp);
    free_split(argv_exec);
    free(path);
    error_exit(cmd);
}