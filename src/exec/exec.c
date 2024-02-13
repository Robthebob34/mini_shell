/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <mgigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:54:22 by rheck             #+#    #+#             */
/*   Updated: 2024/02/13 11:58:51 by mgigot           ###   ########.fr       */
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

int	prepare_execute(t_main *data_base)
{
	my_global.in_cmd = 1;
	if (data_base->pipes == 0)
		single_cmd(data_base->cmds_list, data_base);
	else
	{
		printf("nombre de processus = %i\n", data_base->pipes + 1);
		data_base->pid = ft_calloc(sizeof(int), data_base->pipes + 1);
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