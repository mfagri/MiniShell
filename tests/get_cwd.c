#include <stdio.h>
#include <unistd.h>

int main()
{
    char test[200];

    getcwd(test, sizeof(test));
    printf ("%s\n", test);
    return (0);
}