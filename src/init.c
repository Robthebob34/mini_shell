/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <mgigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:07:12 by rheck             #+#    #+#             */
/*   Updated: 2024/02/06 12:45:23 by mgigot           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/mini.h"

int init_shell(char **env, t_main *data_base)
{
    char *str;

    data_base->env_tab = ft_arraydup(env);
    str = getenv("PWD");
    data_base->pwd = ft_strdup(str);
    str = getenv("OLWPWD");
    data_base->old_pwd = ft_strdup(str);
    free(str);
    data_base->index = 0;
    data_base->fork_index = 0;
    data_base->redirection = 0;
    data_base->heredoc = 0;
    data_base->pipes = 0;
    return (0);
}