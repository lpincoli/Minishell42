/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:40:38 by lpincoli          #+#    #+#             */
/*   Updated: 2023/03/25 23:40:38 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*g_sp;

void	ft_suppress_output(void)
{
	struct termios	new_settings;

	if (tcgetattr(0, &new_settings))
		perror("minishell: tcsetattr");
	new_settings.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &new_settings))
		perror("minishell: tcsetattr");
}

void	handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		g_sp->exit = 130;
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig_num == SIGQUIT)
		return ;
}

void	ft_init_main_1(int ac, char **av, char **env)
{
	if (ac != 1 || av[1] != NULL)
	{
		printf("No arguments needed\n");
		exit(0);
	}
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	signal(SIGTSTP, handler);
	g_sp = malloc(sizeof(t_env));
	g_sp->tk = NULL;
	g_sp->pwd = malloc(sizeof(t_path));
	ft_copyenv(env, g_sp);
	g_sp->exit = 0;
	g_sp->bald = 0;
	g_sp->son = 0;
	g_sp->hdoc = 0;
	g_sp->o_home = ft_get_envious("HOME", g_sp);
	ft_init_path (g_sp->pwd, g_sp);
	ft_mkdir_heredoc(g_sp);
}

void	ft_ema_distrugge(void)
{
	if (g_sp->line[0])
	{
		g_sp->tk = ft_lexer(g_sp);
		if (g_sp->tk)
			ft_passerone(g_sp, g_sp->pwd);
		g_sp->hdoc = 0;
		ft_release_while(g_sp);
	}
}

int	main(int ac, char **av, char **env)
{
	int	h;

	ft_init_main_1(ac, av, env);
	while (1)
	{
		g_sp->line = readline("minishell> ");
		g_sp->hfname = ft_calloc(1, 1);
		g_sp->delim = ft_calloc(1, 1);
		if (!g_sp->line)
		{
			ft_rm_heredoc(g_sp);
			ft_interrupt_release(g_sp);
			exit (0);
		}
		if (g_sp->line && *g_sp->line)
		{
			h = ft_is_heredoc(g_sp->line);
			if (ft_check_heredoc1(h, g_sp))
				continue ;
			if (ft_check_heredoc2(h, g_sp))
				continue ;
		}
		ft_ema_distrugge();
	}
}
