#include "../inc/mini.h"
int event(void)
{
    my_global.last_err_code = 130;
    return(my_global.last_err_code);
}
void    signal_handler(int sig)
{
	(void) sig;

    rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void    init_signal(void)
{
    rl_event_hook = event;
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, SIG_IGN);
}
