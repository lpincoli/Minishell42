/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:22 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:40:23 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sub_var(char *var, t_env *sp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i++] == '=')
			break ;
	}
	while (sp->vars[j])
	{
		if (!ft_strncmp(sp->vars[j], var, (i - 1)))
		{
			free(sp->vars[j]);
			sp->vars[j] = ft_strdup(var);
			return ;
		}
		j++;
	}
}

int	ft_var_is_saved(char *var, t_env *sp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (var[i] != '=' && var[i])
		i++;
	if (!sp->vars)
		return (0);
	while (sp->vars[j])
	{
		if (!ft_strncmp(var, sp->vars[j++], (i)))
			return (1);
	}
	return (0);
}

void	ft_save_var(char *var, t_env *sp)
{
	int	i;

	i = 0;
	if (!var)
		return ;
	if (ft_var_is_saved(var, sp))
	{
		ft_sub_var(var, sp);
		return ;
	}
	while (sp->vars[i] != NULL)
		i++;
	sp->vars[i] = ft_strdup(var);
	sp->vars[i + 1] = NULL;
}

void	ft_save_vari1(char *vari1, t_env *sp)
{
	int	i;
	int	j;

	i = ft_strlen(vari1);
	j = 0;
	while (sp->vars[j])
	{
		if (!ft_strncmp(vari1, sp->vars[j], i))
			return ;
		j++;
	}
	sp->vars[j] = ft_strdup(vari1);
	sp->vars[j + 1] = NULL;
}

int	ft_is_vari1(char *vari1, t_env *sp)
{
	int	j;

	j = 0;
	while (sp->vars[j])
	{
		if (!ft_strcmp(vari1, sp->vars[j++]))
			return (1);
	}
	return (0);
}
