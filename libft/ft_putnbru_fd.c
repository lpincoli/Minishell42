/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbru_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocastell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 21:21:56 by ocastell          #+#    #+#             */
/*   Updated: 2022/10/17 21:22:49 by ocastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbru_fd(unsigned int nb, int fd, int *count)
{
	long long unsigned	n;

	n = (long long unsigned)nb;
	if (n >= 10)
		ft_putnbrs_fd(n / 10, fd, count);
	ft_putchars_fd((char)(n % 10 + 48), fd, count);
}
