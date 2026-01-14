/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirect_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:37:05 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/14 17:41:10 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_rdt(t_rdt *rdt)
{
	t_rdt	*next;

	while (rdt != NULL)
	{
		next = rdt->next;
		free(rdt->rdt);
		free(rdt);
		rdt = next;
	}
}

t_rdt_type	get_rdt_type(t_token *token)
{
	if (token->tk_type == SGL_INRDT)
		return (INFILE);
	else if (token->tk_type == SGL_OUTRDT)
		return (OUTFILE);
	else if (token->tk_type == DBL_INRDT)
		return (HEREDOC);
	else
		return (APPEND);
}

void	add_last(t_rdt **head, t_rdt *new_rdt)
{
	t_rdt	*last;

	last = *head;
	while (last != NULL && last->next != NULL)
		last = last->next;
	last->next = new_rdt;
}

void	no_rdt_file(t_token *token)
{
	char	*missing_rdt;

	if (token->tk_type == SGL_INRDT)
		missing_rdt = "<";
	else if (token->tk_type == SGL_OUTRDT)
		missing_rdt = ">";
	else if (token->tk_type == DBL_INRDT)
		missing_rdt = "<<";
	else
		missing_rdt = ">>";
	ft_dprintf(2, "minishell: syntax error after \'%s\'\n", missing_rdt);
}

int	new_rdt_node(t_token *current, t_rdt **head)
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
	new_rdt->next = NULL;
	if (*head == NULL)
		*head = new_rdt;
	else
		add_last(head, new_rdt);
	return (SUCCESS);
}

int	get_in_out_rdt(t_token **tokens, t_command *command)
{
	t_rdt	*head_in;
	t_rdt	*head_out;
	t_token	*current;

	head_in = NULL;
	head_out = NULL;
	current = *tokens;
	while (current != NULL && current->tk_type != AND && current->tk_type != OR
		&& current->tk_type != SEMI && current->tk_type != PIPE)
	{
		if (current->tk_type == SGL_INRDT || current->tk_type == DBL_INRDT)
		{
			if (new_rdt_node(current, &head_in) == FAILURE)
			{
				free_rdt(head_in);
				return (FAILURE);
			}
			clear_token(tokens, current->next, NULL);
			clear_token(tokens, current, free);
		}
		if (current->tk_type == SGL_OUTRDT || current->tk_type == DBL_OUTRDT)
		{
			if (new_rdt_node(current, &head_out) == FAILURE)
			{
				free_rdt(head_in);
				return (FAILURE);
			}
			clear_token(tokens, current->next, NULL);
			clear_token(tokens, current, free);
		}
		current = current->next;
	}
	command->inrdt = head_in;
	command->outrdt = head_out;
	return (SUCCESS);
}
