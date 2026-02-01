/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 09:57:15 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/01 18:04:02 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	init_tokens(t_token **tokens, t_env **env_lst, t_sub *sub)
{
	int	is_success;

	while (*tokens != NULL && (*tokens)->tk_type == SPACES)
		clear_token(tokens, *tokens, free);
	if (*tokens == NULL)
		return (NO_COMMAND);
	is_success = check_format_error(tokens);
	if (is_success == FORMAT_ERROR)
		return (FORMAT_ERROR);
	is_success = expand_specials(tokens, *env_lst, sub);
	if (is_success == FAILURE || is_success == SIGNALED)
		return (is_success);
	is_success = check_assignment(tokens, env_lst);
	if (is_success == FAILURE)
		return (FAILURE);
	is_success = check_history(tokens, sub->his);
	if (is_success == FAILURE || is_success == NO_EVENT)
		return (is_success);
	is_success = rm_space_and_join_tokens(tokens);
	if (is_success == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
