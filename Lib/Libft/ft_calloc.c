/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:27:37 by mgigot            #+#    #+#             */
/*   Updated: 2023/04/10 11:56:21 by mgigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*data;
	size_t	ptr;

	ptr = count * size;
	if (count && ptr / count != size)
		return (NULL);
	data = malloc(count * size);
	if (data == 0)
		return (NULL);
	ft_bzero(data, size * count);
	return (data);
}
