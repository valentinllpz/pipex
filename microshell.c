/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlugand- <vlugand-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 21:45:39 by vlugand-          #+#    #+#             */
/*   Updated: 2021/10/08 18:48:47 by vlugand-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>


typedef struct	s_cmd
{
	int		pipe_before;
	int		pipe_after;
	int		fd_before[2];
	int		fd_after[2];
	int		argc;
	char	**argv;
} 				t_cmd;

void	fatal_error()
{
	printf("Fatal error\n");
	exit(0);
}

int		ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

t_cmd	*build_cmd(char **argv, int start, int len)
{
	t_cmd *cmd;

	if (!(cmd = malloc(sizeof(t_cmd))))
		fatal_error();
	cmd->argc = len;
	cmd->argv = &argv[start];
	cmd->argv[len] = NULL;
	cmd->pipe_after = 0;
	cmd->pipe_before = 0;
	return (cmd);
}

int		cd(t_cmd *cmd)
{
	if (cmd->argc != 2)
		ft_putstr_fd("error: bad arguments\n", 2);
	else if (chdir(cmd->argv[1]) == -1)
	{
		ft_putstr_fd("error: cannot change directory to ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd("\n", 2);
	}
	else
		return (0);
	return (1);	
}

int		execution(t_cmd *cmd, char **envp)
{
	int		ret;
	
	ret = execve();
	return (ret);
}

void	handle_pipe(t_cmd *cmd, char **envp, int next_pipe)
{	
	pid_t		pid;

	cmd->argv[next_pipe] = NULL;
	if (!cmd->pipe_before)
		if (pipe(cmd->fd_before) == - 1)
			fatal_error();
	else
		if (pipe(cmd->fd_after) == - 1)
			fatal_error();
	if ((pid = fork()) == -1)
		fatal_error();
	if (pid == 0 && !cmd->pipe_before)
	{
		close(cmd->fd_before[0]);
		dup2(cmd->fd_before[1], STDOUT_FILENO);
		close(cmd->fd_before[1]);
	}
	else if (pid == 0 && cmd->pipe_before)
	{
		close(cmd->fd_before[1]);
		dup2(cmd->fd_before[0], STDIN_FILENO);
		close(cmd->fd_before[0]);
		
	}
	
}

int		binary(t_cmd *cmd, char **envp)
{
	int		i = 0;

	while (cmd->argv[i])
	{
		if (strcmp(cmd->argv[i], "|") == 0)
			handle_pipe(cmd, envp, i);

	}
		
}



int		main(int argc, char **argv, char **envp)
{
	int		i = 0;
	t_cmd	*cmd = NULL;
	int 	start = 1;

	while (++i < argc)
	{
		if (strcmp(argv[i], ";") == 0)
		{
			cmd = build_cmd(argv, start, i - start);
		//	execution(cmd, envp);
			start = i + 1;
		}
		else if (!argv[i + 1])
		{
			cmd = build_cmd(argv, start, i + 1);
		//	return (execution(cmd, envp));
		}
	}
	return (0);
}
