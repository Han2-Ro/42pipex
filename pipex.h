/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:30:26 by hannes            #+#    #+#             */
/*   Updated: 2023/11/29 16:25:24 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
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