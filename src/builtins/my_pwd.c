#include <../../inc/mini.h>
int my_pwd(t_main *tools, t_cmd *simple_cmd)
{
    (void)simple_cmd;
    ft_putendl_fd(tools->pwd, 1);
    return(0);
}