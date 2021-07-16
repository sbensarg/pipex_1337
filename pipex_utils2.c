/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 18:29:19 by sbensarg          #+#    #+#             */
/*   Updated: 2021/07/13 13:32:35 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_file1(t_pipex data)
{
	data.fd1 = open(data.fd_in, O_RDONLY);
	if (open(data.fd_in, O_RDONLY) < 0)
	{
		perror("ERROR 1 ");
	}
	return (data.fd1);
}

int	check_file2(t_pipex data, int *j)
{
	data.fd2 = open(data.fd_out, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (data.fd2 < 0)
		perror("ERROR 3 ");
	if (errno == 13)
		*j = 1;
	return (data.fd2);
}

int	check_file2_append(t_pipex data, int *j)
{
	data.fd2 = open(data.fd_out, O_CREAT | O_APPEND | O_RDWR, 0777);
	if (data.fd2 < 0)
		perror("ERROR 3 ");
	if (errno == 13)
		*j = 1;
	return (data.fd2);
}

char	*ft_if_exec(char **path, char *file, int *j)
{
	char	*newpath;

	newpath = ft_strjoin(path[*j], file);
	if (access(newpath, F_OK) == 0)
	{
		if (access(newpath, R_OK | X_OK) == 0)
		{
			free(file);
			return (newpath);
		}
		else
		{
			free(file);
			free(newpath);
			return (NULL);
		}	
	}
	free(newpath);
	return (NULL);
}

char	*ft_check_path(char **path, char **cmd)
{
	int		j;
	char	*newpath;
	char	*file;

	j = 0;
	file = ft_strjoin("/", *cmd);
	while (path[j] != NULL)
	{
		newpath = ft_if_exec(path, file, &j);
		if (newpath)
			return (newpath);
		j++;
	}
	free(file);
	return (NULL);
}
