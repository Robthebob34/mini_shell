/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:03:39 by rheck             #+#    #+#             */
/*   Updated: 2023/12/28 13:15:25 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

//still to finsih
void	set_type_value(t_token *previous, char *token)
{
	t_token *new_token;

	new_token = ft_new_token(token);
	if (ft_strncmp(token, "|", 1))
		new_token->type = "PIPE";
	else if (ft_strncmp(token, ">", 1))
		new_token->type = "GREAT";
	else if (ft_strncmp(token, ">>", 2))
		new_token->type = "GREATGREAT";
	else if (ft_strncmp(token, "<", 1))
		new_token->type = "LESS";
	else if (ft_strncmp(token, "<<", 2))
		new_token->type = "LESSLESS";
	else
		new_token->type = "WORD";
	previous->next = new_token;
}

void	lex(t_main data)
{
	char **tokens;
	int	i;
	t_token *first;
	
	tokens = ft_split(data.my_prompt_line, ' ');
	i = 0;
	first = ft_new_token(tokens[0]);
	while (tokens[i])
	{
		set_type_value(first, tokens[i]);
		i++;
	}
}