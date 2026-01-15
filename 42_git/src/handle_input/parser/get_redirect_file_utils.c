/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirect_file_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 19:12:13 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/15 10:40:56 by hanakamu         ###   ########.fr       */
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
