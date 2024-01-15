#include "../inc/mini.h"

int	my_env(t_main *data_base, t_cmd *simple_cmd)
{
	(void)simple_cmd;
	int	i;

	i = 0;
	while(data_base->env_tab[i] != NULL)
	{
		ft_putendl_fd(data_base->env_tab[i], 1);
		i++;
	}
	return(0);
}