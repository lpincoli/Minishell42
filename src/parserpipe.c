/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserpipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:56 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:40:56 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pipadestra(t_token *args, t_env *sp, t_path *pwd, int *p)
{
	t_token	*head;

	head = sp->tk;
	sp->son = 1;
	dup2(p[0], 0);
	close(p[0]);
	close(p[1]);
	sp->tk = args;
	sp->tk = sp->tk->next;
	sp->bald = 1;
	ft_passerone(sp, pwd);
	sp->tk = head;
	ft_special_release(sp);
	exit(0);
}

void	ft_pipasinistra(t_token *args, t_env *sp, t_path *pwd, int *p)
{
	t_token	*left_side;
	t_token	*head;

	head = sp->tk;
	sp->son = 1;
	dup2(p[1], 1);
	close(p[1]);
	left_side = ft_leftargs(args, '|');
	sp->tk = left_side;
	close(p[0]);
	ft_passerone(sp, pwd);
	ft_freelist(left_side);
	sp->tk = head;
	ft_special_release(sp);
	exit(0);
}

void	ft_parsepipe(t_token *args, t_env *sp, t_path *pwd)
{
	int		p[2];

	(void) pwd;
	if (pipe(p) < 0)
		exit(1);
	sp->pid = fork();
	if (sp->pid == 0)
		ft_pipasinistra(args, sp, pwd, p);
	sp->pid = fork();
	if (sp->pid == 0)
		ft_pipadestra(args, sp, pwd, p);
	sp->bald = 0;
	close(p[0]);
	wait(0);
	close(p[1]);
	wait(0);
}

void	ft_special_release(t_env *sp)
{
	t_token	*temp;

	temp = ft_mammamia_release(sp);
	free(temp->str);
	free(sp->line);
	free(temp);
	free(sp->pwd->path);
	free(sp->pwd->old_path);
	free(sp->pwd);
	free(sp->vars);
	free(sp->n);
	free(sp->hdpath);
	free(sp->hfname);
	free(sp->delim);
	free(sp);
}
