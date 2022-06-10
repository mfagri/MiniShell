/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederections_utils_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 09:48:33 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/10 12:47:09 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_default(int *fd, int **std)
{
	(*std) = malloc (sizeof (int) * 2);
	(*std)[0] = -2;
	(*std)[1] = -2;
	(*fd) = -2;
}

int	get_fd_utils_1(t_spl *comm, t_arg tt, int **std, int *fd)
{
	int	k;
	int	r;

	r = -1;
	k = fd_utils_1(comm, tt.k, tt.r, std);
	if (k == 1 || k == 2)
		r = k;
	if (!k)
		return (free_two(fd, std));
	k = fd_utils_2(comm, tt.k, tt.r, std);
	if (k == 1 || k == 2)
		r = k;
	if (!k)
		return (free_two(fd, std));
	k = fd_utils_4(comm, tt, std, 3);
	if (k == 1 || k == 2)
		r = k;
	if (!k)
		return (free_two(fd, std));
	return (r);
}

void	get_dup(int r, int fd, int *std)
{
	if (r == 2)
	{
		if (std[0] != -2)
		{
			dup2 (std[0], 0);
			close (std[0]);
		}
		if (std[1] != -2)
		{
			dup2 (std[1], 1);
			close (std[1]);
		}
		if (fd != -2)
		{
			fd = open (".here_doc.txt", O_RDONLY, 0777);
			dup2 (fd, 0);
			close (fd);
		}
	}
	get_dup_2(r, fd, std);
}

int	get_fd(t_spl *comm, t_arg tt, int *fdd, int *st)
{
	int		fd;
	int		*std;
	int		t;
	int		k;
	int		r;

	r = 0;
	get_default(&fd, &std);
	while (comm->a_var[tt.k][++tt.r])
	{
		t = get_fd_utils_1(comm, tt, &std, &fd);
		if (t == 0)
			return (0);
		if (t != -1)
			r = t;
		k = fd_utils_3(comm, tt, &fd, st);
		if (k == 1 || k == 2)
			r = k;
		if (!k)
			return (free_two(&fd, &std));
	}
	get_dup(r, fd, std);
	free (std);
	return (1);
}

char	**get_aftere_red(t_spl *comm, int i, int k, int t)
{
	char	**tmp;

	tmp = malloc (sizeof (char *) * (k + 1));
	k = 0;
	while (comm->a_var[t][++i])
	{
		if (!(ft_strcmp(">", comm->a_var[t][i]))
			|| !(ft_strcmp("<", comm->a_var[t][i]))
			|| !(ft_strcmp(">>", comm->a_var[t][i])))
			i++;
		else if (!(ft_strcmp("<<", comm->a_var[t][i])))
		{
			if (check_next(comm, t, i + 1))
				i++;
		}
		else
		{
			tmp[k] = cpy(tmp[k], comm->a_var[t][i]);
			k++;
		}
		if (!comm->a_var[t][i])
			break ;
	}
	tmp[k] = NULL;
	return (tmp);
}
