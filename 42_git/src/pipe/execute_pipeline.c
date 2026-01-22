/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:56:57 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/22 20:34:02 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	handle_signal(void);
int	detect_signal(pid_t pid, int signum);

int	count_proc(t_command *command)
{
	int	count;

	count = 0;
	while (command)
	{
		count++;
		command = command->next;
	}
	return (count);
}

int	setfd_infile(t_command *command)
{
	while (command->inrdt != NULL)
	{
		if (command->inrdt->type == INFILE)
			command->infd = open(command->inrdt->rdt, O_RDONLY);
		if (command->inrdt->type == HEREDOC)
			command->infd = STDIN_FILENO;
		command->inrdt = command->inrdt->next;
	}
	return (SUCCESS);
}

int	setfd_outfile(t_command *command)
{
	while (command->outrdt != NULL)
	{
		if (command->outrdt->type == OUTFILE)
			command->outfd = open(command->outrdt->rdt, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (command->outrdt->type == APPEND)
			command->outfd = open(command->outrdt->rdt, O_WRONLY | O_CREAT | O_APPEND, 0644);
		command->outrdt = command->outrdt->next;
	}
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
	int		proc_count;
	int		ret;

	envp = convert_to_envp(env_lst);
	proc_count = count_proc(command);
	if (proc_count == 1)
		ret = nopipe_execute(command, envp);
	else
		ret = pipeline(command, envp, proc_count);
	free_null_term_strs(envp);

	(void)top;
//	free_env_lst(env_lst);
//	free_node_exec(top);

	return (ret);
}
