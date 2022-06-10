/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:30:00 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/10 15:00:15 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (get_glo_2(1, k + 128) == 130)
			write(1, "\n", 1);
		if (get_glo_2(1, k + 128) == 131)
			write(1, "Quit: 3\n", 8);
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

void	return_default(t_spl *comm, int k, int **st, int **r)
{
	get_glo(1);
	return_handler(k);
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
