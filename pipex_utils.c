/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 17:57:33 by sbensarg          #+#    #+#             */
/*   Updated: 2021/07/13 17:04:35 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*if_absolute_path(char **cmd, int *j)
{
	char	*newpath;

	newpath = ft_strdup(*cmd);
	*j = 0;
	if (access(newpath, F_OK) == 0)
	{
		if (open(newpath, O_DIRECTORY) > 0)
		{
			*j = 1;
			return (newpath);
		}
		else if (access(newpath, R_OK | X_OK) == 0)
		{
			*j = 0;
			return (newpath);
		}
	}
	free(newpath);
	return (NULL);
}

char	*ft_check_absolute_path(int *j, int **statuscode, t_pipex data)
{
	int	flag;

	data.newpath = if_absolute_path(data.cmd[*j], &flag);
	if (flag == 1 && data.fd2 != -1)
	{
		free(data.newpath);
		write(1, data.newpath, ft_strlen(data.newpath));
		write(1, ": is a directory\n", 17);
		if ((*j == 1 && data.nbr_cmd == 2) || (*j == data.nbr_cmd - 1))
			**statuscode = 126;
		data.newpath = NULL;
	}
	else if (data.newpath == NULL)
	{
		write(1, "invalid cmd\n", 12);
		if ((*j == 1 && data.nbr_cmd == 2) || (*j == data.nbr_cmd - 1))
			**statuscode = 127;
	}
	return (data.newpath);
}

void	fill_cmd_with_paths(t_pipex data, int *j)
{
	if (data.cmd[*j][0] != '\0')
	{
		free(data.cmd[*j][0]);
		data.cmd[*j][0] = data.newpath;
	}
}

void	ft_tab_of_paths(t_pipex data, char **argv, int i, int *statuscode)
{
	int	j;
	int	nbr;

	j = 0;
	nbr = data.nbr_cmd;
	while (nbr > 0)
	{
		data.cmd[j] = ft_split(argv[i], ' ');
		if (data.cmd[j][0] == '\0' && data.fd2 != -1)
			ft_invalid_cmd_127(&statuscode, data, &j);
		else if (ft_strncmp(data.cmd[j][0], "/", 1) == 0)
			data.newpath = ft_check_absolute_path(&j, &statuscode, data);
		else
		{
			data.newpath = ft_check_path(data.path, data.cmd[j]);
			if (data.newpath == NULL)
				ft_invalid_cmd_127(&statuscode, data, &j);
		}
		fill_cmd_with_paths(data, &j);
		nbr--;
		j++;
		i++;
	}
}

int	loop_pids(t_pipex data, int scode)
{
	int	i;

	i = 0;
	while (i < data.nbr_cmd)
	{
		waitpid(data.tab_pids[i], &scode, 0);
		i++;
	}
	return (scode);
}
