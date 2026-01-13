/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:59:55 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/13 17:13:42 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

volatile sig_atomic_t	g_signal;

static void	*signal_handler(int signum)
{
	g_signal = signum;
}

void	handle_sigint()
{
}

void	handle_sigquit()
{
}

int	handle_signal()
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	if (sigemptyset(&sa.sa_mask) == -1)
		return (FAILURE);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (FAILURE);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (FAILURE);
}
