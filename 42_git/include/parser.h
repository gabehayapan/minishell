/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:27:16 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/19 16:00:40 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "tokenizer.h"
# include "env_var.h"
# include "../libft/header/libft.h"
# include "../libft/header/ftprintf.h"

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
	int					is_subshell;
	struct s_command	*next;
}	t_command;

typedef struct s_exec
{
	t_tk_type		tk_type;
	struct s_exec	*left;
	struct s_exec	*right;
	t_command		*command;
}	t_exec;

// handle_input/handle_input.c
int			handle_input(char *input, t_env *env_lst, t_exec **exec_tree,
				long exit_status);

// handle_input/parser/parser.c
int			parser(t_token **tokens, t_env *env_lst, t_exec **exec_tree,
				long exit_status);
char		**new_exec(t_token **tokens, t_exec *node_exec, t_env *env_lst);
void		free_command(t_command *command);

// handle_input/parser/parser_utils.c
void		get_remaining_tokens(t_token **tokens);
void		add_new_command(t_command **head, t_command *new_command,
				t_command **last);
void		remove_tk_spaces(t_token **tokens);
int			join_command(t_token **tokens, t_token *current, char **command,
				t_token **next);

// handle_input/parser/init.c
void		init_node_exec(t_exec *node_exec);
void		init_command(t_command *command);

// handle_input/parser/free.c
void		free_strs(char **strs, size_t size);
void		free_null_term_strs(char **strs);
void		free_command(t_command *command);
void		free_node_exec(t_exec *node_exec);
void		clear_token(t_token **tokens, t_token *target, void (*del)(void *));

// handle_input/parser/counter.c
size_t		get_len_command(t_token *tokens);
t_size_exec	count_size_exec(t_token **tokens);
size_t		get_size_command(t_token *tokens);

// handle_input/parser/get_redirect_file.c
int			get_in_out_rdt(t_token **tokens, t_command *command);

// handle_input/parser/get_redirect_file_utils.c
void		free_rdt(t_rdt *rdt);
t_rdt_type	get_rdt_type(t_token *token);
void		add_last(t_rdt **head, t_rdt *new_rdt);
void		no_rdt_file(t_token *token);

// handle_input/parser/get_command.c
void		get_command(char *exec, t_token *tokens);

// handle_input/parser/expand_specials.c
int			expand_specials(t_token **tokens, t_env *env_lst, long exit_status);
int			expand_quoted_dollar(t_token **tokens, t_token *current,
				t_env *env_lst, long exit_status);

// handle_input/parser/expand_specials_utils.c
char		*rm_extra_space(char *str);
int			expand_quoted_dollar(t_token **tokens, t_token *current,
				t_env *env_lst, long exit_status);
int			handle_dbl_quoted_dollar(t_token **tokens, t_token *current,
				t_env *env_lst, long exit_status);

// handle_input/parser/expand_wildcard.c
char		*get_target_dir(void);
int			get_dir_ent(t_token *current, char *cwd);

// handle_input/parser/handle_exit_status.c
char		*handle_exit_status(t_token **next, long exit_status);

// handle_input/parser/join_word.c
char		*join_word_with_space(char *str, char *word, size_t *len_str);
char		*join_word_no_space(char *str, char *word);

// handle_input/parser/exec_tree.c
t_exec		*set_exec_elem(t_token **tokens, t_exec *top, t_exec *node_exec);
int			new_exec_tree(t_token **tokens, t_exec **top, t_env *env_lst);
t_exec		*set_last_node(t_exec *top, t_exec *node_exec);
t_exec		*set_new_node(t_exec *top, t_exec *node_exec, t_exec *ctrl_op_node);
t_exec		*new_ctrl_op_node(t_token *token);

// handle_input/parser/print_redirection_error.c
void		syntax_error_redirection(void);

// handle_input/parser/add_path.c
int			add_path_to_command(t_token *tokens, t_env *env_lst);

#endif
