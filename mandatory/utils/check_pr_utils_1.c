/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pr_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:29:37 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/08 18:37:11 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	get_q_single(char c, char q)
{
	if (c == 34 | c == 39)
	{
		if (q && q == c)
			q = '\0';
		else if (!q)
			q = c;
	}
	return (q);
}

int	check_utils_4(int k, char *s, int j, char q)
{
	if (k == 1)
	{
		if (!q && ((s[j] == '<' && s[j + 1] == '<'
					&& s[j + 2] != '<') || (s[j] == '>'
					&& s[j + 1] == '>' && s[j + 2] != '>')))
			return (1);
	}
	return (0);
}
