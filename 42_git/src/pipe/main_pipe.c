/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:56:57 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/15 16:27:17 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "parser.h"

int	count_pipes(t_command *command)
{
	int	count;

	count = -1;
	while (command)
	{
		count++;
		command = command->next;
	}
	return (count);
}

int	nopipe_execute(char **command, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		exec_command(command, envp);
	wait(&status);
	return (status_code(status));
}

int	execute(t_command *command, t_env *env_lst)
{
	char	**envp;
	int		pipe_count;
	int		ret;

	envp = convert_to_envp(env_lst);
	pipe_count = count_pipes(command);
	if (pipe_count == 0)
		ret = nopipe_execute(command->command, envp);
	else
		ret = pipex(command, envp, pipe_count);
	free_null_term_strs(envp);
	return (ret);
}
