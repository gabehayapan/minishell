/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 08:52:30 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/28 14:58:20 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <sys/wait.h>

int	default_signal(void);
int	execute_input_command(char **input, t_env **env_lst, int is_child);

void	free_cmd_replace(t_token **tokens, t_token **current)
{
	t_token	*next;

	next = (*current)->next;
	clear_token(tokens, *current, free);
	*current = next;
	next = (*current)->next;
	clear_token(tokens, *current, free);
	*current = next;
	next = (*current)->next;
	clear_token(tokens, *current, free);
	*current = next;
}

int	set_cmd_output(t_token **tokens, t_token **current, int *pipefd, int status)
{
	char	*buf;
	ssize_t	n;
	t_token	*next;

	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		buf = (char *)malloc(sizeof(char) * 8192);
		if (buf == NULL)
			return (FAILURE);
		n = read(pipefd[0], buf, 8192);
		buf[n - 1] = '\0';
		close(pipefd[0]);
		free((*current)->word);
		(*current)->word = buf;
		*current = (*current)->next;
		free_cmd_replace(tokens, current);
	}
	else
	{
		next = (*current)->next;
		clear_token(tokens, *current, free);
		*current = next;
		free_cmd_replace(tokens, current);
	}
	return (SUCCESS);
}

void	get_cmd_output(int *pipefd, t_token *current, t_env *env_lst)
{
	int	ret;

	if (default_signal() == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	close(STDOUT_FILENO);
	ret = dup2(pipefd[1], STDOUT_FILENO);
	if (ret == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	if ((current->next)->next != NULL)
	{
		ret = execute_input_command(&((current->next)->next)->word, &env_lst,
				1);
		exit(ret);
	}
	exit(EXIT_FAILURE);
}

int	wait_for_child(void)
{
	int	status;

	if (wait(&status) == -1)
	{
		perror("wait");
		return (FAILURE);
	}
	if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		return (SIGNALED);
	}
	return (status);
}

int	replace_with_cmd_output(t_token **tokens, t_token **current,
			t_env *env_lst)
{
	int		pipefd[2];
	pid_t	pid;
	int		ret;

	if (((*current)->next)->next != NULL
		&& (((*current)->next)->next)->tk_type == C_PAREN)
	{
		free_cmd_replace(tokens, current);
		return (SUCCESS);
	}
	pipe(pipefd);
	pid = fork();
	if (pid < -1)
	{
		perror("fork");
		return (FAILURE);
	}
	else if (pid == 0)
		get_cmd_output(pipefd, *current, env_lst);
	ret = wait_for_child();
	if (ret == FAILURE || ret == SIGNALED)
		return (ret);
	return (set_cmd_output(tokens, current, pipefd, ret));
}
