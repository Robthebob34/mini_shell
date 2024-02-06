#include "../../inc/mini.h"
int	check_redirections(t_cmd *cmd)
{
    int i;

    i = 0;
	while (cmd[i].cmd_name != NULL)
	{
		if (cmd[i].redirection && cmd[i].redirection[0] == '<' && cmd[i].redirection[1] == '\0')
		{
			if (handle_infile(cmd[i].redirection_name))
				return (1);
		}
		else if (cmd[i].redirection && cmd[i].redirection[0] == '>')
		{
			if (handle_outfile(cmd + i))
				return (1);
		}
		else if (cmd[i].redirection && cmd[i].redirection[0] == '<' && cmd[i].redirection[1] == '<')
		{
			if (handle_infile(cmd[i].redirection_name))
				return (1);
		}
		i++;
	}
	return (0);
}
int	check_append_outfile(t_cmd *redirections)
{
	int	fd;

	if (ft_strncmp(redirections[0].redirection, ">>", 2))
		fd = open(redirections[0].redirection_name,
				O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(redirections[0].redirection_name,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}

int	handle_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: infile: No such file or directory\n",
			2);
		return (1);
	}
	if (fd > 0 && dup2(fd, 0) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", 2);
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

int	handle_outfile(t_cmd *redirection)
{
	int	fd;

	fd = check_append_outfile(redirection);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: outfile: Error\n", 2);
		return (1);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", 2);
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (1);
}
