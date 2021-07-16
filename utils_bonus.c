/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:47:33 by sbensarg          #+#    #+#             */
/*   Updated: 2021/07/14 16:18:14 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_if_multiple_pipe(t_pipex data, int argc, char **argv, char **env)
{
	int	i;
	int	scode;
	int	statuscode;

	i = 2;
	scode = 0;
	if (argc < 5)
		write(1, "invalid args\n", 13);
	ft_tab_of_paths(data, argv, i, &statuscode);
	free_path(data.path);
	data.fd2 = check_file2(data, &scode);
	if (scode == 1)
		scode = 1;
	loop_pipe(data, env);
	ft_free_triple_pointer(data.cmd, data.nbr_cmd);
	free(data.newpath);
	scode = ft_scode(data, statuscode, scode);
	return (scode);
}

void	ft_close_all(t_pipex data)
{
	close(data.fd[0]);
	close(data.fd[1]);
	close(data.pip[0]);
	close(data.pip[1]);
	free_path(data.path);
	free(data.newpath);
	ft_free_triple_pointer(data.cmd, data.nbr_cmd);
}

void	exec_cmds(t_pipex data, char **env)
{
	if (data.cmd[0][0])
		part1_here_doc(data, env);
	if (data.cmd[1][0])
		part2_here_doc(data, env);
}
