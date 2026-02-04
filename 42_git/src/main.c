/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 20:31:52 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/04 13:18:23 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static int	display_minishell(void)
//{
//	char		*bp;
//	const char	*term;
//	int			result;
//	int			cols;
//
//	bp = (char *)malloc(sizeof(*bp));
//	if (bp == NULL)
//		return (FAILURE);
//	term = getenv("TERM");
//	result = tgetent(bp, term);
//	if (result == 1)
//	{
//		cols = tgetnum("co");
//		if (cols >= 40)
//		{
//			ft_printf(\
//			"           _       _     _          _ _ \n"\
//			"\033[36m _ __ ___ (_)_ __ (_)___| |__   ___| | |\033[0m\n"\
//			"| '_ ` _ \\| | '_ \\| / __| '_ \\ / _ \\ | |\n"\
//			"\033[36m| | | | | | | | | | \\__ \\ | | |  __/ | |\033[0m\n"\
//			"|_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|\n");
//		}
//	}
//	free(bp);
//	return (SUCCESS);
//}

static int	new_history(t_his **his, char *input)
{
	t_his	*new_his;

	new_his = (t_his *)malloc(sizeof(t_his));
	if (new_his == NULL)
		return (FAILURE);
	if (*his == NULL)
		new_his->id = 1;
	else
		new_his->id = (*his)->id + 1;
	new_his->line = ft_strdup(input);
	if (new_his->line == NULL)
	{
		free(new_his);
		return (FAILURE);
	}
	new_his->prev = NULL;
	new_his->next = *his;
	if (*his != NULL)
		(*his)->prev = new_his;
	*his = new_his;
	return (SUCCESS);
}

int	execute_input_command(char **input, t_env **env_lst, t_sub *sub,
			int is_child)
{
	t_exec		*exec_tree;
	t_to_free	to_free;
	int			ret;

	ret = handle_input(input, env_lst, &exec_tree, sub);
	if (ret == FAILURE)
		return (FAILURE);
	if (is_child == 0)
	{
		if (new_history(&sub->his, *input) == FAILURE)
			return (FAILURE);
	}
	if (ret == SUCCESS)
	{
		init_to_free(&to_free, exec_tree, sub->his);
		sub->exit_status = execute_command(exec_tree, env_lst, &to_free);
		free_node_exec(exec_tree);
	}
	else
		sub->exit_status = set_exit_status(ret);
	if (is_child == 1)
		return (sub->exit_status);
	add_history(*input);
	return (SUCCESS);
}

static int	read_and_execute(t_env **env_lst)
{
	char	*input;
	int		is_success;
	t_sub	sub;

	init_input_and_sub(&input, &sub);
	while (1)
	{
		if (readline_signal() == FAILURE)
			return (free_his(sub.his), FAILURE);
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		if (*input != '\0')
		{
			if (ignore_signal() == FAILURE)
				return (free_his(sub.his), FAILURE);
			is_success = execute_input_command(&input, env_lst, &sub, 0);
			free(input);
			if (is_success == FAILURE)
				return (free_his(sub.his), FAILURE);
		}
	}
	return (free_his(sub.his), SUCCESS);
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
//	if (display_minishell() == FAILURE)
//		return (EXIT_FAILURE);
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
