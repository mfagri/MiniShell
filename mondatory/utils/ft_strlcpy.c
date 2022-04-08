/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:50:39 by aaitoual          #+#    #+#             */
/*   Updated: 2021/11/11 19:38:07 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"../minishell.h"

static size_t	lenp(const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	*cpy(char *dest, const char *src)
{
	size_t	i;
	size_t	r;

	i = 0;
	r = lenp(src);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	i = 0;
	while (src[i] != '\0')
		i++;
	return (i);
}
