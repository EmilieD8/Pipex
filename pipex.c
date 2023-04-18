/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:14:28 by edrouot           #+#    #+#             */
/*   Updated: 2023/04/18 15:27:13 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_access(char **envp, char **cmd)
{
	char		*path_cmd;
	int			i;
	char		**path_arr;
	char		*tmp;

	path_arr = get_path(envp);
	i = 0;
	while (path_arr[i] != (void *) '\0')
	{
		tmp = ft_strjoin(path_arr[i], "/");
		path_cmd = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(path_cmd, F_OK | X_OK) != 0)
			free(path_cmd);
		else
			break ;
		i++;
	}
	if (path_arr[i] == (void *) '\0')
		free_all(path_arr, cmd);
	free_arr(path_arr);
	return (path_cmd);
}

void	child_one(int *pipefd, char **argv, char **envp)
{
	char	**cmd;
	char	*path;
	int		fd;

	cmd = NULL;
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
	execve(path, cmd, envp);
	free(path);
}

void	child_two(int *pipefd, char **argv, char **envp)
{
	char	**cmd;
	char	*path;
	int		fd;

	fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
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
	free(path);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid[2];

	if (argc != 5)
	{
		write (2, "Error\n", 6);
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
