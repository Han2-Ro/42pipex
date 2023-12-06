/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:44 by hannes            #+#    #+#             */
/*   Updated: 2023/12/06 20:17:17 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_command	cmd;

	if (argc != 5)
	{
		ft_printf("usage: %s infile cmd1 cmd2 outfile\n", argv[0]);
		return (1);
	}
	cmd = parse_input(argv + 1, envp);
	if (!cmd.bin1 || !cmd.bin2)
	{
		ft_putendl_fd("command not found", 2);
		free_cmd(cmd);
		return (2);
	}
	pipex(cmd, envp);
	free_cmd(cmd);
}
