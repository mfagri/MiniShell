/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:52:02 by aaitoual          #+#    #+#             */
/*   Updated: 2021/11/05 15:52:25 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;
	int	j;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && n-- > 0)
	{
		if (s1[i] != s2[i])
		{
			j = (unsigned char) s1[i] - (unsigned char) s2[i];
			return (j);
		}
		i++;
	}
	return (0);
}
