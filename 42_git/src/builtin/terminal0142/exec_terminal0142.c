/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_terminal0142.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 11:21:40 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/31 11:28:13 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "parser.h"
#include "env_var.h"
#include <sys/wait.h>

int	default_signal(void);

int	exec_clone_term0142(t_term *term, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (FAILURE);
	else if (pid == 0)
	{
		close(2);
		if (default_signal() == FAILURE)
			exit(EXIT_FAILURE);
		execve(*term->git, term->git, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	if (wait(&status) == -1)
	{
		perror("wait");
		free_null_term_strs(envp);
		free_term(term);
		exit(EXIT_FAILURE);
	}
	return (status);
}

int	exec_launch_term0142(t_term *term, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (FAILURE);
	else if (pid == 0)
	{
		if (default_signal() == FAILURE)
			exit(EXIT_FAILURE);
		if (chdir("TERMINAL0142") != -1)
		{
			execve(*term->term0142, term->term0142, envp);
			perror("execve");
		}
		exit(EXIT_FAILURE);
	}
	if (wait(&status) == -1)
	{
		perror("wait");
		free_null_term_strs(envp);
		free_term(term);
		exit(EXIT_FAILURE);
	}
	return (status);
}

int	exec_remove_term0142(t_term *term, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (FAILURE);
	else if (pid == 0)
	{
		if (default_signal() == FAILURE)
			exit(EXIT_FAILURE);
		execve(*term->rm, term->rm, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	if (wait(&status) == -1)
	{
		perror("wait");
		free_null_term_strs(envp);
		free_term(term);
		exit(EXIT_FAILURE);
	}
	return (status);
}
