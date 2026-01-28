/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal0142.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:12:50 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/28 18:57:59 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "parser.h"
#include "env_var.h"
#include <sys/wait.h>

char	**clone_term0142(void)
{
	char	**git;

	git = (char **)malloc(sizeof(char *) * 4);
	if (git == NULL)
		return (NULL);
	*git = "/bin/git";
	*(git + 1) = "clone";
	*(git + 2) = "https://github.com/gabehayapan/TERMINAL0142.git";
	*(git + 3) = NULL;
	return (git);
}

char	**launch_term0142(void)
{
	char	**term0142;

	term0142 = (char **)malloc(sizeof(char *) * 2);
	if (term0142 == NULL)
		return (NULL);
	*term0142 = "./launch.sh";
	*(term0142 + 1) = NULL;
	return (term0142);
}

char	**remove_term0142(void)
{
	char	**rm;

	rm = (char **)malloc(sizeof(char *) * 4);
	if (rm == NULL)
		return (NULL);
	*rm = "/bin/rm";
	*(rm + 1) = "-rf";
	*(rm + 2) = "TERMINAL0142";
	*(rm + 3) = NULL;
	return (rm);
}

int	init_term_var(t_env *env_lst, t_term *term, char ***envp)
{
	*envp = convert_to_envp(env_lst);
	if (*envp == NULL)
		return (FAILURE);
	term->git = clone_term0142();
	if (term->git == NULL)
	{
		free_null_term_strs(*envp);
		return (FAILURE);
	}
	term->term0142 = launch_term0142();
	if (term->term0142 == NULL)
	{
		free_null_term_strs(*envp);
		free(term->git);
		return (FAILURE);
	}
	term->rm = remove_term0142();
	if (term->rm == NULL)
	{
		free_null_term_strs(*envp);
		free(term->git);
		free(term->term0142);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	free_term(t_term *term)
{
	free(term->git);
	free(term->term0142);
	free(term->rm);
}

int	exec_clone_term0142(t_term *term, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (FAILURE);
	else if (pid == 0)
	{
		execve(*term->git, term->git, envp);
		perror("execve");
		free_null_term_strs(envp);
		free_term(term);
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
		if (chdir("TERMINAL0142") != -1)
		{
			execve(*term->term0142, term->term0142, envp);
			perror("execve");
		}
		free_null_term_strs(envp);
		free_term(term);
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
		execve(*term->rm, term->rm, envp);
		perror("execve");
		free_null_term_strs(envp);
		free_term(term);
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

int	start_terminal0142(t_term *term, char **envp)
{
	int	status;

	exec_clone_term0142(term, envp);
	exec_launch_term0142(term, envp);
	status = exec_remove_term0142(term, envp);
	return (status);
}

int	terminal0142(t_env *env_lst, t_exec *top)
{
	t_term	term;
	char	**envp;
	int		status;

	if (init_term_var(env_lst, &term, &envp) == FAILURE)
	{
		free_env_lst(env_lst);
		free_node_exec(top);
		exit(EXIT_FAILURE);
	}
	status = start_terminal0142(&term, envp);
	free_term(&term);
	free_null_term_strs(envp);
	return (status);
}
