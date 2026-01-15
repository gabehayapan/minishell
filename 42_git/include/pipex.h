/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:58:59 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/15 12:13:36 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

typedef struct s_pipex
{
	char	*infile;
	char	**cmd1;
	char	**cmd2;
	char	*outfile;
	int		i_fd;
	int		o_fd;
	int		p_fd[2];
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

// main.c
int		execute(t_command *command, t_env *env_lst);

// pipex.c
int		pipex(t_command *command, char **ev);

// process.c
int		fork_process(t_pipex *p, char **ev, int p_nbr);

// exec.c
int		exec_command(char **cmd, char **ev);
char	*free_arrs_ret_s(char **arrs, char *s);

//wait.c
int		wait_for_children(t_pipex *p);
int		status_code(int status);

//helper.c
bool	include_quote(char *str);
int		handle_noexist_cmd(char **cmdset);

#endif
