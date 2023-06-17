/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocastell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 19:57:23 by ocastell          #+#    #+#             */
/*   Updated: 2022/10/08 20:10:16 by ocastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;

	i = -1;
	if (*little == '\0')
		return ((char *)big);
	while (big[++i] != '\0' && i <= len)
	{
		j = 0;
		if (big[i] == little[j])
		{
			while (big[i] == little[j] && little[j] != '\0' && i <= len)
			{
				i++;
				j++;
			}
		}
		if (little[j] == '\0' && i <= len)
		{
			i -= j;
			return ((char *)&big[i]);
		}
		i -= j;
	}
	return (NULL);
}
