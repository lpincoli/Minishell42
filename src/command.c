/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:39:38 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:39:39 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pwd(t_env *sp, int a)
{
	char	pwd[256];

	getcwd(pwd, sizeof(pwd));
	sp->pwd->path = ft_strcpy(sp->pwd->path, pwd);
	if (a)
		printf("%s\n", sp->pwd->path);
}

void	ft_exit(t_env *sp)
{
	long long int	i;

	i = 0;
	if (sp->tk->next)
	{
		if (sp->tk->next->next)
		{
			write(2, "cd has too many arguments\n", 26);
			sp->exit = 1;
			return ;
		}
		if (ft_check_num(sp->tk->next->str, sp))
			i = ft_atol(sp->tk->next->str);
		else
			return ;
	}
	ft_rm_heredoc(sp);
	ft_release(sp);
	exit(i);
}

void	ft_env(t_env *sp)
{
	int	i;

	i = 0;
	while (sp->env[i] != NULL)
	{
		printf("%s\n", sp->env[i]);
		i++;
	}
}

int	ft_command_utils(t_env *sp, t_path *pwd)
{
	if (ft_strcmp(sp->tk->str, "echo") == 0)
		echo(sp->tk->next, sp);
	else if (!ft_strcmp(sp->tk->str, "pwd"))
		ft_pwd(sp, 1);
	else if (!ft_strcmp(sp->tk->str, "exit"))
		ft_exit(sp);
	else if (!ft_strcmp(sp->tk->str, "export"))
		ft_export(sp);
	else if (!ft_strcmp(sp->tk->str, "env"))
		ft_env(sp);
	else if (!ft_strcmp(sp->tk->str, "unset"))
	{
		if (ft_unset(sp))
			return (1);
	}
	else if (!ft_strcmp(sp->tk->str, "cd"))
		ft_cd (sp, pwd);
	else if (ft_is_variable(sp->tk->str, sp->n))
	{
		if (!ft_subenv(sp->tk->str, sp, ft_get_equal_index(sp->tk->str)))
			ft_save_var(sp->tk->str, sp);
	}
	else
		ft_exec2(sp);
	return (0);
}

void	ft_command(t_env *sp, t_path *pwd)
{
	if (!sp->tk)
		return ;
	while (!*sp->tk->str)
	{
		if (*sp->tk->str)
			break ;
		sp->tk = sp->tk->next;
	}
	if (!*sp->tk->str)
		return ;
	if (ft_command_utils(sp, pwd))
		return ;
}
