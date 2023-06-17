/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_killer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:41:03 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:41:04 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_sp_kl_init(char *line, t_norm *n)
{
	n->flg = 0;
	n->j = 0;
	n->i = 0;
	while (line[n->i] == ' ' || line[n->i] == '\t')
		n->i += 1;
	return (ft_calloc(sizeof(char), (ft_strlen(line) + 1)));
}

void	ft_sp_kl_f(char *line, t_norm *n)
{
	if (line[n->i] == ' ' || line[n->i] == '\t')
		n->flg = 1;
	if ((line[n->i] == 34 || line[n->i] == 39)
		&& ft_strchr(&line[n->i + 1], line[n->i]) != NULL)
		n->flg += 2;
}

void	ft_sp_kl_lg(char *line, char *str, t_norm *n)
{
	char	c;

	if (n->flg == 2 || n->flg == 3)
	{
		if (n->flg == 3)
			str[n->j++] = ' ';
		c = line[n->i++];
		str[n->j++] = c;
		while (line[n->i] != c)
			str[n->j++] = line[n->i++];
		str[n->j++] = c;
	}
}

char	*space_killer(char *line, t_norm *n)
{
	char	*str;

	str = ft_sp_kl_init(line, n);
	while (line[n->i])
	{
		ft_sp_kl_f(line, n);
		if (!(line[n->i] == ' ' || line[n->i] == '\t'))
		{
			if (n->flg == 1)
				str[n->j++] = ' ';
			ft_sp_kl_lg(line, str, n);
			if (n->flg != 2 && n->flg != 3)
				str[n->j++] = line[n->i];
			n->flg = 0;
		}
		n->i++;
	}
	free(line);
	return (str);
}
