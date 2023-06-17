/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:41:00 by lpincoli          #+#    #+#             */
/*   Updated: 2023/06/17 11:45:19 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sep_pip_while(char *str, char *line, t_norm *n)
{
	char	c;

	c = str[n->i];
	if (str[n->i + 1] == c && (str[n->i + 2] == '<'
			|| str[n->i + 2] == '>' || str[n->i + 2] == '|'))
	{
		line[n->j++] = str[n->i++];
		line[n->j++] = str[n->i++];
		line[n->j++] = ' ';
	}
	else if (str[n->i + 1] != c && str[n->i])
	{
		while (ft_strchr(&str[n->i + 1], c))
			line[n->j++] = str[n->i++];
		line[n->j++] = str[n->i++];
	}
	else if (str[n->i + 1] == c)
	{
		line[n->j++] = str[n->i++];
		line[n->j++] = str[n->i++];
	}
}

int	ft_cntr_invalid(char *str, char *line, t_norm *n)
{
	if (ft_strncmp(&str[n->i], ">>>", 3) == 0
		|| ft_strncmp(&str[n->i], "<<<", 3) == 0
		|| ft_strncmp(&str[n->i], "||", 2) == 0)
	{
		printf("ERROR INVALID COMMAND\n");
		free(str);
		free(line);
		n->flg = 1;
		return (1);
	}
	return (0);
}

void	ft_sep_pip_if(char *str, char *line, t_norm *n)
{
	char	c;

	c = 0;
	if (str[n->i] == '<' || str[n->i] == '>')
		c = str[n->i];
	if (n->i != 0)
	{
		if (str[n->i - 1] != ' ')
			line[n->j++] = ' ';
	}
	line[n->j++] = str[n->i++];
	if (str[n->i] == c)
		line[n->j++] = str[n->i++];
	if (str[n->i] != ' ')
		line[n->j++] = ' ';
	else
		line[n->j++] = str[n->i++];
}

char	*ft_separate_pipes(char *str, t_norm *n)
{
	char	*line;

	ft_reset_norm(n);
	line = ft_calloc(sizeof(char), (3 * ft_strlen(str)));
	while (str[n->i])
	{
		while (str[n->i] != '<' && str[n->i] != '>' && str[n->i] != '|'
			&& str[n->i] != 34 && str[n->i] != 39 && str[n->i])
			line[n->j++] = str[n->i++];
		while (str[n->i] == 34 || str[n->i] == 39)
			ft_sep_pip_while(str, line, n);
		if (ft_cntr_invalid(str, line, n))
			return (NULL);
		if (str[n->i] == '<' || str[n->i] == '>' || str[n->i] == '|')
			ft_sep_pip_if(str, line, n);
	}
	free(str);
	return (line);
}
