/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:59:31 by aaitoual          #+#    #+#             */
/*   Updated: 2021/11/06 17:01:20 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		k;
	int		j;
	char	*a;

	i = ft_strlen(s1) + ft_strlen(s2);
	j = 0;
	k = 0;
	a = malloc(i + 1);
	if (a == 0)
		return (0);
	while (s1 && s1[j] != '\0')
	{
		a[j] = s1[j];
		j++;
	}
	while (s2 && s2[k] != '\0')
		a[j++] = s2[k++];
	a[j] = '\0';
	if (s1)
		free (s1);
	return (a);
}
