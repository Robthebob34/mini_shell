#include "../inc/mini.h"

const char *read_number(Lexer *lexer)
{
    int start_position;
	int number_length;
	char *number;
	
	start_position = lexer->position;
    while (ft_isdigit(lexer->input[lexer->position]))
        lexer->position++;
    number_length = lexer->position - start_position;
    number = malloc(number_length + 1);
    if (number != NULL)
	{
        ft_strncpy(number, lexer->input + start_position, number_length);
        number[number_length] = '\0';
    }
    return (number);
}