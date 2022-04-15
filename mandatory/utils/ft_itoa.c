/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:15:55 by aaitoual          #+#    #+#             */
/*   Updated: 2021/11/11 21:02:05 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

static int	tol(long n)
{
	long	i;
	long	k;

	i = 0;
	k = 0;
	if (n < 0)
	{
		k = 1;
		n *= -1;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i + 1 + k);
}

static void	emer(char *a, int ich, int k, long n)
{
	int	i;

	i = k;
	while (k-- >= ich)
	{
		a[i--] = '0' + (n % 10);
		n = n / 10;
	}
}

char	*ft_itoa(int j)
{
	char	*a;
	int		k;
	int		i;
	long	n;

	n = j;
	k = tol(n);
	i = 0;
	a = malloc(k + 1);
	if (a == 0)
		return (0);
	if (n < 0)
	{
		a[0] = '-';
		n *= -1;
		i = 1;
	}
	a[k--] = '\0';
	emer(a, i, k, n);
	return (a);
}
