#include <unistd.h>
#include <stdio.h>

int	main()
{
	printf ("%d\n", access("/Users/aaitoual/Desktop/out", F_OK));
}