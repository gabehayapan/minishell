/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 14:30:07 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/05 16:25:55 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	main(int argc, char **argv, char **envp)
{
	t_token	*tokens;
	t_token	*tmp;
	t_env	*env_lst;
	char	*line;

	(void)argc;
	(void)argv;
	env_lst = init_env_list(envp);
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
	parser(&tokens, env_lst);
	free(line);
	free_token(tokens);
	free(env_lst);
	return (0);
}
