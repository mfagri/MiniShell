/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:32:12 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/09 16:07:37 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export_utils(char **env, char **arg, int i, char **t)
{
	int	l;

	l = 0;
	if (!arg[i])
	{
		ft_print_export(t, -1, 0);
		l = 1;
	}
	else
		while (arg[i])
			if (check_arg_export(arg[i++], env))
				l = 0;
	return (l);
}

void	set_new_norm(char **env, char *name, char *f)
{
	int		i;
	int		j;
	char	**t;

	i = -1;
	while (env[++i])
	{
		t = ft_split(env[i], '=');
		if (!ft_strncmp(name, env[i], ft_strlen(t[0]))
			&& (ft_strlen(t[0]) == ft_strlen(name)))
		{
			j = 123456;
			if (ft_strchr(f, '='))
				env[i] = cpy(env[i], f);
		}
		free_2(t);
	}
	if (j != 123456)
	{
		env[i] = cpy (env[i], f);
		i++;
	}
	env[i] = NULL;
	free(f);
	free(name);
}

void	set_new(char *arg, char **env)
{
	int		i;
	char	*name;
	char	*f;
	int		j;

	i = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	name = malloc(i + 1);
	i = -1;
	while (arg[++i] != '=' && arg[i])
		name[i] = arg[i];
	name[i] = '\0';
	f = final_srt(arg, name, i);
	set_new_norm(env, name, f);
}

char	*final_srt_add(char *value, char *name)
{
	char	*f;

	f = malloc(1);
	f[0] = '\0';
	f = ft_strjoin(f, name);
	f = ft_strjoin(f, "=");
	f = ft_strjoin(f, value);
	return (f);
}

int	ft_print_export_error(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}
