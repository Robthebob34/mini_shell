/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <mgigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:19:43 by mgigot            #+#    #+#             */
/*   Updated: 2024/02/06 10:34:17 by mgigot           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "libft.h"
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if(!str1 || !str2)
		return (1);
	if (n == 0)
		return (0);
	while (str1[i] != '\0' && str2[i] != '\0' && n - 1 > 0)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
		n--;
	}
	return (str1[i] - str2[i]);
}
