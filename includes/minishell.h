/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpincoli <lpincoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:41:14 by lpincoli          #+#    #+#             */
/*   Updated: 2023/06/17 11:49:40 by lpincoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <errno.h>
# include <fcntl.h>

typedef struct s_norm
{
	int			i;
	int			j;
	int			k;
	int			flg;
	char		type;
	char		*filename;
	char		*stringapino;
	char		*linea;
}	t_norm;

typedef struct s_token
{
	char			*str;
	char			type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_path
{
	char	*path;
	char	*new_path;
	char	*old_path;
}	t_path;

typedef struct s_env
{
	char	*o_home;
	char	**env;
	char	*line;
	char	*delim;
	int		exit;
	int		pid;
	char	**vars;
	int		fvar;
	int		hdoc;
	int		bald;
	int		skip_word;
	int		found_hidoc;
	int		son;
	char	*hfname;
	char	*hdpath;
	t_token	*tk;
	t_norm	*n;
	t_path	*pwd;
}	t_env;

void	ft_special_release(t_env *sp);
t_token	*ft_mammamia_release(t_env *sp);
void	ft_interrupt_release(t_env *sp);
void	ft_parsepipe(t_token *args, t_env *sp, t_path *pwd);
void	ft_remove_redirect(t_env *sp);
void	ft_find_redirect(t_env *sp);
int		ft_cerca_il_milanese(t_env *sp);
void	ft_pulisci_bene(t_env *sp);
void	ft_freelist(t_token *list);
t_token	*ft_leftargs(t_token *tk, char c);
int		ft_is_heredoc(char *str);
void	ft_mkdir_heredoc(t_env *sp);
void	ft_rm_heredoc(t_env *sp);
char	*ft_get_heredoc_delim(char *str, int h);
t_token	*ft_tk_swipe(t_env *sp);
char	**ft_envtonew(t_env *sp, char **new, char *str);
void	ft_print_env(char **env);
int		ft_is_word(char *line);
void	ft_sub_var(char *var, t_env *sp);
int		ft_var_is_saved(char *var, t_env *sp);
void	ft_save_var(char *var, t_env *sp);
void	ft_save_vari1(char *vari1, t_env *sp);
int		ft_is_vari1(char *vari1, t_env *sp);
void	realloc_env(t_env *sp, char *str);
int		primo_if(t_env *sp);
int		secondo_if(t_env *sp, t_token *head);
int		terzo_if(t_env *sp, t_token *head);
void	quarto_if(t_env *sp);
int		quinto_if(t_env *sp);
int		ft_tksize(t_token *lst);
char	**ft_sugar_mommy(t_token *tk);
void	handler1(int signum);
int		ft_nonlosoio(t_env *sp);
int		ft_unset_init(t_env *sp);
int		ft_unset_logic(t_env *sp);
int		ft_unset(t_env *sp);
void	ft_parsereadir(t_env *sp, t_token *args, t_path *pwd);
void	ft_of_gondo(t_env *sp);
void	ft_adda_schifo(t_env *sp);
int		ft_is_denied(char *str, t_env *sp);
void	addbot(t_token **start, char *str, t_norm *n);
void	ft_grouponize(t_token *token, t_env *sp);
void	ft_create_tk(t_token	*token, char *str, t_env *sp);
void	ft_get_heredoc(t_env *sp);
char	*ft_get_heredoc_delim(char *str, int h);
int		ft_is_heredoc(char *str);
void	ft_rm_heredoc(t_env *sp);
void	ft_mkdir_heredoc(t_env *sp);
void	ft_add_slash(t_path *pwd);
int		ft_strlen_dol(char *str);
char	*ft_separate_pipes(char *str, t_norm *n);
char	*ft_lavori_in_casa_pd(char *line, t_norm *n);
void	ft_reset_norm(t_norm *n);
int		ft_get_equal_index(char *str);
char	*ft_get_envious(char *var, t_env *sp);
void	ft_del_env(char *sub, t_env *sp, int u);
char	*space_killer(char *line, t_norm *n);
void	ft_save_var(char *var, t_env *sp);
void	ft_release(t_env *sp);
void	ft_command(t_env *sp, t_path *pwd);
t_token	*ft_lexer(t_env *sp);
char	*ft_tokenizer(char *str);
void	echo(t_token *head, t_env *sp);
char	*ft_strcat(char *dest, char *src);
char	*ft_errors(t_env *sp, int errn, int sp_exit);
char	*ft_strcpy(char *dest, const char *src);
void	ft_change_path(t_env *sp, t_path *pwd, char *new_path);
void	ft_change_env(t_env *sp, t_path *pwd);
void	ft_init_path(t_path *pwd, t_env *sp);
void	replace_with_tilde(char *stringa, int x);
int		ft_strcmp(char *s1, const char *s2);
char	*ft_sub_dollar(char *tok, t_env *sp, t_norm *n);
int		ft_is_variable(char *line, t_norm *n);
int		ft_subenv(char *sub, t_env *sp, int u);
void	printlist(t_token *head);
char	*ft_slashyer(char *str, t_norm *n);
void	ft_passerone(t_env *sp, t_path *pwd);
void	ft_export(t_env *sp);
void	ft_exec2(t_env *sp);
void	ft_cd(t_env *sp, t_path *pwd);
void	ft_release_while(t_env *sp);
void	replace_with_tilde(char *stringa, int x);
void	ft_save_oldpath(t_path *pwd);
void	ft_add_slash(t_path *pwd);
void	ft_remove_slash(t_env *sp);
void	ft_make_line(t_env *sp, t_path *pwd);
void	ft_make_path(t_env *sp, t_path *pwd);
void	ft_pwd(t_env *sp, int a);
long	ft_atol(char *str);
int		ft_check_num(char *str, t_env *sp);
int		ft_check_heredoc2(int h, t_env *sp);
int		ft_check_heredoc1(int h, t_env *sp);
void	ft_copyenv(char **e, t_env *sp);
void	ft_aggiungi_fname(char *dest, char *src);
#endif
