/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 09:57:15 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/04 13:34:07 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	init_tokens(t_token **tokens, t_env **env_lst, t_sub *sub)
{
	int	ret;

	while (*tokens != NULL && (*tokens)->tk_type == SPACES)
		clear_token(tokens, *tokens, free);
	if (*tokens == NULL)
		return (ONLY_SPACES);
	ret = check_format_error(tokens);
	if (ret == FORMAT_ERROR)
		return (FORMAT_ERROR);
	ret = expand_specials(tokens, *env_lst, sub);
	if (ret == FAILURE || ret < 0)
		return (ret);
	ret = check_history(tokens, sub->his);
	if (ret == FAILURE || ret == NO_EVENT)
		return (ret);
	ret = check_assignment(tokens, env_lst);
	if (ret == FAILURE)
		return (FAILURE);
	ret = rm_space_and_join_tokens(tokens);
	if (ret == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
