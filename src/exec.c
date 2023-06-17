/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:11 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:40:11 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_cose(t_env *sp, char **argv)
{
	execve(sp->tk->str, argv, sp->env);
	ft_errors(sp, 4, 127);
	if (!sp->bald && !sp->son)
	{
		free(argv);
		ft_release(sp);
		exit(127);
	}
}

void	ft_printacose(int corpse, int status, pid_t pid)
{
	if (corpse < 0)
		printf("Failed to wait for process %d (errno = %d)\n",
			(int)pid, errno);
	else if (corpse != pid)
	{
		printf("Got corpse of process %d ", corpse);
		printf("(status 0x%.4X) when expecting PID %d\n", status, (int)pid);
	}
}

void	ft_wife_status(t_env *sp, int status)
{
	if (WTERMSIG(status) == 1)
		ft_errors(sp, 1, 1);
	else if (WTERMSIG(status) == 10)
		ft_errors(sp, 1, 10);
	else if (WTERMSIG(status) == 11)
		ft_errors(sp, 3, 139);
	else if (WTERMSIG(status) == 126)
	{
		errno = EACCES;
		ft_errors(sp, 1, 126);
	}
	else if (WTERMSIG(status) == 127)
		ft_errors(sp, 3, 127);
	else
		return ;
}

void	ft_fai_altro(t_env *sp, int status, pid_t pid)
{
	int		corpse;

	corpse = wait(&status);
	if (corpse < 0)
		ft_printacose(corpse, status, pid);
	else if (corpse != pid)
		ft_printacose(corpse, status, pid);
	else if (WIFEXITED(status))
		sp->exit = 0;
	else if (WIFSIGNALED(status))
		ft_wife_status(sp, status);
	else
	{
		ft_errors(sp, 1, 0);
		return ;
	}
}

void	ft_exec2(t_env *sp)
{
	pid_t	pid;
	char	**argv;
	int		status;

	status = 0;
	if (ft_nonlosoio(sp))
		return ;
	argv = ft_sugar_mommy(sp->tk);
	pid = fork();
	if (pid == 0)
		ft_init_cose(sp, argv);
	else
		ft_fai_altro(sp, status, pid);
	free(argv);
}
