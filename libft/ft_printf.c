/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocastell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:35:32 by ocastell          #+#    #+#             */
/*   Updated: 2022/10/17 10:35:55 by ocastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check(const char **str, va_list args, int *count)
{
	char	*stringa;

	*str += 1;
	if (**str == 'c')
		ft_putchars_fd((char)va_arg(args, int), 1, count);
	else if (**str == 's')
	{
		stringa = va_arg(args, char *);
		ft_print_s(stringa, 1, count);
	}
	else if (**str == 'p')
		ft_print_p(va_arg(args, uintptr_t), 1, count);
	else if (**str == 'd' || **str == 'i')
		ft_putnbrs_fd(va_arg(args, int), 1, count);
	else if (**str == 'u')
		ft_putnbru_fd(va_arg(args, unsigned int), 1, count);
	else if (**str == 'x')
		ft_putnbr_base_fd(va_arg(args, unsigned int), 1, count);
	else if (**str == 'X')
		ft_putnbr_xup(va_arg(args, unsigned int), 1, count);
	else if (**str == '%')
		ft_putchars_fd('%', 1, count);
	*str += 1;
	return (*count);
}

int	ft_printfinternal(const char *str, va_list args, int *count)
{
	while (*str)
	{
		if (*str == '%')
			ft_check(&str, args, count);
		else
		{
			ft_putchars_fd(*str, 1, count);
			str++;
		}
	}
	return (*count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;

	count = 0;
	va_start(args, str);
	if (!str)
		return (0);
	ft_printfinternal(str, args, &count);
	va_end(args);
	return (count);
}
