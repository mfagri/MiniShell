/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:51:54 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/09 11:55:53 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_allocation(char *str)
{
	char	q;
	int		i;
	int		k;

	i = -1;
	k = 0;
	q = '\0';
	while (str && str[++i])
	{
		k++;
		q = get_q_1(str, i, q);
		if (!q && ((str[i] == '>' && str[i + 1] != '>')
				|| (str[i] == '<' && str[i + 1] != '<')))
			k = k + 2;
		if (!q && ((str[i] == '>' && str[i + 1] == '>')
				|| (str[i] == '<' && str[i + 1] == '<')) && i++)
		{
			k = k + 3;
			q = get_q_1(str, i, q);
		}
		if (str[i] == '|')
			k = k + 2;
	}
	return (k);
}

void	sep_utils(int i, int k, char **ret, char *str)
{
	char	q;

	q = '\0';
	while (str[i])
	{
		q = get_q_1(str, i, q);
		if (!q && ((str[i] == '>' && str[i + 1] != '>')
				|| (str[i] == '<' && str[i + 1] != '<') || str[i] == '|'))
		{
			(*ret)[k++] = ' ';
			(*ret)[k++] = str[i++];
			(*ret)[k++] = ' ';
		}
		if (!q && ((str[i] == '>' && str[i + 1] == '>')
				|| (str[i] == '<' && str[i + 1] == '<')))
		{
			(*ret)[k++] = ' ';
			(*ret)[k++] = str[i++];
			(*ret)[k++] = str[i++];
			q = get_q_1(str, i, q);
			(*ret)[k++] = ' ';
		}
		(*ret)[k++] = str[i++];
	}
	(*ret)[k] = '\0';
}

char	*sep(char *str, int i, int k)
{
	char	*ret;
	char	q;

	ret = malloc (sizeof (char) * (get_allocation(str) + 2));
	q = '\0';
	sep_utils(i, k, &ret, str);
	return (ret);
}
