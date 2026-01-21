/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_retrieve.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:01:34 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/21 09:51:51 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdbool.h>
#include <errno.h>
#include <dirent.h>

#define NOT_FOUND 4
#define END 5

void	set_type_word(t_token *current)
{
	while (current != NULL && current->tk_type != SPACES)
	{
		if (current->tk_type == WILDCARD)
			current->tk_type = WORD;
		current = current->next;
	}
}

void	clear_filter_token(t_token **tokens, t_token *head)
{
	t_token	*next;

	while (head != NULL && head->tk_type != SPACES)
	{
		next = head->next;
		clear_token(tokens, head, free);
		head = next;
	}
}

int	filter_file(t_token *head, DIR *dir, char **name)
{
	struct dirent	*ent;
	char			*d_name;
	size_t			len_d_name;

	errno = 0;
	ent = readdir(dir);
	if (ent == NULL && errno != 0)
	{
		perror("ent");
		return (FAILURE);
	}
	else if (ent == NULL)
		return (END);
	if (head->tk_type == WILDCARD && *(ent->d_name) == '.')
			return (NOT_FOUND);
	d_name = ent->d_name;
	len_d_name = ft_strlen(ent->d_name);
	while (head != NULL && head->tk_type != SPACES)
	{
		if (head->tk_type != WILDCARD)
		{
			d_name = ft_strnstr(d_name, head->word, len_d_name);
			if (d_name == NULL)
				return (NOT_FOUND);
		}
		head = head->next;
	}
	*name = ft_strdup(ent->d_name);
	if (*name == NULL)
		return (FAILURE);
	return (SUCCESS);
}

t_token	*new_file_token(t_token *head, char *name)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->tk_type = WORD;
	new_token->word = ft_strdup(name);
	if (new_token->word == NULL)
	{
		free(new_token);
		return (NULL);
	}
	new_token->is_join = false;
	new_token->prev = head->prev;
	new_token->next = head;
	if (head->prev != NULL)
		(head->prev)->next = new_token;
	head->prev = new_token;
	return (new_token);
}

int	get_first_file(t_token **tokens, t_token *token_dir, t_token *head,
			DIR *dir)
{
	char	*name;
	t_token	*new_token;
	int		ret;

	ret = filter_file(head, dir, &name);
	while (ret != END)
	{
		if (ret == SUCCESS)
		{
			new_token = new_file_token(head, name);
			free(name);
			if (new_token == NULL)
				return (FAILURE);
			if (*tokens == head)
				*tokens = new_token;
			if (token_dir != NULL && token_dir->tk_type == WORD)
				token_dir->tk_type = WILDCARD;
			else
				new_token->tk_type = WILDCARD;
			return (SUCCESS);
		}
		else if (ret == FAILURE)
			return (FAILURE);
		ret = filter_file(head, dir, &name);
	}
	return (NOT_FOUND);
}

int	get_remaining_files(t_token *token_dir, t_token *head, DIR *dir)
{
	char	*name;
	t_token	*new_token;
	int		ret;

	ret = filter_file(head, dir, &name);
	while (ret != END)
	{
		if (ret == SUCCESS)
		{
			if (token_dir != NULL && token_dir->tk_type == WORD)
				new_token = new_file_token(head, token_dir->word);
			if (new_token != NULL)
			{
				new_token = new_file_token(head, name);
				free(name);
			}
			if (new_token == NULL)
				return (FAILURE);
		}
		else if (ret == FAILURE)
			return (FAILURE);
		ret = filter_file(head, dir, &name);
	}
	return (SUCCESS);
}

int	get_matching_files(t_token **tokens, t_token *head, char *cwd)
{
	DIR		*dir;
	t_token	*token_dir;
	int		ret;

	dir = opendir(cwd);
	if (dir == NULL)
	{
		set_type_word(head);
		return (SUCCESS);
	}
	token_dir = head->prev;
	ret = get_first_file(tokens, token_dir, head, dir);
	if (ret == FAILURE)
	{
		closedir(dir);
		return (FAILURE);
	}
	else if (ret == NOT_FOUND)
	{
		set_type_word(head);
		return (SUCCESS);
	}
	if (get_remaining_files(token_dir, head, dir) == FAILURE)
	{
		closedir(dir);
		return (FAILURE);
	}
	clear_filter_token(tokens, head);
	closedir(dir);
	return (SUCCESS);
}
