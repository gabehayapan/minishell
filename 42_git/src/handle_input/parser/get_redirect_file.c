/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirect_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:37:05 by hanakamu          #+#    #+#             */
/*   Updated: 2026/02/02 10:43:28 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_numeric_word(char *str)
{
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 0)
			return (FAILURE);
		str++;
	}
	return (SUCCESS);
}

static int	get_fd_rdt(t_token **tokens, t_token *current, t_rdt_type rdt_type)
{
	int	fd;

	if (current->prev == NULL || current->is_join == false
		|| is_numeric_word(current->prev->word) == FAILURE)
	{
		if (rdt_type == INFILE || rdt_type == HEREDOC)
			return (STDIN_FILENO);
		else
			return (STDOUT_FILENO);
	}
	fd = ft_atoi(current->prev->word);
	clear_token(tokens, current->prev, free);
	return (fd);
}

static int	new_rdt_node(t_token **tokens, t_token *current, t_rdt **head)
{
	t_rdt	*new_rdt;

	if (current->next == NULL)
	{
		no_rdt_file(current);
		return (SUCCESS);
	}
	new_rdt = (t_rdt *)malloc(sizeof(t_rdt));
	if (new_rdt == NULL)
		return (FAILURE);
	new_rdt->rdt = (current->next)->word;
	new_rdt->type = get_rdt_type(current);
	new_rdt->fd_rdt = get_fd_rdt(tokens, current, new_rdt->type);
	new_rdt->next = NULL;
	if (*head == NULL)
		*head = new_rdt;
	else
		add_last(head, new_rdt);
	return (SUCCESS);
}

static int	set_rdt_node(t_token **tokens, t_token *current, t_rdt **head)
{
	int	is_success;

	is_success = new_rdt_node(tokens, current, head);
	if (is_success == FAILURE)
	{
		free_rdt(*head);
		return (FAILURE);
	}
	clear_token(tokens, current->next, NULL);
	clear_token(tokens, current, free);
	return (SUCCESS);
}

int	get_in_out_rdt(t_token **tokens, t_command *command)
{
	t_rdt	*head_in;
	t_rdt	*head_out;
	t_token	*current;
	int		is_success;

	head_in = NULL;
	head_out = NULL;
	current = *tokens;
	is_success = SUCCESS;
	while (current != NULL && current->tk_type != AND && current->tk_type != OR
		&& current->tk_type != SEMI && current->tk_type != PIPE)
	{
		if (current->tk_type == SGL_INRDT || current->tk_type == DBL_INRDT)
			is_success = set_rdt_node(tokens, current, &head_in);
		if (current->tk_type == SGL_OUTRDT || current->tk_type == DBL_OUTRDT)
			is_success = set_rdt_node(tokens, current, &head_out);
		if (is_success == FAILURE)
			return (FAILURE);
		current = current->next;
	}
	command->inrdt = head_in;
	command->outrdt = head_out;
	return (SUCCESS);
}
