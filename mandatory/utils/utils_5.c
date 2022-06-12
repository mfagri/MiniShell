/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:29:17 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/12 12:19:22 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shlvl_increment(char **env, int i)
{
	char	*tmp;
	int		k;
	char	*t;
	char	*s;

	tmp = cpy (NULL, "SHLVL=");
	t = ft_strrchr(env[i], '=');
	k = ft_atoi(++t) + 1;
	if(k < 0)
		k = 0;
	s = ft_itoa(k);
	tmp = ft_strjoin(tmp, s);
	free (s);
	env[i] = cpy (env[i], tmp);
	free (tmp);
}
