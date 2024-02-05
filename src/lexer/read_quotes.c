/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:06:54 by rheck             #+#    #+#             */
/*   Updated: 2024/02/05 13:12:09 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

int find_closing_quote(Lexer *lexer, char quote_type)
{
    while (lexer->input[lexer->position] != '\0' && lexer->input[lexer->position] != quote_type)
        lexer->position++;
    return lexer->position;
}


int find_index_quotes(const char *input)
{
	int		i;
	int		index;

	i = 0;
	index = 0;
	while(input[i])
	{
		if (input[i] == '$' && input[i + 1] != '\0' && input[i + 1] != ' ')
		{
			while(input[i] != '\0' && input[i] != ' ')
				i++;
			index = i;
		}
		if (input[i] == '\0')
				break;
		i++;
	}
	return (index);
}

char *replace_env_variables_quotes(const char *input)
{
	int		i;
	int		cursor;
	int		length_1;
	char	*var_name;
	const char	*begin;

	i = 0;
	cursor = 0;
	while(input[i])
	{
		if (input[i] == '$' && input[i + 1] != '\0' && input[i + 1] != ' ')
		{
			begin = &input[i + 1];
			length_1 = i;
			i++;
			while(input[i] != '\0' && input[i] != ' ')
			{
				cursor++;
				i++;
			}
			var_name = malloc(sizeof(char) * (cursor + 1));
			ft_strlcpy(var_name, begin, cursor + 1);
			if (!getenv(var_name))
				return ("\n");
			if (input[i] == '\0')
				break;
		}
		i++;
	}
	return (complete_line_quotes(length_1, input, var_name));
}

char *complete_line_quotes(int length_1, const char *input, char *var_name)
{
	char *part_1;
	char *part_2;
	char *var;

	var = getenv(var_name);
	part_1 = malloc(sizeof(char) * (length_1 + 1));
	ft_memcpy(part_1, input, length_1);
	part_1[length_1] = '\0';
	part_2 = ft_strjoin(part_1, var);
	return (ft_strjoin(part_2, &input[find_index_quotes(input)]));
}


const char *read_quoted_string(Lexer *lexer, char quote_type)
{
    int start_position;
    int closing_quote_position;
    int quoted_string_length;
    char *quoted_string;
    size_t new_size;

    start_position = lexer->position + 1;  // Skip the opening quote
    lexer->position++;  // Move past the opening quote
    while (lexer->input[lexer->position] != '\0' && lexer->input[lexer->position] != quote_type)
        lexer->position++;
    closing_quote_position = lexer->position;
    lexer->position++;  // Move past the closing quote
    quoted_string_length = closing_quote_position - start_position;
    quoted_string = malloc(quoted_string_length + 1);
    if (quoted_string != NULL)
    {
        ft_strncpy(quoted_string, lexer->input + start_position, quoted_string_length);
        quoted_string[quoted_string_length] = '\0';
        // Check if the character after the closing quote is not a space
        while (lexer->input[lexer->position] != ' ' && lexer->input[lexer->position] != '\0')
        {
            // Determine the new size and reallocate memory
            new_size = quoted_string_length + 1;
            quoted_string = my_realloc(quoted_string, quoted_string_length, new_size);
            if (quoted_string != NULL)
            {
                // Append the new character to the string
                quoted_string[quoted_string_length - 1] = lexer->input[lexer->position];
                quoted_string[quoted_string_length] = '\0';
                lexer->position++;
                quoted_string_length++;
            }
            else
            {
                // Handle memory allocation error
                free(quoted_string);
                return NULL;
            }
        }
    }
	if (!is_dollar(quoted_string) || quote_type == '\'')
    	return quoted_string;
	return replace_env_variables_quotes(quoted_string);
}
