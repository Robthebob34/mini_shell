
#include "../inc/mini.h"

int	is_valid_identifier_char(char c)
{
    return (ft_isalnum(c) || c == '_' || c =='/' || c == '.');
}

const char *read_identifier(Lexer *lexer)
{
    int start_position;
	int identifier_length;
	char *identifier;
	
	start_position = lexer->position;
    if (!ft_isalpha(lexer->input[start_position]) && lexer->input[start_position] != '_')
        return (NULL);
    while (is_valid_identifier_char(lexer->input[lexer->position]))
        lexer->position++;
    identifier_length = lexer->position - start_position;
    identifier = malloc(identifier_length + 1);
    if (identifier != NULL)
	{
        ft_strncpy(identifier, lexer->input + start_position, identifier_length);
        identifier[identifier_length] = '\0';
    }
    return (identifier);
}
