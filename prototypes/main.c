/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:31:52 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/10 13:05:02 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/header/libft.h"

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Usage: ./minishell", 2);
		return (EXIT_FAILURE);
	}
	while (1)
	{
		prompt = readline("minishell> ");
		if (prompt == NULL)
			exit(EXIT_FAILURE);
//		execute_prompt(prompt); /* parse prompt and execute command */
		add_history(prompt);
		free(prompt);
	}
	return (EXIT_SUCCESS);
}
