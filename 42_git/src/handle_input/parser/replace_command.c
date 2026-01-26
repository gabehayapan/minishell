/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 08:52:30 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/26 09:46:47 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <sys/wait.h>

int	execute_input_command(char **input, t_env **env_lst);

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

int	set_cmd_output(t_token **tokens, t_token **current, int *pipefd)
{
	char	*buf;
	ssize_t	n;

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
	return (SUCCESS);
}

void	get_cmd_output(int *pipefd, t_token *current, t_env *env_lst)
{
	int	ret;

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
		ret = execute_input_command(&((current->next)->next)->word, &env_lst);
		if (ret == FAILURE)
			exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

int	replace_with_cmd_output(t_token **tokens, t_token **current,
			t_env *env_lst)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

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
	waitpid(pid, &status, 0);
	return (set_cmd_output(tokens, current, pipefd));
}
