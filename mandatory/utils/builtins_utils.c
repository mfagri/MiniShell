/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 20:06:41 by aaitoual          #+#    #+#             */
/*   Updated: 2022/05/26 22:43:54 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strchr(env[i], '='))
		{
			ft_putstr_fd(env[i], 1);
			write(1, "\n", 1);
		}
		i++;
	}
}

void	remove_from_env(char *arg, char **env, int l)
{
	int	i;
	int	j;

	if (!(ft_isalpha(arg[0])) && arg[0] != '_'
		&& strchr (arg, '=') && strchr (arg, '+'))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return ;
	}
	i = -1;
	while (env[++i])
	{
		j = i + 1;
		if (!ft_strncmp(env[i], arg, ft_strlen(arg)))
		{
			free (env[i]);
			l = 1;
			while (env[j])
				env[i++] = env[j++];
		}
	}
	if (l)
		env[i - 1] = NULL;
}
