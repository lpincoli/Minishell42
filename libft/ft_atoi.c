/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocastell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 22:37:42 by ocastell          #+#    #+#             */
/*   Updated: 2022/10/08 22:51:08 by ocastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	sum;
	int	i;

	i = 0;
	sign = 1;
	sum = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		sum *= 10;
		sum += nptr[i] - 48;
		i++;
	}
	return (sum * sign);
}
/*#include<stdio.h>

int main()
{
	printf("%d\n", ft_atoi("-2445678"));
}*/
