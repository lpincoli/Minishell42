/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:24 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:40:25 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_word(char *line)
{
	int	i;
	int	flg;

	flg = 0;
	i = 0;
	if (line[0] == '_' && line[1] == '\0')
		return (0);
	while (line[i])
	{
		if ((line[i] >= '0' && line[i] <= '9'))
			i++;
		else if ((line[i] >= 'a' && line[i++] <= 'z'))
			flg = 1;
		else if ((line[i] >= 'A' && line[i++] <= 'Z'))
			flg = 1;
		else if (line[i] == '_')
			i++;
		else
			return (0);
	}
	return (flg);
}

void	ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
}

char	**ft_envtonew(t_env *sp, char **new, char *str)
{
	int	i;

	i = -1;
	while (sp->env[++i])
	{
		new[i] = ft_strdup(sp->env[i]);
		if (!sp->env[i])
		{
			free(sp->env);
			return (NULL);
		}
	}
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	return (new);
}

t_token	*ft_tk_swipe(t_env *sp)
{
	t_token	*head;

	head = sp->tk;
	if (sp->tk->next != NULL)
		sp->tk = sp->tk->next;
	else
		ft_print_env(sp->env);
	return (head);
}

void	ft_export(t_env *sp)
{
	t_token	*head;

	head = ft_tk_swipe(sp);
	while (sp->tk != NULL && sp->tk->type != '|'
		&& sp->tk->type != '>' && sp->tk->type != '-'
		&& sp->tk->type != '+' && sp->tk->type != '<' )
	{
		if (primo_if(sp))
			continue ;
		if (secondo_if(sp, head))
			return ;
		if (terzo_if(sp, head))
			return ;
		if (sp->tk->str && !ft_strchr(sp->tk->str, '='))
			quarto_if(sp);
		else
		{
			if (quinto_if(sp))
				continue ;
		}
	}
	sp->exit = 0;
	sp->tk = head;
}
