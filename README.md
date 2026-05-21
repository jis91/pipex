*This project has been created as part of the 42 curriculum by jstrasse*

# Pipex | 42 Lausanne
made by Jefferson Strasser (jstrasse@student.42lausanne.ch)

## Description

What is Pipex ? And what is the goal of this project ?

Pipex is a program that reproduces the behavior of the Unix pipe mechanism in C.
It takes two commands and two files as arguments and executes the following
shell behavior:

< file1 cmd1 | cmd2 > file2

The program creates a pipe between two child processes. The first child reads
from file1 and executes cmd1, sending its output into the pipe. The second
child reads from the pipe and executes cmd2, writing the result to file2.

The bonus part handles multiple pipes with N commands, and supports here_doc
mode which reads from stdin until a LIMITER word is found, appending the
result to the output file. 
I did not do this part for time reasons but I have understood the concept 
and will probably implement it for Minishell.

## Instructions

To compile the mandatory part:
make

To compile with bonus:
make bonus

Usage:
./pipex file1 cmd1 cmd2 file2

Example:
./pipex infile "ls -l" "wc -l" outfile

Bonus usage with multiple pipes:
./pipex file1 cmd1 cmd2 cmd3 file2

Bonus usage with here_doc:
./pipex here_doc LIMITER cmd1 cmd2 file

## Resources

Before starting I read this Medium article by a fellow 42 student which
explains pipe, fork and dup2 with clear diagrams and code examples:
https://medium.com/@lannur-s/pipex-42-chapter-4-pipe-5b4afa4a37b7

It helped me understand the pipe fd flow, why unused ends must be closed
after fork, and how dup2 redirects stdin/stdout to the pipe.

I also consulted the man pages for every syscall used in this project:
pipe(2), fork(2), dup2(2), execve(2), waitpid(2), open(2), access(2).

I used AI (Claude) throughout this project as a guided tutor. Rather than
generating code automatically, I used it to understand concepts step by step:
- understanding pipe fd flow and why unused ends must be closed
- understanding what dup2 actually changes in the fd table
- understanding fork return values and parent/child process behavior
- debugging error messages going to stdout instead of stderr
- designing a clean modular architecture reusable for minishell

All code was written by me after understanding each concept through guided
explanation and pseudo-code hints. Claude did not generate any code for me.

## Difficulties

The main difficulty I encountered was file descriptor management. Understanding
why each process must close the pipe ends it does not use — and why the parent
must close both ends before waitpid — took time to fully grasp. Getting it
wrong causes silent hangs that are hard to debug.

The second difficulty was error handling — making sure error messages go to
stderr and not stdout, which would pollute the pipe output.

Thank you for reading, I hope you enjoy my work. Cheers ! Jefferson