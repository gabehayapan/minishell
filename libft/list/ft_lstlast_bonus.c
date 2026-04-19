/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:42:03 by hanakamu          #+#    #+#             */
/*   Updated: 2025/10/21 14:55:24 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lst_last;

	lst_last = lst;
	if (lst_last != NULL)
	{
		while ((*lst_last).next != NULL)
			lst_last = (*lst_last).next;
	}
	return (lst_last);
}
