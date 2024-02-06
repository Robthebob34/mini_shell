#include "../../inc/mini.h"
void	single_cmd(t_cmd *cmd, t_main *tools)
{
	int	pid;
	int	status;

	if ((cmd->builtin = look_for_builtin(cmd->cmd_name)))
	{
		my_global.last_err_code = cmd->builtin(tools, cmd);
		return ;
	}
	send_heredoc(tools, cmd);
	pid = fork();
	if (pid < 0)
		return; // erreur creation des processus 
	if (pid == 0)
		handle_cmd(cmd, tools, 0);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		my_global.last_err_code = WEXITSTATUS(status);
}
int	check_fd_heredoc(t_main *tools, int end[2], t_cmd cmd) // attention dereference du pointeur 
{
	int	fd_in;

	if (tools->heredoc)
	{
		close(end[0]);
		fd_in = open(cmd.redirection_name, O_RDONLY);
	}
	else
		fd_in = end[0];
	return (fd_in);
}