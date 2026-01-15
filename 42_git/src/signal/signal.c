/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:59:55 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/15 17:49:15 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>

volatile sig_atomic_t	g_sig;

void	signal_handler(int signum)
{
	g_sig = signum;
}

int	detect_signal(pid_t pid, int signum)
{
	kill(pid, signum);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	return (signum + 128);
}

int	handle_signal(void)
{
	static struct sigaction	sa;

	sa.sa_handler = signal_handler;
	if (sigemptyset(&sa.sa_mask) == -1)
		return (EXIT_FAILURE);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
