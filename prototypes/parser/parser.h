/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:27:16 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/31 11:31:31 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../tokenize/tokenize.h"
# include "../../libft/header/libft.h"
# include "../env_var/env_var.h"

typedef struct s_exec
{
	t_tk_type		tk_type;
	struct s_exec	*left;
	struct s_exec	*right;
	char			**exec;
}	t_exec;

typedef struct s_parser
{
	size_t	num_infile;
	size_t	num_outfile;
	size_t	is_heredoc;
	size_t	num_command;
	t_exec	*exec_tree;
}	t_parser;

#endif
