/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_more_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:39:58 by lpincoli          #+#    #+#             */
/*   Updated: 2023/06/17 11:51:45 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

long	ft_atol(char *str)
{
	int		sign;
	long	nmb;

	sign = 1;
	nmb = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nmb *= 10;
		nmb += (*str - '0');
		str++;
	}
	return (nmb *= sign);
}

int	ft_check_num(char *str, t_env *sp)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
		{
			write(2, " numeric argument required\n", 27);
			sp->exit = 2;
			return (0);
		}
	}
	return (1);
}

char	*ft_tokenizer(char *str)
{
	static char	*last_token = NULL;
	char		*token;

	token = last_token;
	if (str != NULL)
	{
		last_token = str;
		token = last_token;
	}
	if (last_token)
		last_token = ft_strrchr(last_token, 47);
	if (last_token)
	{
		*last_token = '\0';
		last_token++;
	}
	return (token);
}

int	ft_strlen_dol(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strcat(char *dest, char *src)
{
	char	*new;
	char	*d;
	char	*s;
	int		len;
	int		i;

	len = ft_strlen(src);
	i = ft_strlen(dest);
	new = malloc(sizeof(char) *(len + i + 1));
	d = dest;
	s = new;
	while (*d != '\0')
		*s++ = *d++;
	d = src;
	while (*d != '\0')
		*s++ = *d++;
	*s = '\0';
	free(dest);
	return (new);
}
