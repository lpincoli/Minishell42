/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocastell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:48:36 by ocastell          #+#    #+#             */
/*   Updated: 2022/10/08 17:49:51 by ocastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*i;

	i = 0;
	while (*s)
	{
		if (*s == (unsigned char)c)
			i = (char *)s;
		s++;
	}
	if (i)
		return (i);
	if (c == '\0')
		return ((char *)s);
	return (0);
}
/*
#include <stdio.h>
int main()
{
	char a[] = "acd";
	printf("%s ", ft_strrchr(a, 'b'));
}
*/