/* struct_file.c */
/* Date  : 18 April 2016
 * Author: Ankit Pati
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char name[50];
    unsigned height;
} s;

int main()
{
    unsigned i, n;
    s stht[50];
    FILE *fp;

    if(!(fp = fopen("stheight.txt", "wb+"))){
        fprintf(stderr, "File could not be opened!\n");
        exit(5);
    }

    printf("Number of Students? ");
    scanf(" %u%*c", &n);

    for(i = 0; i < n; ++i){
        printf("\nStudent %u\n", i + 1);
        printf("Name   : "); fgets(stht[i].name, 50, stdin);
        printf("Height : "); scanf(" %u%*c", &stht[i].height);
    }
    putchar('\n');

    puts("Writing to file...");
    fwrite(stht, sizeof(*stht), n, fp);
    fflush(fp);

    rewind(fp);

    puts("Reading from file...");
    fread(stht, sizeof(*stht), n, fp);

    for(i = 0; i < n; ++i){
        printf("\nStudent %u\n", i + 1);
        printf("Name   : %s", stht[i].name);
        printf("Height : %u", stht[i].height);
        putchar('\n');
    }

    return 0;
}
/* end of struct_file.c */

/* OUTPUT

Number of Students? 2

Student 1
Name   : Ankit Pati
Height : 170

Student 2
Name   : Tiashaa Chatterjee
Height : 168

Writing to file...
Reading from file...

Student 1
Name   : Ankit Pati
Height : 170

Student 2
Name   : Tiashaa Chatterjee
Height : 168

*/
