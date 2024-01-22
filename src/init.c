#include "../inc/mini.h"
int init_shell(char **env, t_main *data_base)
{
    char *str;

    data_base->env_tab = ft_arraydup(env);
    str = getenv("PWD");
    data_base->pwd = ft_strdup(str);
    str = getenv("OLWPWD");
    data_base->old_pwd = ft_strdup(str);
    free(str);
    data_base->index = 0;
    return (0);
}