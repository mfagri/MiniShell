/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:46:11 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/08 14:46:14 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_command_utils(char **splited, char **env, int t, int fd)
{
	if (!(ft_strcmp(splited[0], "pwd")))
		ft_pwd(splited, fd);
	else if (!(ft_strcmp(splited[0], "cd")))
		ft_cd(splited, env, fd);
	else if (!(ft_strcmp(splited[0], "env")))
		ft_print_env(env, fd);
	else if (!(ft_strcmp(splited[0], "exit")))
	{
		if (!t)
			ft_exit(splited, env);
	}
	else
		return (1);
	return (0);
}

int	check_command(char **env, char **splited, int t, int fd)
{
	if (!(ft_strcmp(splited[0], "export")))
		ft_export(env, splited, fd);
	else if (!(ft_strcmp(splited[0], "unset")))
		ft_unset(splited, env, fd);
	else if (!(ft_strcmp(splited[0], "echo")))
		ft_echo(splited, fd);
	else
		return (check_command_utils(splited, env, t, fd));
	return (0);
}

int	check_shlvl(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("SHLVL=", env[i], ft_strlen("SHLVL=")))
			return (1);
		i++;
	}
	return (0);
}

void	shlvl_increment(char **env, int i)
{
	char	*tmp;
	int		k;
	char	*t;
	char	*s;

	tmp = cpy (tmp, "SHLVL=");
	t = ft_strrchr(env[i], '=');
	k = ft_atoi(++t) + 1;
	s = ft_itoa(k);
	tmp = ft_strjoin(tmp, s);
	free (s);
	env[i] = cpy (env[i], tmp);
	free (tmp);
}

void	get_env(char **env)
{
	int	i;

	i = -1;
	if (check_shlvl(env))
	{
		while (env[++i])
		{
			if (!ft_strncmp("SHLVL=", env[i], 6))
			{
				shlvl_increment(env, i);
				i++;
			}
			env[i] = cpy (env[i], env[i]);
		}
	}
	else
	{
		while (env[++i])
			env[i] = cpy (env[i], env[i]);
		env[i] = cpy (env[i], "SHLVL=1");
		env[i + 1] = NULL;
	}
}
