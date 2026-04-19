/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nopipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:56:57 by keitotak          #+#    #+#             */
/*   Updated: 2026/02/03 12:03:34 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include "builtin.h"

int	default_signal(void);

int	nopipe_builtin(t_command *command, t_env **env_lst, t_to_free *to_free)
{
	int	stdin_fd;
	int	stdout_fd;
	int	exit_code;

	stdin_fd = dup(STDIN_FILENO);
	stdout_fd = dup(STDOUT_FILENO);
	if (redirect_fd(command) == FAILURE)
		return (FAILURE);
	exit_code = pass_to_builtin(command, env_lst, to_free);
	dup2(stdin_fd, STDIN_FILENO);
	dup2(stdout_fd, STDOUT_FILENO);
	close(stdin_fd);
	close(stdout_fd);
	return (exit_code);
}

void	exit_free_vars(t_env **env_lst, t_to_free *to_free)
{
	free_vars(env_lst, to_free);
	exit(EXIT_FAILURE);
}

int	nopipe_execute(t_command *command, t_env **env_lst, t_to_free *to_free)
{
	pid_t	pid;

	if (is_builtin(command->command[0]) != ELSE)
		return (nopipe_builtin(command, env_lst, to_free));
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (FAILURE);
	}
	if (pid == 0)
	{
		if (default_signal() == EXIT_FAILURE)
			exit_free_vars(env_lst, to_free);
		if (redirect_fd(command) == EXIT_FAILURE)
			exit_free_vars(env_lst, to_free);
		exec_command(command, env_lst, to_free);
	}
	return (wait_for_children(&pid, 1));
}
