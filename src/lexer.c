/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:03:39 by rheck             #+#    #+#             */
/*   Updated: 2024/01/04 15:49:43 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

void	init_lexer(Lexer *lexer, const char *input)
{
	lexer->input = input;
	lexer->position = 0;
}

void skip_whitespace(Lexer *lexer)
{
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
    char current_char;
    const char *value;

    skip_whitespace(lexer);
    // Vérifiez la fin du fichier
    if (lexer->input[lexer->position] == '\0')
        return create_token(EOF_TOKEN, NULL);
	
    // Logique pour identifier différents types de tokens
    current_char = lexer->input[lexer->position];
	if (current_char == '\'' || current_char == '"')
	{
		//identifier les single / double quotes
    	value = read_quoted_string(lexer, current_char);
    	return create_token(STRING, value);
    }
    if (ft_isalpha(current_char))
	{
        // Identifier un identificateur (mot)
        value = read_identifier(lexer);
        return create_token(IDENTIFIER, value);
    }
	else if (ft_isdigit(current_char))
	{
        // Identifier un nombre
        value = read_number(lexer);
        return create_token(NUMBER, value);
    }
	else
	{
        // Identifier un opérateur
        value = read_operator(lexer);
        return create_token(OPERATOR, value);
    }
}

