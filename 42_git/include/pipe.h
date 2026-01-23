/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:16:22 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/23 19:26:28 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "libft.h"
# include "ftprintf.h"
# include "parser.h"

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>

# define STDIN 0
# define STDOUT 1

extern volatile sig_atomic_t	g_sig;

typedef enum s_bool
{
	error = -1,
	success,
	failure
}	t_bool;

typedef struct s_pipe
{
	int	*procid;
	int	*pipefd;
}	t_pipe;

// main.c
int		execute(t_command *command, t_env *env_lst, t_exec *top);
int		redirect_fd(t_command *command);

// pipe.c
int		pipeline(t_command *command, t_env *env_lst, int count, t_exec *top);
void	close_pipes(int	*pipefd, int count);
void	free_pipe(t_pipe *p);

// fork.c
int		fork_process(t_pipe *p, t_command *command, t_env *env_lst, int p_nbr, t_exec *top);

// exec.c
int		exec_command(t_command *command, t_env *env_lst, t_exec *top);
int		pass_to_builtin(t_command *command, t_env *env_lst, t_exec *top);
char	*free_arrs_ret_s(char **arrs, char *s);

//wait.c
int		wait_for_children(t_pipe *p, int proc_count);
int		status_code(int status);

//helper.c
bool	include_quote(char *str);
int		handle_noexist_cmd(char **cmdset);

#endif
