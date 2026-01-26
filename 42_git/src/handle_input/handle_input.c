/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:40:19 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/26 09:48:04 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	handle_input(char **input, t_env **env_lst, t_exec **exec_tree,
			long exit_status)
{
	t_token	*tokens;
	int		ret;

	ret = tokenizer(input, &tokens);
	if (ret == FAILURE)
		return (FAILURE);
	ret = parser(&tokens, env_lst, exec_tree, exit_status);
	free_token(tokens);
	if (ret == FAILURE || ret == NO_COMMAND || ret == FORMAT_ERROR)
		return (ret);
	return (SUCCESS);
}
