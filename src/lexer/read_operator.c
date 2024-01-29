/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_operator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:06:32 by rheck             #+#    #+#             */
/*   Updated: 2024/01/29 18:17:30 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/mini.h"


int is_operator_char(char c)
{
    return (c == '|' || c == '>' || c == '<' || c == '$');
}

const char  *read_operator(Lexer *lexer)
{
    size_t  start_position;
    size_t  operator_length;
    char    *operator_str;

    start_position = lexer->position;
    while (is_operator_char(lexer->input[lexer->position]))
        lexer->position++;
    operator_length = lexer->position - start_position;
    operator_str = malloc(operator_length + 1);
    if (operator_str != NULL)
    {
        ft_strncpy(operator_str, lexer->input + start_position, operator_length);
        operator_str[operator_length] = '\0';
    }
    return operator_str;
}
