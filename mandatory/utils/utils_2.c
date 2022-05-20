/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 09:17:31 by aaitoual          #+#    #+#             */
/*   Updated: 2022/05/20 09:17:32 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	**get_ret(char **pr, int i)
{
	static int	j = -1;
	int			k;
	char		**ret;

	ret = malloc (sizeof (char *) * (i - j + 1));
	k = 0;
	while (++j < i && pr[j])
	{
		ret[k] = cpy (ret[k], pr[j]);
		k++;
	}
	ret[k] = NULL;
	if (!pr[j])
		j = -1;
	return (ret);
}

int	get_size(char **pr, int i, int j, char q)
{
	int	k;

	k = 0;
	while (pr[i])
	{
		j = 0;
		while (pr[i][j])
		{
			if (pr[i][j] == 34 || pr[i][j] == 39)
			{
				if (q && q == pr[i][j])
					q = '\0';
				else if (!q)
					q = pr[i][j];
			}
			j++;
		}
		if (!(ft_strncmp(pr[i], "|", ft_strlen(pr[i]))) && !q
			&& (ft_strncmp(pr[i + 1], "|", ft_strlen(pr[i + 1]))))
			k++;
		i++;
	}
	return (k);
}

char	get_q_1(char *pr, int i, char q)
{
	if (pr[i] == 34 || pr[i] == 39)
	{
		if (q && q == pr[i])
			q = '\0';
		else if (!q)
			q = pr[i];
	}
	return (q);
}

char	get_q(char **pr, int i, int j, char q)
{
	if (pr[i][j] == 34 || pr[i][j] == 39)
	{
		if (q && q == pr[i][j])
			q = '\0';
		else if (!q)
			q = pr[i][j];
	}
	return (q);
}

char	***split_pr(char **pr, int i, int k, char q)
{
	int		j;
	int		r;
	char	***ret;

	k = get_size(pr, 0, 0, '\0');
	ret = malloc (sizeof (char **) * (k + 2));
	q = '\0';
	k = 0;
	while (pr[i])
	{
		j = -1;
		while (pr[i][++j])
			q = get_q(pr, i, j, q);
		if (!(ft_strncmp(pr[i], "|", ft_strlen(pr[i]))) && !q
			&& (ft_strncmp(pr[i + 1], "|", ft_strlen(pr[i + 1]))))
		{
			ret[k] = get_ret(pr, i);
			k++;
		}
		i++;
	}
	if (ft_strncmp(pr[i - 1], "|", ft_strlen(pr[i - 1])))
		ret[k++] = get_ret(pr, i);
	ret[k] = NULL;
	return (ret);
}
