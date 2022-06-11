/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 14:46:41 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/11 12:54:11 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**cpy_2(char **str)
{
	int		i;
	char	**ret;

	i = -1;
	while (str[++i])
		i = i + 1 - 1;
	ret = malloc (sizeof (char *) * (i + 1));
	i = -1;
	while (str[++i])
		ret[i] = cpy(ret[i], str[i]);
	ret[i] = NULL;
	return (ret);
}

void	child_exec(char ***splited, char *path, int t, char **env)
{
	if (path && access(path, F_OK | X_OK))
		exit (126);
	if (execve(path, splited[t], env) == -1)
	{
		ft_printf_error(splited[t][0], 4);
		exit (127);
	}
	exit (0);
}

int	remove_path_2(char *str)
{
	if (str[0] == '/' || str[0] == '.')
		return (1);
	return (0);
}

char	*remove_pwd(char **env, int i)
{
	char	*ret;
	int		k;

	k = 3;
	ret = malloc (sizeof(char) * (ft_strlen(env[i]) - 2));
	while (env[i][++k])
		ret[k - 4] = env[i][k];
	ret[k - 4] = '\0';
	return (ret);
}

int	check_next(t_spl *comm, int t, int i)
{
	int	k;

	k = 0;
	while (comm->b_var[t][i] && ft_strcmp(comm->b_var[t][i], "|"))
	{
		if (!comm->a_var[t][i])
			return (0);
		if (ft_strcmp(comm->a_var[t][i], comm->b_var[t][i]))
			return (0);
		i++;
	}
	return (1);
}
