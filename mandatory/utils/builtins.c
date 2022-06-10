/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 04:30:33 by mfagri            #+#    #+#             */
/*   Updated: 2022/06/10 19:36:30 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	ft_check_n(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if ((!s1 || !s2))
		return (1);
	if (s1[i] == '-')
	{
		i++;
		while (s1[i])
		{
			if (s1[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

void	ft_echo(char **pr, int fd)
{
	int		i;
	int		n_option;

	i = 1;
	n_option = 0;
	while (pr[i] && ft_check_n(pr[i], "-n") == 0)
	{
		if (pr[i][1] == 'n')
			n_option = 1;
		if (pr[i][1] != 'n')
			break ;
		i++;
	}
	while (pr[i])
	{
		ft_putstr_fd(pr[i], 1);
		if (pr[i + 1] && pr[i][0] != '\0')
			write(1, " ", 1);
		i++;
	}
	if (n_option == 0)
		write(1, "\n", 1);
	if (!fd)
		exit (0);
	get_glo_2(1, 0);
}

void	ft_pwd(char **arg, int fd)
{
	char	s[1024];

	getcwd(s, sizeof(s));
	if (!s[0])
	{
		ft_putstr_fd("pwd\n", 2);
		exit (1);
	}
	printf("%s\n", s);
	if (!fd)
		exit (0);
}

void	ft_unset(char **arg, char **env, int fd)
{
	int	i;

	i = 0;
	while (arg[++i])
		remove_from_env(arg[i], env, 0, fd);
	if (!fd)
		exit (0);
	get_glo_2(1, 0);
}
