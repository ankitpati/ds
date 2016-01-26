/* dynalloc.c */
/* Date  : 11 January 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    size_t n, i;
    double *a;
    int cal;

    puts("How many numbers?");
    scanf(" %lu%*c", &n);
    puts("Which allocation routine?\n(0) malloc\n(1) calloc");
    scanf(" %d%*c", &cal);
    if(!(a = cal ? calloc(n, sizeof(*a)) : malloc(n * sizeof(*a)))){
        fprintf(stderr, "Cannot allocate memory!\n");
        exit(12);
    }

    printf("Enter %lu numbers:\n", n);
    for(i = 0; i < n; ++i) scanf(" %lf%*c", a + i);

    for(i = 1; i < n; ++i) a[0] += a[i];
    printf("Sum is %lf.\n", a[0]);

    free(a);
    return 0;
}
/* end of dynalloc.c */

/* OUTPUT

How many numbers?
5
Which allocation routine?
(0) malloc
(1) calloc

0
Enter 5 numbers:
43 50 62 12 54
Sum is 221.000000.

1
Enter 5 numbers:
78 86 95 12 43
Sum is 314.000000.

*/
