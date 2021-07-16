/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 11:16:12 by sbensarg          #+#    #+#             */
/*   Updated: 2021/07/13 17:02:43 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

void	ft_free_double_poniter(char **str, int	nbr_cmd)
{
	int	i;

	i = 0;
	while (i < nbr_cmd && str[i] != NULL)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	ft_free_triple_pointer(char ***str, int	nbr_cmd)
{
	int	i;

	i = 0;
	while (i < nbr_cmd && str[i] != NULL)
	{
		ft_free_double_poniter(str[i], nbr_cmd);
		i++;
	}
	free(str);
	str = NULL;
}

int	ft_scode(t_pipex data, int statuscode, int scode)
{
	if (scode && statuscode)
	{
		free(data.tab_pids);
		return (scode);
	}
	else if (statuscode)
	{
		free(data.tab_pids);
		return (statuscode);
	}
	else if (scode && statuscode == 0)
	{
		free(data.tab_pids);
		return (scode);
	}
	scode = loop_pids(data, statuscode);
	free(data.tab_pids);
	 return (WEXITSTATUS(scode));
}

void	ft_invalid_cmd_127(int **statuscode, t_pipex data, int *j)
{
	write(1, "invalid cmd\n", 12);
	if ((*j == 1 && data.nbr_cmd == 2) || (*j == data.nbr_cmd - 1))
		**statuscode = 127;
}
