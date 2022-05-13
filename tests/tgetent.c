#include <stdlib.h>

#include <curses.h>
#include <term.h>

int main(int argc, char **argv)
{
    int ret;
    char *term_type = getenv("TERM");

    ret = tgetent(NULL, term_type);

    /* On évite les warnings pour variables non utilisées. */
    (void)argc;
    (void)argv;
	printf("%s\n",term_type);
	printf("%d\n",ret);
    return ret;
}