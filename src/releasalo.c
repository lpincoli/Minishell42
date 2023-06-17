/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   releasalo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:58 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:40:58 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_interrupt_release(t_env *sp)
{
	int	i;

	i = 0;
	while (sp->vars[i] != NULL)
		free(sp->vars[i++]);
	i = 0;
	while (sp->env[i] != NULL)
		free(sp->env[i++]);
	if (sp->env)
		free(sp->env);
	if (sp->vars)
		free(sp->vars);
	if (sp->pwd->path)
		free(sp->pwd->path);
	if (sp->pwd->old_path)
		free(sp->pwd->old_path);
	free(sp->pwd);
	free(sp->n);
	free(sp->hdpath);
	free(sp->hfname);
	free(sp->delim);
	free(sp);
}

void	ft_release_norm(t_env *sp)
{
	free(sp->tk->str);
	free(sp->line);
	free(sp->tk);
	if (sp->pwd->path)
		free(sp->pwd->path);
	if (sp->pwd->old_path)
		free(sp->pwd->old_path);
	free(sp->pwd);
	free(sp->vars);
	free(sp->n);
	free(sp->hdpath);
	free(sp->hfname);
	free(sp->delim);
	free(sp);
}

void	ft_release(t_env *sp)
{
	t_token	*temp;
	int		i;

	i = 0;
	temp = sp->tk;
	while (sp->env[i] != NULL)
		free(sp->env[i++]);
	if (sp->env)
		free(sp->env);
	i = 0;
	while (sp->vars[i] != NULL)
		free(sp->vars[i++]);
	if (sp->tk)
	{
		while (temp->next != NULL)
		{
			sp->tk = temp->next;
			free(temp->str);
			free(temp);
			temp = sp->tk;
		}
	}
	ft_release_norm(sp);
}

void	ft_release_while(t_env *sp)
{
	t_token	*temp;

	temp = sp->tk;
	if (sp->tk)
	{
		while (temp->next != NULL)
		{
			sp->tk = temp->next;
			free(temp->str);
			free(temp);
			temp = sp->tk;
		}
		free(sp->tk->str);
		free(sp->tk);
		free(sp->hfname);
		free(sp->delim);
		free(sp->line);
	}
}

void	ft_copyenv(char **e, t_env *sp)
{
	int		count;
	int		index;

	count = 0;
	while (e[count++])
		continue ;
	sp->env = malloc(sizeof(char *) * (count + 1));
	if (!sp->env)
		return ;
	index = -1;
	while (e[++index])
	{
		sp->env[index] = ft_strdup(e[index]);
		if (!sp->env[index])
			return ;
	}
	sp->env[index] = NULL;
	return ;
}
