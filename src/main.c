/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:44 by hannes            #+#    #+#             */
/*   Updated: 2023/12/08 23:26:56 by hannes           ###   ########.fr       */
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
	pipex(cmd, envp);
	free_cmd(cmd);
}
