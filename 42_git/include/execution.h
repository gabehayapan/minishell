/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:37:43 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/24 00:45:32 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"
# include "pipe.h"

// execution/execution.c
long	execute_command(t_exec *exec_node, t_env *env_lst, t_exec *top);
long	check_execution_success(t_exec *exec_tree, t_env *env_lst);

#endif
