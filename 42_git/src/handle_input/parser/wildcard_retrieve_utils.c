/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_retrieve_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:20:30 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/28 14:42:31 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

int	handle_return_value(t_token *head, DIR *dir, int ret)
{
	if (ret == FAILURE)
	{
		closedir(dir);
		return (FAILURE);
	}
	else
	{
		set_type_word(head);
		closedir(dir);
		return (SUCCESS);
	}
}

int	check_file_name(t_token *head, struct dirent *ent, t_dir dnames)
{
	char	*d_name;
	size_t	len_d_name;

	(void)dnames;
	d_name = ent->d_name;
	len_d_name = ft_strlen(ent->d_name);
	while (head != NULL && head->tk_type != SPACES)
	{
		//if (*(head->word) == '/')
		//	open_another_dir(head, ent, dnames);
		if (head->tk_type != WILDCARD)
		{
			d_name = ft_strnstr(d_name, head->word, len_d_name);
			if (d_name == NULL)
				return (NOT_FOUND);
		}
		head = head->next;
	}
	return (SUCCESS);
}

t_token	*new_file_token(t_token *head, char *name)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->tk_type = WORD;
	new_token->word = name;
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
