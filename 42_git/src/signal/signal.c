/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:59:55 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/27 10:57:53 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include "ftprintf.h"

void	redisplay_prompt(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	signal_in_loop(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = redisplay_prompt;
	sa_quit.sa_handler = SIG_IGN;
	if (sigemptyset(&sa_int.sa_mask) == -1)
		return (EXIT_FAILURE);
	if (sigemptyset(&sa_quit.sa_mask) == -1)
		return (EXIT_FAILURE);
	sa_int.sa_flags = 0;
	sa_quit.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
		return (EXIT_FAILURE);
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ignore_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	if (sigemptyset(&sa.sa_mask) == -1)
		return (EXIT_FAILURE);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	default_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	if (sigemptyset(&sa.sa_mask) == -1)
		return (EXIT_FAILURE);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
