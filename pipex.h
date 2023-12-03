/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:30:26 by hannes            #+#    #+#             */
/*   Updated: 2023/11/30 16:39:18 by hannes           ###   ########.fr       */
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
	char	*file1;
	char	*file2;
	char	*cmd1;
	char	**args1;
	char	*cmd2;
	char	**args2;
}	t_command;

t_command	parse_input(char **input);

#endif