/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rederections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 10:12:08 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/05 10:12:09 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_two(int **fd, int **std)
{
	if ((*fd)[0] != -2 || (*fd)[1] != -2)
	{
		close ((*fd)[1]);
		close ((*fd)[0]);
	}
	if ((*std)[0] != -2 || (*std)[1] != -2)
	{
		close ((*std)[1]);
		close ((*std)[0]);
	}
	free (*fd);
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
	if (i == 3)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(com, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

int	fd_utils_1(t_spl *c, int t, int i, int **std)
{
	int	k;
	int	r;

	r = 3;
	if (!(ft_strcmp(">", c->a_var[t][i])))
	{
		if (c->a_var[t][i + 1])
		{
			k = open (c->a_var[t][i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (k == -1)
			{
				ft_printf_error(c->a_var[t][i + 1], 1);
				return (0);
			}
		}
		else
		{
			ft_printf_error(c->a_var[t][i + 1], 2);
			return (0);
		}
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
		if (comm->a_var[t][i + 1])
		{
			k = open (comm->a_var[t][i + 1], O_WRONLY, 0777);
			if (k == -1)
			{
				ft_printf_error(comm->a_var[t][i + 1], 1);
				return (0);
			}
		}
		else
		{
			ft_printf_error(comm->a_var[t][i + 1], 2);
			return (0);
		}
		(*std)[1] = k;
		r = 1;
	}
	return (r);
}

void	get_here_doc(t_spl *comm, t_arg tt, int **fd, int *fdd)
{
	char	*str;

	str = readline("> ");
	while (ft_strcmp(str, comm->b_var[tt.k][tt.r + 1]))
	{
		if (!comm->a_var[tt.k + 1])
		{
			write ((*fd)[1], str, ft_strlen(str));
			write ((*fd)[1], "\n", 1);
		}
		free (str);
		str = readline("> ");
	}
	free (str);
}

int	fd_utils_3(t_spl *comm, t_arg tt, int **fd, int *fdd)
{
	int		k;
	int		r;
	char	*str;

	r = 3;
	if (!(ft_strcmp("<<", comm->a_var[tt.k][tt.r])))
	{
		if ((*fd)[0] == -2)
			pipe ((*fd));
		else
		{
			close ((*fd)[0]);
			close ((*fd)[1]);
			pipe ((*fd));
		}
		get_here_doc(comm, tt, fd, fdd);
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

void	get_default(int **fd, int **std)
{
	(*std) = malloc (sizeof (int) * 2);
	(*std)[0] = dup(0);
	(*std)[1] = dup(1);
	(*fd) = malloc (sizeof (int) * 2);
	(*fd)[0] = -2;
	(*fd)[1] = -2;
}

int	get_fd_utils_1(t_spl *comm, t_arg tt, int **std, int **fd)
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

void	get_dup(int r, int **fd, int **std)
{
	if (r == 2)
	{
		dup2 ((*std)[0], 0);
		dup2 ((*std)[1], 1);
		close ((*std)[0]);
		close ((*std)[1]);
		if ((*fd)[0] != -2 || (*fd)[1] != -2)
			dup2 ((*fd)[0], 0);
	}
	else if (r == 1)
	{
		if ((*fd)[0] != -2 || (*fd)[1] != -2)
			dup2 ((*fd)[0], 0);
		dup2 ((*std)[0], 0);
		dup2 ((*std)[1], 1);
		close ((*std)[0]);
		close ((*std)[1]);
	}
	if ((*fd)[0] != -2 || (*fd)[1] != -2)
	{
		close ((*fd)[1]);
		close ((*fd)[0]);
	}
}

int	get_fd(t_spl *comm, t_arg tt, int *fdd, int stdin)
{
	int		*fd;
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
		k = fd_utils_3(comm, tt, &fd, fdd);
		if (k == 1 || k == 2)
			r = k;
		if (!k)
			return (free_two(&fd, &std));
	}
	get_dup(r, &fd, &std);
	return (1);
}

int	check_redi(t_spl *comm, int t, int stdin, int *fdd)
{
	int		i;
	int		j;
	int		r = 0;
	int		k;
	char	**tmp;
	char	***splited = comm->a_var;
	char	***before = comm->b_var;
	char	*str;
	int		*fd;
	t_arg	tt;

	// i = -1;
	// while (comm->a_var[t][++i])
	// 	printf ("%s\n", comm->a_var[t][i]);
	tt.k = t;
	tt.r = -1;
	fd = malloc (sizeof (int) * 2);
	fd[0] = -2;
	fd[1] = -2;
	i = -1;
	k = -1;
	// puts ("yooo");
	if (!get_fd(comm, tt, fdd, stdin))
		return (0);
	i = -1;
	k = -1;
	while (splited[t][++k])
		t = t;
	tmp = malloc (sizeof (char *) * (k + 1));
	k = 0;
	while (splited[t][++i])
	{
		if (!(ft_strcmp(">", splited[t][i]))
			|| !(ft_strcmp("<", splited[t][i]))
			|| !(ft_strcmp(">>", splited[t][i])))
			i++;
		else if (!(ft_strcmp("<<", splited[t][i])))
		{
			if (check_next(comm, t, i + 1))
				i++;
		}
		else
		{
			tmp[k] = cpy(tmp[k], splited[t][i]);
			k++;
		}
		if (!splited[t][i])
			break ;
	}
	tmp[k] = NULL;
	i = -1;
	while (splited[t][++i])
		free (splited[t][i]);
	free (splited[t]);
	splited[t] = tmp;
	i = -1;
	k = -1;
	free (fd);
	return (1);
}
