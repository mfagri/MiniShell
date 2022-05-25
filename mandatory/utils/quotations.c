/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:54:55 by aaitoual          #+#    #+#             */
/*   Updated: 2022/05/20 13:54:55 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_next_qu(char *str, char c, int i)
{
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	remove_qu_utils_1(char *str, int *k, int i, char u)
{
	if ((str[i] == 39 || str[i] == 34))
	{
		if (u && str[i] == u)
			(*k)++;
		else if (!u && check_next_qu(str, str[i], i + 1))
		{
			u = str[i];
			(*k)++;
		}
	}
	return (u);
}

char	*remove_qu(char *str, int i, int j)
{
	int		k;
	char	u;
	char	*tmp;

	k = 0;
	u = '\0';
	tmp = malloc (ft_strlen(str) - 1);
	while (str[++i])
	{
		u = remove_qu_utils_1(str, &k, i, u);
		if (k < 2)
		{
			if ((!u || (u && str[i] != u)) && ++j)
				tmp[j - 1] = str[i];
		}
		if (k >= 2)
		{
			u = '\0';
			k = 0;
		}
	}
	tmp[j] = '\0';
	return (tmp);
}

char	***edit_qu(char ***str)
{
	int		i;
	int		j;
	int		k;
	char	r;
	char	*tmp;

	i = -1;
	while (str[++i])
	{
		k = -1;
		while (str[i][++k])
		{
			j = -1;
			r = 0;
			while (str[i][k][++j])
			{
				if ((str[i][k][j] == 34 || str[i][k][j] == 39) && !r)
					r = str[i][k][j];
				else if (r && str[i][k][j] == r)
				{
					tmp = cpy(tmp, str[i][k]);
					free (str[i][k]);
					str[i][k] = remove_qu(tmp, -1, 0);
					free (tmp);
					break ;
				}
			}
		}
	}
	return (str);
}