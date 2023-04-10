#include "pipex.h"

char **get_path(char **envp)
{
    int i = 0;
    int length = 0;
    char *path;
    char **path_arr;
    while (*envp != (void *)'\0')
    {
        if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H')
            break;
        i++;
    }
    length = ft_strlen(envp[i]);
    path = malloc(sizeof(char *) * length + 1);
    if (!path)
        return (NULL);
    ft_strlcpy(path, envp[i], length + 1);
    path_arr = ft_split(path, ':');
    free(path);
    /// has to be freed, the path_arr via a while loop
    return (path_arr);
}


char *check_access(char **path_arr, char**argv, int cmd)
{
    char **split_argv;
    char *path_cmd;
    // int acc;
    int i;
    i = 0;

    split_argv = ft_split(argv[cmd], ' ');
    // free stuff

    while (access(path_cmd, F_OK | X_OK) != 0)
    {
        path_cmd = ft_strjoin(path_arr[i], "/");
        path_cmd = ft_strjoin(path_cmd, split_argv[0]);
        if (access(path_cmd, F_OK | X_OK) != 0)
            free(path_cmd);
        i++;
    }

    // printf("complete path is %s and path_arr is set to %d\n", path_cmd, i); // should be /usr/bin/ls    and i = 5
    return (path_cmd);
}

void child_one(int fd)


int main(int argc, char **argv, char **envp)
{
    argc++; // useless

    // int pid_fd[2];
    int fd[2];
    pid_t pid;

    if (argc != 5)
    {
        write (2, "Error\n", 6); // check if other error message is supposed to be written 
        return (0);
    }
    
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid = -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    child_one(pipefd, fd, argv, envp);


    int cmd = 2; // set up to be at the first command
    char **path_arr;
    path_arr = get_path(envp);
    check_access(path_arr, argv, cmd);


    return (0);
}