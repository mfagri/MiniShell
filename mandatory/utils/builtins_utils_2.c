/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 08:50:42 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/08 11:39:35 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_home(char **env, char *s, int fd)
{
	int		i;
	char	*path;

	i = 0;
	while (ft_strncmp(env[i], "HOME", ft_strlen("HOME")))
		i++;
	if (env[i][4] == '=')
	{
		path = ft_strrchr(env[i], '=');
		path++;
	}
	else
		path = NULL;
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		free(s);
		if (!fd)
			exit(1);
		get_glo_2(1, 1);
		return (0);
	}
	return (1);
}

int	ft_oldpwd(char **env)
{
	int		i;
	char	*s;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp("OLDPWD", env[i], ft_strlen("OLDPWD")))
		{
			ft_putstr_fd(&env[i][7], 1);
			write(1, "\n", 1);
			s = ft_strrchr(env[i], '=');
			s++;
			if (chdir(s) == -1)
			{
				ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
				return (1);
			}
			return (0);
		}
	}
	ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	return (1);
}

char	*ft_take_pwd_old(char p[])
{
	char	pwd[1000000];
	char	*path;

	getcwd(pwd, sizeof(pwd));
	path = malloc(1);
	path[0] = '\0';
	path = ft_strjoin(path, p);
	path = ft_strjoin(path, pwd);
	return (path);
}

void	ft_cd_norm(char **env, char *path, char s[])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[++i])
	{
		if (!ft_strncmp(s, env[i], ft_strlen(s)))
		{
			j = 1;
			free(env[i]);
			env[i] = cpy(env[i], path);
		}
	}
	if (j != 1)
	{
		env[i] = cpy(env[i], path);
		i++;
	}
	env[i] = NULL;
	free(path);
}
