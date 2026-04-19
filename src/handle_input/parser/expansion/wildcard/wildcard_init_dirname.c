/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_init_dirname.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:06:21 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/30 16:08:03 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*split_token_with_slash(t_token **head_dir, char *ptr_slash)
{
	char	*dirname;
	char	*stash;

	dirname = ft_substr((*head_dir)->word, 0,
			ptr_slash - (*head_dir)->word + 1);
	if (dirname == NULL)
		return (NULL);
	if (*(ptr_slash + 1) == '\0')
	{
		clear_head_dir_token(head_dir);
		return (dirname);
	}
	stash = ft_strdup(ptr_slash + 1);
	if (stash == NULL)
	{
		free(dirname);
		return (NULL);
	}
	free((*head_dir)->word);
	(*head_dir)->word = stash;
	return (dirname);
}

char	*get_open_dir_name(t_token **head_dir,
			char *ptr_slash, char **disname)
{
	char	*dirname;

	dirname = split_token_with_slash(head_dir, ptr_slash);
	if (dirname == NULL)
		return (NULL);
	*disname = ft_strdup(dirname);
	if (*disname == NULL)
	{
		free(dirname);
		return (NULL);
	}
	return (dirname);
}

char	*get_cwd_name(char **disname)
{
	char	*dirname;

	dirname = getcwd(NULL, 0);
	if (dirname == NULL)
		return (NULL);
	*disname = ft_strdup("");
	if (*disname == NULL)
	{
		free(dirname);
		return (NULL);
	}
	return (dirname);
}
