/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:40:19 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/14 09:51:50 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_exec	*handle_input(char *input, t_env *env_lst)
{
	t_token	*tokens;
	t_exec	*exec_tree;

	tokens = tokenizer(input);
	if (tokens == NULL)
		return (NULL);
	exec_tree = parser(&tokens, env_lst);
	free_token(tokens);
	if (exec_tree == NULL)
		return (NULL);
	return (exec_tree);
}
