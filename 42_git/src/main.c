/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:31:52 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/08 19:03:37 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_minishell(void)
{
	char	*bp;
	int		result;
	int		cols;

	bp = (char *)malloc(2048);
	if (bp == NULL)
		return (FAILURE);
	result = tgetent(bp, "xterm");
	if (result == 1)
	{
		cols = tgetnum("co");
		if (cols >= 40)
		{
			ft_printf(\
			"           _       _     _          _ _ \n"\
			"\033[36m _ __ ___ (_)_ __ (_)___| |__   ___| | |\033[0m\n"\
			"| '_ ` _ \\| | '_ \\| / __| '_ \\ / _ \\ | |\n"\
			"\033[36m| | | | | | | | | | \\__ \\ | | |  __/ | |\033[0m\n"\
			"|_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|\n");
		}
	}
	free(bp);
	return (SUCCESS);
}

int	read_and_execute(t_env *env_lst, char **envp)
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
		is_success = check_execution_success(exec_tree, env_lst, envp);
		if (is_success == FAILURE)
			return (FAILURE);
		add_history(input);
		free(input);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_lst;
	int		is_success;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Usage: ./minishell", 2);
		return (EXIT_FAILURE);
	}
	if (display_minishell() == FAILURE)
		return (EXIT_FAILURE);
	env_lst = init_env_list(envp);
	if (env_lst == NULL)
		return (EXIT_FAILURE);
	is_success = read_and_execute(env_lst, envp);
	if (is_success == FAILURE)
	{
		free_env_lst(env_lst);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
