/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:36:27 by vlugand-          #+#    #+#             */
/*   Updated: 2021/10/08 18:48:12 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return ;
}

char	**get_env_paths(char **envp)
{
	int		i;
	char	**all;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	all = ft_split(envp[i] + 5, ':');
	return (all);	
}

char	*find_path(char *cmd, char **envp)
{
	char	*path;
	char	*tmp;
	char	**all;
	int		i;

	all = get_env_paths(envp);
	if (!all)
		return (NULL);
	i = 0;
	while (all[i])
	{
		tmp = ft_strjoin(all[i], "/");
		path = ft_strjoin(tmp, cmd);
		if (tmp)
			free(tmp);
		if (access(path, F_OK) == 0)
		{
			free_split(all);
			return (path);
		}
		free(path);
		i++;
	}
	return (NULL);
}

void	error()
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	exec_cmd(char **envp, char **argv, int n)
{
	char	**split;
	char	*path;

	split = ft_split(argv[n], ' ');
	path = find_path(split[0], envp);
	if (!split)
		return ;
	execve(path, split, envp);
	return ;
}

void	read_from_pipe(int *fd, char **argv, char **envp)
{
	int		file;

	file = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU); //flag pas ouf pour la crea
	if (file == -1)
		error();
	dup2(file, STDOUT_FILENO);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	exec_cmd(envp, argv, 3);
	close(file); // never reached unless execve issue
}

void	write_to_pipe(int *fd, char **argv, char **envp)
{
	int		file;

	file = open(argv[1], O_RDONLY);
	if (file == -1)
		error();
	dup2(file, STDIN_FILENO);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exec_cmd(envp, argv, 2);
	close(file);
}

int		main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		pid1;
	int		pid2;

	if (argc != 5)
	{
		write(1, "Error: not enough arguments", 27);
		return (1);
	}
	if (pipe(fd) == - 1)
		error();
	pid1 = fork();
	if (pid1 < 0)
		return (1);
	if (pid1 == 0)
		write_to_pipe(fd, argv, envp); // execve will stop here
	pid2 = fork(); // only 3 processes since previous child will never reach this line
	if (pid2 < 0)
		return (1);
	if (pid2 == 0)
		read_from_pipe(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
