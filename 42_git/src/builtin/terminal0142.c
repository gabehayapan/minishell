/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal0142.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:12:50 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/31 11:28:15 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "parser.h"
#include "env_var.h"
#include <sys/wait.h>

void	free_term(t_term *term)
{
	free(term->git);
	free(term->term0142);
	free(term->rm);
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
