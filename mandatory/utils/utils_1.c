/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 06:39:48 by aaitoual          #+#    #+#             */
/*   Updated: 2022/05/20 06:39:50 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	*remove_path(char *str)
{
	int		i;
	char	*tmp;

	i = 5;
	tmp = malloc (strlen(str) - 4);
	while (str[i])
	{
		tmp[i - 5] = str[i];
		i++;
	}
	tmp[i - 5] = '\0';
	return (tmp);
}

char	**get_path_2(char **env, char *command)
{
	int		i;
	char	**ret;
	char	*path;
	char	*tmp;

	i = -1;
	while (env[++i])
		if (!strncmp(env[i], "PATH=", 5))
			break ;
	path = remove_path(env[i]);
	ret = ft_split(path, ':');
	i = -1;
	while (ret[++i])
	{
		tmp = cpy(tmp, ret[i]);
		free (ret[i]);
		ret[i] = ft_strjoin(tmp, "/");
		tmp = cpy(tmp, ret[i]);
		free (ret[i]);
		ret[i] = ft_strjoin(tmp, command);
	}
	return (ret);
}

char	*get_path(char **env, char *command)
{
	int		i;
	char	**ret;
	char	*path;
	char	*tmp;

	ret = get_path_2(env, command);
	i = -1;
	while (ret[++i])
		if (!access(ret[i], F_OK))
			break ;
	if (!ret[i])
		path = NULL;
	else
		path = cpy(path, ret[i]);
	i = 0;
	while (ret[i])
	{
		free (ret[i]);
		i++;
	}
	free (ret);
	return (path);
}

int	get_history(void)
{
	int		i;
	char	*tmp;

	i = open(HISTORY_PATH, O_RDWR);
	if (i == -1)
		i = open(HISTORY_PATH, O_RDWR | O_CREAT);
	while (1)
	{
		tmp = get_next_line(i);
		if (!tmp)
			break ;
		add_history(tmp);
		free (tmp);
	}
	free (tmp);
	return (i);
}
