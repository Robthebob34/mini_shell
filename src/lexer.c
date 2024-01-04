/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 15:03:39 by rheck             #+#    #+#             */
/*   Updated: 2024/01/04 13:47:26 by rheck            ###   ########.fr       */
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
    const char *identifier;
    const char *number;
    const char *operator;

    skip_whitespace(lexer);
    // Vérifiez la fin du fichier
    if (lexer->input[lexer->position] == '\0')
        return create_token(EOF_TOKEN, NULL);

    // Logique pour identifier différents types de tokens
    current_char = lexer->input[lexer->position];
    if (ft_isalpha(current_char))
	{
        // Identifier un identificateur (mot)
        identifier = read_identifier(lexer);
        return create_token(IDENTIFIER, identifier);
    }
	else if (ft_isdigit(current_char))
	{
        // Identifier un nombre
        number = read_number(lexer);
        return create_token(NUMBER, number);
    }
	else
	{
        // Identifier un opérateur
        operator = read_operator(lexer);
        return create_token(OPERATOR, operator);
    }
}

