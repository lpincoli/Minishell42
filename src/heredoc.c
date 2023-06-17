/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:30 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:40:30 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_heredoc(t_env *sp, int pino)
{
	sp->n->stringapino = ft_itoa(pino);
	sp->n->filename = ft_strjoin("/.s", sp->n->stringapino);
	free(sp->n->stringapino);
	sp->n->stringapino = sp->n->filename;
	sp->n->filename = ft_strjoin(sp->hdpath, sp->n->filename);
	free(sp->n->stringapino);
}

int	free_ifnot_fd(t_env *sp, int fd)
{
	if (!fd)
	{
		printf("vabeh..\n");
		free(sp->n->filename);
		free(sp->n->linea);
		return (1);
	}
	free(sp->hfname);
	sp->hfname = ft_strdup(sp->n->filename);
	free(sp->n->filename);
	return (0);
}

void	ft_get_heredoc(t_env *sp)
{
	static int	pino = 1;
	int			fd;

	sp->n->linea = readline("<");
	if (sp->n->linea)
	{
		ft_init_heredoc(sp, pino);
		fd = open(sp->n->filename, O_RDWR | O_CREAT
				| O_APPEND, S_IRUSR | S_IWUSR);
		if (free_ifnot_fd(sp, fd))
			return ;
		pino++;
		ft_putstr_fd(sp->n->linea, fd);
	}
	while (ft_strcmp(sp->delim, sp->n->linea))
	{
		free(sp->n->linea);
		sp->n->linea = readline("<");
		if (ft_strcmp(sp->delim, sp->n->linea))
			ft_putstr_fd(sp->n->linea, fd);
	}
	free(sp->n->linea);
	close(fd);
}
