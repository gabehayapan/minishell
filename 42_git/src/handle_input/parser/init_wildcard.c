/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:22:35 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/20 11:27:29 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	new_echo_token(t_token **tokens)
{
	t_token	*token_echo;

	token_echo = new_token_str("echo", NULL, WORD);
	if (token_echo == NULL)
		return (FAILURE);
	token_echo->next = *tokens;
	(*tokens)->prev = token_echo;
	*tokens = token_echo;
	return (SUCCESS);
}

char	*get_target_dir(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		return (NULL);
	}
	return (cwd);
}
