/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:36 by lpincoli          #+#    #+#             */
/*   Updated: 2023/06/19 14:26:32 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_lexer_1(t_env *sp, char *str, t_token *token)
{
	str = space_killer(str, sp->n);
	if (!ft_is_denied(str, sp))
		return (NULL);
	str = ft_slashyer(str, sp->n);
	if (sp->n->flg)
	{
		free(token);
		return (NULL);
	}
	str = space_killer(str, sp->n);
	return (str);
}

void	ft_free_lex(char *str, t_token *token, t_env *sp)
{
	free(str);
	free(token);
	free(sp->hfname);
	free(sp->delim);
}

t_token	*ft_lexer(t_env *sp)
{
	char	*str;
	t_token	*token;

	str = ft_strdup(sp->line);
	token = ft_calloc(sizeof(t_token), 1);
	if (str[0] == 0)
		return (NULL);
	str = ft_lexer_1(sp, str, token);
	str = ft_separate_pipes(str, sp->n);
	if (sp->n->flg)
	{
		free(token);
		return (NULL);
	}
	str = space_killer(str, sp->n);
	str = ft_sub_dollar(str, sp, sp->n);
	if (!str || !*str)
	{
		ft_free_lex(str, token, sp);
		return (NULL);
	}
	ft_create_tk(token, str, sp);
	return (token);
}