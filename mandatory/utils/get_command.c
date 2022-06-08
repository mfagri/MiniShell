/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:08:09 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/08 15:45:42 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_spl	check_tmp(char **tmp, int fd, char **env)
{
	t_spl	ret;
	int		i;

	i = -1;
	if (!(*tmp))
	{
		write (1, "\033[1A\033[11Cexit\n", 14);
		while (env[++i])
			free (env[i]);
		exit (0);
	}
	if (!ft_strncmp("(null)", (*tmp), ft_strlen((*tmp))))
	{
		free ((*tmp));
		return (get_command(env, fd));
	}
	add_history((*tmp));
	if ((*tmp))
	{
		write (fd, "\n", 1);
		write (fd, (*tmp), ft_strlen((*tmp)));
	}
	ret.a_var = NULL;
	return (ret);
}

int	get_comm_loop(char **tmp, char ***ret, int *i, int *k)
{
	static char	r;
	static int	t;

	if ((*i) == 0)
	{
		t = -1;
		r = '\0';
	}
	r = get_q_1((*tmp), (*i), r);
	if (((*tmp)[(*i)] == ' ' && (*tmp)[(*i) + 1] != ' ' && (*tmp)[(*i) + 1]))
	{
		if (!r)
		{
			(*ret)[(*k)] = get_arg((*tmp), (*i), t);
			(*k)++;
			t = (*i);
			(*i)++;
			r = get_q_1((*tmp), (*i), r);
		}
	}
	return (t);
}

char	**get_command_utils(char **tmp, int i, int k)
{
	char	**ret;
	char	*tmp2;
	int		t;

	t = -1;
	ret = malloc (sizeof(char *) * (get_spaces(*tmp) + 1));
	tmp2 = cpy(tmp2, (*tmp));
	free ((*tmp));
	(*tmp) = sep(tmp2, 0, 0);
	free (tmp2);
	i = -1;
	while ((*tmp)[++i])
	{
		t = get_comm_loop(tmp, &ret, &i, &k);
		if (!(*tmp)[i])
			break ;
	}
	if (i - t - 1 > 0 && (*tmp)[t + 1])
		ret[k++] = get_arg((*tmp), i, t);
	free ((*tmp));
	ret[k] = NULL;
	return (ret);
}

t_spl	exit_checker(char ***ret, char **env, int fd)
{
	t_spl	comm;

	comm.a_var = NULL;
	if (!check_pr(*ret))
	{
		ft_putstr_fd ("syntax error\n", 2);
		get_glo_2(1, 258);
		free_2(*ret);
		return (get_command(env, fd));
	}
	return (comm);
}

t_spl	get_command(char **env, int fd)
{
	char		*tmp;
	char		**ret;
	char		**ret2;
	t_spl		comm;
	// static int i = 0;
	
	// if (!i++)
	// 	tmp = get_next_line(open ("s", O_RDONLY));
	// tmp = get_next_line(0);
	get_glo_3(1);
	tmp = readline ("minishell=> ");
	get_glo_3(0);
	comm = check_tmp(&tmp, fd, env);
	if (comm.a_var)
		return (comm);
	ret = get_command_utils(&tmp, -1, 0);
	comm = exit_checker(&ret, env, fd);
	if (comm.a_var)
		return (comm);
	ret2 = cpy_2(ret);
	return (get_comm(fd, &ret, &ret2, env));
}
