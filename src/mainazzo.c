/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainazzo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:40 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:40:40 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_subenv(char *sub, t_env *sp, int u)
{
	int	i;

	i = 0;
	while (sp->env[i])
	{
		if (!ft_strncmp(sub, sp->env[i], u))
		{
			free(sp->env[i]);
			sp->env[i] = ft_strdup(sub);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_del_env(char *sub, t_env *sp, int u)
{
	int	i;
	int	flg;

	i = 0;
	flg = 1;
	while (sp->env[i])
	{
		if (!ft_strncmp(sub, sp->env[i], u))
		{
			free(sp->env[i]);
			flg = 0;
		}
		if (flg)
			i++;
		else
		{
			sp->env[i] = sp->env[i + 1];
			i++;
		}
	}
	sp->env[i] = NULL;
}

int	ft_get_equal_index(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		i++;
	}
	if (str[i] == '=')
		return (i);
	else
		return (-1);
}

char	*ft_get_envious(char *var, t_env *sp)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(var);
	while (sp->env[i])
	{
		if (!ft_strncmp(var, sp->env[i], j))
		{
			if (sp->env[i][j] == '=')
				return (&sp->env[i][j + 1]);
		}
		i++;
	}
	return (NULL);
}

void	ft_aggiungi_fname(char *dest, char *src)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (dest[i] != '\0')
		i++;
	while (src[k])
	{
		dest[i] = src[k];
		i++;
		k++;
	}
	dest[i] = '\0';
}
