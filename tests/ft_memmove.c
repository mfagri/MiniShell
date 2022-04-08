/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:33:12 by aaitoual          #+#    #+#             */
/*   Updated: 2021/11/11 19:34:19 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

void	*ft_memmove(void *d, const void *s, size_t i)
{
	unsigned int	r;
	unsigned int	p;
	char			*dest;
	const char		*src;

	r = 0;
	dest = d;
	src = s;
	if (src == NULL && dest == NULL)
		return (NULL);
	if (s > d)
		p = 0;
	if (s < d)
		p = 1;
	while (p == 0 && i-- > 0)
	{
		dest[r] = src[r];
		r++;
	}
	while (p == 1 && i-- > 0)
		dest[i] = src[i];
	return (d);
}
