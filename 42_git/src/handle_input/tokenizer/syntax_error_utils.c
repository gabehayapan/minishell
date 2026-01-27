/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanakamu <hanakamu@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 19:16:24 by hanakamu          #+#    #+#             */
/*   Updated: 2026/01/22 19:19:42 by hanakamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	remove_last_new_line(char *input)
{
	if (input == NULL || *input == '\0')
		return ;
	while (*(input + 1) != '\0')
		input++;
	if (*input == '\n')
		*input = '\0';
}
