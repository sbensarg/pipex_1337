# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/13 12:04:11 by sbensarg          #+#    #+#              #
#    Updated: 2021/07/14 16:19:48 by sbensarg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
SRCS = pipex.c init.c pipex_utils.c pipex_utils2.c free_all.c ft_split.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_memcpy.c
BSRCS = main_bonus.c init.c here_doc_bonus.c multiple_pipe_bonus.c pipex_utils.c pipex_utils2.c utils_bonus.c free_all.c ft_split.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_memcpy.c GNL/*.c 
FLAGS= -Wall -Wextra -Werror
rm = rm -f
CC = gcc

all : $(NAME)

$(NAME) : $(SRCS)
	@$(CC) $(FLAGS) $(SRCS) -o $(NAME)
	
bonus: $(NAME_BONUS)

$(NAME_BONUS) : $(BSRCS)
	@$(CC) $(FLAGS) $(BSRCS) -o $(NAME_BONUS)

clean :

fclean : clean
	@$(rm) $(NAME)
	@$(rm) $(NAME_BONUS)

re: fclean all