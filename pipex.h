/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:15:53 by edrouot           #+#    #+#             */
/*   Updated: 2023/04/19 15:24:18 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	**get_path(char **envp);
char	*check_access(char **envp, char **cmd);
void	child_one(int *pipefd, char **argv, char **envp);
void	child_two(int *pipefd, char **argv, char **envp);
void	error_out(char	*function);
void	free_arr(char **arr);
void	free_all(char **path_arr, char **cmd);

#endif
