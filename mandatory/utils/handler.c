/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 22:41:47 by mfagri            #+#    #+#             */
/*   Updated: 2022/06/06 21:35:52 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_glo_3(int i)
{
	static int	j;

	if (i == 0)
		j = 0;
	else if (i == 1)
		j = 1;
	else
		return (j);
	return (j);
}

int	get_glo_4(int i)
{
	static int	j;

	if (i == 0)
		j = 0;
	else if (i == 1)
		j = 1;
	else
		return (j);
	return (j);
}

int	get_glo(int i)
{
	static int	j;

	if (i == 0)
		j = 0;
	else if (i == 1)
		j = 1;
	else
		return (j);
	return (j);
}

void	ft_sig(int signum)
{
	if (signum == SIGINT && !get_glo(2) && get_glo_3(3) )//&& get_glo_4(2) != 1)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT && !get_glo(2) && get_glo_3(3) ) //&& get_glo_4(2) != 1)
		return ;
	// else if (signum == SIGINT && get_glo_4(2) == 1)
	// {
	// 	get_glo_4(0);
	//  	write(1, "\n", 1);
	// 	exit(1);
	// }
}
