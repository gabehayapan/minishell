/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:16:22 by keitotak          #+#    #+#             */
/*   Updated: 2026/02/05 15:19:10 by hanakamu         ###   ########.fr       */
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

typedef enum s_bool
{
	error = -1,
	success,
	failure
}	t_bool;

typedef struct s_to_free
{
	t_exec	*top;
	t_his	*his;
}	t_to_free;

typedef struct s_pipe
{
	int			proccnt;
	int			*procid;
	int			*pipefd;
	int			stdin_fd;
	int			stdout_fd;
	t_env		**env_lst;
	t_to_free	*to_free;
}	t_pipe;

// nopipe.c
int		nopipe_execute(t_command *command, t_env **env_lst, t_to_free *to_free);

// redirect.c
int		redirect_fd(t_command *command);

// pipe.c
int		pipeline(t_command *command, t_env **env_lst, int count,
			t_to_free *to_free);

// fork.c
int		fork_process(t_pipe *p, t_command *command, int p_nbr);

// exec.c
int		exec_command(t_command *command, t_env **env_lst, t_to_free *to_free);
int		pass_to_builtin(t_command *command, t_env **env_lst,
			t_to_free *to_free);
int		handle_noexist_cmd(char **cmdset);

//wait.c
int		wait_for_children(int *procid, int proc_count);
int		status_code(int status);

//helper.c
void	close_pipes(int	*pipefd, int count);
void	free_pipe(t_pipe *p);
void	cleanup_pipe(t_pipe *p);
void	free_vars(t_env **env_lst, t_to_free *to_free);

#endif
