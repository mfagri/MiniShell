/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:33:29 by mfagri            #+#    #+#             */
/*   Updated: 2022/06/08 10:57:06 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_utils_1(t_spl comm, int t, int *st, char **env)
{
	int		r;
	char	*path;
	int		*fdd;
	
	r = 1;
	fdd = malloc (sizeof (int) * 2);
	if (comm.a_var[t + 1])
		pipe(fdd);
	if (!comm.a_var[t][0] && r)
	{
		dup2(st[0], 0);
		dup2(st[1], 1);
		close (st[0]);
		close (st[1]);
		return (0);
	}
	r = fork();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
	if (!r)
	{
		if (comm.a_var[t + 1])
			dup2 (fdd[1], 1);
		check_redi(&comm, t, st, fdd);
		if (comm.a_var[t + 1])
		{
			close (fdd[0]);
			close (fdd[1]);
		}
		check_command(env, comm.a_var[t], t, r);
		path = get_path(env, comm.a_var[t][0]);
		child_exec(comm.a_var, path, t, env);
	}
	if (comm.a_var[t + 1])
	{
		dup2 ((fdd)[0], 0);
		close ((fdd)[0]);
		close ((fdd)[1]);
	}
	else
	{
		dup2 (st[1], 1);
		dup2 (st[0], 0);
		close (st[0]);
		close (st[1]);
	}
	free (fdd);
	return (r);
}

int	get_default_2(int *k, int **st, t_spl comm, int **r)
{
	int	i;

	i = -1;
	while (comm.a_var[++i])
		i = i;
	*r = malloc (sizeof(int) * (i + 1));
	*st = malloc (sizeof(int) * 2);
	(*st)[0] = dup(0);
	(*st)[1] = dup(1);
	*k = -1;
	return (-1);	
}

void	return_handler(int k)
{
	if (WIFSIGNALED(k))
	{
		if(get_glo_2(1, k + 128) == 130)
			write(1,"\n",1);
	}
	else if (WEXITSTATUS(k))
	{
		get_glo_2(1, k / 128 / 2);
	}
	else if (k >= 25600)
		get_glo_2(1, (k * 100) / 25600);
	else
		get_glo_2(1, 0);
}

int	exec(int fd, char **env)
{
	int		*r;
	int		k;
	int		t;
	int		*st;
	t_spl	comm;

	comm = get_command(env, fd);
	t = get_default_2(&k, &st, comm, &r);
	if (!comm.a_var[1] && !check_command(env, comm.a_var[0], 0, 1))
		t++;
	if (comm.a_var[t + 1])
	{
		while (comm.a_var[++t])
		{
			r[t] = exec_utils_1(comm, t, st, env);
			if (!r[t])
				break ;
		}
		r[t] = '\0';
		while (--t != -1)
		{
			get_glo(1);
			waitpid(r[t], &k, 0);
		}
		return_handler(k);
		dup2(st[0], 0);
		dup2(st[1], 1);
		close (st[0]);
		close (st[1]);
	}
	k = -1;
	while (comm.a_var[++k])
		free_2 (comm.a_var[k]);
	free (comm.a_var);
	k = -1;
	while (comm.b_var[++k])
		free_2 (comm.b_var[k]);
	free (comm.b_var);
	free (r);
	return (1);
}