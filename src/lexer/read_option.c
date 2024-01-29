/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:49:35 by rheck             #+#    #+#             */
/*   Updated: 2024/01/15 13:56:18 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

const char *read_option(Lexer *lexer)
{
    int start_position;
    int option_length;
    char *option;

    start_position = lexer->position;
    while (ft_isalpha(lexer->input[lexer->position]) || lexer->input[lexer->position] == '-')
        lexer->position++;
    option_length = lexer->position - start_position;
    option = malloc(option_length + 1);
    if (option != NULL)
    {
        ft_strncpy(option, lexer->input + start_position, option_length);
        option[option_length] = '\0';
    }
    return (option);
}
