/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:56:57 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/15 17:57:17 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	handle_signal(void);
int	detect_signal(pid_t pid, int signum);

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
	g_sig = 0;
	if (waitpid(pid, &status, 0) == error)
	{
		if (g_sig == SIGINT || g_sig == SIGQUIT)
			return (detect_signal(pid, g_sig));
	}
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
		ret = pipex(command, envp);
	free_null_term_strs(envp);
	return (ret);
}
