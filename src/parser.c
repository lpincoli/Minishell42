/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:44 by lpincoli          #+#    #+#             */
/*   Updated: 2023/06/19 14:32:23 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_hand_redirect(t_env *sp, t_path *pwd)
{
	ft_find_redirect(sp);
	ft_remove_redirect(sp);
	if (ft_find_red(sp))
		ft_passerone(sp, pwd);
}

void	ft_clean_order(t_env *sp, t_path *pwd)
{
	ft_find_redirect(sp);
	ft_remove_redirect(sp);
	ft_command(sp, pwd);
}

void	ft_parseredir(t_env *sp, t_token *args, t_path *pwd)
{
	char	*filename;
	int		fd;

	sp->pid = fork();
	if (sp->pid == 0)
	{
		sp->son = 1;
		args->type = 'z';
		args = args->next;
		args->type = 'z';
		filename = ft_strdup(args->str);
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		free(filename);
		if (fd < 0)
			exit(1);
		dup2(fd, 1);
		ft_clean_order(sp, pwd);
		dup2(1, fd);
		close(fd);
		ft_special_release(sp);
		exit(0);
	}
	wait(0);
	ft_hand_redirect(sp, pwd);
}

void	ft_parseplus(t_env *sp, t_token *args, t_path *pwd)
{
	char	*filename;
	int		fd;

	sp->pid = fork();
	if (sp->pid == 0)
	{
		sp->son = 1;
		args->type = 'z';
		args = args->next;
		args->type = 'z';
		filename = ft_strdup(args->str);
		fd = open(filename, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
		free(filename);
		if (fd < 0)
			exit(1);
		dup2(fd, 1);
		ft_command(sp, pwd);
		dup2(1, fd);
		close(fd);
		ft_special_release(sp);
		exit(0);
	}
	wait(0);
	ft_hand_redirect(sp, pwd);
}

void	ft_passerone(t_env *sp, t_path *pwd)
{
	t_token	*temp;

	temp = sp->tk;
	while ((temp->type == 's' || temp->type == '\'' || temp->type == '"'
			|| temp->type == 'z' || temp->type == 'm') && temp->next != NULL)
		temp = temp->next;
	if (temp->type == 's' || temp->type == '\'' || temp->type == '"')
		ft_command(sp, pwd);
	else if (temp->type == 'm')
	{
		ft_insert_redir(sp);
		ft_parsereadir(sp, temp->prev, pwd);
	}
	else
	{
		if (temp->type == '|')
			ft_parsepipe(temp, sp, pwd);
		else if (temp->type == '>')
			ft_parseredir(sp, temp, pwd);
		else if (temp->type == '+')
			ft_parseplus(sp, temp, pwd);
		else if (temp->type == '<')
			ft_parsereadir(sp, temp, pwd);
	}
}
