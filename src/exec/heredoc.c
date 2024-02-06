#include "../../inc/mini.h"
int	create_heredoc(t_cmd *cmd_list, bool quotes,
	t_main *tools, char *file_name)
{
	int		fd;
	char	*line;

    (void)quotes;
    (void)tools;
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	line = readline("\033[1;34m> \033[0m");
	while (line && ft_strncmp(cmd_list->redirection_name2, line, ft_strlen(cmd_list->redirection_name2))
		&& !my_global.stop_heredoc)
	{
		//if (quotes == 0)
		//	line = expander_str(tools, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("\033[1;34m> \033[0m");
	}
	free(line);
	if (my_global.stop_heredoc || !line)
		return (1);
	close(fd);
	return (0);
}

int	ft_heredoc(t_main *tools, t_cmd *cmd_list, char *file_name)
{
	bool	quotes;
	int		sl;

	sl = 0;
	if ((cmd_list[0].redirection_name2[0] == '\"'
			&& cmd_list->redirection_name2[ft_strlen(cmd_list->redirection_name2) - 1] == '\"')
		|| (cmd_list->redirection_name2[0] == '\''
			&& cmd_list->redirection_name2[ft_strlen(cmd_list->redirection_name2) - 1] == '\''))
		quotes = 1;
	else
		quotes = 0;
	delete_quotes(cmd_list->redirection_name2, '\"');
	delete_quotes(cmd_list->redirection_name2, '\'');
	my_global.stop_heredoc = 0;
	my_global.in_heredoc = 1;
	sl = create_heredoc(cmd_list, quotes, tools, file_name);
	my_global.in_heredoc = 0;
	tools->heredoc = 1;
	return (sl);
}

char	*generate_heredoc_filename(void)
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin("build/.tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

int	send_heredoc(t_main *tools, t_cmd *cmd)
{
	int		sl;
    int     i;

	sl = 0;
    i = 0;
	while (cmd[i].cmd_name != NULL)
	{	
		if (ft_strncmp(cmd[i].redirection, "<<", 2) == 0)
		{
			printf("non pas ici !!\n");
			if (cmd[i].redirection_name)
				free(cmd[i].redirection_name);
			cmd[i].redirection_name = generate_heredoc_filename();
			sl = ft_heredoc(tools, cmd + i, cmd[i].redirection_name);
			if (sl)
			{
				my_global.last_err_code = 1;
				return (1); // TROUVER UN MOYEN DE REVENIR AU A LA BOUCLE PRINCIPAL 
			}
		}
		i++;
	}
	return (0);
}
