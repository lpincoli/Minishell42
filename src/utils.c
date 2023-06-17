/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:41:05 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:41:10 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Suddivide la linea in tokens */

char	*ft_strcpy(char *dest, const char *src)
{
	char	*dest_start;

	dest_start = dest;
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (dest_start);
}

int	ft_strcmp(char *s1, const char *s2)
{
	int				i;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	i = 0;
	while ((p1[i] != '\0' || p2[i] != '\0'))
	{
		if (p1[i] == p2[i])
			i++;
		else if (p1[i] > p2[i])
			return (1);
		else if (p1[i] < p2[i])
			return (-1);
	}
	return (0);
}

void	ft_is_variable_logic(char *line, t_norm *n)
{
	while (n->i < n->j)
	{
		if (line[n->i] == 39 || line[n->i] == 34)
			n->flg = 0;
		if (line[n->i] == ' ' || line[n->i] == '\t')
			n->flg = 0;
		n->i++;
	}
	n->i = 0;
}

int	ft_is_variable_while(char *line, t_norm *n)
{
	if ((line[n->i] >= '0' && line[n->i] <= '9'))
		n->flg = 1;
	else if ((line[n->i] >= 'a' && line[n->i] <= 'z'))
		n->flg = 1;
	else if ((line[n->i] >= 'A' && line[n->i] <= 'Z'))
		n->flg = 1;
	else if (line[n->i] == '_')
		n->flg = 1;
	else
	{
		n->flg = 0;
		return (1);
	}
	n->i++;
	return (0);
}

int	ft_is_variable(char *line, t_norm *n)
{
	ft_reset_norm(n);
	if (line[0] == '_' && line[1] == '=')
		return (0);
	if (ft_strchr(line, '='))
	{
		n->j = (int)(ft_strchr(line, '=') - line);
		if (line[n->j + 1] == ' ' || line[n->j + 1] == '\t')
			return (0);
		else if (line[n->j + 1] == '\0')
			return (1);
		ft_is_variable_logic(line, n);
		while (line[n->i] != '=')
		{
			if (ft_is_variable_while(line, n))
				break ;
		}
	}
	return (n->flg);
}
