/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:12:09 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/04 19:32:57 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_if_exist(char *new_shell, t_env *env_lst, t_env **target)
{
	char	**new_strs;

	new_strs = ft_split(new_shell, '=');
	if (new_strs == NULL)
		return (FAILURE);
	*target = env_find(env_lst, *new_strs);
	if (*target == NULL)
		return (free_null_term_strs(new_strs), NOT_FOUND);
	return (SUCCESS);
}

static int	update_old_shell_var(char *new_shell, t_env *target)
{
	while (*new_shell != '\0' && *new_shell != '=')
		new_shell++;
	if (*new_shell == '\0')
		target->value = ft_strdup("");
	else
		target->value = ft_strdup(new_shell + 1);
	if (target->value == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	add_shell_var(char *new_shell, t_env **env_lst)
{
	t_env	*new_shell_ptr;
	t_env	*last_env;
	int		is_success;

	new_shell_ptr = (t_env *)malloc(sizeof(t_env));
	if (new_shell_ptr == NULL)
		return (FAILURE);
	is_success = new_env_var(new_shell_ptr, new_shell);
	if (is_success == FAILURE)
	{
		free(new_shell_ptr);
		return (FAILURE);
	}
	new_shell_ptr->is_env = SHELL_VAR;
	last_env = get_last_env(*env_lst);
	if (last_env == NULL)
		*env_lst = new_shell_ptr;
	else
		last_env->next = new_shell_ptr;
	return (SUCCESS);
}

static int	join_remaining_word(t_token **tokens, t_env *target, t_env *env_lst)
{
	t_env	*last;

	if (target == NULL)
		last = get_last_env(env_lst);
	else
		last = target;
	while (*tokens != NULL && (*tokens)->tk_type != SPACES)
	{
		last->value = join_word_no_space(last->value, (*tokens)->word);
		if (last->value == NULL)
			return (FAILURE);
		clear_token(tokens, *tokens, free);
	}
	return (SUCCESS);
}

int	check_assignment(t_token **tokens, t_env **env_lst)
{
	int		is_success;
	t_env	*target;

	while (*tokens != NULL && (*tokens)->tk_type == SPACES)
		clear_token(tokens, *tokens, free);
	if (*tokens == NULL || (*tokens)->tk_type != WORD
		|| ft_isalpha(*((*tokens)->word)) == 0
		|| ft_strchr((*tokens)->word, '=') == NULL)
		return (SUCCESS);
	is_success = check_if_exist((*tokens)->word, *env_lst, &target);
	if (is_success == FAILURE)
		return (FAILURE);
	if (is_success == SUCCESS)
		is_success = update_old_shell_var((*tokens)->word, target);
	else
		is_success = add_shell_var((*tokens)->word, env_lst);
	if (is_success == FAILURE)
		return (FAILURE);
	clear_token(tokens, *tokens, free);
	if (join_remaining_word(tokens, target, *env_lst) == FAILURE)
		return (SUCCESS);
	return (check_assignment(tokens, env_lst));
}
