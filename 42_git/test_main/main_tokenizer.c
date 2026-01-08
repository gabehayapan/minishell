/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tokenizer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 14:30:07 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/29 15:10:23 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	main(void)
{
	t_token	*tokens;
	t_token	*tmp;
	char	*line;

	line = readline("test> ");
	printf("line:%s\n", line);
	tokens = tokenizer(line);
	if (tokens == NULL)
	{
		printf("error at tokenizer\n");
		return (1);
	}
	tmp = tokens;
	while (tmp != NULL)
	{
		printf("word:%s, token type:%d\n", tmp->word, tmp->tk_type);
		tmp = tmp->next;
	}
	free(line);
	free(tokens);
	return (0);
}
