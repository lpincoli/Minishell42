/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:07 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:40:08 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_tksize(t_token *lst)
{
	int	i;

	i = 0;
	while (lst != NULL && lst->type != '>' && lst->type != '<'
		&& lst->type != '+' && lst->type != '-' && lst->type != '|')
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	**ft_sugar_mommy(t_token *tk)
{
	char	**av;
	int		i;
	int		j;

	i = ft_tksize(tk);
	j = 0;
	if (!tk)
		return (NULL);
	av = ft_calloc (sizeof(char *), (i + 1));
	while (j < i)
	{
		av[j] = tk->str;
		tk = tk->next;
		j++;
	}
	return (av);
}

void	handler1(int signum)
{
	if (signum == SIGSEGV)
		WEXITSTATUS(139);
}

int	ft_nonlosoio(t_env *sp)
{
	char	*str;
	char	*str1;

	if (!(ft_strncmp(sp->tk->str, "~", 1)))
	{
		str = ft_strdup(sp->tk->str);
		ft_strcpy(str, ft_get_envious("HOME", sp));
		if (sp->tk->str[1] == '/')
		{
			str1 = ft_strdup(ft_strchr(sp->tk->str, 47));
			free(sp->tk->str);
			sp->tk->str = ft_strdup(ft_strcat(str, str1));
			free(str1);
			free(str);
		}
		else
		{
			ft_errors (sp, 5, 187);
			return (1);
		}
	}
	return (0);
}
