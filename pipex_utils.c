/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:30:05 by edrouot           #+#    #+#             */
/*   Updated: 2023/04/18 15:30:19 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != (void *)0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return ;
}

void	error_out(char	*function)
{
	perror(function);
	exit(EXIT_FAILURE);
}

void	free_all(char **path_arr, char **cmd)
{
	free_arr(path_arr);
	free_arr(cmd);
	error_out("Command not found");
}

char	**get_path(char	**envp)
{
	int		i;
	int		length;
	char	*path;
	char	**path_arr;

	length = 0;
	i = 0;
	while (*envp != (void *) '\0')
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
			&& envp[i][2] == 'T' && envp[i][3] == 'H')
			break ;
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
