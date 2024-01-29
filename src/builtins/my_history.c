#include "../../inc/mini.h"

int	my_history(t_main *data_base, t_cmd *simple_cmd)
{
    int     fd;
    char    *line;
    (void)simple_cmd;
    (void)data_base;
    if(simple_cmd->cmd_args[1])
    {
        if(ft_strncmp(simple_cmd->cmd_args[1], "-c", 2) == 0)
        {
            fd = open("history_file", O_TRUNC | O_CREAT |O_RDONLY, 0644);
            close(fd);
        }
        return (0); //potentiel erreur d'arguments a renvoyer 
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