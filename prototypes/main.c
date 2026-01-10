/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:31:52 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/08 11:48:21 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/header/libft.h"

int	read_and_execute(t_env *env_lst)
{
	char	*input;
	t_exec	*exec_tree;
	int		is_success;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			exit(EXIT_FAILURE);
		exec_tree = handle_input(input, env_lst);
		if (exec_tree == NULL)
			return (FAILURE);
		is_success = check_execution_success(exec_tree, env_lst);
		if (is_success == FAILURE)
			return (FAILURE);
		add_history(input);
		free(input);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_lst
	int		is_success;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Usage: ./minishell", 2);
		return (EXIT_FAILURE);
	}
	env_lst = init_env_list(envp);
	if (env_lst == NULL)
		return (EXIT_FAILURE);
	is_success = read_and_execute(env_lst);
	if (is_success == FAILURE)
	{
		free_env_lst(env_Lst);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
