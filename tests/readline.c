#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/errno.h>
int	main()
{
	char	*test;

	while (1)
	{
		test = readline("minitest->");
		printf ("%s", test);
		if (strcmp(test, ""))
		{
			printf ("\n");
			rl_replace_line();
			add_history(test);
		}
		if (!strcmp(test, "exit"))
		{
			exit(0);
		}
	}
}