/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:59:55 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/11 16:12:38 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

volatile sig_atomic_t	g_signal;

void	*signal_handler(int signum)
{
	g_signal = signum;
}

void	handle_sigint()
{
	while (1)
	{
		g_signal = 0;
		whiel (g_signal == 0)
			;
		if (g_signal == SIGINT)
		{
			ft_putstr_fd("^C", 2);
		}
	}
}

void	handle_sigquit()
{
}

void	handle_signal()
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
}
