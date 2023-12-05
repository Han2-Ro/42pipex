/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hannes <hrother@student.42vienna.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 23:28:44 by hannes            #+#    #+#             */
/*   Updated: 2023/12/05 14:23:34 by hannes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void getpath(char **envp) {
    // Iterate through the envp array to find the PATH environment variable
    while (*envp != NULL) {
        // Check if the current environment variable starts with "PATH="
        if (ft_strncmp(*envp, "PATH=", 5) == 0) {
            // Print the value of the PATH environment variable
            ft_printf("PATH: %s\n", *envp + 5); // +5 to skip "PATH=" in the string
            return ; // Exit the program after finding PATH
        }

        envp++; // Move to the next environment variable
    }

    // If the loop completes without finding PATH
    ft_printf("PATH environment variable not found.\n");
}


void print_strs(char **strs)
{
	while(strs)
	{
		ft_printf("'%s',\n", strs);
		strs++;
	}
	ft_printf("\n");
}

void	print_cmd(t_command cmd)
{
	ft_printf("file1: '%s'\n", cmd.file1);
	ft_printf("file2: '%s'\n", cmd.file2);
	ft_printf("cmd1: '%s'\n", cmd.cmd1);
	ft_printf("args1: ");
	print_strs(cmd.args1);
	ft_printf("cmd2: '%s'\n", cmd.cmd2);
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
	int file1;
	int file2;
	t_command cmd;

	getpath(envp);
	if(argc !=5)
		return (1);
	cmd = parse_input(argv + 1);
	if (pipe(pipe_fd) == -1)
		return (2);
	file1 = open(cmd.file1, O_RDONLY);
	if (file1 < 0)
		exit_onerror("file1", cmd);
	pid1 = exec_prgr(cmd.cmd1, cmd.args1, envp, file1,  pipe_fd[1], pipe_fd[0]);
	if (pid1 < 0)
		exit_onerror("exec", cmd);
	close(file1);
	file2 = open(cmd.file2, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file2 < 0)
		exit_onerror("file2", cmd);
	pid2 = exec_prgr(cmd.cmd2, cmd.args2, envp, pipe_fd[0], file2, pipe_fd[1]);
	if (pid1 < 0)
		exit_onerror("exec", cmd);
	close(file2);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_cmd(cmd);
	write(1, "All processes terminated.\n", 26);
}
