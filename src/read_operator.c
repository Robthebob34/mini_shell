/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:29:29 by rheck             #+#    #+#             */
/*   Updated: 2024/01/04 14:29:32 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"



const char *read_single_quote(Lexer *lexer, int start_position)
{
    // Lire jusqu'à ce qu'un guillemet simple fermant soit trouvé
    while (lexer->input[lexer->position] != '\0' && lexer->input[lexer->position] != '\'')
        lexer->position++;
    // Si un guillemet simple fermant est trouvé, avancer la position du lexer
    if (lexer->input[lexer->position] == '\'')
        lexer->position++;
    return (create_operator_str(lexer, start_position));
}

const char *read_double_quote(Lexer *lexer, int start_position)
{
    // Lire jusqu'à ce qu'un guillemet double fermant soit trouvé
    while (lexer->input[lexer->position] != '\0' && lexer->input[lexer->position] != '"')
        // TODO: Ajouter votre logique spéciale pour le caractère '$' dans les guillemets doubles
        lexer->position++;

    // Si un guillemet double fermant est trouvé, avancer la position du lexer
    if (lexer->input[lexer->position] == '"')
        lexer->position++;
    return (create_operator_str(lexer, start_position));
}

const char *read_regular_operator(Lexer *lexer, int start_position)
{
    // Sinon, si le caractère est un opérateur, avancer la position du lexer
    lexer->position++;

    // Si le caractère suivant est également un opérateur, avancez la position du lexer
    if (is_operator_char(lexer->input[lexer->position]))
        lexer->position++;
    return (create_operator_str(lexer, start_position));
}

const char *create_operator_str(Lexer *lexer, int start_position)
{
    int operator_length = lexer->position - start_position;
    char *operator_str = malloc(operator_length + 1);

    if (operator_str != NULL)
	{
        ft_strncpy(operator_str, lexer->input + start_position, operator_length);
        operator_str[operator_length] = '\0';
    }

    return (operator_str);
}

const char *read_operator(Lexer *lexer)
{
    // Déclarations au début de la fonction
    char current_char;
    int start_position;
    int operator_length;
    char *operator_str;

    current_char = lexer->input[lexer->position];

    if (!is_operator_char(current_char) && current_char != '\'' && current_char != '"')
        return (NULL);

    start_position = lexer->position;

    // Si le caractère est un guillemet simple
    if (current_char == '\'')
        return read_single_quote(lexer, start_position);
    // Si le caractère est un guillemet double
    else if (current_char == '"')
        return read_double_quote(lexer, start_position);
    else
        return read_regular_operator(lexer, start_position);
}
