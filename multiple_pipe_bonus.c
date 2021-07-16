/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 15:45:12 by sbensarg          #+#    #+#             */
/*   Updated: 2021/07/14 16:16:01 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_child(t_pipex data, int *i, char **env)
{
	close(data.fd[0]);
	dup2(data.pipe_fd_in, 0);
	close(data.pipe_fd_in);
	if (data.cmd[*i + 1] != NULL)
		dup2(data.fd[1], 1);
	close(data.fd[1]);
	if (data.cmd[*i + 1] == NULL)
	{
		dup2(data.fd2, 1);
		close (data.fd2);
	}
	if (data.pipe_fd_in == -1 && data.cmd[0][0])
		return ;
	if (data.fd2 == -1)
		return ;
	execve(data.cmd[*i][0], data.cmd[*i], env);
	exit(EXIT_FAILURE);
}

void	loop_pipe(t_pipex data, char **env)
{
	int	ret;
	int	i;

	data.pipe_fd_in = data.fd1;
	i = 0;
	while (data.cmd[i] != NULL)
	{
		ret = pipe(data.fd);
		if (ret == -1)
			exit (EXIT_FAILURE);
		data.p = fork();
		if (data.p == -1)
			exit (EXIT_FAILURE);
		else if (data.p == 0)
			exec_child(data, &i, env);
		else
		{
			data.tab_pids[i] = data.p;
			close(data.fd[1]);
			close(data.pipe_fd_in);
			data.pipe_fd_in = data.fd[0];
		}
		i++;
	}
}
