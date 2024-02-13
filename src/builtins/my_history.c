#include "../../inc/mini.h"
void    ft_history_error(char *str, t_main *data_base, t_cmd *simple_cmd)
{
    (void)data_base;
    (void)simple_cmd;
    ft_putstr_fd(str, 2);
    write(2, "\n", 1);
    return;
}
int	my_history(t_main *data_base, t_cmd *simple_cmd)
{
    int     fd;
    char    *line;

    if(simple_cmd->cmd_args[1])
    {
        if(ft_strncmp(simple_cmd->cmd_args[1], "-c", 2) == 0)
        {
            fd = open("history_file", O_TRUNC | O_CREAT |O_RDONLY, 0644);
            close(fd);
            return(0);
        }
        else
            ft_history_error("history: usage: history [-c]", data_base, simple_cmd);
        return (1); 
    }
    fd = open("history_file", O_CREAT | O_RDONLY, 0644);
    line = get_next_line(fd);
    while(line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}
void add_myhistory(char *str)
{
    int fd;
    // DEFINIR UNE TAILLE MAX D'HISTO
    fd = open("history_file", O_CREAT | O_APPEND | O_WRONLY, 0644);
    write(fd, str, ft_strlen(str));
    write(fd, "\n", 1);
    close(fd);
}
void    super_history(char *str)
{
    add_history(str);
	add_myhistory(str);
}