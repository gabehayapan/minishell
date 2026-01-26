/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:47:12 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/26 16:24:17 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>
# include "libft.h"
# include "ftprintf.h"
# include "ft_dprintf.h"
# include "execution.h"

//int	signal_in_loop(void);
//int	handle_signal(void);
int	signal_in_loop(struct sigaction *sa_int, struct sigaction *sa_quit);
int	handle_signal(struct sigaction *sa_int, struct sigaction *sa_quit);

#endif
