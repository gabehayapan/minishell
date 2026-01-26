/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:59:55 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/26 10:56:18 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include "ftprintf.h"

volatile sig_atomic_t	g_sig;

void	signal_handler(int signum)
{
	g_sig = signum;
}

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

int	detect_signal(pid_t pid, int signum)
{
	int	wstatus;

	kill(pid, signum);
	write(1, "\n", 1);
	if (waitpid(pid, &wstatus, 0) == -1)
	{
		perror("waitpid");
		return (EXIT_FAILURE);
	}
	return (WTERMSIG(wstatus) + 128);
}

int	handle_signal(void)
{
	struct sigaction	sa;

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
