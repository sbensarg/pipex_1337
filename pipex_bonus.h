/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:10:09 by chicky            #+#    #+#             */
/*   Updated: 2021/07/14 16:27:57 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "GNL/get_next_line.h"
# include "errno.h"

typedef struct s_pipex
{
	int		fd1;
	int		fd2;
	int		nbr_cmd;
	char	*fd_in;
	char	*fd_out;
	char	***cmd;
	char	**path;
	int		fd[2];
	int		pip[2];
	pid_t	p;
	char	*newpath;
	char	**newenviron;
	int		pipe_fd_in;
	int		*tab_pids;
	int		statuscode;
	char	*oldpath;
	char	*file;
}	t_pipex;

t_pipex	ft_init(char **argv, int argc, char **env);
char	*ft_check_path(char **path, char **cmd);
char	**ft_path(char **env);
int		check_file2(t_pipex data, int *j);
int		check_file2_append(t_pipex data, int *j);
int		check_file1(t_pipex data);
void	ft_tab_of_paths(t_pipex data, char **argv, int i, int *statuscode);
void	part1_here_doc(t_pipex data, char **env);
void	part2_here_doc(t_pipex data, char **env);
void	loop_pipe(t_pipex data, char **env);
int		exec_here_doc(t_pipex	data, char **argv, char **env);
int		loop_pids(t_pipex data, int scode);
void	ft_free_triple_pointer(char ***str, int	nbr_cmd);
void	free_path(char **path);
int		ft_scode(t_pipex data, int statuscode, int scode);
void	exec_cmds(t_pipex data, char **env);
void	ft_close_all(t_pipex data);
int		ft_if_multiple_pipe(t_pipex data, int argc, char **argv, char **env);
void	ft_invalid_cmd_127(int **statuscode, t_pipex data, int *j);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif