/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 10:08:26 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/11 12:40:58 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_spaces(char *str)
{
	int		i;
	int		k;
	int		j;
	char	qu;

	j = 0;
	i = 0;
	k = 1;
	qu = '\0';
	while (str[i])
	{
		qu = get_q_1(str, i, qu);
		if (!qu && ((str[i] == ' ' && i != 0)
				&& (str[i + 1] != '>'
					&& str[i + 1] != '<' && str[i + 1] != '|')))
			j++;
		if (!qu && (str[i] == '>' || str[i] == '<' || str[i] == '|'))
			j = j + 2;
		i++;
	}
	return (j + 1);
}

char	*get_arg_2(char *str, int t, int i)
{
	char	*ret;
	int		r;
	char	q;

	r = 0;
	q = '\0';
	while (++t <= i)
	{
		q = get_q_1(str, t, q);
		if (str[t] != ' ' || q)
			r++;
	}
	ret = malloc (sizeof(char) * (r + 1));
	return (ret);
}

char	*get_arg(char *tmp, int i, int t)
{
	int		r;
	char	*str;
	char	q;
	char	*ret;

	str = cpy(NULL, tmp);
	r = 0;
	q = '\0';
	ret = get_arg_2(str, t, i);
	while (++t <= i)
	{
		q = get_q_1(str, t, q);
		if (str && str[t] && (str[t] != ' ' || q))
		{
			ret[r] = str[t];
			r++;
		}
	}
	ret[r] = '\0';
	free (str);
	return (ret);
}
