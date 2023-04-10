#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

# include "Libft/libft.h"

char **get_path(char **envp);
char *check_access(char **path_arr, char **cmd);
void child_one(int *pipefd, char **argv, char **envp);
void child_two(int *pipefd, char **argv, char **envp);

#endif