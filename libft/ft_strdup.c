/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocastell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 01:57:09 by ocastell          #+#    #+#             */
/*   Updated: 2022/10/11 16:16:26 by ocastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	char	*d;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * ft_strlen(src) +1);
	d = (char *)src;
	if (!dest)
		return (NULL);
	while (d[i])
	{
		dest[i] = d[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int	main(int argc, char*argv[])
{
	if (argc == 2)
		printf("%s\n", ft_strdup(argv[1]));
}*/
