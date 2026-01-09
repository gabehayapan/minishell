/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:01:56 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/09 18:02:22 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# define SUCCESS 0
# define FAILURE 1

# include <stdlib.h>
# include <readline/readline.h>
# include "../libft/header/libft.h"

typedef enum e_tk_type
{
	SINGLE_REDIRECTION,	/* >, < */
	DOUBLE_REDIRECTION,	/* <<, >> */
	SINGLE_HISTORY,		/* ! */
	DOUBLE_HISTORY,		/* !! */
	WILDCARD,			/* * */
	PIPE,				/* | */
	SINGLE_QUOTE,		/* ' */
	DOUBLE_QUOTE,		/* " */
	DOLLAR,				/* $ */
	OPTION,				/* - */
	PARENTHESIS,		/* () */
	BRACES,				/* {} */
	AND,				/* && */
	OR,					/* || */
	TILDE,				/* ~ */
	SEMICOLON,			/* ; */
	END,				/* \0 */
	WORD,				/* string */
	SPACES,				/* white space */
}	t_tk_type;

typedef struct s_token
{
	t_tk_type		tk_type;
	char			*word;
	struct s_token	*next;
}	t_token;

typedef struct s_syntax_err
{
	char	c;
	char	*input;
	char	*new_input;
	char	*new_str;
}	t_syntax_err;

// handle_input/tokenizer/tokenizer.c
t_token		*tokenizer(char *str);
t_token		*create_new_token(char **str, t_token *current, t_tk_type tk_type);

// handle_input/tokenizer/tokenizer_utils.c
void		*free_token(t_token *token);
t_tk_type	get_token_type(char *str);
t_token		*new_token_quoted_str(char *start, char *end, t_token *current);

// handle_input/tokenizer/tokenize_quote.c
t_token		*handle_quote(char **str, t_token *current, t_tk_type tk_type);

// handle_input/tokenizer/tokenize_keywords.c
t_token		*tokenize_parenthesis(char **str, t_token *current);
t_token		*tokenize_env_var(char **str, t_token *current);
t_token		*tokenize_dollar(char *start, char **str, t_token *current);

// handle_input/tokenizer/syntax_error.c
char		*syntax_error(char *start, t_tk_type tk_type);

// handle_input/tokenizer/ft_isspace.c
int			ft_isspace(int c);

#endif
