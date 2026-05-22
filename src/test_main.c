/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 15:36:54 by hanakamu          #+#    #+#             */
/*   Updated: 2026/05/20 20:56:33 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef TEST

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
	env_lst = init_env_list(envp);
	if (env_lst == NULL)
		return (EXIT_FAILURE);
	is_success = read_and_execute(&env_lst);
	free_env_lst(env_lst);
	if (is_success == FAILURE)
		return (EXIT_FAILURE);
	if (isatty(STDIN_FILENO))
		ft_dprintf(2, "exit\n");
	return (EXIT_SUCCESS);
}
#endif
