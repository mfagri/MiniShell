/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:30:52 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/10 12:16:59 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env(char **env, int fd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
		{
			ft_putstr_fd(env[i], 1);
			write(1, "\n", 1);
		}
		i++;
	}
	if (!fd)
		exit (0);
}

int	remove_from_env_utils(char **env, char *arg, int l, int *i)
{
	int		j;
	char	**t;
	char	*v;

	*i = -1;
	while (env[++(*i)])
	{
		j = (*i) + 1;
		if (ft_strchr(env[*i], '='))
		{
			t = ft_split(env[*i], '=');
			v = cpy(v, t[0]);
			free_2(t);
		}
		else
			v = cpy(v, env[*i]);
		if (!ft_strcmp(v, arg))
		{
			free (env[*i]);
			l = 1;
			while (env[j])
				env[(*i)++] = env[j++];
		}
	}
	return (l);
}

void	remove_from_env(char *arg, char **env, int l, int fd)
{
	int	i;
	int	j;

	if (export_is_invalid(arg))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		if (!fd)
			exit (1);
		return ;
	}
	l = remove_from_env_utils(env, arg, l, &i);
	if (l)
		env[i - 1] = NULL;
}
