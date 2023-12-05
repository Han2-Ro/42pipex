/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:44 by hannes            #+#    #+#             */
/*   Updated: 2023/12/05 19:04:15 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void print_strs(char **strs)
{
	while(strs && *strs)
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

void free_strs(char **arr)
{
	int i;

	i = 0;
	while(arr[i])
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

void exit_onerror(char *msg, t_command cmd)
{
	free_cmd(cmd);
	perror(msg);
	exit(1);
}

int    exec_prgr(char *path, char *args[], char *envp[], int in, int out, int close_fd)
{
	int pid;

	pid = fork();
	if(pid < 0)
		return(-1);
	if (pid == 0)
	{
		dup2(in, STDIN_FILENO);
		close(in);
		dup2(out, STDOUT_FILENO);
		close(out);
		close(close_fd);
		if (access(path, X_OK) == 0)
			execve(path, args, envp);
		else
			return (-1);
		ft_printf("This shouldn't be printed\n");
	}
	return (pid);
}

int main(int argc, char **argv, char **envp)
{
	int pipe_fd[2];
	int pid1;
	int pid2;
	int infile;
	int outfile;
	t_command cmd;

	if(argc !=5)
		return (1);
	cmd = parse_input(argv + 1, envp);
	if (pipe(pipe_fd) == -1)
		return (2);
	infile = open(cmd.infile, O_RDONLY);
	if (infile < 0)
		exit_onerror(cmd.infile, cmd);
	pid1 = exec_prgr(cmd.bin1, cmd.args1, envp, infile,  pipe_fd[1], pipe_fd[0]);
	if (pid1 < 0)
		exit_onerror("exec", cmd);
	close(infile);
	outfile = open(cmd.outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
		exit_onerror(cmd.outfile, cmd);
	pid2 = exec_prgr(cmd.bin2, cmd.args2, envp, pipe_fd[0], outfile, pipe_fd[1]);
	if (pid1 < 0)
		exit_onerror("exec", cmd);
	close(outfile);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_cmd(cmd);
	write(1, "All processes terminated.\n", 26);
}
