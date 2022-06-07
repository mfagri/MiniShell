/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 14:15:25 by mfagri            #+#    #+#             */
/*   Updated: 2022/06/07 18:12:27 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 1
# define HISTORY_PATH "/Users/mfagri/.minishell_history"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
#include <curses.h>
# include <signal.h>
#include <sys/wait.h>

typedef struct s_arg
{
	char	r;
	int		k;
	int		stdout;
}	t_arg;

typedef struct	s_spl
{
	char	***b_var;
	char	***a_var;
}	t_spl;

void			ft_cd_free(char *s);
char			**get_ret(char **pr, int i, int *j);
void			ft_putstr_fd(char *s, int fd);
void			ft_echo(char **pr);
void			ft_pwd(char **arg);
void			ft_cd(char **arg, char **env);
void			ft_exit(char **arg, char **env);
void			ft_home(char **env);
int				ft_oldpwd(char **env);
char			*ft_take_pwd_old(char p[]);
void			ft_cd_norm(char **env, char *path, char s[]);
void			ft_unset(char **arg, char **env);
int				ft_count_args(char **args);
int				ft_check_n(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char *s1, char *s2);
char			*cpy(char *dest, char *src);
int				cpy_next_line(char **all, int fd);
int				check_next_ln(char *all);
char			*ft_strjoin(char *s1, char *s2);
char			*get_next_line(int fd);
int				new_line_index(char	*all);
int				ft_strlen(char *c);
char			*ft_return(char *all, int i);
char			*edit_all(char *all, int i, int k);
int				get_history();
char			*get_path(char **env, char *command);
int				ft_isalnum(int c);
int				ft_isdigit(int c);
char			*ft_itoa(int j);
void			ft_sig(int signum);
int				exec(int fd, char **env);
int				get_glo(int i);
void			ft_pwd();
char			***split_pr(char **pr, int i, int k, char q);
char			get_q(char **pr, int i, int j, char q);
void			remove_ctlc(void);
char			get_q_1(char *pr, int i, char q);
char			*remove_qu(char *str, int i, int j);
int				check_next_qu(char *str, char c, int i);
char			*get_arg(char *str, int i, int t);
int				get_spaces(char *str);
char			*get_var(char *str, char **env, int j, int i);
char			*get_var_utils_1(char *str, int *j, int *k);
void			edit_var(char **ret, char **env, int i, int k);
void			edit_qu(char ***str, int i, int j, t_arg k);
char			*sep(char *str, int i, int k);
char			*remove_pwd(char **env, int i);
int				ft_strcmp(const char *s1, const char *s2);
void			ft_echo(char **pr);
void			ft_pwd(char **arg);
void 			ft_cd(char **arg,char **env);
void			 ft_print_env(char **env);
void			ft_export(char **env,char **arg);
void 			ft_unset(char **arg,char **env);
int				ft_isalpha(int c);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strrchr(char *s, int c);
void			remove_from_env(char *arg, char **env, int l);
char			**ft_sort_env(char **env);
void			check_arg_export(char *arg, char **env);
void			add_to_env(char *arg, char **env);
void			add_to_env_norm(char *name, char *value, char *f, char **env);
void			set_new_norm(char **env, char *name, char *f);
void			set_new(char *arg, char **env);
char			*final_srt_add(char *value, char *name);
void			ft_print_export_error(char *arg);
void			ft_print_export(char **t, int i, int k);
int				ft_isalpha(int c);
int				ft_do_nothing(char *arg);
char			*final_srt(char *arg, char *name, int i);
void			ft_export(char **env, char **arg);
void			ft_exit(char **arg,char **env);
int				get_glo_2(int i, int j);
void			get_var_2_utils(char *env, int j, char **ret, int k);
t_spl			get_command(char **env, int fd);
void			free_2(char **str);
void			edit_ret(char **str);
char			**cpy_2(char **str);
t_spl			get_comm(int fd, char ***ret, char ***ret2, char **env);
int				check_pr(char **str);
int				ft_atoi(const char *str);
char			*ft_strchr(const char *s, int c);
void			ft_putstr_fd(char *s, int fd);
int				check_redi(t_spl *comm, int t, int *st, int *fdd);
int				check_next(t_spl *comm, int t, int i);
void			remove_from_env(char *arg, char **env, int l);
void			ft_print_env(char **env);
void    		get_dup_2(int r, int fd, int *std);
void			get_here_doc(t_spl *comm, t_arg tt, int *fd, int *st);
int				check_k(int k, t_spl *comm, t_arg tt);
int				fd_utils_4(t_spl *c, t_arg tt, int **std, int r);
char			**get_aftere_red(t_spl *comm, int i, int k, int t);
int				get_fd(t_spl *comm, t_arg tt, int *fdd, int *st);
void			get_dup(int r, int fd, int *std);
int				get_fd_utils_1(t_spl *comm, t_arg tt, int **std, int *fd);
void			get_default(int *fd, int **std);
int				fd_utils_2(t_spl *comm, int t, int i, int **std);
int				fd_utils_1(t_spl *c, int t, int i, int **std);
void			ft_printf_error(char *com, int i);
int				free_two(int *fd, int **std);
int				fd_utils_3(t_spl *comm, t_arg tt, int *fd, int *st);
int				get_glo_3(int i);
int				get_glo_4(int i);
struct termios	get_term(struct termios term, int i);
int				check_command(char **env, char **splited, int t);
void			child_exec(char ***splited, char *path, int t, char **env);

#endif