/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:40:19 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/19 10:18:11 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_input(char *input, t_env *env_lst, t_exec **exec_tree)
{
	t_token	*tokens;
	int		ret;

	ret = tokenizer(input, &tokens);
	if (ret == FAILURE || ret == NO_COMMAND)
		return (ret);
	*exec_tree = parser(&tokens, env_lst);
	free_token(tokens);
	if (*exec_tree == NULL)
		return (FAILURE);
	return (SUCCESS);
}
