/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocastell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 22:54:13 by ocastell          #+#    #+#             */
/*   Updated: 2022/10/08 22:55:44 by ocastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	size_t			i;
	size_t			l;

	i = 0;
	l = 0;
	ptr = (char *)s;
	ptr = (char *)malloc((len + 1) * sizeof(*ptr));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		if (i >= start && l < len)
		{
			ptr[l] = s[i];
			l++;
		}
		i++;
	}
	ptr[l] = 0;
	return (ptr);
}
