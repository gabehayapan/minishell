/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:47:12 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/04 13:16:50 by hanakamu         ###   ########.fr       */
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

// init_vars.c
void			init_input_and_sub(char **input, t_sub *sub);
void			init_to_free(t_to_free *to_free, t_exec *top, t_his *his);

// exit_status.c
unsigned char	set_exit_status(int ret);

// signal/signal.c
int				readline_signal(void);
int				ignore_signal(void);

#endif
