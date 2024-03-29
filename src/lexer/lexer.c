/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:17:58 by rheck             #+#    #+#             */
/*   Updated: 2024/01/31 12:29:14 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

void	init_lexer(Lexer *lexer, const char *input)
{
	lexer->position = 0;
	lexer->is_cmd = 1;
	lexer->input = input;
}

void skip_whitespace(Lexer *lexer)
{
    if (!lexer->input)
        return ;
    while (is_space(lexer->input[lexer->position]))
        lexer->position++;
}

Token	create_token(TokenType type, const char *value)
{
    Token token;
    token.type = type;
    token.value = value;
    return (token);
}

Token get_next_token(Lexer *lexer)
{
    char        current_char;
    const char  *value;

    skip_whitespace(lexer);
    if (lexer->input[lexer->position] == '\0')
        return create_token(EOF_TOKEN, NULL);
    current_char = lexer->input[lexer->position];
	if (current_char == '\'' || current_char == '"')
	{
    	value = read_quoted_string(lexer, current_char);
    	return create_token(STRING, value);
    }
    if (is_valid_identifier_char(current_char))
	{
        value = read_identifier(lexer);
        if (lexer->is_cmd == 1)
        {
            lexer->is_cmd = 0;
			return create_token(IDENTIFIER, value);
		}
        return create_token(ARGUMENT, value);
    }
	else if (ft_isdigit(current_char))
	{
        value = read_number(lexer);
        return create_token(NUMBER, value);
    }
    else if (current_char == '-')
    {
        value = read_option(lexer);
        return (create_token(OPTION, value));
    }
	else if (current_char == '|' || current_char == '>' || current_char == '<')
	{
        value = read_operator(lexer);
        if (ft_strncmp(value, "|", 1) == 0)
        {
            lexer->is_cmd = 1;
            return (create_token(PIPE, value));
        }
        return create_token(OPERATOR, value);
    }
    else
        return create_token(EOF_TOKEN, NULL);
}
