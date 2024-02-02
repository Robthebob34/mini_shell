#include "../../inc/mini.h"
void	single_cmd(t_cmd *cmd, t_main *tools)
{
	int	pid;
	int	status;

	if (cmd->builtin = look_for_builtin(cmd->cmd_name))
	{
		my_global.last_err_code = cmd->builtin(tools, cmd);
		return ;
	}
	send_heredoc(tools, cmd);
	pid = fork();
	if (pid < 0)
		return; // erreur creation des processus 
	if (pid == 0)
		handle_cmd(cmd, tools);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		my_global.last_err_code = WEXITSTATUS(status);
}