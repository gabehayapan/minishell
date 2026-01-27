/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 11:33:49 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/08 11:45:03 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
