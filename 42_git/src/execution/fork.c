/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 16:20:31 by keitotak          #+#    #+#             */
/*   Updated: 2026/02/05 14:52:48 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	default_signal(void);

int	redirect_pipe(t_pipe *p, t_command *command, int p_nbr)
{
	if (command->next)
	{
		if (dup2(p->pipefd[2 * p_nbr + 1], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			return (EXIT_FAILURE);
		}
	}
	if (p_nbr)
	{
		if (dup2(p->pipefd[2 * (p_nbr - 1)], STDIN_FILENO) < 0)
		{
			perror("dup2");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

void	exit_cleanup(t_pipe *p, t_command *command)
{
	cleanup_pipe(p);
	free_vars(p->env_lst, p->to_free);
	close(command->stdfd[0]);
	close(command->stdfd[1]);
	exit(EXIT_FAILURE);
}

int	fork_process(t_pipe *p, t_command *command, int p_nbr)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close_pipes(p->pipefd, p_nbr);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (default_signal() == EXIT_FAILURE)
			exit_cleanup(p, command);
		if (redirect_pipe(p, command, p_nbr) == EXIT_FAILURE)
			exit_cleanup(p, command);
		if (redirect_fd(command) == EXIT_FAILURE)
			exit_cleanup(p, command);
		cleanup_pipe(p);
		exec_command(command, p->env_lst, p->to_free);
	}
	return (pid);
}
