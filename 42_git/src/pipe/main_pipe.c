/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:56:57 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/19 16:49:09 by keitotak         ###   ########.fr       */
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

int	setfd_infile(t_command *command)
{
	while (command->inrdt->next != NULL)
		command->inrdt = command->inrdt->next;
	if (command->inrdt->type == INFILE)
		command->infd = open(command->inrdt->rdt, O_RDONLY);
	if (command->inrdt->type == HEREDOC)
		command->infd = STDIN_FILENO;
	return (SUCCESS);
}

int	setfd_outfile(t_command *command)
{
	while (command->outrdt->next != NULL)
		command->outrdt = command->outrdt->next;
	if (command->outrdt->type == OUTFILE)
		command->outfd = open(command->outrdt->rdt, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (command->outrdt->type == APPEND)
		command->outfd = open(command->outrdt->rdt, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (SUCCESS);
}

int	redirect_fd(t_command *command)
{
	if (command->inrdt)
	{
		setfd_infile(command);
		dup2(command->infd, STDIN_FILENO);
	}
	if (command->outrdt)
	{
		setfd_outfile(command);
		dup2(command->outfd, STDOUT_FILENO);
	}
	return (SUCCESS);
}

int	nopipe_execute(t_command *command, char **envp)
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
	{
		redirect_fd(command);
//		if (is_heredoc(command->inrdt))
//			heredoc();
		exec_command(command->command, envp);
	}
	g_sig = 0;
	if (waitpid(pid, &status, 0) == error)
	{
		if (g_sig == SIGINT || g_sig == SIGQUIT)
			return (detect_signal(pid, g_sig));
	}
	return (status_code(status));
}

int	execute(t_command *command, t_env *env_lst, t_exec *top)
{
	char	**envp;
	int		x;
	int		ret;

	envp = convert_to_envp(env_lst);
	x = count_pipes(command);
	if (x == 0)
		ret = nopipe_execute(command, envp);
	else
		ret = pipex(command, envp, x);
	free_null_term_strs(envp);

	(void)top;
//	free_env_lst(env_lst);
//	free_node_exec(top);

	return (ret);
}
