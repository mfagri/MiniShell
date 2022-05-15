#include <curses.h>
#include <unistd.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
int ft_putchar(int c)
{
	write(1,&c,1);
	return(1);
}
int main()
{

	char *str;
	int i;
	char *p = readline("minishell=>");
	str = tgetstr(p,NULL);
	tputs(str,1,ft_putchar);
	write(1,"minishell=>exit\n",16);
	exit(0);
}