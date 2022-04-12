/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:27:21 by aaitoual          #+#    #+#             */
/*   Updated: 2021/11/11 20:19:58 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"../minishell.h"

static int	check(char *src, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i] != '\0')
	{
		if (src[i] != c && (src[i + 1] == c || src[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

static int	ft_mal(char *str, int k, char c)
{
	int	i;

	i = 0;
	while (str[k++] != c && str[k] != '\0')
		i++;
	return (i);
}

static int	makeit(char	**a, char *str, char c)
{
	int	k;
	int	j;
	int	i;

	k = 0;
	i = 0;
	while (str[k])
	{
		j = 0;
		if (str[k] != c)
		{
			a[i] = (char *)malloc (sizeof(char) * ft_mal(str, k, c) + 1);
			if (a[i] == NULL)
				return (1);
			while (str[k] != c && str[k] != '\0')
				a[i][j++] = str[k++];
			a[i][j] = '\0';
			i++;
		}
		else
			k++;
	}
	return (0);
}

static	void	ft_free(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		free (a[i++]);
	free (a);
}

char	**ft_split(char const *s, char c)
{
	char	**a;
	int		ln;
	int		i;

	if (s == NULL)
		return (NULL);
	ln = check((char *)s, c);
	i = 0;
	a = (char **)malloc(sizeof(char *) * (ln + 1));
	if (a == NULL)
		return (NULL);
	i = makeit(a, (char *)s, c);
	if (i == 1)
	{
		ft_free (a);
		return (NULL);
	}
	a[ln] = NULL;
	return (a);
}
