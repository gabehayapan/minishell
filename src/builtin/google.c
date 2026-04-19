/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   google.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 09:20:42 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/04 10:46:03 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env_var.h"
#include <sys/wait.h>

static void	free_google(char **cmd, t_env *env_lst, t_to_free *to_free)
{
	free(cmd);
	free_all(env_lst, to_free);
	exit(EXIT_FAILURE);
}

static char	**init_google_command(void)
{
	char	**cmd;

	cmd = (char **)malloc(sizeof(char *) * 3);
	if (cmd == NULL)
		return (NULL);
	*cmd = "/bin/xdg-open";
	*(cmd + 1) = ft_strdup("https://www.google.com/search?q=");
	if (*(cmd + 1) == NULL)
	{
		free(cmd);
		return (NULL);
	}
	*(cmd + 2) = NULL;
	return (cmd);
}

static int	append_search_word(char **strs, char **cmd)
{
	while (*strs != NULL && *(strs + 1) != NULL)
	{
		*(cmd + 1) = join_word_no_space(*(cmd + 1), *strs);
		if (*(cmd + 1) == NULL)
			return (FAILURE);
		*(cmd + 1) = join_word_no_space(*(cmd + 1), "+");
		if (*(cmd + 1) == NULL)
			return (FAILURE);
		strs++;
	}
	if (*strs != NULL)
	{
		*(cmd + 1) = join_word_no_space(*(cmd + 1), *strs);
		if (*(cmd + 1) == NULL)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	google_search(char **cmd, t_env *env_lst)
{
	char	**envp;
	int		status;
	pid_t	pid;

	envp = convert_to_envp(env_lst);
	if (envp == NULL)
		return (FAILURE);
	pid = fork();
	if (pid < 0)
	{
		free_null_term_strs(envp);
		return (FAILURE);
	}
	else if (pid == 0)
	{
		execve(*cmd, cmd, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	free_null_term_strs(envp);
	if (wait(&status) == -1)
		return (FAILURE);
	return (status);
}

int	google(char **strs, t_env *env_lst, t_to_free *to_free)
{
	char	**cmd;
	int		is_success;

	cmd = init_google_command();
	if (cmd == NULL)
		free_google(cmd, env_lst, to_free);
	is_success = append_search_word(strs + 1, cmd);
	if (is_success == FAILURE)
		free_google(cmd, env_lst, to_free);
	is_success = google_search(cmd, env_lst);
	if (is_success == FAILURE)
	{
		free(*(cmd + 1));
		free_google(cmd, env_lst, to_free);
	}
	return (SUCCESS);
}
