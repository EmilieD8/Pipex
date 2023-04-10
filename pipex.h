#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "Libft/libft.h"

char **get_path(char **envp);
char *check_access(char **path_arr, char**argv, int cmd);

#endif