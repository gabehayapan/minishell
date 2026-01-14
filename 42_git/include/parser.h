/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:27:16 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/14 14:24:59 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"
# include "env_var.h"
# include "../libft/header/libft.h"

typedef enum s_rdt_type
{
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND,
}	t_rdt_type;

typedef struct s_size_exec
{
	size_t	inrdt;
	size_t	outrdt;
	size_t	cmd;
}	t_size_exec;

typedef struct s_rdt
{
	char			*rdt;
	t_rdt_type		type;
	struct s_rdt	*next;
}	t_rdt;

typedef struct s_command
{
	char				**command;
	t_rdt				*inrdt;
	t_rdt				*outrdt;
	t_size_exec			size;
	struct s_command	*next;
}	t_command;

typedef struct s_exec
{
	t_tk_type		tk_type;
	struct s_exec	*left;
	struct s_exec	*right;

	t_command		*command;

	char			**exec;
	size_t			size_exec;
	size_t			num_heredoc;
	size_t			num_infile;
	size_t			num_command;
	size_t			num_outfile;
	size_t			is_append;
	int				is_subshell;
}	t_exec;

// handle_input/handle_input.c
t_exec		*handle_input(char *input, t_env *env_lst);

// handle_input/parser/parser.c
t_exec		*parser(t_token **tokens, t_env *env_lst);
char		**new_exec(t_token **tokens, t_exec *node_exec, t_env *env_lst);

// handle_input/parser/parser_utils.c
void		init_node_exec(t_exec *node_exec);
void		free_strs(char **strs, size_t size);
void		free_null_term_strs(char **strs);
void		free_node_exec(t_exec *node_exec);
void		clear_token(t_token **tokens, t_token *target, void (*del)(void *));

// handle_input/parser/counter.c
size_t		get_len_command(t_token *tokens);
size_t		count_array_size(t_token *tokens, t_exec *node_exec);

// handle_input/parser/get_redirect_file.c
int			get_redirect_file(t_token **tokens, char **exec, size_t size);
int			get_infile(t_token *tokens, char **exec);
t_token		*get_token_infile(t_token *tokens);
int			get_outfile(t_token *tokens, char **exec);
t_token		*get_token_outfile(t_token *tokens);

// handle_input/parser/get_command.c
void		get_command(char *exec, t_token *tokens);

// handle_input/parser/expand_specials.c
int			expand_specials(t_token **tokens, t_env *env_lst);

// handle_input/parser/exec_tree.c
t_exec		*set_exec_elem(t_token **tokens, t_exec *top, t_exec *node_exec);
int			new_exec_tree(t_token **tokens, t_exec **top, t_env *env_lst);
t_exec		*set_last_node(t_exec *top, t_exec *node_exec);
t_exec		*set_new_node(t_exec *node_exec, t_exec *ctrl_op_node);
t_exec		*new_ctrl_op_node(t_token *token, t_exec *top);

// handle_input/parser/print_redirection_error.c
void		syntax_error_redirection(void);

// handle_input/parser/add_path.c
int			add_path_to_command(t_token *tokens, t_env *env_lst);

#endif
