/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 16:40:25 by sbensarg          #+#    #+#             */
/*   Updated: 2021/07/13 12:21:00 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_path(char **env)
{
	int		i;
	char	**ptr;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			ptr = ft_split(env[i] + 5, ':');
		i++;
	}
	return (ptr);
}

t_pipex	ft_init(char **argv, int argc, char **env)
{
	t_pipex	data;

	data.fd_in = argv[1];
	data.nbr_cmd = argc - 3;
	data.fd_out = argv[argc - 1];
	data.cmd = malloc(sizeof(char **) * (data.nbr_cmd + 1));
	data.cmd[data.nbr_cmd] = NULL;
	data.path = ft_path(env);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) != 0)
		data.fd1 = check_file1(data);
	data.tab_pids = malloc (data.nbr_cmd + 1);
	data.newpath = ft_strdup("");
	return (data);
}
