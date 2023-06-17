/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:16 by lpincoli          #+#    #+#             */
/*   Updated: 2023/06/17 11:50:09 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_stocheck(t_token *stk)
{
	if (stk->type == '|' || stk->type == '>'
		|| stk->type == '<' || stk->type == '+' || stk->type == '-')
		return (1);
	return (0);
}

void	ft_cd(t_env *sp, t_path *pwd)
{
	if (sp->tk->next && sp->tk->next->next)
	{
		if (!ft_stocheck(sp->tk->next->next))
		{
			write(2, "cd has too many arguments\n", 26);
			sp->exit = 1;
			return ;
		}
	}
	ft_save_oldpath(pwd);
	if (!sp->tk->next || !ft_strcmp(sp->tk->next->str, "~"))
		ft_change_path (sp, pwd, ft_get_envious("HOME", sp));
	else if (!ft_strcmp(sp->tk->next->str, "--"))
		ft_change_path (sp, pwd, sp->o_home);
	else if ((!ft_strcmp(sp->tk->next->str, "..")))
		ft_change_path (sp, pwd, sp->tk->next->str);
	else if ((!ft_strcmp(sp->tk->next->str, "-")))
		ft_make_line(sp, pwd);
	else if ((!ft_strcmp(sp->tk->next->str, "/")))
		ft_change_path(sp, pwd, "/");
	else if (ft_strlen(sp->tk->next->str) < PATH_MAX)
		ft_make_path(sp, pwd);
}

void	ft_make_line(t_env *sp, t_path *pwd)
{
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(ft_get_envious("HOME", sp));
	if (!strncmp(pwd->path, ft_get_envious("HOME", sp), j))
		i = 1;
	ft_change_path(sp, pwd, ft_get_envious("OLDPWD", sp));
	if (i == 1)
	{
		if (!ft_strncmp(pwd->path, ft_get_envious("HOME", sp), 11))
			replace_with_tilde(pwd->path, j);
	}
}

void	ft_make_path(t_env *sp, t_path *pwd)
{
	char	*str;
	char	*str2;
	char	*str3;

	if (sp->tk->next->str[0] == '~')
	{
		str = ft_strdup(ft_get_envious("HOME", sp));
		str2 = ft_strdup(ft_strchr(sp->tk->next->str, 47));
		str = ft_strcat(str, str2);
		str3 = ft_strdup(str);
		ft_change_path(sp, pwd, str3);
		free(str3);
		free(str);
		free(str2);
	}
	else if (sp->tk->next->str[0] == '/')
		ft_change_path(sp, pwd, sp->tk->next->str);
	else
	{
		sp->tk->next->str = ft_strcat(sp->tk->next->str, "/");
		pwd->path = ft_strcat(pwd->path, "/");
		pwd->path = ft_strcat(pwd->path, sp->tk->next->str);
		ft_change_path(sp, pwd, pwd->path);
	}
}

void	ft_change_path(t_env *sp, t_path *pwd, char *new_path)
{
	char	*str;

	str = ft_strdup(pwd->path);
	if (!chdir(new_path))
	{
		ft_pwd(sp, 0);
		ft_change_env(sp, pwd);
		sp->exit = 0;
	}
	else
	{
		chdir(pwd->path);
		free(pwd->path);
		pwd->path = ft_strdup(ft_get_envious("PWD", sp));
		if (ft_strcmp(sp->tk->next->str, "/"))
			ft_remove_slash(sp);
		ft_errors(sp, 0, 1);
	}
	free(str);
}
