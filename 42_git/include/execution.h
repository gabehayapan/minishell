/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:37:43 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/31 19:05:43 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"
# include "pipe.h"

// execution/execution.c
unsigned char	execute_command(t_exec *exec_node, t_env **env_lst,
					t_exec *top, t_his *his);

#endif
