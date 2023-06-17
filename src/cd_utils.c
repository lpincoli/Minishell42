/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   emaspazzino.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:39:55 by lpincoli          #+#    #+#             */
/*   Updated: 2023/06/17 11:50:18 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_remove_slash(t_env *sp)
{
	int		i;

	i = ft_strlen(sp->tk->next->str) - 1;
	sp->tk->next->str[i] = '\0';
}

void	ft_add_slash(t_path *pwd)
{
	int		i;

	i = ft_strlen(pwd->path);
	pwd->path[i] = '/';
	pwd->path[i] = '\0';
}

void	ft_save_oldpath(t_path *pwd)
{
	if (pwd->old_path)
		free(pwd->old_path);
	pwd->old_path = ft_strdup(pwd->path);
}

void	replace_with_tilde(char *stringa, int x)
{
	int		len;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(stringa) + 1));
	ft_strcpy(str, stringa);
	len = ft_strlen(str);
	ft_memmove(str + 1, str + x, len - x + 1);
	str[0] = '~';
	printf("%s\n", str);
	free(str);
}

void	ft_change_env(t_env *sp, t_path *pwd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (sp->env[i])
	{
		if (!ft_strncmp(sp->env[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", pwd->path);
			free(sp->env[i]);
			sp->env[i] = ft_strdup(tmp);
			free(tmp);
		}
		else if (!ft_strncmp(sp->env[i], "OLDPWD=", 7) && pwd->old_path)
		{
			tmp = ft_strjoin("OLDPWD=", pwd->old_path);
			free(sp->env[i]);
			sp->env[i] = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
}
