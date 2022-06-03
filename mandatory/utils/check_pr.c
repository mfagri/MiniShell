/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:28:07 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/03 20:46:31 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pr_utils_1(char **str, char q, int i)
{
	int	j;

	if (str[0][0] == ' ')
		i = 1;
	if ((str[i][0] == '|' || str[i][0] == '>' || str[i][0] == '<'))
		return (0);
	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			q = get_q(str, i, j, q);
		if (!(ft_strncmp(str[i], "|", 1)) && !q)
		{
			if (str[i + 1])
			{
				if (!(ft_strncmp(str[i + 1], "|", ft_strlen(str[i + 1]))))
					return (0);
			}
			else
				return (0);
		}
	}
	return (1);
}

int	check_pr_utils_2(char **str, char q)
{
	int	i;
	int	j;

	if (!check_pr_utils_1(str, q, 0))
		return (0);
	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
			q = get_q(str, i, j, q);
	}
	if (q)
		return (0);
	return (1);
}

int	check_pr_utils_4(char **str, int u, int i, int j)
{
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if ((str[i][j] == '<' && str[i][j + 1] == '<'
				&& str[i][j + 2] != '<') || (str[i][j] == '>'
				&& str[i][j + 1] == '>' && str[i][j + 2] != '>'))
			{
				if (u)
					return (0);
				else if (!u)
					u = 1;
			}
			if (str[i][j] != '|' && str[i][j] != '<'
				&& str[i][j] != '>' && str[i][j] != '<'
				&& str[i][j] && str[i][j] != ' ')
				u = 0;
		}
	}
	if (u)
		return (0);
	return (1);
}

int	check_pr_utils_3(char **str, int u, int i, int j)
{
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if ((str[i][j] == '<' && str[i][j + 1] != '<')
				|| (str[i][j] == '>' && str[i][j + 1] != '>'))
			{
				if (u)
					return (0);
				else
					u = 1;
			}
			if (str[i][j] != '|' && str[i][j] != '<' && str[i][j] != '>'
					&& str[i][j] != '<' && str[i][j] && str[i][j] != ' ')
				u = 0;
		}
	}
	if (u)
		return (0);
	return (1);
}

int	check_pr(char **str)
{
	int		i;
	int		j;

	if (!check_pr_utils_2(str, '\0'))
		return (0);
	if (!check_pr_utils_3(str, 0, -1, 0))
		return (0);
	if (!check_pr_utils_4(str, 0, -1, 0))
		return (0);
	return (1);
}
