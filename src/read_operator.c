/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:29:29 by rheck             #+#    #+#             */
/*   Updated: 2024/01/08 14:12:33 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"


int is_operator_char(char c)
{
    return (c == '|' || c == '>' || c == '<' || c == '$');
}

const char  *read_operator(Lexer *lexer)
{
    size_t start_position = lexer->position;

    while (is_operator_char(lexer->input[lexer->position]))
        lexer->position++;

    size_t operator_length = lexer->position - start_position;
    char *operator_str = malloc(operator_length + 1);

    if (operator_str != NULL)
    {
        ft_strncpy(operator_str, lexer->input + start_position, operator_length);
        operator_str[operator_length] = '\0';
    }

    return operator_str;
}
