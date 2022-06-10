/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:12:08 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/10 14:30:57 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_two(int *fd, int **std)
{
	if ((*fd) != -2)
		close ((*fd));
	if ((*std)[0] != -2)
		close ((*std)[0]);
	if ((*std)[1] != -2)
		close ((*std)[1]);
	free (*std);
	return (0);
}

void	ft_printf_error(char *com, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(com, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	if (i == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(com, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
	}
	ft_printf_error_utils(com, i);
}

int	fd_utils_1(t_spl *c, int t, int i, int **std)
{
	int	k;
	int	r;

	r = 3;
	if (!(ft_strcmp(">", c->a_var[t][i])))
	{
		if (c->a_var[t][i + 1] && c->a_var[t][i + 1][0])
		{
			k = open (c->a_var[t][i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (k == -1)
			{
				ft_printf_error(c->a_var[t][i + 1], 1);
				return (0);
			}
		}
		else if (!ft_utils_return(c, t, i))
			return (0);
		(*std)[1] = k;
		r = 1;
	}
	return (r);
}

int	fd_utils_2(t_spl *comm, int t, int i, int **std)
{
	int	k;
	int	r;

	r = 3;
	if (!(ft_strcmp(">>", comm->a_var[t][i])))
	{
		if (comm->a_var[t][i + 1] && comm->a_var[t][i + 1][0])
		{
			k = open (comm->a_var[t][i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
			if (k == -1)
			{
				ft_printf_error(comm->a_var[t][i + 1], 1);
				return (0);
			}
		}
		else if (!ft_utils_return(comm, t, i))
			return (0);
		(*std)[1] = k;
		r = 1;
	}
	return (r);
}

int	check_redi(t_spl *comm, int t, int *st, int *fdd)
{
	int		i;
	int		k;
	char	**tmp;
	t_arg	tt;

	tt.k = t;
	tt.r = -1;
	if (!get_fd(comm, tt, fdd, st))
		return (0);
	i = -1;
	k = -1;
	while (comm->a_var[t][++k])
		t = t;
	tmp = get_aftere_red(comm, -1, k, t);
	i = -1;
	while (comm->a_var[t][++i])
		free (comm->a_var[t][i]);
	free (comm->a_var[t]);
	comm->a_var[t] = tmp;
	return (1);
}
