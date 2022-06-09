/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:32:06 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/09 18:21:21 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_env_norm2(char **env, char *value, int i)
{
	if (ft_strchr(env[i], '='))
			env[i] = ft_strjoin(env[i], value);
	else
	{
			env[i] = ft_strjoin(env[i], "=");
			env[i] = ft_strjoin(env[i], value);
	}
}

void	add_to_env_norm(char *name, char *value, char *f, char **env)
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
			add_to_env_norm2(env, value, i);
		}
		free_2(t);
	}
	if (j != 123456)
	{
		env[i] = cpy (env[i], f);
		i++;
	}
	env[i] = NULL;
	return (free(value), free(name), free(f));
}

void	add_to_env(char *arg, char **env)
{
	int		i;
	char	*name;
	char	*value;
	char	*f;
	int		j;

	i = 0;
	while (arg[i] != '+')
		i++;
	name = malloc(i + 1);
	i = -1;
	while (arg[++i] != '+')
		name[i] = arg[i];
	name[i] = '\0';
	value = malloc(ft_strlen(arg) - i + 1);
	j = 0;
	i++;
	if (arg[i] == '=')
		i++;
	while (arg[i])
		value[j++] = arg[i++];
	value[i] = '\0';
	f = final_srt_add(value, name);
	add_to_env_norm(name, value, f, env);
	return ;
}

int	check_arg_export(char *arg, char **env)
{
	int	j;

	if (export_is_invalid(arg))
		return (ft_print_export_error(arg));
	j = 0;
	while (arg[j] != '+' && arg[j] != '=')
		j++;
	if (ft_do_nothing(arg))
		return (0);
	else
	{
		if (arg[j] == '+')
		{
			if (arg[j + 1] == '+' || arg[j + 1] != '=')
				return (ft_print_export_error(arg));
			add_to_env(arg, env);
		}
		else if (arg[j] == '=')
			set_new(arg, env);
		else if (!(strchr(arg, '=')) && !(ft_strchr(arg, '+')))
			set_new(arg, env);
	}
	return (0);
}

char	**ft_sort_env(char **env)
{
	char	**t;
	int		i;
	int		k;
	int		j;

	i = 0;
	while (env[i])
		i++;
	t = malloc(sizeof(char *) * (i + 1));
	t[i] = NULL;
	i = -1;
	while (env[++i])
	{
		j = -1;
		k = 0;
		while (env[++j])
			if (ft_strncmp(env[i], env[j], ft_strlen(env[i])) > 0)
				k++;
		t[k] = cpy(t[k], env[i]);
	}
	return (t);
}
