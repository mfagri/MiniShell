/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 09:17:31 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/07 16:20:40 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	**get_ret(char **pr, int i, int *j)
{
	int			k;
	char		**ret;

	ret = malloc (sizeof (char *) * (i - (*j) + 2));
	k = 0;
	while (++(*j) < i && pr[(*j)])
	{
		ret[k] = cpy (ret[k], pr[(*j)]);
		k++;
	}
	ret[k] = NULL;
	if (!pr[(*j)])
		(*j) = -1;
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
			q = get_q(pr, i, j, q);
			j++;
		}
		if (!(ft_strncmp(pr[i], "|", ft_strlen(pr[i]))) && !q)
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

char	***split_pr(char **pr, int i, int t, char q)
{
	int		j;
	int		r;
	int		k;
	char	***ret;

	k = get_size(pr, 0, 0, '\0');
	ret = malloc (sizeof (char **) * (k + 2));
	k = 0;
	while (pr[++i])
	{
		j = -1;
		while (pr[i][++j])
			q = get_q(pr, i, j, q);
		if (!(ft_strncmp(pr[i], "|", ft_strlen(pr[i]))) && !q)
		{
			if (i == t + 1)
				t++;
			else
				ret[k++] = get_ret(pr, i, &t);
		}
	}
	if (ft_strncmp(pr[i - 1], "|", ft_strlen(pr[i - 1])))
		ret[k++] = get_ret(pr, i, &t);
	ret[k] = NULL;
	return (ret);
}
