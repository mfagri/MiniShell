/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 08:01:16 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/11 12:43:53 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	get_var_2_utils(char *env, int j, char **ret, int k)
{
	int	i;

	i = 0;
	while (env[j++] != '=')
		i = i + 1 - 1;
	*ret = malloc (sizeof (char) * (ft_strlen(env) - j + 1));
	while (env[j])
		(*ret)[k++] = env[j++];
	(*ret)[k] = '\0';
}

void	get_return_value(char **ret)
{
	char	*tmp;

	tmp = ft_itoa(get_glo_2(0, 0));
	*ret = ft_strjoin(*ret, tmp);
	free (tmp);
}
