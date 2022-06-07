/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitoual <aaitoual@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 22:41:47 by mfagri            #+#    #+#             */
/*   Updated: 2022/06/07 15:11:03 by aaitoual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

struct termios get_term(struct termios term, int i)
{
	static struct termios	terminal;

	if (i)
		terminal = term;
	return (terminal);
}

void	remove_ctlc(void)
{
	struct termios	terminal;
	struct termios	terminal2;

	tcgetattr(0, &terminal);
	terminal2 = terminal;
	terminal.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW | TCSAFLUSH, &terminal);
	get_term(terminal2, 1);
}

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

	if (i != -1)
		j = i;
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
	struct termios	term;
	
	if (signum == SIGINT && !get_glo(2) && get_glo_3(3) && get_glo_4(-1) == 0)
	{
		get_glo_2(1, 1);
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signum == SIGQUIT && !get_glo(2) && get_glo_3(3) && get_glo_4(-1) == 0)
		return ;
	if (signum == SIGINT && get_glo_4(-1) != 0)
	{
		term = get_term(term, 0);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		close (get_glo_4(-1));
		write (1, "\n", 1);
		exit(1);
	}
}
