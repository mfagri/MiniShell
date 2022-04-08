/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:53:22 by aaitoual          #+#    #+#             */
/*   Updated: 2021/11/15 15:53:23 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"../minishell.h"

int	check_next_ln(char *curr)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (curr && curr[i])
	{
		if (curr[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	new_line_index(char	*all)
{
	int	i;

	i = 0;
	while (all && all[i] != '\0' && all[i] != '\n')
		i++;
	if (all && all[i] == '\n')
		i++;
	return (i);
}
