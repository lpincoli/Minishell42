/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_realloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:20 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:40:21 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	realloc_env(t_env *sp, char *str)
{
	int		c;
	int		i;
	char	**new;
	char	**p;

	c = 0;
	while (sp->env[c++])
		continue ;
	new = malloc(sizeof(char *) * (c + 1));
	if (!sp->env)
		return ;
	new = ft_envtonew(sp, new, str);
	if (!new)
		return ;
	i = 0;
	p = sp->env;
	while (p[i] != NULL)
		free(p[i++]);
	free(p);
	sp->env = new;
	return ;
}
