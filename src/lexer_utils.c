/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:34 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:40:34 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_denied(char *str, t_env *sp)
{
	if (!ft_strncmp(str, "''\0", 3) || !ft_strncmp(str, "'' ", 3)
		|| !ft_strncmp(str, "''\t", 3) || !ft_strncmp(str, "\"\"\0", 3)
		|| !ft_strncmp(str, "\"\" ", 3) || !ft_strncmp(str, "\"\"\t", 3))
	{	
		sp->exit = 126;
		return (0);
	}
	else
		return (1);
}

void	addbot(t_token **start, char *str, t_norm *n)
{
	t_token	*last;
	t_token	*tmp;

	last = (t_token *)malloc(sizeof(t_token));
	last->str = ft_lavori_in_casa_pd(str, n);
	last->type = n->type;
	last->next = NULL;
	tmp = *start;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = last;
	last->prev = tmp;
}

/*usare strcmp invece di strcmp pwd e pwds riconosciuti come uguali*/

void	ft_grouponize(t_token *token, t_env *sp)
{
	while (token != NULL)
	{
		if (token->type == 's')
		{
			if (!ft_strcmp(token->str, "<"))
				token->type = '<';
			if (!ft_strcmp(token->str, ">"))
				token->type = '>';
			if (!ft_strcmp(token->str, ">>"))
				token->type = '+';
			if (!ft_strcmp(token->str, "<<"))
				token->type = '-';
			if (!ft_strcmp(token->str, "|"))
				token->type = '|';
			if (!ft_strcmp(token->str, sp->hfname))
				token->type = 'm';
		}
		token = token->next;
	}
}

void	ft_create_tk(t_token	*token, char *str, t_env *sp)
{
	ft_reset_norm(sp->n);
	token->str = ft_lavori_in_casa_pd(str, sp->n);
	token->type = sp->n->type;
	token->next = NULL;
	token->prev = NULL;
	while (str[sp->n->i])
		addbot(&token, str, sp->n);
	ft_grouponize(token, sp);
	free(str);
}
