#include <stdio.h>
# include <unistd.h>
# include <signal.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/errno.h>

void	ft_sig(int signum)
{
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main()
{
	char	*test;

	signal(SIGINT, ft_sig);
	while (1)
	{
		puts ("yoooo");
		test = readline("minitest->");
	}
}