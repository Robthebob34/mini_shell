#include "../inc/mini.h"
int	change_path(t_main *tools)
{
	char *tmp;

	tmp = ft_strdup(tools->pwd);
	free(tools->old_pwd);
	tools->old_pwd = tmp;
	free(tools->pwd);
	tools->pwd = getcwd(NULL, sizeof(NULL));
	return(0);
}
int	specific_path(t_main *tools, char *str)
{
	char	*tmp;
	int		ret;

	tmp = find_env_variable(tools->env_tab, str);
	ret = chdir(tmp);
	free(tmp);
	if(ret != 0)
	{
		ft_putstr_fd(str, 2);
		free(str); // verifier l'utilite de free une variable hardcoder
		ft_putendl_fd(" not set", 2);
	}
	return(ret);
}
int my_cd(t_main *tools, t_cmd *simple_cmd)
{
	int	ret;

	// segfault a cause de cmd_args non initialiser 
	if(!simple_cmd->cmd_args[1])
		ret = specific_path(tools, "HOME=");
	// else if (volonter de l'utilisateur de revenir a old_pwd)
	else
	{	
		if(((ret) = chdir(simple_cmd->cmd_args[1])))
		{
			ft_putstr_fd("minishell: ", 2);
			//ft_putstr_fd(simple_cmd->cmd_args[1], 2);
			perror(" ");
			return(1);
		}
	}
    change_path(tools);
	return(0);
}