#include "../../inc/mini.h"
int	is_digit(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(ft_isdigit(str[i]) == 0)
			return(1);
		i++;
	}
	return(0);
}
int choose_exit_code(t_main *tools, t_cmd *simple_cmd)
{
	(void)simple_cmd;
	(void)tools;
	int	exit_code;

	if (!simple_cmd->cmd_args[1])
		exit_code = 0;
	else if (is_digit(simple_cmd->cmd_args[1]) == 0)
		exit_code = ft_atoi(simple_cmd->cmd_args[1]);
	else
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(simple_cmd->cmd_args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_code = 255;
	}
	exit(exit_code);
	return(0);
}
int	my_exit(t_main *tools, t_cmd *simple_cmd)
{
	ft_putendl_fd("exit", 2);
	if (simple_cmd->cmd_args[1] && simple_cmd->cmd_args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	choose_exit_code(tools, simple_cmd);
	return (0);
}
