/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 22:58:03 by hannes            #+#    #+#             */
/*   Updated: 2023/12/06 00:05:01 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	exec_cmd(t_exec exec, char **envp)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		dup2(exec.in, STDIN_FILENO);
		close(exec.in);
		dup2(exec.out, STDOUT_FILENO);
		close(exec.out);
		close(exec.close);
		if (access(exec.bin, X_OK) == 0)
			execve(exec.bin, exec.args, envp);
		else
			return (-1);
		ft_printf("This shouldn't be printed\n");
	}
	return (pid);
}

int	start_firstcmd(t_command cmd, int pipe_fd[2], char **envp)
{
	int		pid;
	t_exec	exec;

	exec.in = open(cmd.infile, O_RDONLY);
	if (exec.in < 0)
		exit_onerror(cmd.infile, cmd);
	exec.out = pipe_fd[1];
	exec.close = pipe_fd[0];
	exec.bin = cmd.bin1;
	exec.args = cmd.args1;
	pid = exec_cmd(exec, envp);
	if (pid < 0)
		exit_onerror("exec", cmd);
	close(exec.in);
	return (pid);
}

int	start_secondcmd(t_command cmd, int pipe_fd[2], char **envp)
{
	int		pid;
	t_exec	exec;

	exec.in = pipe_fd[0];
	exec.out = open(cmd.outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (exec.in < 0)
		exit_onerror(cmd.outfile, cmd);
	exec.close = pipe_fd[1];
	exec.bin = cmd.bin2;
	exec.args = cmd.args2;
	pid = exec_cmd(exec, envp);
	if (pid < 0)
		exit_onerror("exec", cmd);
	close(exec.out);
	return (pid);
}

void	pipex(t_command cmd, char **envp)
{
	int		pipe_fd[2];
	int		pid1;
	int		pid2;

	if (pipe(pipe_fd) == -1)
		return ;
	pid1 = start_firstcmd(cmd, pipe_fd, envp);
	pid2 = start_secondcmd(cmd, pipe_fd, envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
