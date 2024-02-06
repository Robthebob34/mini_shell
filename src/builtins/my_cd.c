#include "../../inc/mini.h"
int	change_path(t_main *tools)
{
	char *tmp;

	tmp = ft_strdup(tools->pwd);
	free(tools->old_pwd);
	tools->old_pwd = tmp;
	change_env_tab(tools->old_pwd, tools, "OLDPWD=");
	free(tools->pwd);
	tools->pwd = getcwd(NULL, sizeof(NULL));
	change_env_tab(tools->pwd, tools, "PWD=");
	return(0);
}
void	change_env_tab(char *new_pos, t_main *tools, const char *to_find)
{
	int	i;
	char	*str;

	i = 0;
	while(ft_strncmp(tools->env_tab[i], to_find, ft_strlen(to_find)) != 0)
	{
		i++;
	}
	free(tools->env_tab[i]);
	str = ft_strjoin(to_find, new_pos);
	tools->env_tab[i] = str;
	return;
}
int	specific_path(t_main *tools, char *str)
{
	char	*tmp;
	int		ret;

	(void)tools;
	tmp = getenv(str);
	ret = chdir(tmp);
	//free(tmp);
	if(ret != 0)
	{
		ft_putstr_fd(str, 2);
		free(str); // verifier l'utilite de free une variable hardcoder
		ft_putendl_fd(" not set", 2);
	}
	return(ret);
}
int	back_on_path(t_main *tools, t_cmd *simple_cmd)
{
	char 	*tmp;
	int		ret;
	int		i;
	//attention au cas ou l'utilisateur se trouve deja a la racine de l'orgdinateur ('/')
	(void)simple_cmd;
	i = ft_strlen(tools->pwd);
	while(tools->pwd[i] != '/')
		i--;
	tmp = malloc(sizeof(char) * i + 1);
	ft_memcpy(tmp, tools->pwd, i);
	tmp[i] = '\0';
	ret = chdir(tmp);
	if(ret != 0)
		printf("fail parsing back on path\n");
	return(ret);
}
int my_cd(t_main *tools, t_cmd *simple_cmd)
{
	int	ret;

	if(!simple_cmd->cmd_args[1])
	{
		ret = specific_path(tools, "HOME=");
	}
	else if (ft_strncmp(simple_cmd->cmd_args[1], "..", 2) == 0)
	{
		ret = back_on_path(tools, simple_cmd);
	}
	else
	{	
		if(((ret) = chdir(simple_cmd->cmd_args[1])))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(simple_cmd->cmd_args[1], 2);
			perror(" ");
			return(1);
		}
	}
    change_path(tools);
	return(0);
}