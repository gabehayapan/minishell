/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 09:27:16 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/31 10:43:29 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <dirent.h>
# include <stdbool.h>
# include <errno.h>
# include "tokenizer.h"
# include "env_var.h"
# include "../libft/header/libft.h"
# include "../libft/header/ftprintf.h"

# define NOT_FOUND 4
# define NO_DIR 5
# define NO_FILTER 6
# define NEW_MATCH 7
# define FORMAT_ERROR 8
# define SIGNALED 9
# define END 10

typedef enum s_rdt_type
{
	INFILE,
	OUTFILE,
	HEREDOC,
	APPEND,
}	t_rdt_type;

typedef struct s_rdt
{
	char			*rdt;
	t_rdt_type		type;
	int				fd_rdt;
	struct s_rdt	*next;
}	t_rdt;

typedef struct s_command
{
	char				**command;
	t_rdt				*inrdt;
	t_rdt				*outrdt;
	int					infd;
	int					outfd;
	int					is_subshell;
	struct s_command	*next;
}	t_command;

typedef struct s_exec
{
	t_tk_type		tk_type;
	struct s_exec	*left;
	struct s_exec	*right;
	t_command		*command;
	struct s_exec	*next;
}	t_exec;

typedef struct s_dir
{
	char	*dirname;
	char	*disname;
	DIR		*dir;
	t_token	*tk_last;
	int		is_found;
}	t_dir;

typedef struct s_d_info
{
	char	*d_name;
	size_t	len_d_name;
	size_t	len_str;
}	t_d_info;

typedef struct s_tk_ptr
{
	t_token	*head_filter;
	t_token	*tk_filter;
	t_token	*head_dir;
	t_token	*tk_dir;
}	t_tk_ptr;

typedef struct s_his
{
	int				id;
	char			*line;
	struct s_his	*next;
}	t_his;

// handle_input/handle_input.c
int			handle_input(char **input, t_env **env_lst, t_exec **exec_tree,
				unsigned char exit_status);

// handle_input/parser/parser.c
int			parser(t_token **tokens, t_env **env_lst, t_exec **exec_tree,
				unsigned char exit_status);
char		**new_exec(t_token **tokens, t_exec *node_exec, t_env *env_lst);
void		free_command(t_command *command);

// handle_input/parser/parser_utils.c
void		get_remaining_tokens(t_token **tokens);
void		add_new_command(t_command **head, t_command *new_command,
				t_command **last);
int			join_command(t_token **tokens, t_token *current, char **command,
				t_token **next);

// handle_input/parser/shell_var.c
int			check_assignment(t_token **tokens, t_env **env_lst);
int			add_shell_var(char *new_shell, t_env **env_lst);

// handle_input/parser/init.c
void		init_node_exec(t_exec *node_exec);
int			initialize_command(t_token **tokens, t_command *current,
				int *subshell);

// handle_input/parser/init_utils.c
int			check_opening_parenthesis(t_token **tokens, int *subshell);
int			check_closing_parenthesis(t_token **tokens, int *subshell);

// handle_input/parser/init_tokens.c
int			init_tokens(t_token **tokens, t_env **env_lst,
				unsigned char exit_status);

// handle_input/parser/free.c
void		free_strs(char **strs, size_t size);
void		free_null_term_strs(char **strs);
void		free_command(t_command *command);
void		free_node_exec(t_exec *node_exec);
void		clear_token(t_token **tokens, t_token *target, void (*del)(void *));

// handle_input/parser/free_all.c
void		free_all(t_env *env_lst, t_exec *top);

// handle_input/parser/counter.c
size_t		get_len_command(t_token *tokens);
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
int			expand_specials(t_token **tokens, t_env *env_lst,
				unsigned char exit_status);
int			expand_dollar(t_token **tokens, t_token **current, t_env *env_lst,
				unsigned char exit_status);
int			expand_tilde(t_token *current, t_env *env_lst);
int			expand_wildcard(t_token **tokens, t_token *current);

// handle_input/parser/expand_specials_utils.c
char		*rm_extra_space(char *str);
int			expand_quoted_dollar(t_token **tokens, t_token **current,
				t_env *env_lst, unsigned char exit_status);
int			handle_dbl_quoted_dollar(t_token **tokens, t_token **current,
				t_env *env_lst, unsigned char exit_status);
int			handle_others(t_token **tokens, t_token **current, t_env *env_lst,
				unsigned char exit_status);

// handle_input/parser/replace_command.c
int			replace_with_cmd_output(t_token **tokens, t_token **current,
				t_env *env_lst);

// handle_input/parser/wildcard/wildcard_init.c
int			init_wildcard(t_token **filter, t_token **token_dir, t_dir *dnames);
int			replace_token_word(char **word, char *new_word);

// handle_input/parser/wildcard/wildcard_init_slash.c
int			new_separated_tokens(t_token **curr_filter, char **strs);
int			add_head_slash(t_token **curr_filter, char *str);
int			add_last_slash(t_token **curr_filter);

// handle_input/parser/wildcard/wildcard_init_dirname.c
char		*get_open_dir_name(t_token **head_dir, char *ptr_slash,
				char **disname);
char		*get_cwd_name(char **disname);

// handle_input/parser/wildcard/wildcard_init_utils.c
t_token		*get_head_dir_token(t_token *token);
char		*is_slash(t_token *token_dir);
void		clear_head_dir_token(t_token **head_dir);

// handle_input/parser/wildcard/wildcard_initial_dir.c
int			check_initial_dir(t_token **tokens, t_token *filter,
				t_token **head_dir, t_dir *dnames);

// handle_input/parser/wildcard/wildcard_deeper_dir.c
int			check_deeper_dir(t_token **tokens, t_token *head_filter,
				t_token **head_dir, char *disname);

// handle_input/parser/wildcard/wildcard_deeper_dir.c
void		set_head_dir(t_token **head_dir, t_token *curr_dir, t_dir *dnames,
				int ret);
int			handle_not_found(t_token **tokens, t_token *head_filter,
				char *disname);

// handle_input/parser/wildcard/wildcard_get_dirent.c
int			check_dirent(t_token **tokens, t_token *filter, t_token **head_dir,
				t_dir *dnames);

// handle_input/parser/wildcard/wildcard_file_token.c
t_token		*add_new_matched_file(t_token *last_dir, t_dir *dnames, char *name);

// handle_input/parser/wildcard/wildcard_utils.c
void		set_type_word(t_token *current);
int			reset_wildcard_tokens(t_token **tokens, t_token *filter,
				t_token *token_dir, char *disname);
void		clear_filter_token(t_token **tokens, t_token *filter);
t_token		*skip_one_filter_dir(t_token *filter);
int			set_dnames(t_token *dir, t_dir *dnames);

// handle_input/parser/wildcard/wildcard_expansion_utils.c
int			check_file_name(t_token *head, struct dirent *ent);
t_token		*new_file_token(t_token *head, char *name);

// handle_input/parser/handle_exit_status.c
char		*handle_exit_status(t_token **next, unsigned char exit_status);

// handle_input/parser/join_word.c
char		*join_word_with_space(char *str, char *word, size_t *len_str);
char		*join_word_no_space(char *str, char *word);

// handle_input/parser/exec_nodes.c
int			add_exec_node(t_token **tokens, t_exec **head, t_exec *node_exec);

// handle_input/parser/exec_ast.c
t_exec		*create_exec_ast(t_exec *head);

// handle_input/parser/print_redirection_error.c
void		syntax_error_redirection(void);

// handle_input/parser/add_path.c
int			add_path_to_command(t_token *tokens, t_env *env_lst);

#endif
