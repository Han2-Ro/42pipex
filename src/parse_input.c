/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:06:32 by hrother           #+#    #+#             */
/*   Updated: 2023/11/29 16:46:52 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_command	parse_input(char **input)
{
	t_command cmd;
	char **cmd1;
	char **cmd2;

	cmd.file1 = input[0];
	cmd.file2 = input[3];
	cmd1 = ft_split(input[1], ' ');
	cmd.cmd1 = cmd1[0];
	cmd.args1 = cmd1;
	cmd2 = ft_split(input[2], ' ');
	cmd.cmd2 = cmd2[0];
	cmd.args2 = cmd2;
	return (cmd);
}
