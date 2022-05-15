/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfagri <mfagri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 22:41:47 by mfagri            #+#    #+#             */
/*   Updated: 2022/05/15 00:50:53 by mfagri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_putchar(int c)
{
	write(1,&c,1);
	return(1);
}
void get_tt()
{
	write(1,"\033[1A\033[11Cexit\n",14); // \033[1A Move the cursor up 1 line && \033[11C  Move the cursor forward 11 columns
	exit(0);
}
int get_glo(int i)
{
	static int j;
	if(i == 0)
		j = 0;
	else if(i == 1)
		j  = 1;
	else
		return (j);
	return (j);
}
void ft_sig(int signum)
{
	// printf("%d",g_globle.i);
	//if(signum == SIGINT && !g_globle.i)
	if(signum == SIGINT && !get_glo(2))
	{
		write(1,"\n",1);	
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
	}
	else if(signum == SIGQUIT && !get_glo(2))
	{
        rl_on_new_line();
        rl_replace_line("", 0);
		rl_redisplay();
		// puts("ergrtgr");
		return;
	}
	// else if(signum == SIGINT)
	else
		write(1,"\n",1);
	//return ;
}