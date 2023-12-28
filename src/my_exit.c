#include "../inc/mini.h"
int choose_exit_code(t_main *tools, t_cmd *simple_cmd)
{
	(void) simple_cmd;
	exit(tools->last_err_code);
	return(0);
}
int	my_exit(t_main *tools, t_cmd *simple_cmd)
{
	ft_putendl_fd("exit", 2);
	choose_exit_code(tools, simple_cmd);
	return (0);
}