#include "../inc/mini.h"
int	export_error(char *c)
{
	ft_putstr_fd("minishell: export: ", 2);
	if (c)
	{
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(c, 2);
		ft_putstr_fd("\': is ", 2);
	}
	ft_putendl_fd("not a valid identifier", 2);
	return (1);
}