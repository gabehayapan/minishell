/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:31:52 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/31 17:25:22 by hanakamu         ###   ########.fr       */
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

int	execute_input_command(char **input, t_env **env_lst, int is_child)
{
	t_exec			*exec_tree;
	int				ret;
	static t_sub	sub;

	ret = handle_input(input, env_lst, &exec_tree, &sub);
	if (ret == FAILURE)
		return (FAILURE);
	if (ret == SUCCESS)
	{
		sub.exit_status = execute_command(exec_tree, env_lst, exec_tree);
		free_node_exec(exec_tree);
		if (is_child == 1)
			return (sub.exit_status);
	}
	add_history(*input);
	return (SUCCESS);
}

int	read_and_execute(t_env **env_lst)
{
	char				*input;
	int					is_success;

	input = NULL;
	while (1)
	{
		if (readline_signal() == FAILURE)
			return (FAILURE);
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		if (*input != '\0')
		{
			if (ignore_signal() == FAILURE)
				return (FAILURE);
			is_success = execute_input_command(&input, env_lst, 0);
			free(input);
			if (is_success == FAILURE)
				return (FAILURE);
		}
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
		ft_putstr_fd("Usage: ./minishell\n", 2);
		return (EXIT_FAILURE);
	}
	if (display_minishell() == FAILURE)
		return (EXIT_FAILURE);
	env_lst = init_env_list(envp);
	if (env_lst == NULL)
		return (EXIT_FAILURE);
	is_success = read_and_execute(&env_lst);
	free_env_lst(env_lst);
	if (is_success == FAILURE)
		return (EXIT_FAILURE);
	ft_dprintf(2, "exit\n");
	return (EXIT_SUCCESS);
}
