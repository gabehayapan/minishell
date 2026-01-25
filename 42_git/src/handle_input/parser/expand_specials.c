/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specials.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:00:14 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/25 09:18:41 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	expand_dollar(t_token **tokens, t_token **current, t_env *env_lst,
			long exit_status)
{
	t_token	*next;
	char	*env_var;

	next = (*current)->next;
	if (next->tk_type == O_PAREN)
		return (replace_with_cmd_output(tokens, current, env_lst));
	env_var = env_value(env_lst, next->word);
	free((*current)->word);
	if (env_var != NULL)
		(*current)->word = rm_extra_space(env_var);
	else if (next->word != NULL && ft_strncmp(next->word, "?", 1) == 0)
		(*current)->word = handle_exit_status(&next, exit_status);
	else
		(*current)->word = ft_strdup("");
	clear_token(tokens, next, free);
	if ((*current)->word == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	expand_tilde(t_token *current, t_env *env_lst)
{
	char	*path_home;

	if (current->prev == NULL || (current->prev)->tk_type == SPACES)
	{
		path_home = env_value(env_lst, "HOME");
		free(current->word);
		if (path_home == NULL)
			current->word = ft_strdup("");
		else
			current->word = ft_strdup(path_home);
		if (current->word == NULL)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	expand_quote(t_token **tokens, t_token **current, t_env *env_lst,
			long exit_status)
{
	t_tk_type	tk_qte;
	t_token		*next;

	tk_qte = (*current)->tk_type;
	next = (*current)->next;
	clear_token(tokens, *current, free);
	while (next != NULL && next->tk_type != tk_qte)
	{
		if (handle_dbl_quoted_dollar(tokens, next, env_lst, exit_status)
			== FAILURE)
			return (FAILURE);
		next = next->next;
	}
	if (next != NULL)
		*current = next->next;
	else
		*current = NULL;
	clear_token(tokens, next, free);
	return (SUCCESS);
}

int	expand_wildcard(t_token **tokens, t_token *current)
{
	char	*dirname;
	char	*disname;
	int		is_success;

	dirname = get_target_dir(&current, &disname);
	if (dirname == NULL)
		return (FAILURE);
	errno = 0;
	is_success = get_matching_files(tokens, current, dirname, disname);
	if (is_success == FAILURE || errno != 0)
	{
		free(dirname);
		free(disname);
		if (errno != 0)
			perror("readdir");
		return (FAILURE);
	}
	free(dirname);
	free(disname);
	return (SUCCESS);
}

int	expand_specials(t_token **tokens, t_env *env_lst, long exit_status)
{
	t_token	*current;
	int		is_success;

	current = *tokens;
	is_success = SUCCESS;
	while (current != NULL)
	{
		if (current->tk_type == SGL_QTE || current->tk_type == DBL_QTE)
		{
			is_success = expand_quote(tokens, &current, env_lst, exit_status);
			if (is_success == FAILURE)
				return (FAILURE);
			continue ;
		}
		is_success = handle_others(tokens, &current, env_lst, exit_status);
		if (is_success == FAILURE)
			return (FAILURE);
		if (current == NULL)
			break ;
		current = current->next;
	}
	return (SUCCESS);
}
