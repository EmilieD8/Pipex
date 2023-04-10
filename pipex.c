#include "pipex.h"

void error_out(char *function)
{
    perror(function);
    exit(EXIT_FAILURE);
}

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

    return (path_arr);
}

char *check_access(char **envp, char **cmd)
{
    char *path_cmd;
    int i;
    char **path_arr;

    path_arr = get_path(envp);
    i = 0;
    // free stuff
    write(2, "888", 3);
    while (path_arr[i] != (void*)'\0' || access(path_cmd, F_OK | X_OK) != 0)
    {
        path_cmd = ft_strjoin(path_arr[i], "/");
        path_cmd = ft_strjoin(path_cmd, cmd[0]);
        if (access(path_cmd, F_OK | X_OK) != 0)
            free(path_cmd);
        i++;
    }
    // if (path_arr[i] == (void*)'\0')
    //     error_out("Command not found");
    // free(path_arr) // while loop
    return (path_cmd);
}

void child_one(int *pipefd, char **argv, char **envp)
{
    char **cmd = NULL;
    char *path;
    int fd;

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        error_out("Error_fd_open");
    if (dup2(fd, STDIN_FILENO) == -1)
        error_out("Error_duplicate");
    if (dup2(pipefd[1], STDOUT_FILENO) == -1)
       error_out("Error_duplicate");
    close(pipefd[0]);
    close(fd);
    close(pipefd[1]);
    cmd = ft_split(argv[2], ' ');
    path = check_access(envp, cmd);
    write(2, "111", 3);
    execve(path, cmd, envp);
}

void child_two(int *pipefd, char **argv, char **envp)
{
    char **cmd;
    char *path;
    int fd;

    fd = open(argv[4], O_CREAT | O_WRONLY |  O_TRUNC, 0777);
    if (fd < 0)
        error_out("Error_fd_open");
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
        error_out("Error_duplicate");
    if (dup2(fd, STDOUT_FILENO) == -1)
        error_out("Error_duplicate");
    close(pipefd[1]);
    close(fd);
    close(pipefd[0]);
    cmd = ft_split(argv[3], ' ');
    path = check_access(envp, cmd);
    execve(path, cmd, envp);
}

int main(int argc, char **argv, char **envp)
{
    int pipe_fd[2];
    pid_t pid[2];

    if (argc != 5)
    {
        write (2, "Error\n", 6); // check if other error message is supposed to be written 
        return (0);
    }
    if (pipe(pipe_fd) == -1)
        error_out("pipe");
    pid[0] = fork();
    if (pid[0] == -1)
        error_out("Fork");
    else if (pid[0] == 0)
        child_one(pipe_fd, argv, envp);
    pid[1] = fork();
    if (pid[1] == -1)
        error_out("Fork");
    else if (pid[1] == 0)
       child_two(pipe_fd, argv, envp);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
    return (0);
}