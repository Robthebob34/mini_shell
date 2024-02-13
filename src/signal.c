/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <mgigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:16:50 by rheck             #+#    #+#             */
/*   Updated: 2024/02/13 11:03:05 by mgigot           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/mini.h"

int event(void)
{
    return(0);
}
void	signal_handler(int sig)
{
	if (!my_global.in_heredoc)
		ft_putstr_fd("\n", 2);
	if (my_global.in_cmd)
	{
		my_global.stop_heredoc = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void    init_signal(void)
{
    rl_event_hook = event;
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, SIG_IGN);
}
