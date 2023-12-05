/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 22:58:49 by hannes            #+#    #+#             */
/*   Updated: 2023/12/05 23:00:05 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	print_strs(char **strs)
{
	while (strs && *strs)
	{
		ft_printf("'%s',\n", *strs);
		strs++;
	}
	ft_printf("\n");
}

void	print_cmd(t_command cmd)
{
	ft_printf("file1: '%s'\n", cmd.infile);
	ft_printf("file2: '%s'\n", cmd.outfile);
	ft_printf("cmd1: '%s'\n", cmd.bin1);
	ft_printf("args1: ");
	print_strs(cmd.args1);
	ft_printf("cmd2: '%s'\n", cmd.bin2);
	ft_printf("args2: ");
	print_strs(cmd.args2);
}

void	free_strs(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_cmd(t_command cmd)
{
	free_strs(cmd.args1);
	free_strs(cmd.args2);
	free(cmd.bin1);
	free(cmd.bin2);
}

void	exit_onerror(char *msg, t_command cmd)
{
	free_cmd(cmd);
	perror(msg);
	exit(1);
}
