#include "../inc/mini.h"
int init_shell(char **env, t_main *data_base)
{
    data_base->env_tab = ft_arraydup(env);
    data_base->pwd = getenv("PWD");
    data_base->old_pwd = getenv("OLWPWD");
    data_base->index = 0;
    return (0);
}