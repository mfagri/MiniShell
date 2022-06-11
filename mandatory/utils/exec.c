/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:33:29 by mfagri            #+#    #+#             */
/*   Updated: 2022/06/11 12:56:16 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_default_exec(int **fdd, int *st, t_spl comm, int t)
{
	*fdd = malloc (sizeof (int) * 2);
	if (comm.a_var[t + 1])
		pipe(*fdd);
	if (!comm.a_var[t][0])
	{
		dup2(st[0], 0);
		dup2(st[1], 1);
		close (st[0]);
		close (st[1]);
		return (0);
	}
	return (1);
}

void	after_exec(int **fdd, int *st, t_spl comm, int t)
{
	if (comm.a_var[t + 1])
	{
		dup2 ((*fdd)[0], 0);
		close ((*fdd)[0]);
		close ((*fdd)[1]);
	}
	else
	{
		dup2 (st[1], 1);
		dup2 (st[0], 0);
		close (st[0]);
		close (st[1]);
	}
	free (*fdd);
}

void	get_here_doc_content(t_spl comm, int t, int *st)
{
	int		fd;
	int		k;
	t_arg	tt;

	tt.k = t;
	tt.r = -1;
	while (comm.a_var[tt.k][++tt.r])
	{
		if (!(ft_strcmp("<<", comm.a_var[tt.k][tt.r])))
		{
			dup2(st[0], 0);
			dup2(st[1], 1);
			fd = open (".here_doc.txt", O_CREAT | O_TRUNC | O_RDWR, 0777);
			k = fork();
			if (k == 0)
				get_here_doc(&comm, tt, &fd, st);
			get_glo_4(0);
			waitpid (k, NULL, 0);
			close (fd);
		}
	}
}

void	lah_ysame7(t_spl comm, int t, int *st, int **fdd)
{
	int	i;

	i = exec_utils_2(comm, t, st, fdd);
	if (i == 1)
		exit (1);
	if (i == 0)
		exit (0);
}

int	exec(int fd, char **env)
{
	int		*r;
	int		k;
	int		t;
	int		*st;
	t_spl	comm;

	t = -1;
	comm = get_command(env, fd);
	t = get_default_2(&k, &st, comm, &r);
	if (!comm.a_var[1] && !check_command(env, &comm, 0, 1))
	{
		t++;
		r[0] = -1;
	}
	while (comm.a_var[++t])
	{
		r[t] = exec_utils_1(comm, t, st, env);
		if (!r[t])
			break ;
	}
	r[t] = '\0';
	get_value(r, -1, 0);
	return_default(&comm, k, &st, &r);
	unlink (".here_doc.txt");
	return (1);
}
