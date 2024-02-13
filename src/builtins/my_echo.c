#include "../../inc/mini.h"

void	print_lines(int i, char **str, int out)
{
	while (str[i])
	{
		ft_putstr_fd(str[i], out);
		i++;
		if (str[i])
			ft_putchar_fd(' ' , out);
	}
}
int	my_echo(t_main *tools, t_cmd *simple_cmd)
{
	int		i;
	int		j;
	bool	n_option;

	i = 1;
	n_option = false;
	(void) tools;
	while (simple_cmd->cmd_args[i] && simple_cmd->cmd_args[i][0] == '-'
		&& simple_cmd->cmd_args[i][1] == 'n')
	{
		j = 1;
		while (simple_cmd->cmd_args[i][j] == 'n')
			j++;
		if (simple_cmd->cmd_args[i][j] == '\0')
			n_option = true;
		else
			break ;
		i++;
	}
	print_lines(i, simple_cmd->cmd_args, STDOUT_FILENO);
	if (n_option == false)
		ft_putchar_fd('\n', 1);
	return (0);
}