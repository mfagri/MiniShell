/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:06:41 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/07 18:41:30 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void	ft_cd_free(char *s, char *arg, int i)
{
	if(!arg && i)
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	else if(arg != NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}	
	free(s);
	exit (1);
}
void	ft_cd(char **arg, char **env)
{
	char	*oldpath;
	char	*newpath;

	oldpath = ft_take_pwd_old("OLDPWD=");
	if (!arg[1])
		ft_home(env,oldpath);
	else
	{
		if (!ft_strncmp("-", arg[1], ft_strlen("-")))
		{
			if(ft_oldpwd(env))
				ft_cd_free(oldpath,NULL,0);
		}
		else if (ft_count_args(arg) > 2)
			ft_cd_free(oldpath,NULL,1);
		else
			if (chdir(arg[1]) == -1)
				ft_cd_free(oldpath,arg[1],0);
	}
	newpath = ft_take_pwd_old("PWD=");
	ft_cd_norm(env, oldpath, "OLDPWD");
	ft_cd_norm(env, newpath, "PWD");
	exit (0);
}

int	ft_exit_utils(char **arg, int t, int j)
{
	if (ft_isalpha(arg[1][j]))
		t = 255;
	else if (!arg[2])
		t = ft_atoi(arg[1]);
	get_glo_2(1, t);
	return (t);
}

long double	ft_atoi_exit(const char *str)
{
	int				i;
	long long		a;
	long double		c;

	i = 0;
	a = 1;
	c = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			a = -a;
		}
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		c = c * 10 + (str[i] - '0');
		i++;
	}
	return (a * c);
}

void	exit_norm(char *arg, int *t)
{
	long double	l;
	long double	n;

	l = ft_atoi_exit("9223372036854775807");
	n = ft_atoi_exit("-9223372036854775808");
	if (ft_atoi_exit(arg) > l || ft_atoi_exit(arg) < n)
	{
		ft_printf_error(arg, 5);
		*t = 255;
	}
	return ;
}

void	ft_exit(char **arg, char **env)
{
	int	i;
	int	t;
	int	j;

	t = get_glo_2(0, 0);
	i = 0;
	j = 0;
	while (arg[i])
		i++;
	if (i >= 2)
		if (arg[1][j] == '+' || arg[1][j] == '-')
			j++;
	ft_putstr_fd("exit\n", 1);
	if (i > 2 && !ft_isalpha(arg[1][j]))
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	if (i >= 2 && ft_isalpha(arg[1][j]))
		ft_printf_error(arg[1], 5);
	if (arg[1])
		t = ft_exit_utils(arg, t, j);
	if (i > 1)
		exit_norm(arg[1], &t);
	i = -1;
	while (env[++i])
		free(env[i]);
	exit (t);
}
