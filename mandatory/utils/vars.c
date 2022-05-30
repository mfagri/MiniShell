/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 13:52:55 by aaitoual          #+#    #+#             */
/*   Updated: 2022/05/30 18:06:46 by mfagri           ###   ########.fr       */
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
		ret = ft_itoa(k);
		return (ret);
	}
	tmp = cpy(tmp, str);
	str = ft_strjoin(tmp, "=");
	while (env[++i])
		if (!ft_strncmp(env[i], str, ft_strlen(str)))
			break ;
	if (!env[i])
		return (NULL);
	while (env[i][j++] != '=')
		i = i;
	ret = malloc (sizeof (char) * (ft_strlen(env[i]) - j + 1));
	while (env[i][j])
		ret[k++] = env[i][j++];
	ret[k] = '\0';
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
	while (str[i] != 34 && str[i])
	{
		i++;
		(*j)++;
	}
	ret = cpy(ret, tmp);
	free (tmp);
	return (ret);
}

// void	get_old_var(char *tmp, char *str, int i)
// {
// 	int			k;
// 	int			j;
// 	static int	p;

// 	k = -1;
// 	if (!i)
// 	{
// 		while (str[++k])
// 			if (str[k] == '|')
// 				j++;
// 		g_glo.after_here_doc = malloc (sizeof (char *) * (j + 1));
// 		p = 0;
// 	}
// 	else
// 	{
// 		g_glo.after_here_doc[p] = cpy(g_glo.after_here_doc[p], "$");
// 		g_glo.after_here_doc[p] = ft_strjoin(g_glo.after_here_doc[p], tmp);
// 		p++;
// 	}
// }

char	*get_var(char *str, char **env, int j)
{
	char	*ret;
	char	*tmp2;
	int		i;
	int		k;

	ret = get_var_utils_1(str, &j, &k);
	tmp2 = malloc (sizeof (char) * (j + 1));
	i = 0;
	while (str[k] && (ft_isalnum(str[k]) || str[k] == '_' || str[k] == '?'))
	{
		tmp2[i++] = str[k++];
		if (str[k + 1] == '?')
			break ;
	}
	tmp2[i] = '\0';
	if (!strcmp(tmp2, "?"))
		ret = ft_strjoin(ret, ft_itoa(get_glo_2(0, 0)));
	else if (!tmp2[0])
		ret = ft_strjoin(ret, "$");
	else
		ret = ft_strjoin(ret, get_var_2(tmp2, env, 0, -1));
	free (tmp2);
	tmp2 = malloc(ft_strlen(str) - k + 1);
	i = 0;
	while (str[k])
		tmp2[i++] = str[k++];
	tmp2[i] = '\0';
	ret = ft_strjoin(ret, tmp2);
	free (tmp2);
	return (ret);
}

char	**edit_var(char **ret, char **env)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	k = 1;
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
				ret[i] = get_var(ret[i], env, j);
		}
	}
	i = -1;
	return (ret);
}
