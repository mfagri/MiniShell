/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:06:41 by aaitoual          #+#    #+#             */
/*   Updated: 2022/05/26 22:43:54 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strchr(env[i], '='))
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
		&& strchr (arg, '=') && strchr (arg, '+'))
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
		if (!strncmp("-", arg[1], ft_strlen("-")))
			ft_oldpwd(env);
		else if (ft_count_args(arg) > 2)
			return (ft_putstr_fd("minishell: cd: too many arguments\n", 2));
		else
			if (chdir(arg[1]) == -1)
				printf("minishell: cd: %s : No such file \
					or directory\n", arg[1]);
	}
	newpath = ft_take_pwd_old("PWD=");
	ft_cd_norm(env, oldpath, "OLDPWD");
	ft_cd_norm(env, newpath, "PWD");
	free(oldpath);
	free(newpath);
}

void	ft_exit(char **arg, char **env)
{
	int	i;
	int	t;

	t = get_glo_2(0, 0);
	i = 0;
	while (arg[i])
		i++;
	ft_putstr_fd("exit\n", 1);
	if (i > 2)
		printf("minishell: exit: too many arguments\n");
	if (arg[1] && i <= 2)
	{
		t = atoi(arg[1]);
		get_glo_2(1, t);
	}
	i = 0;
	while (env[i++])
		free(env[i]);
	exit (t);
}
