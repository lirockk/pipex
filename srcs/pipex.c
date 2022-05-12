/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:54:37 by ademurge          #+#    #+#             */
/*   Updated: 2022/05/12 16:28:07 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_cmd(t_arg *args)
{
	int		i;

	i = 0;
	args->pid = fork();
	if (args->pid == -1)
		pipex_error(FORK_ERROR, 1, args);
	if (args->pid == CHILD)
	{
		dup2(args->fd_1, STDIN_FILENO);
		dup2(args->pipe[1], STDOUT_FILENO);
		close(args->pipe[0]);
		while (args->split_path[i])
		{
			execve(args->cmd_1_path, args->cmd_1_args, args->env);
			args->cmd_1_path = ft_strjoin(args->split_path[i],
					args->cmd_1, args);
			i++;
		}
		pipex_error("Command not found", 1, args);
	}
	waitpid(args->pid, NULL, 0);
	close(args->fd_1);
	close(args->pipe[1]);
}

void	second_cmd(t_arg *args)
{
	int		i;

	i = 0;
	args->pid = fork();
	if (args->pid == -1)
		pipex_error(FORK_ERROR, 1, args);
	if (args->pid == CHILD)
	{
		dup2(args->pipe[0], STDIN_FILENO);
		dup2(args->fd_2, STDOUT_FILENO);
		close(args->pipe[1]);
		while (args->split_path[i])
		{
			execve(args->cmd_2_path, args->cmd_2_args, args->env);
			args->cmd_2_path = ft_strjoin(args->split_path[i],
					args->cmd_2, args);
			i++;
		}
		pipex_error("Command not found", 1, args);
	}
	waitpid(args->pid, NULL, 0);
	close(args->fd_2);
	close(args->pipe[0]);
}
