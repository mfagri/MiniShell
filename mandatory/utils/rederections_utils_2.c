/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederections_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 09:47:47 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/06 16:10:51 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    get_dup_2(int r, int fd, int *std)
{
	if (r == 1)
	{
		if (fd != -2)
        {
            close (fd);
			fd = open (".here_doc.txt", O_RDONLY, 0777);
			dup2 (fd, 0);
            close (fd);
        }
		if (std[0] != -2)
		{
			dup2 (std[0], 0);
			close (std[0]);
		}
		if (std[1] != -2)
		{
			// write (2, "yoo\n", 4);
			dup2 (std[1], 1);
			close (std[1]);
		}
	}
}

void	get_here_doc(t_spl *comm, t_arg tt, int *fd, int *st)
{
	char	*str;

	str = readline("> ");
	while (ft_strcmp(str, comm->b_var[tt.k][tt.r + 1]))
	{
		write ((*fd), str, ft_strlen(str));
		write ((*fd), "\n", 1);
		free (str);
		str = readline("> ");
	}
	free (str);
}

int	fd_utils_3(t_spl *comm, t_arg tt, int *fd, int *st)
{
	int		k;
	int		r;
	char	*str;

	r = 3;
	if (!(ft_strcmp("<<", comm->a_var[tt.k][tt.r])))
	{
		dup2(st[0], 0);
		dup2(st[1], 1);
		*fd = open (".here_doc.txt", O_CREAT | O_TRUNC | O_RDWR, 0777);
		get_here_doc(comm, tt, fd, st);
		r = 2;
	}
	return (r);
}

int	check_k(int k, t_spl *comm, t_arg tt)
{
	if (k == -1)
	{
		ft_printf_error(comm->a_var[tt.k][tt.r + 1], 1);
		return (0);
	}
	return (1);
}

int	fd_utils_4(t_spl *c, t_arg tt, int **std, int r)
{
	int	k;

	if (!(ft_strcmp("<", c->a_var[tt.k][tt.r])))
	{
		if (c->a_var[tt.k][tt.r + 1])
		{
			if (access(c->a_var[tt.k][tt.r + 1], F_OK))
			{
				ft_printf_error(c->a_var[tt.k][tt.r + 1], 3);
				return (0);
			}
			k = open (c->a_var[tt.k][tt.r + 1], O_RDONLY, 0777);
			if (!check_k(k, c, tt))
				return (0);
		}
		else
		{
			ft_printf_error(c->b_var[tt.k][tt.r + 1], 2);
			return (0);
		}
		(*std)[0] = k;
		r = 1;
	}
	return (r);
}
