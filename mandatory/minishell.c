/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 09:40:16 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/07 20:13:41 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_glo_2(int i, int j)
{
	static int	yo;

	if (i)
		yo = j;
	return (yo);
}

int	get_t(char *tmp, int t)
{
	while (tmp[++t])
	{
		if (tmp[t] == ' ')
			break ;
	}
	return (t);
}

void	edit_ret(char **str)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = -1;
	j = -1;
	k = 0;
	while (str[++i])
	{
		if (!str[i][0])
			i++;
		if (!str[i])
			break ;
		tmp = cpy (tmp, str[i]);
		free (str[k]);
		str[k] = cpy (str[k], tmp);
		free (tmp);
		k++;
	}
	if (str[i - 1] && !str[i - 1][0])
		free (str[i - 1]);
	i = -1;
	str[k] = NULL;
}

void	free_2(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free (str);
}

char	**cpy_2(char **str)
{
	int		i;
	int		j;
	char	**ret;

	i = -1;
	while (str[++i])
		i = i;
	ret = malloc (sizeof (char *) * (i + 1));
	i = -1;
	while (str[++i])
		ret[i] = cpy(ret[i], str[i]);
	ret[i] = NULL;
	return (ret);
}

void	child_exec(char ***splited, char *path, int t, char **env)
{
	if (path && access(path, F_OK | X_OK))
		exit (126);
	if (execve(path, splited[t], env) == -1)
	{
		ft_printf_error(splited[t][0], 4);
		exit (127);
	}
	exit (0);
}

int	remove_path_2(char *str)
{
	if (str[0] == '/' || str[0] == '.')
		return (1);
	return (0);
}

char	*remove_pwd(char **env, int i)
{
	char	*ret;
	int		k;

	k = 3;
	ret = malloc (sizeof(char) * (ft_strlen(env[i]) - 2));
	while (env[i][++k])
		ret[k - 4] = env[i][k];
	ret[k - 4] = '\0';
	return (ret);
}

int	check_next(t_spl *comm, int t, int i)
{
	int	k;

	k = 0;
	while (comm->b_var[t][i] && ft_strcmp(comm->b_var[t][i], "|"))
	{
		if (!comm->a_var[t][i])
			return (0);
		if (ft_strcmp(comm->a_var[t][i], comm->b_var[t][i]))
			return (0);
		i++;
	}
	return (1);
}

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
	while(env[i])
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
	if(check_shlvl(env))
		while(env[++i])
		{
			if (!ft_strncmp("SHLVL=", env[i], 6))
			{
				shlvl_increment(env,i);
				i++;
			}
			env[i] = cpy (env[i], env[i]);
		}
	else
	{
		while(env[++i])
			env[i] = cpy (env[i], env[i]);
		env[i] = cpy (env[i], "SHLVL=1");
		env[i+1] = NULL;
	}
}



int	main(int ac, char **av, char **env)
{
	int		fd;

	rl_catch_signals = 0;
	fd = get_history();
	get_env(env);
	signal(SIGINT, ft_sig);
	signal(SIGQUIT,ft_sig);
	while (1)
	{
		// get_glo_4(0);
		get_glo(0);
		exec(fd, env);
	}
}
