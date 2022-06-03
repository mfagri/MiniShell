/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:32:06 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/03 18:29:37 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_env_norm(char *name, char *value, char *f, char **env)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], name, ft_strlen(name)))
		{
			j = 123456;
			if (strchr(env[i], '='))
				env[i] = ft_strjoin(env[i], value);
			else
			{
				env[i] = ft_strjoin(env[i], "=");
				env[i] = ft_strjoin(env[i], value);
			}
		}
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

void	check_arg_export(char *arg, char **env)
{
	int	j;

	if (!(ft_isalpha(arg[0])) && arg[0] != '_')
		return (ft_print_export_error(arg));
	j = 0;
	while ((ft_isalpha(arg[j])) || arg[j] == '_')
		j++;
	if (ft_do_nothing(arg))
		return ;
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
		else if (!(strchr(arg, '=')) && !(strchr(arg, '+')))
			set_new(arg, env);
	}
	return ;
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
