/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:46:11 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/09 15:29:14 by aaitoual         ###   ########.fr       */
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

int	check_redi_2(t_spl *comm, int t, int i, int k)
{
	char	**tmp;
	t_arg	tt;
	int		*st;

	st = malloc (sizeof (int) * 2);
	st[0] = dup(0);
	st[1] = dup(1);
	get_here_doc_content(*comm, t, st);
	tt.k = t;
	tt.r = -1;
	if (!get_fd(comm, tt, NULL, st))
	{
		free (st);
		return (0);
	}
	while (comm->a_var[t][++k])
		t = t;
	tmp = get_aftere_red(comm, -1, k, t);
	i = -1;
	while (comm->a_var[t][++i])
		free (comm->a_var[t][i]);
	free (comm->a_var[t]);
	comm->a_var[t] = tmp;
	free (st);
	return (1);
}

int	check_command(char **env, t_spl *comm, int t, int fd)
{
	if (!check_redi_2(comm, t, -1, -1))
		return (1);
	if (!(ft_strcmp(comm->a_var[t][0], "export")))
		ft_export(env, comm->a_var[t], fd);
	else if (!(ft_strcmp(comm->a_var[t][0], "unset")))
		ft_unset(comm->a_var[t], env, fd);
	else if (!(ft_strcmp(comm->a_var[t][0], "echo")))
		ft_echo(comm->a_var[t], fd);
	else
		return (check_command_utils(comm->a_var[t], env, t, fd));
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
