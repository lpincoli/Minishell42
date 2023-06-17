/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:42 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:40:42 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printlist(t_token *head)
{
	t_token	*current_node;

	current_node = head;
	while (current_node != NULL)
	{
		printf("String is:'%s'\n", current_node->str);
		printf("Valid %c\n", current_node->type);
		current_node = current_node->next;
	}
}

void	ft_echo_while(t_token *current_node)
{
	while (current_node != NULL)
	{
		if (current_node->type != 'z' && current_node->type != 'm')
			printf("%s", current_node->str);
		if (!*current_node->str)
		{
			current_node = current_node->next;
			continue ;
		}
		else if (current_node->next != NULL && current_node->type != 'm')
			printf(" ");
		current_node = current_node->next;
	}
}

void	echo(t_token *head, t_env *sp)
{
	t_token	*current_node;
	int		flag;

	current_node = head;
	flag = 0;
	if (!current_node)
	{
		printf("\n");
		sp->exit = 0;
		return ;
	}
	if (!ft_strncmp(current_node->str, "-n", 2))
	{
		flag = 1;
		current_node = current_node->next;
	}
	ft_echo_while(current_node);
	if (!flag)
		printf("\n");
	sp->exit = 0;
}
