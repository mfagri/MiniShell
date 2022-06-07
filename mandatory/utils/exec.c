/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:33:29 by mfagri            #+#    #+#             */
/*   Updated: 2022/06/07 18:12:57 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_utils_1(t_spl comm, int *t, int *st, char **env)
{
	int		r;
	char	*path;
	int		*fdd;
	
	fdd = malloc (sizeof (int) * 2);
	if (comm.a_var[(*t) + 1])
		pipe(fdd);
	if (!comm.a_var[(*t)][0])
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
		if (comm.a_var[(*t) + 1])
			dup2 (fdd[1], 1);
		check_redi(&comm, (*t), st, fdd);
		if (comm.a_var[(*t) + 1])
		{
			close ((fdd)[0]);
			close ((fdd)[1]);
		}
		check_command(env, comm.a_var[(*t)], (*t));
		path = get_path(env, comm.a_var[(*t)][0]);
		child_exec(comm.a_var, path, (*t), env);
	}
	if (comm.a_var[(*t) + 1])
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
	(*t)++;
	free (fdd);	
	return (r);
}

int	exec(int fd, char **env)
{
	int		*r;
	int		k;
	int		i;
	int		j = -1;
	int		t;
	int		st[2];
	int		fdd[2];
	char	*path;
	t_spl	comm;

	comm = get_command(env, fd);
	st[0] = dup(0);
	st[1] = dup(1);
	fdd[0] = -2;
	fdd[1] = -2;
	k = -1;
	t = -1;
	k = -1;
	t = -1;
	t = -1;
	k = 0;
	while (comm.a_var[++t])
		k++;
	r = malloc (sizeof(int) * (k + 1));
	k = -1;
	t = 0;
	while (comm.a_var[t])
	{
		r[t] = exec_utils_1(comm, &t, st, env);
		if (!r[t])
			break ;
	}
	r[t] = '\0';
	while (--t != -1)
	{
		get_glo(1);
		waitpid(r[t], &k, 0);
	}
	dup2(st[0], 0);
	dup2(st[1], 1);
	close (st[0]);
	close (st[1]);
	if (WIFSIGNALED(k))
	{
		if(get_glo_2(1, k + 128) == 130)
			write(1,"\n",1);
	}
	else if (WEXITSTATUS(k))
		get_glo_2(1, k / 128 / 2);
	if (k >= 25600)
		get_glo_2(1, (k * 100) / 25600);
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