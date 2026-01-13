/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:56:57 by keitotak          #+#    #+#             */
/*   Updated: 2026/01/13 16:37:46 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "parser.h"

int	execute(t_exec *exec_node, t_env *env_lst)
{
	char	**argv;
	char	**envp;
	size_t	size_env_lst;
	int		ret;

	argv = exec_node->exec;
	envp = convert_to_envp(env_lst);
	ret = pipex(&argv[0], envp);
	size_env_lst = count_size_env_lst(env_lst);
	free_strs(envp, size_env_lst);
	return (ret);
}
