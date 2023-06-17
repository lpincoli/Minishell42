/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:27 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:40:27 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_heredoc(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			if (!ft_strchr(&str[i], c))
				return (-2);
			while (str[i] != c)
				i++;
		}
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 1])
		{
			if (i == 0 && str[i] && str[i + 1] != '<')
				return (i + 2);
			else if (i > 0 && str[i + 2]
				&& str[i - 1] != '<' && str[i + 2] != '<')
				return (i + 2);
		}
		i++;
	}
	return (-1);
}

void	ft_mkdir_heredoc(t_env *sp)
{
	char	**argv;
	int		pid;
	int		status;

	pid = fork();
	status = 0;
	sp->hdpath = ft_strjoin(getenv("PWD"), "/.heredoc");
	if (pid == 0)
	{
		argv = malloc(sizeof(char *) * 4);
		argv[0] = malloc(sizeof(char) * 11);
		argv[0] = "/bin/mkdir";
		argv[1] = malloc(sizeof(char) * 9);
		argv[1] = ".heredoc";
		argv[2] = NULL;
		execve("/bin/mkdir", argv, sp->env);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			sp->exit = 0;
	}
}

void	ft_rm_heredoc(t_env *sp)
{
	char	**argv;
	int		pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		argv = malloc(sizeof(char *) * 4);
		argv[0] = malloc(sizeof(char) * 8);
		argv[0] = "/bin/rm";
		argv[1] = sp->hdpath;
		argv[2] = malloc(sizeof(char) * 4);
		argv[2] = "-rf";
		argv[3] = NULL;
		execve("/bin/rm", argv, sp->env);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			sp->exit = 0;
	}
}

char	*ft_get_heredoc_delim(char *str, int h)
{
	int		i;
	char	*ret;

	i = 0;
	if (!str[h])
		return (NULL);
	while (str[h] && (str[h] == ' ' || str[h] == '\t'))
		h++;
	ret = ft_calloc(sizeof(char), 1000);
	while (str[h] && (str[h] != ' ' && str[h] != '\t'))
		ret[i++] = str[h++];
	return (ret);
}
