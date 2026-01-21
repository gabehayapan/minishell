/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:17:51 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/21 13:14:09 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*is_dir(t_token *token_dir)
{
	char	*ret;

	if (token_dir == NULL)
		return (NULL);
	ret = ft_strrchr(token_dir->word, '/');
	return (ret);
}

char	*split_token_with_slash(t_token **token_dir, char *ptr_slash)
{
	char	*dirname;
	char	*stash;
	t_token	*tmp;

	dirname = ft_substr((*token_dir)->word, 0,
			ptr_slash - (*token_dir)->word + 1);
	if (dirname == NULL)
		return (NULL);
	if (*(ptr_slash + 1) == '\0')
	{
		tmp = (*token_dir)->next;
		clear_token(&(*token_dir)->prev, *token_dir, free);
		*token_dir = tmp;
		return (dirname);
	}
	stash = ft_strdup(ptr_slash + 1);
	if (stash == NULL)
	{
		free(dirname);
		return (NULL);
	}
	free((*token_dir)->word);
	(*token_dir)->word = stash;
	return (dirname);
}

char	*get_open_dir_name(t_token **current, t_token *token_dir,
			char *ptr_slash, char **disname)
{
	char	*dirname;

	dirname = split_token_with_slash(&token_dir, ptr_slash);
	if (dirname == NULL)
		return (NULL);
	*disname = ft_strdup(dirname);
	if (*disname == NULL)
	{
		free(dirname);
		return (NULL);
	}
	*current = token_dir;
	return (dirname);
}

char	*get_cwd_name(t_token **current, char **disname)
{
	char	*dirname;

	dirname = getcwd(NULL, 0);
	if (dirname == NULL)
		return (NULL);
	while ((*current)->prev != NULL
		&& ((*current)->prev)->tk_type != SPACES)
		*current = (*current)->prev;
	*disname = ft_strdup("");
	if (*disname == NULL)
	{
		free(dirname);
		return (NULL);
	}
	return (dirname);
}

char	*get_target_dir(t_token **current, char **disname)
{
	char	*dirname;
	t_token	*token_dir;
	char	*ptr_slash;

	token_dir = *current;
	while (token_dir->prev != NULL && (token_dir->prev)->tk_type != SPACES)
		token_dir = token_dir->prev;
	ptr_slash = is_dir(token_dir);
	if (ptr_slash != NULL)
		dirname = get_open_dir_name(current, token_dir, ptr_slash, disname);
	else
		dirname = get_cwd_name(current, disname);
	if (dirname == NULL)
		return (NULL);
	return (dirname);
}
