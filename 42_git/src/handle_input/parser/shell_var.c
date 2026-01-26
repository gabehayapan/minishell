/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:12:09 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/26 10:17:51 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

int	check_assignment(t_token **tokens, t_env **env_lst)
{
	int	is_success;

	if (*tokens != NULL
		&& ((*tokens)->tk_type == AND || (*tokens)->tk_type == OR
			|| (*tokens)->tk_type == PIPE || (*tokens)->tk_type == SEMI))
	{
		ft_dprintf(2, "minishell: syntax error near unexpected token `%s'\n",
			(*tokens)->word);
		return (FORMAT_ERROR);
	}
	while (*tokens != NULL && (*tokens)->tk_type == SPACES)
		clear_token(tokens, *tokens, free);
	if (*tokens == NULL || (*tokens)->tk_type != WORD
		|| ft_isalpha(*((*tokens)->word)) == 0
		|| ft_strchr((*tokens)->word, '=') == NULL)
		return (SUCCESS);
	is_success = add_shell_var((*tokens)->word, env_lst);
	if (is_success == FAILURE)
		return (FAILURE);
	clear_token(tokens, *tokens, free);
	return (check_assignment(tokens, env_lst));
}
