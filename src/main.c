/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:44 by hannes            #+#    #+#             */
/*   Updated: 2023/11/29 00:27:08 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int    exec_prgr(char *path, char *args[], char *env[], int in, int out)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		if (in != STDIN_FILENO)
		{
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (out != STDOUT_FILENO)
		{
			dup2(out, STDOUT_FILENO);
			close(out);
		}
		execve(path, args, env);
	}
	return (pid);
}

int main(void)
{
	char *args1[] = {"/bin/ls","-la", NULL};
	char *args2[] = {"/bin/grep","d", NULL};
	int fd[2];
	int pid1;
	int pid2;

	if (pipe(fd) == -1)
		return (1);
	pid1 = exec_prgr("/bin/ls", args1, NULL, STDIN_FILENO, fd[1]);
	pid2 = exec_prgr("/bin/grep", args2, NULL, fd[0], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	write(1, "Succes\n", 7);
}
