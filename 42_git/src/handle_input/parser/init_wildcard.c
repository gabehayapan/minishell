/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wildcard.c                                    :+:      :+:    :+:   */ /*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:22:35 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/21 06:56:06 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*is_dir(t_token *token_dir)
{
	char	*str;

	if (token_dir == NULL)
		return (NULL);
	str = token_dir->word;
	while (*str != '\0')
	{
		if (*str == '/')
			return (str);
		str++;
	}
	return (NULL);
}

char	*split_token_with_slash(t_token *token_dir, char *ptr_slash)
{
	char	*dirname;
	char	*stash;
	char	*cp_stash;
	t_token	*new_token;
	t_token	*next;

	dirname = ft_substr(token_dir->word, 0, ptr_slash - token_dir->word + 1);
	if (dirname == NULL)
		return (NULL);
	stash = ft_strdup(ptr_slash + 1);
	if (stash == NULL)
		return (NULL);
	free(token_dir->word);
	token_dir->word = dirname;
	cp_stash = stash;
	next = token_dir->next;
	new_token = create_new_token(&cp_stash, token_dir, WORD);
	free(stash);
	if (new_token == NULL)
		return (NULL);
	new_token->next = next;
	next->prev = new_token;
	return (dirname);
}

char	*get_target_dir(t_token **current)
{
	char	*dirname;
	t_token	*token_dir;
	char	*ptr_slash;

	token_dir = *current;
	while (token_dir->prev != NULL && (token_dir->prev)->tk_type != SPACES)
		token_dir = token_dir->prev;
	ptr_slash = is_dir(token_dir);
	if (ptr_slash != NULL)
	{
		dirname = split_token_with_slash(token_dir, ptr_slash);
		*current = token_dir->next;
	}
	else
	{
		dirname = getcwd(NULL, 0);
		while ((*current)->prev != NULL
			&& ((*current)->prev)->tk_type != SPACES)
			*current = (*current)->prev;
	}
	if (dirname == NULL)
		return (NULL);
	return (dirname);
}
