#include "../inc/mini.h"
int (*look_for_builtin(char *name))(t_main *data_base, t_cmd *single_cmd)
{
    static void *builtins[1][2] = {
        {"exit", my_exit}
    };
    int i;
    i = 0;
    while (i < 1)
    {   
        if (name)
        {
            if (!ft_strncmp(builtins[i][0], name, ft_strlen(name)))
                return(builtins[i][1]);
        }
        i++;
    }
    return (NULL);
}