/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:44:26 by aaitoual          #+#    #+#             */
/*   Updated: 2021/11/17 13:44:27 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"../minishell.h"

int	cpy_next_line(char **all, int fd)
{
	char	*curr;
	int		i;
	int		j;

	i = 0;
	j = BUFFER_SIZE;
	curr = malloc(BUFFER_SIZE + 1);
	while (i == 0 && j != 0)
	{
		j = read(fd, curr, BUFFER_SIZE);
		if (j == -1)
		{
			free (curr);
			return (0);
		}
		if (j == 0)
			break ;
		curr[j] = '\0';
		*all = ft_strjoin(*all, curr);
		i = check_next_ln(*all);
	}
	free (curr);
	return (1);
}

char	*ft_return(char *all, int i)
{
	int		k;
	char	*ret;

	k = 0;
	ret = malloc (i + 1);
	while (all && all[k] && all[k] != '\n')
	{
		ret[k] = all[k];
		k++;
	}
	if (all[k] == '\n')
		ret[k++] = '\n';
	ret[k] = '\0';
	return (ret);
}

char	*edit_all(char *all, int i, int k)
{
	int		p;
	char	*tmp;

	if (ft_strlen (all) - i)
	{
		tmp = malloc (ft_strlen (all) + 1);
		while (all && all[++k])
			tmp[k] = all[k];
		tmp[k] = '\0';
		p = ft_strlen (all);
		free (all);
		all = malloc (p - i + 1);
		k = 0;
		while (tmp[i])
			all[k++] = tmp[i++];
		all[k] = '\0';
		free (tmp);
	}
	else
	{
		free (all);
		all = NULL;
	}
	return (all);
}

char	*get_next_line(int fd)
{
	static char	*all;
	char		*ret;
	int			i;
	int			k;

	k = 0;
	i = cpy_next_line(&all, fd);
	if (i == 0)
	{
		free (all);
		return (NULL);
	}
	i = new_line_index(all);
	if (i == 0)
	{
		free (all);
		return (NULL);
	}
	ret = ft_return (all, i);
	k = -1;
	all = edit_all(all, i, k);
	return (ret);
}
