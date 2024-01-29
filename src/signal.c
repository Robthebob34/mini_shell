/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:16:50 by rheck             #+#    #+#             */
/*   Updated: 2024/01/16 15:33:02 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mini.h"

int event(void)
{
    my_global.last_err_code = 130;
    return(my_global.last_err_code);
}
void    signal_handler(int sig)
{
	(void) sig;

	rl_replace_line("\n", 0);
    rl_redisplay();
	rl_redisplay();
}
void    init_signal(void)
{
    rl_event_hook = event;
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, SIG_IGN);
}
