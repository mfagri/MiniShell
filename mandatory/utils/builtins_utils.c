/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:06:41 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/10 18:27:54 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(char **arg, char **env, int fd)
{
	char	*oldpath;
	char	*newpath;

	oldpath = ft_take_pwd_old("OLDPWD=");
	if (!arg[1])
	{
		if (!ft_home(env, oldpath, fd))
			return ;
	}
	else
	{
		if (!ft_cd_utils(arg, env, oldpath, fd))
			return ;
	}
	newpath = ft_take_pwd_old("PWD=");
	ft_cd_norm(env, oldpath, "OLDPWD");
	ft_cd_norm(env, newpath, "PWD");
	if (!fd)
		exit (0);
	get_glo_2(1, 0);
}

int	ft_exit_utils(char **arg, int t, int j)
{
	int	k;

	if (arg[1][j] == '+' || arg[1][j] == '-')
			j++;
	if (arg[1])
	{
		while (arg[1][k])
		{
			if (!ft_isdigit(arg[1][k]))
			{
				ft_printf_error(arg[1], 5);
				t = 255;
			}
			k++;
		}
	}
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

	t = get_glo_2(0, 0);
	i = 0;
	ft_putstr_fd("exit\n", 1);
	while (arg[i])
		i++;
	if (i >= 2)
		t = ft_exit_utils(arg, t, 0);
	if (i > 2 && t != 255)
	{
		get_glo_2(1, 1);
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2));
	}
	else if (arg[1] && t != 255)
	{
		t = ft_atoi(arg[1]);
		get_glo_2(1, t);
		exit_norm(arg[1], &t);
	}
	i = -1;
	while (env[++i])
		free(env[i]);
	exit (t);
}
