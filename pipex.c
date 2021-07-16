/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:30:40 by sbensarg          #+#    #+#             */
/*   Updated: 2021/07/14 16:27:35 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	part1(t_pipex data, char **env)
{
	data.p = fork();
	if (data.p == -1)
		exit (EXIT_FAILURE);
	if (data.p != 0)
		data.tab_pids[0] = data.p;
	else if (data.p == 0)
	{
		close(data.fd[0]);
		dup2(data.fd1, 0);
		close(data.fd1);
		dup2(data.fd[1], 1);
		close(data.fd[1]);
		execve(data.cmd[0][0], data.cmd[0], env);
	}
}

void	part2(t_pipex data, char **env)
{
	data.p = fork();
	if (data.p == -1)
		exit (EXIT_FAILURE);
	if (data.p != 0)
		data.tab_pids[1] = data.p;
	if (data.p == 0)
	{
		close(data.fd[1]);
		dup2(data.fd[0], 0);
		close(data.fd[0]);
		dup2(data.fd2, 1);
		close(data.fd2);
		if (data.fd2 == -1)
			return ;
		execve(data.cmd[1][0], data.cmd[1], env);
	}
}

void	ft_close_and_free(t_pipex data)
{
	free_path(data.path);
	ft_free_triple_pointer(data.cmd, data.nbr_cmd);
	free(data.newpath);
	close(data.fd[0]);
	close(data.fd[1]);
}

int	ft_norm_pipex(int argc, char **argv, char **env)
{
	int		ret;
	int		statuscode;
	int		scode;
	int		i;
	t_pipex	data;

	i = 2;
	statuscode = 0;
	scode = 0;
	data = ft_init(argv, argc, env);
	ft_tab_of_paths(data, argv, i, &statuscode);
	data.fd2 = check_file2(data, &scode);
	if (scode == 1)
		scode = 1;
	ret = pipe(data.fd);
	if (ret == -1)
		exit (EXIT_FAILURE);
	if (data.fd1 != -1 && data.cmd[0][0])
		part1(data, env);
	if (data.cmd[1][0])
		part2(data, env);
	ft_close_and_free(data);
	scode = ft_scode (data, statuscode, scode);
	return (scode);
}

int	main(int argc, char **argv, char **env)
{
	int		scode;

	scode = 0;
	if (argc != 5)
		write(1, "invalid args\n", 13);
	else
		scode = ft_norm_pipex(argc, argv, env);
	return (scode);
}
