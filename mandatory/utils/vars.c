/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:52:55 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/10 15:19:41 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	*get_var_2(char *str, char **env, int k, int i)
{
	int		j;
	char	*ret;
	char	*tmp;

	j = 0;
	if (!ft_strncmp(str, "$", ft_strlen(str)))
	{
		ret = ft_itoa(0);
		return (ret);
	}
	tmp = cpy(tmp, str);
	str = ft_strjoin(tmp, "=");
	while (env[++i])
		if (!ft_strncmp(env[i], str, ft_strlen(str)))
			break ;
	if (!env[i])
	{
		free (str);
		return (NULL);
	}
	get_var_2_utils(env[i], j, &ret, k);
	free (str);
	return (ret);
}

char	*get_var_utils_1(char *str, int *j, int *k)
{
	int		i;
	char	*tmp;
	char	*ret;

	i = 0;
	tmp = malloc ((*j) + 1);
	while (str[i] && str[i] != '$')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	(*k) = i + 1;
	while (str[i] && str[i] != 34)
	{
		i++;
		(*j)++;
	}
	ret = cpy(ret, tmp);
	free (tmp);
	return (ret);
}

void	get_var_utils_2(char *str, char **ret, int k, char **tmp2)
{
	int	i;

	i = 0;
	free (*tmp2);
	*tmp2 = malloc(ft_strlen(str) - k + 1);
	while (str[k])
	{
		(*tmp2)[i] = str[k];
		i++;
		k++;
	}
	(*tmp2)[i] = '\0';
	*ret = ft_strjoin(*ret, *tmp2);
	free (*tmp2);
}

char	*get_var(char *str, char **env, int j, int i)
{
	char	*ret;
	char	*tmp;
	char	*tmp2;
	int		k;

	ret = get_var_utils_1(str, &j, &k);
	tmp2 = malloc (sizeof (char) * (j + 1));
	while (str[k] && (ft_isalnum(str[k]) || str[k] == '_'))
		tmp2[i++] = str[k++];
	if (str[k] == '?')
		tmp2[i++] = str[k++];
	tmp2[i] = '\0';
	if (!strcmp(tmp2, "?"))
		get_return_value(&ret);
	else if (!tmp2[0])
		ret = ft_strjoin(ret, "$");
	else
	{
		tmp = get_var_2(tmp2, env, 0, -1);
		ret = ft_strjoin(ret, tmp);
		free (tmp);
	}
	get_var_utils_2(str, &ret, k, &tmp2);
	return (ret);
}

void	edit_var(char **ret, char **env, int k, int i)
{
	int		j;
	char	*tmp;	

	while (ret[++i])
	{
		j = -1;
		while (ret[i][++j])
		{
			if (k && ret[i][j] == 39)
				k = 0;
			else if (!k && ret[i][j] == 39)
				k = 1;
			if (ret[i][j] == 34 && check_next_qu(ret[i], 34, j) && !k)
				k = 0;
			if (k && ret[i][j] == '$')
			{
				tmp = cpy (tmp, ret[i]);
				free (ret[i]);
				ret[i] = get_var(tmp, env, j, 0);
				free (tmp);
			}
		}
	}
	ret[i] = NULL;
}
