/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:07:42 by chicky            #+#    #+#             */
/*   Updated: 2021/07/14 16:15:48 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	write_in_pipe(char **argv, t_pipex	data)
{
	char	*line;

	write(1, "heredoc>", 8);
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
			break ;
		write(data.fd[1], line, ft_strlen(line));
		write(data.fd[1], "\n", 1);
		write(1, "heredoc>", 8);
		free(line);
	}
	free(line);
}

void	part1_here_doc(t_pipex data, char **env)
{
	data.p = fork();
	if (data.p == -1)
		exit (EXIT_FAILURE);
	if (data.p != 0)
		data.tab_pids[0] = data.p;
	else if (data.p == 0)
	{
		dup2(data.fd[0], 0);
		dup2(data.pip[1], 1);
		close(data.fd[1]);
		close(data.pip[0]);
		execve(data.cmd[0][0], data.cmd[0], env);
	}
}

void	part2_here_doc(t_pipex data, char **env)
{
	data.p = fork();
	if (data.p == -1)
		exit (EXIT_FAILURE);
	if (data.p != 0)
		data.tab_pids[1] = data.p;
	if (data.p == 0)
	{
		close(data.fd[0]);
		close(data.fd[1]);
		close(data.pip[1]);
		dup2(data.pip[0], 0);
		dup2(data.fd2, 1);
		close(data.fd2);
		if (data.fd2 == -1)
			return ;
		execve(data.cmd[1][0], data.cmd[1], env);
	}
}

int	exec_here_doc(t_pipex data, char **argv, char **env)
{
	int		i;
	int		ret;
	int		statuscode;
	int		scode;

	i = 3;
	data.nbr_cmd = 2;
	scode = 0;
	ret = pipe(data.fd);
	if (ret == -1)
		exit (EXIT_FAILURE);
	ret = pipe(data.pip);
	if (ret == -1)
		exit (EXIT_FAILURE);
	write_in_pipe(argv, data);
	ft_tab_of_paths(data, argv, i, &statuscode);
	data.fd2 = check_file2_append(data, &scode);
	if (scode == 1)
		scode = 1;
	exec_cmds(data, env);
	ft_close_all(data);
	scode = ft_scode (data, statuscode, scode);
	return (scode);
}
