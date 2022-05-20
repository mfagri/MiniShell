/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:51:54 by aaitoual          #+#    #+#             */
/*   Updated: 2022/05/20 16:51:55 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_allocation(char *str)
{
	char	*ret;
	char	q;
	int		i;
	int		k;
	int		j;

	i = -1;
	k = 0;
	j = 1;
	q = '\0';
	while (str[++i])
	{
		k++;
		q = get_q_1(str, i, q);
		if (!q && ((str[i] == '>' && str[i + 1] != '>')
				|| (str[i] == '<' && str[i + 1] != '<')))
			k++;
		if (!q && ((str[i] == '>' && str[i + 1] == '>')
				|| (str[i] == '<' && str[i + 1] == '<')) && i++)
			k++;
		if (str[i] == '|' && j)
			k++;
	}
	ret = malloc (sizeof (char) * (k));
	return (ret);
}

char	*sep(char *str, int i, int k)
{
	char	*ret;
	char	q;

	ret = get_allocation(str);
	q = '\0';
	while (str[i])
	{
		q = get_q_1(str, i, q);
		if (!q && ((str[i] == '>' && str[i + 1] != '>')
				|| (str[i] == '<' && str[i + 1] != '<') || str[i] == '|'))
		{
			ret[k++] = ' ';
			ret[k++] = str[i++];
			ret[k++] = ' ';
		}
		if (!q && ((str[i] == '>' && str[i + 1] == '>')
				|| (str[i] == '<' && str[i + 1] == '<')))
		{
			ret[k++] = ' ';
			ret[k++] = str[i++];
		}
		ret[k++] = str[i++];
	}
	ret[k] = '\0';
	return (ret);
}
