/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:50 by lpincoli          #+#    #+#             */
/*   Updated: 2023/06/19 14:35:27 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pulizie_primavera(t_token *pulisco)
{
	if (pulisco->type == 'z')
	{
		pulisco->prev->next = NULL;
		free(pulisco->str);
		free(pulisco);
	}
}

int	ft_free_check(t_env *sp)
{
	t_token	*pulisco;

	pulisco = sp->tk;
	if (pulisco->type == 'z')
	{
		if (pulisco->next->next != NULL)
			ft_pulisci_bene(sp);
		else
		{
			ft_release(sp);
			exit (1);
		}
		return (1);
	}
	return (0);
}

void	ft_remove_redirect(t_env *sp)
{
	t_token	*pulisco;
	t_token	*seguo;

	pulisco = sp->tk;
	if (ft_free_check(sp))
		return ;
	while (pulisco->next)
	{
		if (pulisco->type == 'z')
		{
			seguo = pulisco->prev;
			seguo->next = pulisco->next;
			seguo->next->prev = seguo;
			free(pulisco->str);
			free(pulisco);
			pulisco = seguo;
		}
		pulisco = pulisco->next;
	}
	ft_pulizie_primavera(pulisco);
}

void	ft_find_redirect(t_env *sp)
{
	t_token	*finder;
	int		flag;

	flag = 0;
	finder = sp->tk;
	while (finder->next)
	{
		if ((finder->type == '>' || finder->type == '+') && flag == 0)
		{
			finder->type = 'z';
			finder->next->type = 'z';
			flag = 1;
		}
		else if ((finder->type == '|') && flag == 0)
		{
			finder->type = 'z';
			flag = 1;
		}
		finder = finder->next;
	}
}

t_token	*ft_struct_release(t_env *sp)
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
			if (temp && temp->next->str)
				free(temp->str);
			free(temp);
			temp = sp->tk;
		}
	}
	return (temp);
}
