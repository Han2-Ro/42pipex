/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:06:32 by hrother           #+#    #+#             */
/*   Updated: 2023/12/03 20:25:16 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_command	parse_input(char **input)
{
	t_command cmd;
	char **cmd1;
	char **cmd2;

	//TODO: check if files are valid
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
