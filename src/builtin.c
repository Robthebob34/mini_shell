#include "../inc/mini.h"

int	my_exit(t_main *tools, t_cmd *simple_cmd);

int (*look_for_builtin(char *name))(t_main *data_base, t_cmd *single_cmd)
{
    static void *builtins[5][2] = {
        {"exit", my_exit},
        {"cd", my_cd},
        {"env", my_env},
        {"history", my_history},
        {"echo", my_echo} // not finish 
    };
    int i;
    i = 0;
    while (i < 5)
    {   
        if (name)
        {
            if (!ft_strncmp(builtins[i][0], name, ft_strlen(name) + 1))
                return(builtins[i][1]);
        }
        i++;
    }
    return (NULL);
}