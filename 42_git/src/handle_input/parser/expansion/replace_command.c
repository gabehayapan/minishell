/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 08:52:30 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/04 13:11:07 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "get_next_line.h"
#include <sys/wait.h>

int	default_signal(void);
int	execute_input_command(char **input, t_env **env_lst, t_sub *sub,
		int is_child);

int	new_cmd_output_token(t_token **current, int pipefd)
{
	char	*line;
	char	*new_str;
	t_token	*new_token;
	t_token	*next;

	line = get_next_line(pipefd);
	next = (*current)->next;
	while (line != NULL)
	{
		new_str = ft_strtrim(line, " \n\t\r\v\f");
		free(line);
		if (new_str == NULL)
			return (FAILURE);
		new_token = new_token_str(new_str, *current, WILDCARD);
		free(new_str);
		if (new_token == NULL)
			return (FAILURE);
		new_token->next = next;
		if (next != NULL)
			next->prev = new_token;
		*current = new_token;
		line = get_next_line(pipefd);
	}
	return (SUCCESS);
}

int	set_cmd_output(t_token **tokens, t_token **current, int *pipefd, int status)
{
	t_token	*tmp;
	t_token	*next;

	close(pipefd[1]);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
	{
		tmp = *current;
		new_cmd_output_token(current, pipefd[0]);
		clear_token(tokens, tmp, free);
		close(pipefd[0]);
		*current = (*current)->next;
		free_cmd_replace(tokens, current);
	}
	else
	{
		next = (*current)->next;
		clear_token(tokens, *current, free);
		*current = next;
		free_cmd_replace(tokens, current);
		close(pipefd[0]);
	}
	return (SUCCESS);
}

void	get_cmd_output(int *pipefd, t_token *current, t_env *env_lst,
			t_sub *sub)
{
	int	ret;

	if (default_signal() == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	close(pipefd[0]);
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
				sub, 1);
		exit(ret);
	}
	exit(EXIT_FAILURE);
}

int	wait_for_child(int *pipefd)
{
	int	status;

	if (wait(&status) == -1)
	{
		perror("wait");
		close(pipefd[0]);
		close(pipefd[1]);
		return (FAILURE);
	}
	if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		close(pipefd[0]);
		close(pipefd[1]);
		return (-WTERMSIG(status));
	}
	return (status);
}

int	replace_with_cmd_output(t_token **tokens, t_token **current,
			t_env *env_lst, t_sub *sub)
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
		get_cmd_output(pipefd, *current, env_lst, sub);
	ret = wait_for_child(pipefd);
	if (ret == FAILURE || ret < 0)
		return (ret);
	return (set_cmd_output(tokens, current, pipefd, ret));
}
