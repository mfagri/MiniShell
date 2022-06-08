/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:38:39 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/08 11:42:28 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd_free(char *s, char *arg, int i, int fd)
{
	if (!arg && i)
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	else if (arg != NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}	
	free(s);
	if (!fd)
		exit (1);
	get_glo_2(1, 1);
	return (0);
}

int	ft_cd_utils(char **arg, char **env, char *oldpath, int fd)
{
	if (!ft_strncmp("-", arg[1], ft_strlen("-")))
	{
		if (ft_oldpwd(env))
			if (!ft_cd_free(oldpath, NULL, 0, fd))
				return (0);
	}
	else if (ft_count_args(arg) > 2)
	{	
		if (!ft_cd_free(oldpath, NULL, 1, fd))
			return (0);
	}
	else
		if (chdir(arg[1]) == -1)
			if (!ft_cd_free(oldpath, arg[1], 0, fd))
				return (0);
	return (1);
}
