/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 08:01:16 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/03 08:01:17 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	get_var_2_utils(char *env, int j, char **ret, int k)
{
	int	i;

	i = 0;
	while (env[j++] != '=')
		i = i;
	*ret = malloc (sizeof (char) * (ft_strlen(env) - j + 1));
	while (env[j])
		(*ret)[k++] = env[j++];
	(*ret)[k] = '\0';
}
