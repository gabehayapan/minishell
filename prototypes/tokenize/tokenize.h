/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:01:56 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/07 12:12:13 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# define SUCCESS 0
# define FAILURE 1

#include <stdlib.h>
#include <readline/readline.h>
#include "../../libft/header/libftall.h"

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

t_token	*tokenizer(char *str);
void	*free_token(t_token *token);
int		ft_isspace(int c);

#endif
