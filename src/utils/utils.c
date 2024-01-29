/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheck <rheck@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:54:46 by rheck             #+#    #+#             */
/*   Updated: 2023/12/21 14:54:48 by rheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini.h"

char	**ft_arraydup(char **tab)
{
	char	**new_array;
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	new_array = ft_calloc(sizeof(char *), i + 1);
	if (!new_array)
		return (NULL);
	i = 0;
	while (tab[i] != NULL)
	{
		new_array[i] = ft_strdup(tab[i]);
		if (new_array[i] == NULL)
		{
			free_arr(new_array);
			return (NULL);
		}
		i++;
	}
	return (new_array);
}

void	free_arr(char **split_arr)
{
	int	i;

	i = 0;
	while (split_arr[i])
	{
		free(split_arr[i]);
		i++;
	}
	free(split_arr);
}
