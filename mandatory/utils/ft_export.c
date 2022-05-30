/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:25:32 by mfagri            #+#    #+#             */
/*   Updated: 2022/05/29 19:18:06 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_export(char **t, int i, int k)
{
	int	j;
	int	l;

	i = -1;
	while (t[++i])
	{
		k = 0;
		if (t[i][0])
			write (1, "declare -x ", 12);
		j = -1;
		l = 0;
		while (t[i][++j])
		{
			write(1, &t[i][j], 1);
			if (t[i][j] == '=')
			{
				k = 1;
				if (l == 0 && ++l)
					write (1, "\"", 1);
			}
		}
		if (k == 1)
			write (1, "\"", 1);
		write (1, "\n", 1);
	}
}

int	ft_isalpha(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90))
		return (1);
	return (0);
}

int	ft_do_nothing(char *arg)
{
	int	j;
	int	a;
	int	n;

	a = 0;
	n = 0;
	j = 0;
	while (arg[j])
	{
		if (!(ft_isalpha(arg[j])) && (arg[j] != '_'))
			break ;
		if (ft_isalpha(arg[j]))
			a++;
		if (arg[j] == '_')
			n++;
		j++;
	}
	if (n == 2)
		return (0);
	else if (n == 1 && a == 0)
		return (1);
	return (0);
}

char	*final_srt(char *arg, char *name, int i)
{
	char	*value;
	char	*f;
	int		j;

	f = malloc(1);
	f[0] = '\0';
	value = malloc(ft_strlen(arg) - i + 1);
	j = 0;
	i++;
	while (arg[i])
		value[j++] = arg[i++];
	value[i] = '\0';
	f = ft_strjoin(f, name);
	if (strchr(arg, '='))
		f = ft_strjoin(f, "=");
	if (value[0])
		f = ft_strjoin(f, value);
	free(value);
	return (f);
}

void	ft_export(char **env, char **arg)
{
	int		i;
	char	**t;

	t = ft_sort_env(env);
	i = 1;
	if (!arg[i])
		ft_print_export(t, -1, 0);
	else
		while (arg[i])
			check_arg_export(arg[i++], env);
	i = 0;
	while(t[i])
		free(t[i++]);
}
