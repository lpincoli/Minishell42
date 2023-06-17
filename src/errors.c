/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:04 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:40:05 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_errors(t_env *sp, int errn, int sp_exit)
{
	if (!errn)
		printf("cd: %s: %s\n", strerror(errno), sp->tk->next->str);
	else if (errn == 1)
		printf("minishell: %s: %s\n", strerror(errno), sp->tk->str);
	else if (errn == 2)
		printf("unset: not enough arguments\n");
	else if (errn == 3)
		printf("minishell: segmentation fault (core dumped)   %s\n",
			sp->tk->str);
	else if (errn == 4)
		printf("minishell: command not found: %s\n", sp->tk->str);
	else if (errn == 5)
		printf("minishell: no such user or named directory: %s\n", sp->tk->str);
	sp->exit = sp_exit;
	return (0);
}
