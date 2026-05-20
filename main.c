#include "pipex.h"

void    run_pipex(int fd[2], int file1, int file2, char **argv, char **envp)
{
    pid_t pid1;
    pid_t pid2;
    pid1 = fork();
    if (pid1 < 0)
        error_exit("fork");
    else if (pid1 == 0)
        child_one(fd, file1, argv, envp);
    else
    {
        pid2 = fork();
        if (pid2 < 0)
            error_exit("fork");
        else if (pid2 == 0)
            child_two(fd, file2, argv, envp);
        close(fd[0]);
        close(fd[1]);
        close(file1);
        close(file2);
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
    }
}

int main(int argc, char **argv, char **envp)
{
    int file1;
    int file2;
    int fd[2];

    if (argc != 5)
    {
        write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
        return (1);
    }
    file1 = open(argv[1], O_RDONLY);
    if (file1 < 0)
    {
        perror(argv[1]);
    }
    file2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file2 < 0)
        error_exit(argv[4]);
    if (pipe(fd) < 0)
        error_exit("pipe");
    run_pipex(fd, file1, file2, argv, envp);
    return (0);
}

