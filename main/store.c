/* store.c */
/* Date  : 18 April 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned i, n;
    char name[80];
    unsigned mark;
    FILE *fout;

    if(!(fout = fopen("stinfo.txt", "a"))){
        fprintf(stderr, "File could not be opened!\n");
        exit(5);
    }

    printf("Number of Students? ");
    scanf(" %u%*c", &n);

    for(i = 0; i < n; ++i){
        printf("\nStudent %u\n", i + 1);
        printf("Name  : "); fgets(name, 80, stdin);
        printf("Marks : "); scanf(" %u%*c", &mark);

        fprintf(fout, "%s%u\n", name, mark);
    }

    return 0;
}
/* end of store.c */

/* OUTPUT

Number of Students? 2

Student 1
Name  : Ankit Pati
Marks : 43

Student 2
Name  : Tiashaa Chatterjee
Marks : 50

----

// stinfo.txt
Ankit Pati
43
Tiashaa Chatterjee
50
// end of stinfo.txt

*/
