/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:27:16 by hanakamu          #+#    #+#             */
/*   Updated: 2025/12/29 14:27:31 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../tokenize/tokenize.h"
# include "../../libft/header/libft.h"

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

int		get_redirect_file(t_token **tokens, char **exec, size_t size);
void	init_parser(t_parser *parser);
void	clear_token(t_token **tokens, t_token *target, void (*del)(void *));
size_t	count_array_size(t_token *tokens, t_parser *parser);
int		get_infile(t_token *tokens, char **exec);
t_token	*get_token_infile(t_token *tokens);
int		get_outfile(t_token *tokens, char **exec);
t_token	*get_token_outfile(t_token *tokens);
void	syntax_error_redirection(void);

#endif
