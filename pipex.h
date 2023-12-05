/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:30:26 by hannes            #+#    #+#             */
/*   Updated: 2023/12/05 19:05:20 by hannes           ###   ########.fr       */
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

t_command	parse_input(char **input, char **envp);
void		free_strs(char **arr);

#endif