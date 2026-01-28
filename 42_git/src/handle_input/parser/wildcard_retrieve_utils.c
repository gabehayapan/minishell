/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_retrieve_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 10:20:30 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/28 18:35:23 by hanakamu         ###   ########.fr       */
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

int	open_another_dir(t_token *head, t_dir dnames, t_d_info *d_info)
{
	t_dir	cp_dnames;

	(void)head;
	(void)dnames;
	cp_dnames.dirname = ft_strdup(d_info->d_name);
	if (cp_dnames.dirname == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	verify_file_name(t_token *head, t_dir dnames, t_d_info *d_info)
{
	char	**strs;
	char	**cp_strs;
	int		is_slash;

	strs = ft_split(head->word, '/');
	if (strs == NULL)
		return (FAILURE);
	cp_strs = strs;
	is_slash = 0;
	while (*strs != NULL)
	{
		if (is_slash == 1)
			open_another_dir(head, dnames, d_info);
		d_info->d_name = ft_strnstr(d_info->d_name, *strs, d_info->len_d_name);
		if (d_info->d_name == NULL)
		{
			free_null_term_strs(cp_strs);
			return (NOT_FOUND);
		}
		d_info->len_str = ft_strlen(*strs);
		is_slash = 1;
		strs++;
	}
	free_null_term_strs(cp_strs);
	return (SUCCESS);
}

int	check_file_name(t_token *head, struct dirent *ent, t_dir dnames)
{
	t_d_info	d_info;
	int			ret;
	int			is_wildcard;

	(void)dnames;
	d_info.d_name = ent->d_name;
	d_info.len_d_name = ft_strlen(ent->d_name);
	d_info.len_str = 0;
	is_wildcard = 0;
	while (head != NULL && head->tk_type != SPACES)
	{
		if (head->tk_type != WILDCARD)
		{
			ret = verify_file_name(head, dnames, &d_info);
			if (ret == FAILURE || ret == NOT_FOUND)
				return (ret);
			is_wildcard = 0;
		}
		else
			is_wildcard = 1;
		head = head->next;
	}
	if (is_wildcard == 0 && *(d_info.d_name + d_info.len_str) != '\0')
		return (NOT_FOUND);
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
