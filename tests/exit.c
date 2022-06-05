/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 14:28:54 by mfagri            #+#    #+#             */
/*   Updated: 2022/06/05 17:19:32 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// static	long long	atoi_exit(const char *str, int i, int *pbm)
// {
// 	int			j;
// 	long		neg;
// 	long long	sum;

// 	neg = 1;
// 	sum = 0;
// 	j = 0;
// 	if (str[i] && (str[i] == '-' || str[i] == '+'))
// 		if (str[i++] == '-')
// 			neg *= -1;
// 	while (str[i] && ((str[i] == ' ') || str[i] == '0'))
// 		i++;
// 	while (str[i] >= '0' && str[i] <= '9' && ++j)
// 	{
// 		sum = (sum * 10) + (str[i] - 48);
// 		if (((i == 18 && neg == 1) && (str[i] > '7' && str[i] <= '9'))
// 			|| ((i == 19 && neg == -1) && (str[i] == '9')))
// 			*pbm = 1;
// 		i++;
// 	}
// 	while (str[i++])
// 		j++;
// 	if ((j > 19 && neg == 1) || (j > 20 && neg == -1))
// 		*pbm = 1;
// 	return (sum * neg);
//}

long double	ft_atoi(const char *str)
{
	int			i;
	long long		a;
	long double	c;

	i = 0;
	a = 1;
	c = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			a = -a;
		}
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		c = c * 10 + (str[i] - '0');
		i++;
	}
	return (a * c);
}

int main(int ac,char **av)
{
	int j;
	long double l;
	long double n;

	(void)ac;
	
	l = ft_atoi("9223372036854775807");
	n = ft_atoi("-9223372036854775808");
	if(ft_atoi(av[1]) > l || ft_atoi(av[1]) < n)
		printf("yoo\n");
	printf("%Lf $$ %Lf\n",l,n);
}