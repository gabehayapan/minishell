/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:27:16 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/09 16:53:54 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"
# include "env_var.h"
# include "../libft/header/libft.h"

typedef struct s_exec
{
	t_tk_type		tk_type;
	struct s_exec	*left;
	struct s_exec	*right;
	char			**exec;
	size_t			size_exec;
	size_t			is_heredoc;
	size_t			num_infile;
	size_t			num_command;
	size_t			num_outfile;
}	t_exec;

t_exec		*handle_input(char *input, t_env *env_lst);
t_exec		*parser(t_token **tokens, t_env *env_lst);
int			get_redirect_file(t_token **tokens, char **exec, size_t size);
void		init_node_exec(t_exec *node_exec);
void		free_strs(char **strs, size_t size);
void		free_node_exec(t_exec *node_exec);
void		clear_token(t_token **tokens, t_token *target, void (*del)(void *));
size_t		count_array_size(t_token *tokens, t_exec *node_exec);
int			get_infile(t_token *tokens, char **exec);
t_token		*get_token_infile(t_token *tokens);
int			get_outfile(t_token *tokens, char **exec);
t_token		*get_token_outfile(t_token *tokens);
int			get_execution(char **exec, size_t size, t_token **tokens);
void		get_command(char *exec, t_token *tokens);
int			expand_specials(t_token **tokens, t_env *env_lst);
t_exec		*set_exec_elem(t_token **tokens, t_exec *top, t_exec *node_exec);
char		**new_exec(t_token **tokens, t_exec *node_exec);
int			new_exec_tree(t_token **tokens, t_exec **top);
t_exec		*set_last_node(t_exec *top, t_exec *node_exec);
t_exec		*set_new_node(t_exec *node_exec, t_exec *ctrl_op_node);
t_exec		*new_ctrl_op_node(t_token *token, t_exec *top);
void		syntax_error_redirection(void);

#endif
