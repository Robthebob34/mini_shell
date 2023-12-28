#include "../inc/mini.h"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:54:22 by rheck             #+#    #+#             */
/*   Updated: 2023/12/21 14:54:25 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"
// permet de trouver une ligne precise dans 
// les variables d' environnement 
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
	return (*envp + ft_strlen(to_find) + 1);
}
// permet de recupere les chemins absolu vers les fichiers des commandes (exemple : /bin/pwd)
char	*get_cmd(char **path, t_main *data_base, t_cmd *just_a_try)
{
	char	*tmp;
	char	*command;
	int i = 0;
	// mettre une premiere tentative d'acces pour verifier que l'entre utilisateur ne soit pas deja un pathing absolu
	if (ft_strncmp(data_base->my_prompt_line, "history", 7) == 0)
	{
		print_history(data_base);
		return(0);
	}
	if((just_a_try->builtin = look_for_builtin(data_base->my_prompt_line)))
	{
		just_a_try->builtin(data_base, just_a_try);
		return (0);
	}
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		command = ft_strjoin(tmp, data_base->my_prompt_line);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		i++;
	}
	return ("command not found\n"); // code d'erreur 127
}
