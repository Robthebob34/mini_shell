#include "../inc/mini.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void *my_realloc(void *ptr, size_t old_size, size_t new_size)
{
    void *new_ptr;
     
    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }
    new_ptr = malloc(new_size);
    if (new_ptr != NULL)
    {
        size_t copy_size = old_size;
        if (new_size < old_size)
            copy_size = new_size;
        if (copy_size > 0)
            ft_memcpy(new_ptr, ptr, copy_size);
        free(ptr);
    }
    return (new_ptr);
}

char *ft_strncpy(char *dest, const char *src, size_t n)
{
    char *start;
	
	start = dest;
    if (dest == NULL || src == NULL)
        return NULL;
    while (n && (*dest++ = *src++))
        n--;
    while (n--)
        *dest++ = '\0';
    return (start);
}
