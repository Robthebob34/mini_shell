/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:02:19 by rheck             #+#    #+#             */
/*   Updated: 2023/12/28 17:35:43 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

int parser(t_token *tokens)
{
	t_token *current;

	current = tokens;
	if (!tokens)
		return (0);
	while(current)
	{
		if (current->type == "WORD")
			//parse word
		current = current->next;
	}
	return (1);
}

void	handle_quotes(t_token *tokens)
{
	//handle shits here
	//for simple and doubles quotes
}