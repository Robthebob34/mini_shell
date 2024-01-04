/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 15:44:10 by rheck             #+#    #+#             */
/*   Updated: 2024/01/04 15:48:06 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

int find_closing_quote(Lexer *lexer, char quote_type)
{
    while (lexer->input[lexer->position] != '\0' && lexer->input[lexer->position] != quote_type)
        lexer->position++;
    return lexer->position;
}

const char *read_quoted_string(Lexer *lexer, char quote_type)
{
    int start_position;
	start_position = lexer->position + 1;  // Skip the opening quote
    lexer->position++;  // Move past the opening quote

    int closing_quote_position = find_closing_quote(lexer, quote_type);

    int quoted_string_length = closing_quote_position - start_position;
    char *quoted_string = malloc(quoted_string_length + 1);

    if (quoted_string != NULL)
	{
        ft_strncpy(quoted_string, lexer->input + start_position, quoted_string_length);
        quoted_string[quoted_string_length] = '\0';
    }
    // Move past the closing quote
    if (lexer->input[lexer->position] == quote_type)
        lexer->position++;
    return (quoted_string);
}
