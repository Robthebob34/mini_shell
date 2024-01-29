/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:13:14 by mgigot            #+#    #+#             */
/*   Updated: 2023/05/04 11:35:30 by mgigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char *str)
{
	long	i;
	long	j;
	long	count;

	i = 0;
	j = 0;
	count = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-')
		count++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		j = j * 10 + str[i] - 48;
		if (j < 0 && count == 0)
			return (-1);
		if (j < 0 && count == 1)
			return (0);
		i++;
	}
	if (count % 2 == 1)
		j = -j;
	return ((int)j);
}
