/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <mgigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:26:54 by rheck             #+#    #+#             */
/*   Updated: 2024/02/13 11:56:53 by mgigot           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../inc/mini.h"

char	**whileloop_del_var(char **arr, char **rtn, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		if (!(ft_strncmp(arr[i], str, equal_sign(arr[i]) - 1) == 0
				&& str[equal_sign(arr[i]) - 1] == '\0' // attention ligne peut segfault
				&& arr[i][ft_strlen(str)] == '='))
		{
			rtn[j] = ft_strdup(arr[i]);
			if (rtn[j] == NULL)
			{
				free_arr(rtn);
				return (rtn);
			}
			j++;
		}	
		i++;
	}
	return (rtn);
}

char	**del_var(char **arr, char *str)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	rtn = whileloop_del_var(arr, rtn, str);
	return (rtn);
}
int	unset_error(t_cmd *simple_cmd)
{
	int		i;

	i = 0;
	if (!simple_cmd->cmd_args[1])
	{
		ft_putendl_fd("minishell: unset: not enough arguments", 2);
		return (1);
	}
	while (simple_cmd->cmd_args[1][i])
	{
		if (simple_cmd->cmd_args[1][i++] == '/')
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(simple_cmd->cmd_args[1], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (1);
		}
	}
	if (equal_sign(simple_cmd->cmd_args[1]) != 0)
	{
		ft_putendl_fd("minishell: unset: not a valid identifier",
			2);
		return (1);
	}
	return (0);
}
int	my_unset(t_main *tools, t_cmd *simple_cmd)
{
	char	**tmp;

	if (unset_error(simple_cmd) == 1)
		return (1);
	else
	{
		tmp = del_var(tools->env_tab, simple_cmd->cmd_args[1]);
		free_arr(tools->env_tab);
		tools->env_tab = tmp;
	}
	return (0);
}