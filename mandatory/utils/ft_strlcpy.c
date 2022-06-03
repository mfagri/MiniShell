/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:50:39 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/03 18:21:13 by mfagri           ###   ########.fr       */
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

char	*cpy(char *tmp, char *src)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc (sizeof (char) * (ft_strlen(src) + 2));
	while (src && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
