/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:10:49 by aaitoual          #+#    #+#             */
/*   Updated: 2022/06/03 11:10:50 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_spl	get_comm(int fd, char ***ret, char ***ret2, char **env)
{
	t_arg	ll;
	t_spl	comm;

	edit_var(*ret, env, 1, -1);
	edit_ret(*ret);
	edit_ret(*ret2);
	if (!ret[0])
	{
		free_2 (*ret);
		free_2 (*ret2);
		return (get_command(env, fd));
	}
	comm.a_var = split_pr(*ret, 0, 0, '\0');
	comm.b_var = split_pr(*ret2, 0, 0, '\0');
	free_2 (*ret);
	free_2 (*ret2);
	edit_qu(comm.a_var, -1, 0, ll);
	edit_qu(comm.b_var, -1, 0, ll);
	return (comm);
}
