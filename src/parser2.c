/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:45 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:40:46 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_leftksize(t_token *lst)
{
	int	i;

	i = 0;
	while (lst->prev != NULL)
	{
		i++;
		lst = lst->prev;
	}
	if (i == 0)
	{
		i++;
	}
	return (i);
}

void	ft_freelist(t_token *list)
{
	t_token	*temp;

	temp = list;
	while (temp->next != NULL)
	{
		list = temp->next;
		free(temp->str);
		free(temp);
		temp = list;
	}
	free(temp->str);
	free(temp);
}

void	ft_printlist(t_token *list)
{
	t_token	*print;

	print = list;
	while (print->next != NULL)
	{
		printf("%s\n", print->str);
		print = print->next;
	}
	printf("%s\n", print->str);
}

void	ft_pulisci_bene(t_env *sp)
{
	t_token	*pulisco;
	t_token	*seguo;

	pulisco = sp->tk;
	seguo = sp->tk;
	seguo = seguo->next->next;
	free(pulisco->str);
	free(pulisco);
	pulisco = seguo->prev;
	free(pulisco->str);
	free(pulisco);
	seguo->prev = NULL;
	sp->tk = seguo;
}

int	ft_cerca_il_milanese(t_env *sp)
{
	t_token	*ptr;

	ptr = sp->tk;
	while (ptr->next)
	{
		if (ptr->type == '>' || ptr->type == '+' || ptr->type == '|')
			return (1);
		ptr = ptr->next;
	}
	return (0);
}
