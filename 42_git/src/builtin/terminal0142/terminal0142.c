/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal0142.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 17:12:50 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/04 10:45:04 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "parser.h"
#include "env_var.h"
#include <sys/wait.h>
#include <termcap.h>

void	free_term(t_term *term)
{
	free(term->git);
	free(term->term0142);
	free(term->rm);
}

static void	clear_screen(void)
{
	char		buf[1024];
	const char	*term;
	char		*str;

	term = getenv("TERM");
	tgetent(buf, term);
	str = tgetstr("cl", NULL);
	if (str != NULL)
		ft_printf("%s", str);
}

static int	start_terminal0142(t_term *term, char **envp)
{
	int	status;

	exec_clone_term0142(term, envp);
	exec_launch_term0142(term, envp);
	status = exec_remove_term0142(term, envp);
	return (status);
}

int	terminal0142(t_env *env_lst, t_to_free *to_free)
{
	t_term	term;
	char	**envp;
	int		status;

	if (init_term_var(env_lst, &term, &envp) == FAILURE)
	{
		free_all(env_lst, to_free);
		exit(EXIT_FAILURE);
	}
	clear_screen();
	status = start_terminal0142(&term, envp);
	free_term(&term);
	free_null_term_strs(envp);
	return (status);
}
