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

    return quoted_string;
}
