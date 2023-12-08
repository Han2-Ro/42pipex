/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:06:32 by hrother           #+#    #+#             */
/*   Updated: 2023/12/08 23:32:24 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**getpath(char **envp)
{
	while (*envp != NULL)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}

char	*build_path(char *folder, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(folder, "/");
	res = ft_strjoin(tmp, cmd);
	free(tmp);
	return (res);
}

char	*path_to_bin(char **folders, char *cmd)
{
	char	*path;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (folders && *folders)
	{
		path = build_path(*folders, cmd);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		folders++;
	}
	ft_printf("pipex: %s: command not found\n", cmd);
	return (NULL);
}

t_command	parse_input(char **input, char **envp)
{
	t_command	cmd;
	char		**cmd1;
	char		**cmd2;
	char		**path;

	path = getpath(envp);
	cmd.infile = input[0];
	cmd.outfile = input[3];
	cmd1 = ft_split(input[1], ' ');
	if (cmd1 != NULL)
		cmd.bin1 = path_to_bin(path, cmd1[0]);
	else
		cmd.bin1 = NULL;
	cmd.args1 = cmd1;
	cmd2 = ft_split(input[2], ' ');
	if (cmd2 != NULL)
		cmd.bin2 = path_to_bin(path, cmd2[0]);
	else
		cmd.bin2 = NULL;
	cmd.args2 = cmd2;
	free_strs(path);
	return (cmd);
}
