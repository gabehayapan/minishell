/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:40:19 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/31 17:22:32 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_input(char **input, t_env **env_lst, t_exec **exec_tree,
			t_sub *sub)
{
	t_token	*tokens;
	int		ret;

	tokens = tokenizer(input);
	if (tokens == NULL)
		return (FAILURE);
	ret = parser(&tokens, env_lst, exec_tree, sub);
	free_token(tokens);
	if (ret == FAILURE || ret == NO_COMMAND
		|| ret == FORMAT_ERROR || ret == SIGNALED)
		return (ret);
	return (SUCCESS);
}
