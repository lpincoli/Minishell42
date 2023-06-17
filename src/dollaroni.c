/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollaroni.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:39:52 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:39:53 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sub_dollar_if_1(char *pippo, t_env *sp, t_norm *n)
{
	char	*str;

	str = ft_itoa(sp->exit);
	while (str[n->k])
		pippo[n->j++] = str[n->k++];
	n->i += 2;
	free(str);
}

void	ft_sub_dollar_elif(char *tok, char *pippo, t_env *sp)
{
	char	*sub;
	char	*str;

	sub = calloc((ft_strlen_dol(&tok[sp->n->i++]) + 1), sizeof(char));
	while (tok[sp->n->i] != ' ' && tok[sp->n->i] != '\t'
		&& tok[sp->n->i] != '\0' && tok[sp->n->i] != 34 && tok[sp->n->i] != 39)
		sub[sp->n->k++] = tok[sp->n->i++];
	sp->n->k = 0;
	str = ft_get_envious(sub, sp);
	free(sub);
	if (str)
	{
		while (str[sp->n->k] != '\0')
			pippo[sp->n->j++] = str[sp->n->k++];
	}
}

int	ft_sub_dollar_if_long(char *tok, char *pippo, t_env *sp, t_norm *n)
{
	if ((n->i == 0 || tok[n->i - 1] == ' ' || tok[n->i - 1] == '\t')
		&& tok[n->i] == '$' && (tok[n->i + 1] == ' ' || tok[n->i + 1] == '\t'))
		pippo[n->j++] = tok[n->i++];
	else if (tok[n->i] == '$' && (tok[n->i + 1] == ' '
			|| tok[n->i + 1] == '\t' || tok[n->i + 1] == '"'))
		pippo[n->j++] = tok[n->i++];
	else if (tok[n->i] == '$' && tok[n->i + 1] == 39)
		n->i++;
	else if (tok[n->i] == '$' && tok[n->i + 1] == '?')
		ft_sub_dollar_if_1(pippo, sp, n);
	else if (tok[n->i] == '$')
	{
		if (tok[n->i + 1] == '\0')
		{
			pippo[n->j] = '$';
			pippo[n->j + 1] = '\0';
			return (1);
		}
		ft_sub_dollar_elif(tok, pippo, sp);
	}
	return (0);
}

int	grazie_pippo(char *pippo, char *tok)
{
	if (!pippo || !*pippo)
	{
		free(pippo);
		free(tok);
		return (1);
	}
	free(tok);
	return (0);
}

char	*ft_sub_dollar(char *tok, t_env *sp, t_norm *n)
{
	char	*pippo;

	ft_reset_norm(n);
	pippo = calloc(1000, sizeof(char));
	while (tok[n->i])
	{		
		while (tok[n->i] != '$' && tok[n->i] != 39 && tok[n->i])
			pippo[n->j++] = tok[n->i++];
		if (ft_sub_dollar_if_long(tok, pippo, sp, n))
			break ;
		if (tok[n->i] == 39)
		{
			while (strchr(&tok[n->i + 1], 39))
				pippo[n->j++] = tok[n->i++];
			pippo[n->j++] = tok[n->i++];
		}
		if (!tok[n->i])
			break ;
		n->k = 0;
	}
	if (grazie_pippo(pippo, tok))
		return (NULL);
	return (pippo);
}
