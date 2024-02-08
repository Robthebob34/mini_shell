/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <mgigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:54:22 by rheck             #+#    #+#             */
/*   Updated: 2024/02/08 12:21:16 by mgigot           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/mini.h"
// permet de trouver une ligne precise dans 
// les variables d' environnement 
// identique a la fonction getenv()
char	*find_env_variable(char **envp, char *to_find)
{
	int		cond;
	int		i;

	i = 0;
	cond = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], to_find, ft_strlen(to_find)) == 0)
			cond = 1;
		i++;
	}
	while (ft_strncmp(to_find, *envp, ft_strlen(to_find)))
		envp++;
	return (*envp + ft_strlen(to_find) + 1); // peut etre nescessaire de renvoye une chaine malloc 
}

// permet de recupere les chemins absolu vers les fichiers des commandes (exemple : /bin/pwd)
char	*get_cmd(char **path, t_main *data_base, t_cmd *just_a_try)
{
	char	*tmp;
	char	*command;
	int i = 0;
	if((just_a_try->builtin = look_for_builtin(data_base->cmds_list->cmd_name)))
	{
		just_a_try->builtin(data_base, just_a_try);
		return (NULL);
	}
	if(access(data_base->cmds_list->cmd_name, X_OK) == 0) // attention un utilisateur peut changer le nom d'executable pour lui donner le nom d' une commande 
		return(data_base->cmds_list->cmd_name);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		command = ft_strjoin(tmp, data_base->cmds_list->cmd_name);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return ("command not found\n"); // code d'erreur 127
}
int	prepare_execute(t_main *data_base)
{
	my_global.in_cmd = 1;
	if (data_base->pipes == 0)
		single_cmd(data_base->cmds_list, data_base);
	else
	{
		printf("nombre de processus = %i\n", data_base->pipes + 2);
		data_base->pid = ft_calloc(sizeof(int), data_base->pipes + 2);
		if (!data_base->pid)
			return (1); // ft_error();
		execute(data_base, data_base->cmds_list);
	}
	my_global.in_cmd = 0;
	return (0);
}
int	execute(t_main *data_base, t_cmd *cmd_list)
{
	int		end[2];
	int		i;
	int		fd_in;

	fd_in = STDIN_FILENO;
	i = 0;
	while (cmd_list[i].cmd_name != NULL)
	{
		printf("un dos tress\n");
		if (cmd_list[i].cmd_name[0] == '|')
			i++;
		if (cmd_list[i + 1].cmd_name)
		{
			printf("cmd name exec = %s\n", cmd_list[i].cmd_name);
			pipe(end);
		}
		if(send_heredoc(data_base, cmd_list))
			return(1);
		ft_fork(data_base, end, fd_in, cmd_list + i);
		close(end[1]);
		if (i > 0)
			close(fd_in);
		fd_in = check_fd_heredoc(data_base, end, cmd_list[i]);
		i++;
	}
	pipe_wait(data_base->pid, data_base->pipes);
	return (0);
}