/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:30:00 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/11 12:52:46 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_default_2(int *k, int **st, t_spl comm, int **r)
{
	int	i;

	i = -1;
	while (comm.a_var[++i])
		i = i + 1 - 1;
	*r = malloc (sizeof(int) * (i + 1));
	*st = malloc (sizeof(int) * 2);
	(*st)[0] = dup(0);
	(*st)[1] = dup(1);
	*k = -1;
	return (-1);
}

void	return_default(t_spl *comm, int k, int **st, int **r)
{
	get_glo(1);
	dup2((*st)[0], 0);
	dup2((*st)[1], 1);
	close ((*st)[0]);
	close ((*st)[1]);
	free (*st);
	k = -1;
	while (comm->a_var[++k])
		free_2 (comm->a_var[k]);
	free (comm->a_var);
	k = -1;
	while (comm->b_var[++k])
		free_2 (comm->b_var[k]);
	free (comm->b_var);
	free (*r);
}

int	exec_utils_2(t_spl comm, int t, int *st, int **fdd)
{
	if (comm.a_var[t + 1])
		dup2 ((*fdd)[1], 1);
	if (!check_redi(&comm, t, st, *fdd))
		return (1);
	if (!comm.a_var[t][0])
		return (0);
	return (2);
}

int	exec_utils_1(t_spl comm, int t, int *st, char **env)
{
	int		r;
	char	*path;
	int		*fdd;

	get_here_doc_content(comm, t, st);
	if (!get_default_exec(&fdd, st, comm, t))
		return (0);
	r = fork();
	if (!r)
	{
		lah_ysame7(comm, t, st, &fdd);
		if (comm.a_var[t + 1])
		{
			close (fdd[0]);
			close (fdd[1]);
		}
		check_command(env, &comm, t, r);
		path = get_path(env, comm.a_var[t][0]);
		child_exec(comm.a_var, path, t, env);
	}
	after_exec(&fdd, st, comm, t);
	return (r);
}

void	get_value(int *r, int t, int k)
{
	while (r[++t])
	{
		if (r[t] != -1)
		{
			waitpid(r[t], &k, 0);
			if (WIFSIGNALED(k))
			{
				if (get_glo_2(1, k + 128) == 131)
					write(1, "Quit: 3\n", 8);
				else
					write(1, "\n", 1);
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
	}
}
