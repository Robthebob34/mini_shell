#include "../inc/mini.h"

int	my_exit(t_main *tools, t_cmd *simple_cmd);

int (*look_for_builtin(char *name))(t_main *data_base, t_cmd *single_cmd)
{
    static void *builtins[4][2] = {
        {"exit", my_exit},
        {"cd", my_cd},
        {"env", my_env},
        {"history", my_history}
    };
    int i;
    i = 0;
    while (i < 4)
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