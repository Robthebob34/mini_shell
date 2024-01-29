#include "../../inc/mini.h"
int	my_history(t_main *data_base, t_cmd *simple_cmd);
int my_cd(t_main *tools, t_cmd *simple_cmd);
int	my_env(t_main *data_base, t_cmd *simple_cmd);
int	my_echo(t_main *tools, t_cmd *simple_cmd);
int my_pwd(t_main *tools, t_cmd *simple_cmd);
int	my_unset(t_main *tools, t_cmd *simple_cmd);
int	my_export(t_main *tools, t_cmd *simple_cmd);
int	my_exit(t_main *tools, t_cmd *simple_cmd);


int (*look_for_builtin(char *name))(t_main *data_base, t_cmd *single_cmd)
{
    static void *builtins[8][2] = {
        {"exit", my_exit},
        {"cd", my_cd},
        {"env", my_env},
        {"history", my_history},
        {"pwd", my_pwd},
        {"echo", my_echo}, // not finish 
        {"export", my_export},
        {"unset", my_unset}
    };
    int i;
    i = 0;
    while (i < 8)
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