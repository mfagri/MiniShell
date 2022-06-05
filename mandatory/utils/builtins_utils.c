/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:06:41 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/04 21:51:44 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			ft_putstr_fd(env[i], 1);
			write(1, "\n", 1);
		}
		i++;
	}
}

void	remove_from_env(char *arg, char **env, int l)
{
	int	i;
	int	j;

	if (!(ft_isalpha(arg[0])) && arg[0] != '_'
		&& ft_strchr (arg, '=') && ft_strchr (arg, '+'))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return ;
	}
	i = -1;
	while (env[++i])
	{
		j = i + 1;
		if (!ft_strncmp(env[i], arg, ft_strlen(arg)))
		{
			free (env[i]);
			l = 1;
			while (env[j])
				env[i++] = env[j++];
		}
	}
	if (l)
		env[i - 1] = NULL;
}

void	ft_cd(char **arg, char **env)
{
	char	*oldpath;
	char	*newpath;

	oldpath = ft_take_pwd_old("OLDPWD=");
	if (!arg[1])
		ft_home(env);
	else
	{
		if (!ft_strncmp("-", arg[1], ft_strlen("-")))
			ft_oldpwd(env);
		else if (ft_count_args(arg) > 2)
		{
			free(oldpath);
			return (ft_putstr_fd("minishell: cd: too many arguments\n", 2));
		}
		else
			if (chdir(arg[1]) == -1)
				printf("minishell: cd: %s : No such file \
					or directory\n", arg[1]);
	}
	newpath = ft_take_pwd_old("PWD=");
	ft_cd_norm(env, oldpath, "OLDPWD");
	ft_cd_norm(env, newpath, "PWD");
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
		printf("minishell: exit: %s: numeric argument required\n", arg[1]);
	if (arg[1])
		t = ft_exit_utils(arg, t, j);
	i = -1;
	while (env[++i])
		free(env[i]);
	exit (t);
}
