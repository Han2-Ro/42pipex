/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:30:26 by hannes            #+#    #+#             */
/*   Updated: 2023/12/06 00:04:19 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_command
{
	char	*infile;
	char	*outfile;
	char	*bin1;
	char	**args1;
	char	*bin2;
	char	**args2;
}	t_command;

typedef struct s_exec
{
	char	*bin;
	char	**args;
	char	**envp;
	int		in;
	int		out;
	int		close;
}	t_exec;

t_command	parse_input(char **input, char **envp);
void		free_strs(char **arr);
void		pipex(t_command cmd, char **envp);
void		free_strs(char **arr);
void		free_cmd(t_command cmd);
void		exit_onerror(char *msg, t_command cmd);

#endif