#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 1
# define HISTORY_PATH "/Users/aaitoual/.minishell_history"
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

typedef struct s_main
{
	int	i;
	int l;
}	t_main;

t_main g_globle;

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
int				exec(int fd, char **env, struct termios terminal2);
int				get_glo(int i);
void			get_tt(void);
int 			ft_echo(char **pr);
void			ft_pwd();
void			ft_cd(char **pr);
char			***split_pr(char **pr, int i, int k, char q);
char			**get_ret(char **pr, int i);
char			get_q(char **pr, int i, int j, char q);
struct termios	remove_ctlc(void);
char			get_q_1(char *pr, int i, char q);
char			*remove_qu(char *str, int i, int j);
int				check_next_qu(char *str, char c, int i);
char			*get_arg(char *str, int i, int t);
int				get_spaces(char *str);
char			*get_var(char *str, char **env, int j);
char  			*get_var_utils_1(char *str, int *j, int *k);
char			**edit_var(char **ret, char **env);
char			**edit_qu(char **str);
char			*sep(char *str, int i, int k);
char			*get_new_path(char **env, char *cmd);
char			*remove_pwd(char **env, int i);
#endif