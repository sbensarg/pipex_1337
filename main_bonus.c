/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:02:11 by sbensarg          #+#    #+#             */
/*   Updated: 2021/07/14 16:24:56 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	data;
	int		i;
	int		statuscode;
	int		scode;

	i = 3;
	statuscode = 0;
	scode = 0;
	data = ft_init(argv, argc, env);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		if (argc != 6)
		{
			write(1, "invalid args\n", 13);
			exit(0);
		}
		scode = exec_here_doc(data, argv, env);
		return (scode);
	}
	else
		scode = ft_if_multiple_pipe(data, argc, argv, env);
	return (scode);
}
