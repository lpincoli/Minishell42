/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puliscimelo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:54 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:40:54 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pulisci_line_while(char *s,	char *d, char *dest, t_env *sp)
{
	while (*s)
	{
		if (!sp->found_hidoc && ft_strncmp(s, "<<", ft_strlen("<<")) == 0)
		{
			s += ft_strlen("<<");
			sp->found_hidoc = 1;
			sp->skip_word = 1;
			while (*s == 32 || (*s <= 13 && *s >= 9))
				s++;
		}
		if (sp->skip_word && (((*s) == 32 || *s == '\0')
				|| (*s <= 13 && *s >= 9)))
		{
			sp->skip_word = 0;
			*d = *s;
			ft_aggiungi_fname(dest, sp->hfname);
			while (*d != '\0')
				d++;
		}
		if (!sp->skip_word)
			*d++ = *s;
		s++;
	}
}

char	*ft_pulisci_line(t_env *sp)
{
	char	*s;
	char	*d;
	char	*dest;

	s = sp->line;
	d = ft_calloc(sizeof(char), (ft_strlen(sp->line) + 80));
	sp->skip_word = 0;
	sp->found_hidoc = 0;
	dest = d;
	ft_pulisci_line_while(s, d, dest, sp);
	if (sp->skip_word && (((*s) == 32 || *s == '\0') || (*s <= 13 && *s >= 9)))
		ft_aggiungi_fname(dest, sp->hfname);
	free(sp->line);
	return (dest);
}

int	ft_check_heredoc1(int h, t_env *sp)
{
	if (h == -2)
	{
		printf("Quotes aperte, maledetto\n");
		free(sp->line);
		return (1);
	}
	return (0);
}

int	ft_check_heredoc2(int h, t_env *sp)
{
	if (h == -1)
		add_history(sp->line);
	else
	{
		free(sp->delim);
		sp->delim = ft_get_heredoc_delim(sp->line, h);
		if (!*sp->delim)
		{
			printf("minishell: parse error near '\\n'\n");
			free(sp->line);
			return (1);
		}
		else
		{
			sp->hdoc = 1;
			ft_get_heredoc(sp);
			add_history(sp->line);
			sp->line = ft_pulisci_line(sp);
		}
	}
	return (0);
}

void	ft_init_path(t_path *pwd, t_env *sp)
{
	pwd->path = calloc(sizeof(char), 257);
	sp->n = ft_calloc(sizeof(t_norm), 1);
	sp->vars = ft_calloc(sizeof(sp->vars), 1000);
	sp->vars[0] = NULL;
	pwd->old_path = ft_strdup(ft_get_envious("OLDPWD", sp));
}
