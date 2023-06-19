/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_if.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:18 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:40:18 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_empty_token_and_move_next(t_env *sp)
{
	if (!*sp->tk->str && sp->tk->next)
	{
		if (sp->tk->type == '"' || sp->tk->type == '\'')
		{
			sp->exit = 1;
			write(2, " not a valid identifier\n", 24);
		}
		sp->tk = sp->tk->next;
		return (1);
	}
	return (0);
}

int	check_equal_sign_alone_and_reset(t_env *sp, t_token *head)
{
	if (sp->tk->str[0] == '=' && sp->tk->str[1] == '\0')
	{
		sp->exit = 1;
		write(2, " not a valid identifier\n", 24);
		sp->tk = head;
		return (1);
	}
	return (0);
}

int	check_valid_identifier_and_reset(t_env *sp, t_token *head)
{
	if (!ft_is_variable(sp->tk->str, sp->n) && !ft_is_word(sp->tk->str))
	{
		sp->exit = 1;
		write(2, " not a valid identifier\n", 24);
		sp->tk = head;
		return (1);
	}
	return (0);
}

void	handle_var_assignment(t_env *sp)
{	
	int	flag;
	int	len;
	int	i;

	i = 0;
	flag = 0;
	len = ft_strlen(sp->tk->str);
	if (ft_is_vari1(sp->tk->str, sp))
	{
		sp->tk->str = ft_strcat(sp->tk->str, "=");
		while (sp->env[i])
		{
			if (!ft_strncmp(sp->tk->str, sp->env[i], (len + 1)))
				flag = 1;
			i++;
		}
		if (flag)
			realloc_env(sp, sp->tk->str);
	}
	else
	{
		ft_save_vari1(sp->tk->str, sp);
		sp->tk = sp->tk->next;
	}
}

int	handle_var_substitution(t_env *sp)
{	
	int	i;

	i = 0;
	ft_save_var(sp->tk->str, sp);
	if (ft_subenv(sp->tk->str, sp, ft_get_equal_index(sp->tk->str)))
	{
		sp->tk = sp->tk->next;
		return (1);
	}
	else
	{
		while (sp->env[i])
			i++;
		realloc_env(sp, sp->tk->str);
	}
	return (0);
}
