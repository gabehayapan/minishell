/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:40:19 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/19 12:56:03 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_input(char *input, t_env *env_lst, t_exec **exec_tree,
			long exit_status)
{
	t_token	*tokens;
	int		ret;

	ret = tokenizer(input, &tokens);
	if (ret == FAILURE || ret == NO_COMMAND)
		return (ret);
	*exec_tree = parser(&tokens, env_lst, exit_status);
	free_token(tokens);
	if (*exec_tree == NULL)
		return (FAILURE);
	return (SUCCESS);
}
