/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slashyer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:41:01 by lpincoli          #+#    #+#             */
/*   Updated: 2023/06/17 11:08:10 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_slashyer_if1(char *str, char *line, t_norm *n)
{
	if (str[n->i] == '\\' && str[n->i + 1] == 'a')
	{
		n->i += 2;
		line[n->j++] = 7;
		n->flg = 1;
	}
	if (str[n->i] == '\\' && str[n->i + 1] == 'b')
	{
		n->i += 2;
		line[n->j++] = 8;
		n->flg = 1;
	}
	if (str[n->i] == '\\' && str[n->i + 1] == 't')
	{
		n->i += 2;
		line[n->j++] = 9;
		n->flg = 1;
	}
	if (str[n->i] == '\\' && str[n->i +1] == 'n')
	{
		n->i += 2;
		line[n->j++] = 10;
		n->flg = 1;
	}
}

void	ft_slashyer_if2(char *str, char *line, t_norm *n)
{
	if (str[n->i] == '\\' && str[n->i +1] == 'v')
	{
		n->i += 2;
		line[n->j++] = 11;
		n->flg = 1;
	}	
	if (str[n->i] == '\\' && str[n->i +1] == 'f')
	{
		n->i += 2;
		line[n->j++] = 12;
		n->flg = 1;
	}	
	if (str[n->i] == '\\' && str[n->i +1] == 'r')
	{
		n->i += 2;
		line[n->j++] = 13;
		n->flg = 1;
	}
	if (!n->flg)
		line[n->j++] = str[n->i++];
}

int	ft_slashyer_while(char *str, char *line, t_norm *n)
{
	char	c;

	if (str[n->i] != 34 && str[n->i] != 39
		&& str[n->i] != '\\' && str[n->i])
		line[n->j++] = str[n->i++];
	else if (str[n->i] == '\\' && (str[n->i] != 34 && str[n->i] != 39))
		n->i++;
	else if ((str[n->i] == 34 || str[n->i] == 39)
		&& ft_strchr(&str[n->i + 1], str[n->i]))
	{
		c = str[n->i];
		line[n->j++] = str[n->i++];
		while (str[n->i] != c)
		{
			ft_slashyer_if1(str, line, n);
			ft_slashyer_if2(str, line, n);
		}
		line[n->j++] = str[n->i++];
	}
	else if ((str[n->i] == 34 || str[n->i] == 39)
		&& !ft_strchr(&str[n->i + 1], str[n->i]))
		return (1);
	return (0);
}

char	*ft_slashyer(char *str, t_norm *n)
{
	char	*line;

	ft_reset_norm(n);
	if (!str)
		return (NULL);
	line = ft_calloc((ft_strlen(str) + 1), sizeof(char));
	while (str[n->i])
	{
		if (ft_slashyer_while(str, line, n))
		{	
			n->flg = 1;
			printf("\nquote aperte!\n");
			free(str);
			free(line);
			return (NULL);
		}
	}
	free(str);
	return (line);
}
