#include "../../inc/mini.h"
int	ft_fork(t_main *data_base, int end[2], int fd_in, t_cmd *cmd)
{
	printf("fork index = %d\n", data_base->fork_index);
	data_base->pid[data_base->fork_index] = fork();
	if (data_base->pid[data_base->fork_index] < 0)
		ft_error(5, data_base);
	if (data_base->pid[data_base->fork_index] == 0)
		dup_cmd(cmd, data_base, end, fd_in);
	data_base->fork_index++;
	return (0);
}

int	pipe_wait(int *pid, int amount)
{
	int	i;
	int	status;

	i = 0;
	printf("je suis ICI\n");
	while (i < amount)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
	if (WIFEXITED(status))
		my_global.last_err_code = WEXITSTATUS(status);
	return (0);
}
void	dup_cmd(t_cmd *cmd, t_main *tools, int end[2], int fd_in)
{
	static int i = 0;
	printf("my statique i = %d\n", i);
	i++;
	printf("tools fork index = %d\n", tools->fork_index);
	printf("my fd_in = %d \n", fd_in);
	if (tools->fork_index > 0 && (dup2(fd_in, 0) < 0))
	{
		ft_error(4, tools);
	}
	close(end[0]);
	if (tools->fork_index < tools->pipes && dup2(end[1], 1) < 0)
	{
		ft_error(4, tools);
	}
	close(end[1]);
	if (tools->fork_index > 0)
		close(fd_in);
	handle_cmd(cmd, tools);
}
void	handle_cmd(t_cmd *cmd, t_main *tools)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->redirection != NULL)
	{
		printf("je suis la cmd = %s\n", cmd->cmd_name);
		if (check_redirections(cmd))
			exit(1);
	}
	if ((cmd->builtin = look_for_builtin(tools->cmds_list->cmd_name)))
	{
		exit_code = cmd->builtin(tools, cmd);
		exit(exit_code);
	}
	else if (cmd->cmd_args[0][0] != '\0')
		exit_code = find_cmd(cmd, tools);
	exit(exit_code);
}
int	find_cmd(t_cmd *cmd, t_main *tools)
{
	int		i;
	char	**path_exec;
	char 	*tmp;
	char	*mycmd;

	i = 0;
	//write(1, cmd[0].cmd_name, ft_strlen(cmd[0].cmd_name));
	//write(1, "\n", 1);
	path_exec = ft_split(tools->env_path, ':'); // a changer avec notre variable d'environnement
	if (!access(cmd[0].cmd_name, F_OK))
		execve(cmd[0].cmd_name, cmd[0].cmd_args, tools->env_tab);
	while (path_exec[i])
	{
		tmp = ft_strjoin(path_exec[i], "/");
		mycmd = ft_strjoin(tmp, cmd[0].cmd_name);
		free(tmp);
		if (!access(mycmd, F_OK))
		{
			execve(mycmd, cmd[0].cmd_args, tools->env_tab);
		}
		free(mycmd);
		i++;
	}
	return (cmd_not_found(cmd[0].cmd_name));
}